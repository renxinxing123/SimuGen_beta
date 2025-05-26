import re 
import json
from io import BytesIO

import requests
from PIL import Image

from camel.agents import ChatAgent
from camel.messages import BaseMessage
from camel.models import ModelFactory
from camel.types import ModelPlatformType, ModelType

from camel.retrievers import AutoRetriever
from camel.types import StorageType
from camel.embeddings import OpenAIEmbedding
from camel.types import EmbeddingModelType
from camel.storages import QdrantStorage
from tqdm import tqdm

import re
import json

import re
import json

no_block_description = False

def extract_json_from_text(text: str) -> dict:
    """
    从任意文本中提取并解析第一个 JSON 对象。
    支持 Markdown 代码块（```json```）、三引号，以及自定义标题“#### **JSON Output**”风格。
    会将 Python 风格的 True/False 转为 JSON 的 true/false，再尝试解析。
    失败时尝试简单清洗（单引号、键未加引号、尾逗号等），仍失败则返回空 dict。
    """
    original = text

    # 1. 按“#### **JSON Output**”标题后的代码块提取
    header_match = re.search(
        r'####\s*\*\*JSON Output\*\*\s*```(?:json)?\s*(.*?)```',
        text, re.IGNORECASE | re.DOTALL
    )
    if header_match:
        text = header_match.group(1).strip()
    else:
        # 2. 匹配 ```json``` 或 ``` ``` 风格
        md_match = re.search(
            r'```(?:json)?\s*(.*?)```',
            text, re.IGNORECASE | re.DOTALL
        )
        if md_match:
            text = md_match.group(1).strip()
        else:
            # 3. 三引号 ''' 或 """
            tri_match = re.search(
                r'("{3}|\'{3})\s*(\{.*?\})\s*\1',
                text, re.DOTALL
            )
            if tri_match:
                text = tri_match.group(2).strip()

    # 4. 大括号平衡提取：确保抓取到完整的 JSON 对象
    if not text.startswith('{'):
        start = original.find('{')
        if start != -1:
            stack = []
            end = None
            for i, ch in enumerate(original[start:], start):
                if ch == '{':
                    stack.append(ch)
                elif ch == '}':
                    stack.pop()
                    if not stack:
                        end = i
                        break
            if end is not None:
                text = original[start:end+1]

    # 5. 预处理 Python 布尔字面量
    #    将 True/False（首字母大写）替换为 true/false，避免 JSONDecodeError
    text = re.sub(r'\bTrue\b', 'true', text)
    text = re.sub(r'\bFalse\b', 'false', text)

    # 6. 尝试直接解析
    try:
        return json.loads(text)
    except json.JSONDecodeError:
        # 7. 简单清洗后重试：全局单引号→双引号、键名加引号、去尾逗号
        cleaned = text

        # —— 把所有单引号字符串换成双引号 —— 
        cleaned = re.sub(r"'([^']*?)'", r'"\1"', cleaned)

        # —— 未加引号的键名加上双引号 —— 
        cleaned = re.sub(
            r'(\{|,)\s*([A-Za-z_][A-Za-z0-9_]*)\s*:',
            r'\1 "\2":',
            cleaned
        )

        # —— 去掉尾随多余逗号 —— 
        cleaned = re.sub(r',\s*([}\]])', r'\1', cleaned)

        try:
            return json.loads(cleaned)
        except json.JSONDecodeError:
            # 最终返回空 dict
            return {}




    
import re
import tempfile
import subprocess
import os

def execute_in_subprocess(Block_builder_result):
    """
    将包含 Markdown 格式代码的字符串清理后保存到临时文件中，
    在子进程中运行该文件，并捕获标准输出与错误输出，
    返回执行代码时的完整输出（包括异常时的完整 traceback）。
    
    参数:
        Block_builder_result (str): 包含 Markdown 格式代码的字符串

    返回:
        str: 执行代码的输出结果（包含 stdout 和 stderr）
    """
    # 清除 Markdown 代码块标记
    code_lines = Block_builder_result.splitlines()
    if code_lines and code_lines[0].strip().startswith("```"):
        code_lines = code_lines[1:]
    if code_lines and code_lines[-1].strip().startswith("```"):
        code_lines = code_lines[:-1]
    clean_code = "\n".join(code_lines)
    
    # 将代码写入临时文件
    with tempfile.NamedTemporaryFile("w", delete=False, suffix=".py") as temp_file:
        temp_file.write(clean_code)
        temp_filename = temp_file.name

    try:
        # 使用 subprocess 运行临时文件，增加 -u 参数保证无缓冲
        result = subprocess.run(["python", "-u", temp_filename],
                                capture_output=True, text=True)
        output = result.stdout + result.stderr
    finally:
        os.remove(temp_filename)
        
    return output

def load_investigator_prompt(investigator_prompt_path, simulation_explanation_path, blocks_list_path):
    """
    从指定的文件路径读取模板内容、模拟说明和blocks列表，
    并将模板中的占位符替换为相应的文件内容。

    参数:
        investigator_prompt_path (str): 模板文件的路径，包含占位符 {simulation_explanation} 和 {simulation_blocks_list}。
        simulation_explanation_path (str): 模拟说明文件的路径。
        blocks_list_path (str): blocks列表文件的路径。

    返回:
        str: 替换后的模板字符串。
    """
    # 读取模板文件内容
    with open(investigator_prompt_path, 'r', encoding='utf-8') as f:
        investigator_prompt_template = f.read()

    # 读取 simulation_explanation 文件内容
    with open(simulation_explanation_path, 'r', encoding='utf-8') as f:
        simulation_explanation = f.read()

    # 读取 blocks_list 文件内容
    with open(blocks_list_path, 'r', encoding='utf-8') as f:
        simulation_blocks_list = f.read()

    # 用对应的内容替换模板中的占位符
    investigator_prompt = investigator_prompt_template.replace('{simulation_explanation}', simulation_explanation)

    if no_block_description != True:
        investigator_prompt = investigator_prompt.replace('{simulation_blocks_list}', simulation_blocks_list)
    
    return investigator_prompt

def load_investigator_reviewer_prompt(Investigator_reviewer_prompt_path, request_blocks_description, Investigator_result):
    """
    Reads the investigator reviewer prompt template from the given file path and replaces 
    the placeholders '{blocks_list}' and '{investigator_simulation_info}' with the provided content.

    Args:
        Investigator_reviewer_prompt_path (str): The file path to the investigator reviewer prompt template.
        request_blocks_description (str): The string to replace the '{blocks_list}' placeholder.
        Investigator_result (str): The string to replace the '{investigator_simulation_info}' placeholder.

    Returns:
        str: The processed investigator reviewer prompt.
    """
    # Read the template file content
    with open(Investigator_reviewer_prompt_path, 'r', encoding='utf-8') as f:
        reviewer_prompt_template = f.read()

    # Replace placeholders with the corresponding content
    reviewer_prompt = reviewer_prompt_template.replace('{investigator_simulation_info}', Investigator_result)
    if no_block_description != True:
        reviewer_prompt = reviewer_prompt.replace('{blocks_list}', request_blocks_description)
    
    return reviewer_prompt


def load_investigator_round1_prompt(investigator_round1_prompt_path, request_blocks_description):
    """
    Reads the investigator round1 prompt template from the given file path and replaces 
    the '{simulation_blocks_list}' placeholder with the provided request_blocks_description.
    
    Args:
        investigator_round1_prompt_path (str): The file path to the investigator round1 prompt template.
        request_blocks_description (str): The string to replace the '{simulation_blocks_list}' placeholder.
    
    Returns:
        str: The processed investigator round1 prompt.
    """
    # Read the template file content
    with open(investigator_round1_prompt_path, 'r', encoding='utf-8') as f:
        investigator_round1_prompt_template = f.read()
    
    # Replace the placeholder with the provided content
    if no_block_description != True:
        investigator_round1_prompt = investigator_round1_prompt_template.replace(
            '{simulation_blocks_list}', 
            request_blocks_description)
        return investigator_round1_prompt
    else:
        return investigator_round1_prompt_template


def load_investigator_round2_prompt(investigator_round2_prompt_path, blocks_list_path, investigator_reviewer_result):
    """
    Reads the investigator round2 prompt template and blocks list files, then replaces
    the placeholders '{simulation_blocks_list}' and '{investigator_reviewer_feedback}' with the
    corresponding content.

    Args:
        investigator_round2_prompt_path (str): The file path to the investigator round2 prompt template.
        blocks_list_path (str): The file path to the blocks list file.
        investigator_reviewer_result (str): The string to replace the '{investigator_reviewer_feedback}' placeholder.

    Returns:
        str: The processed investigator round2 prompt.
    """
    # Read the investigator round2 prompt template file
    with open(investigator_round2_prompt_path, 'r', encoding='utf-8') as f:
        investigator_round2_prompt_template = f.read()

    # Read the blocks list file
    with open(blocks_list_path, 'r', encoding='utf-8') as f:
        blocks_list = f.read()

    # Replace the placeholders with the corresponding content
    investigator_round2_prompt = investigator_round2_prompt_template.replace('{investigator_reviewer_feedback}', investigator_reviewer_result)
    if no_block_description != True:
        investigator_round2_prompt = investigator_round2_prompt.replace('{simulation_blocks_list}', blocks_list)
    
    
    return investigator_round2_prompt

def load_investigator_round3_prompt(Investigator_round3_prompt_path, request_blocks_description, Investigator_reviewer_result):
    """
    Reads the investigator round3 prompt template from the specified file and replaces
    the placeholders '{simulation_blocks_list}' and '{investigator_reviewer_feedback}' with the provided content.

    Args:
        Investigator_round3_prompt_path (str): The file path to the investigator round3 prompt template.
        request_blocks_description (str): The string to replace the '{simulation_blocks_list}' placeholder.
        Investigator_reviewer_result (str): The string to replace the '{investigator_reviewer_feedback}' placeholder.

    Returns:
        str: The processed investigator round3 prompt.
    """
    # Read the template file content
    with open(Investigator_round3_prompt_path, 'r', encoding='utf-8') as f:
        Investigator_round3_prompt_template = f.read()

    # Replace placeholders with the corresponding content
    Investigator_round3_prompt = Investigator_round3_prompt_template.replace('{investigator_reviewer_feedback}', Investigator_reviewer_result)
    if no_block_description != True:
        Investigator_round3_prompt = Investigator_round3_prompt.replace('{simulation_blocks_list}', request_blocks_description)
   
    
    return Investigator_round3_prompt

def load_investigator_round4_prompt(Investigator_round4_prompt_path, execution_code):
    """
    Reads the investigator round3 prompt template from the specified file and replaces
    the placeholders '{simulation_blocks_list}' and '{investigator_reviewer_feedback}' with the provided content.

    Args:
        Investigator_round3_prompt_path (str): The file path to the investigator round3 prompt template.
        request_blocks_description (str): The string to replace the '{simulation_blocks_list}' placeholder.
        Investigator_reviewer_result (str): The string to replace the '{investigator_reviewer_feedback}' placeholder.

    Returns:
        str: The processed investigator round3 prompt.
    """
    # Read the template file content
    with open(Investigator_round4_prompt_path, 'r', encoding='utf-8') as f:
        Investigator_round4_prompt_template = f.read()

    # Replace placeholders with the corresponding content
    Investigator_round4_prompt = Investigator_round4_prompt_template.replace('{execution_code}', execution_code)
    
    return Investigator_round4_prompt



'''import os

def load_investigator_reviewer_prompt_round1(request_images, no_request_template_path, prompt_template_path):
    """
    根据 request_images 的内容选择不同的模板文件，并生成 Investigator_reviewer_prompt_round1。
    
    参数:
        request_images (dict): 包含键 'request_images' 的字典，其值为图像名称的列表。
        no_request_template_path (str): 当 request_images 为空时使用的模板文件路径。
        prompt_template_path (str): 当 request_images 不为空时使用的模板文件路径。
    
    返回:
        str: 生成的 Investigator_reviewer_prompt_round1 字符串。
    """
    # 判断是否有请求的图像
    if request_images == None:
        template_path = no_request_template_path
        if os.path.exists(template_path):
            with open(template_path, 'r', encoding='utf-8') as f:
                template_content = f.read()
        else:
            template_content = ''
        investigator_reviewer_prompt_round1 = template_content
    else:
        # 将列表元素组合成一句话
        image_list = request_images.get('request_images', [])
        if image_list:
            if len(image_list) == 1:
                image_sentence = f'This is the image of {image_list[0]}.'
            else:
                image_sentence = f'These are the images of {", ".join(image_list[:-1])}, and {image_list[-1]}.'
        else:
            image_sentence = ''
        
        # 读取模板文件内容
        template_path = prompt_template_path
        if os.path.exists(template_path):
            with open(template_path, 'r', encoding='utf-8') as f:
                template_content = f.read()
        else:
            template_content = ''
        
        # 将图像句子添加到模板内容的开头
        investigator_reviewer_prompt_round1 = f'{image_sentence}\n\n{template_content}'
    
    return investigator_reviewer_prompt_round1'''

def load_block_builder_prompt(block_builder_with_interpretor_reviewer_prompt_path, code_templates_path, functions_path, blocks_list_path, investigator_reviewer_result):
    """
    从指定的文件路径读取Block Builder模板、代码模板、函数定义和blocks描述，
    并将模板中的占位符替换为对应的文件内容和investigator的评审结果。
    
    参数:
        block_builder_with_interpretor_reviewer_prompt_path (str): Block Builder模板文件路径，
            模板中包含占位符 {code_template}、{functions}、{blocks_description}、{investigator_agent_information}。
        code_templates_path (str): 存放代码模板的文件路径。
        functions_path (str): 存放函数定义的文件路径。
        blocks_list_path (str): 存放blocks描述的文件路径。
        investigator_reviewer_result (str): 用于替换模板中 {investigator_agent_information} 的内容。
    
    返回:
        str: 替换后的Block Builder提示内容。
    """
    # 读取Block Builder模板文件内容
    with open(block_builder_with_interpretor_reviewer_prompt_path, 'r', encoding='utf-8') as f:
        block_builder_prompt_template = f.read()

    # 读取代码模板文件内容
    with open(code_templates_path, 'r', encoding='utf-8') as f:
        code_template = f.read()

    # 读取函数定义文件内容
    with open(functions_path, 'r', encoding='utf-8') as f:
        functions = f.read()

    # 读取blocks描述文件内容
    with open(blocks_list_path, 'r', encoding='utf-8') as f:
        blocks_description = f.read()

    # 替换模板中的占位符
    block_builder_prompt = block_builder_prompt_template.replace('{code_template}', code_template)
    block_builder_prompt = block_builder_prompt.replace('{functions}', functions)
    if no_block_description != True:
        block_builder_prompt = block_builder_prompt.replace('{blocks_description}', blocks_description)
    block_builder_prompt = block_builder_prompt.replace('{investigator_agent_information}', investigator_reviewer_result)
    
    return block_builder_prompt

def load_debug_locator_prompt(debug_locator_prompt_path, block_builder_result, execute_result, functions_path, blocks_description_path, investigator_reviewer_result):
    """
    从指定的文件路径读取 Debug Locator 模板，并将模板中的占位符替换为对应的内容。

    参数:
        debug_locator_prompt_path (str): Debug Locator 模板文件的路径，模板中包含以下占位符：
            {execution_code}, {error_message}, {functions_set}, {blocks_description}, {investigator_implementation_info}。
        block_builder_result (str): 用于替换模板中 {execution_code} 的执行代码。
        execute_result (str): 用于替换模板中 {error_message} 的错误信息。
        functions (str): 用于替换模板中 {functions_set} 的函数集描述。
        blocks_description (str): 用于替换模板中 {blocks_description} 的 blocks 描述。
        investigator_reviewer_result (str): 用于替换模板中 {investigator_implementation_info} 的实现信息。

    返回:
        str: 替换后的 Debug Locator 提示内容。
    """
    # 读取模板文件内容
    with open(debug_locator_prompt_path, 'r', encoding='utf-8') as f:
        debug_locator_prompt_template = f.read()
    
    with open(functions_path, 'r', encoding='utf-8') as f:
        functions = f.read()
    
    with open(blocks_description_path, 'r', encoding='utf-8') as f:
        blocks_description = f.read()

    # 替换模板中的占位符
    debug_locator_prompt = debug_locator_prompt_template.replace('{execution_code}', block_builder_result)
    debug_locator_prompt = debug_locator_prompt.replace('{error_message}', execute_result)
    debug_locator_prompt = debug_locator_prompt.replace('{functions_set}', functions)
    if no_block_description != True:
        debug_locator_prompt = debug_locator_prompt.replace('{blocks_description}', blocks_description)
    debug_locator_prompt = debug_locator_prompt.replace('{investigator_implementation_info}', investigator_reviewer_result)
    
    return debug_locator_prompt

def load_debug_locator_wo_unit_test_prompt(debug_locator_prompt_path, block_builder_result, execute_result, functions_path, blocks_description_path):
    """
    从指定的文件路径读取 Debug Locator 模板，并将模板中的占位符替换为对应的内容。

    参数:
        debug_locator_prompt_path (str): Debug Locator 模板文件的路径，模板中包含以下占位符：
            {execution_code}, {error_message}, {functions_set}, {blocks_description}, {investigator_implementation_info}。
        block_builder_result (str): 用于替换模板中 {execution_code} 的执行代码。
        execute_result (str): 用于替换模板中 {error_message} 的错误信息。
        functions (str): 用于替换模板中 {functions_set} 的函数集描述。
        blocks_description (str): 用于替换模板中 {blocks_description} 的 blocks 描述。
        investigator_reviewer_result (str): 用于替换模板中 {investigator_implementation_info} 的实现信息。

    返回:
        str: 替换后的 Debug Locator 提示内容。
    """
    # 读取模板文件内容
    with open(debug_locator_prompt_path, 'r', encoding='utf-8') as f:
        debug_locator_prompt_template = f.read()
    
    with open(functions_path, 'r', encoding='utf-8') as f:
        functions = f.read()
    
    with open(blocks_description_path, 'r', encoding='utf-8') as f:
        blocks_description = f.read()

    # 替换模板中的占位符
    debug_locator_prompt = debug_locator_prompt_template.replace('{execution_code}', block_builder_result)
    debug_locator_prompt = debug_locator_prompt.replace('{error_message}', execute_result)
    debug_locator_prompt = debug_locator_prompt.replace('{functions_set}', functions)
    if no_block_description != True:
        debug_locator_prompt = debug_locator_prompt.replace('{blocks_description}', blocks_description)
    
    return debug_locator_prompt

def load_block_builder_round1_prompt(block_builder_round1_prompt_path, error_message, debug_locator_result):
    """
    从指定的模板文件路径读取 Block Builder round1 模板内容，
    将占位符 {Debug_locator_response} 替换为 debug_locator_result，
    然后调用 block_builder 的 step 方法执行生成的提示，
    并返回响应中第一个消息的内容作为结果。

    参数:
        block_builder_round1_prompt_path (str): 模板文件路径，即 Block_builder_with_interpretor_reviewer_round1_prompt 的值。
        debug_locator_result (str): 用于替换模板中 {Debug_locator_response} 的字符串。
        block_builder: 拥有 step 方法的对象，用于执行生成的提示内容。

    返回:
        str: 从 block_builder.step 调用返回的响应中提取的结果。
    """
    # 读取模板文件内容
    with open(block_builder_round1_prompt_path, 'r', encoding='utf-8') as f:
        block_builder_round1_prompt_template = f.read()

    # 替换模板中的占位符
    block_builder_round1_prompt = block_builder_round1_prompt_template.replace('{error_message}',error_message)
    block_builder_round1_prompt = block_builder_round1_prompt.replace('{Debug_locator_response}', debug_locator_result)

    return block_builder_round1_prompt

def load_investigator_reviewer_round1_prompt(investigator_reviewer_round1_prompt_path, debug_locator_issues):
    """
    从指定的模板文件路径读取 Block Builder round1 模板内容，
    将占位符 {Debug_locator_response} 替换为 debug_locator_result，
    然后调用 block_builder 的 step 方法执行生成的提示，
    并返回响应中第一个消息的内容作为结果。

    参数:
        block_builder_round1_prompt_path (str): 模板文件路径，即 Block_builder_with_interpretor_reviewer_round1_prompt 的值。
        debug_locator_result (str): 用于替换模板中 {Debug_locator_response} 的字符串。
        block_builder: 拥有 step 方法的对象，用于执行生成的提示内容。

    返回:
        str: 从 block_builder.step 调用返回的响应中提取的结果。
    """
    # 读取模板文件内容
    with open(investigator_reviewer_round1_prompt_path, 'r', encoding='utf-8') as f:
        investigator_reviewer_round1_prompt_template = f.read()

    # 替换模板中的占位符
    investigator_reviewer_round1_prompt = investigator_reviewer_round1_prompt_template.replace('{debug_locator_issues}',debug_locator_issues)

    return investigator_reviewer_round1_prompt

def load_report_writer_round0_prompt(report_writer_prompt_path, execution_code, blocks_description_path, simulation_description_path, Investigator_result):
    # 读取模板文件内容
    with open(report_writer_prompt_path, 'r', encoding='utf-8') as f:
        report_writer_prompt_template = f.read()

    with open(blocks_description_path, 'r', encoding='utf-8') as f:
        blocks_description = f.read()

    with open(simulation_description_path, 'r', encoding='utf-8') as f:
        simulation_description = f.read()

    # 替换模板中的占位符
    report_writer_prompt = report_writer_prompt_template.replace('{execution_code}',execution_code)
    if no_block_description != True:
        report_writer_prompt = report_writer_prompt.replace('{used_block_description}',blocks_description)
    report_writer_prompt = report_writer_prompt.replace('{simulation_description}',simulation_description)
    report_writer_prompt = report_writer_prompt.replace('{connection_description}',Investigator_result)

    return report_writer_prompt

def merge_block_texts(request_blocks, Block_root_path):
    """
    读取 request_blocks 中指定的 txt 文件，并合成为一个字符串
    :param request_blocks: 包含需要读取的 block 名称的字典
    :param Block_root_path: 存放 txt 文件的根目录
    :return: 合并后的字符串
    """
    # 存储合并文本
    merged_text = []

    # 遍历 request_blocks 列表
    for block_name in request_blocks.get('request_blocks', []):
        file_path = os.path.join(Block_root_path, f"{block_name}.txt")

        # 检查文件是否存在
        if os.path.exists(file_path):
            with open(file_path, 'r', encoding='utf-8') as file:
                merged_text.append(file.read())
        else:
            print(f"Warning: {file_path} not found.")

    # 组合最终字符串
    return "\n\n".join(merged_text)

import os

def save_recognized_blocks_description(Recognized_blocks_description, block_root_path='./references/blocks', file_name='recognized_blocks_description.txt'):
    """
    Saves the recognized blocks description string to a text file under the specified directory.

    Args:
        Recognized_blocks_description (str): The string content to be saved.
        block_root_path (str): The directory path where the file will be saved.
        file_name (str): The name of the file to be saved.
    
    Returns:
        str: The full file path of the saved file.
    """
    # Ensure the directory exists
    os.makedirs(block_root_path, exist_ok=True)
    
    # Create the full file path
    full_file_path = os.path.join(block_root_path, file_name)
    
    # Write the string to the file
    with open(full_file_path, 'w', encoding='utf-8') as f:
        f.write(Recognized_blocks_description)
    
    return full_file_path

def save_recognized_blocks_description_4_report(Recognized_blocks_description, block_root_path='./references/blocks4report', file_name='recognized_blocks_description.txt'):
    """
    Saves the recognized blocks description string to a text file under the specified directory.

    Args:
        Recognized_blocks_description (str): The string content to be saved.
        block_root_path (str): The directory path where the file will be saved.
        file_name (str): The name of the file to be saved.
    
    Returns:
        str: The full file path of the saved file.
    """
    # Ensure the directory exists
    os.makedirs(block_root_path, exist_ok=True)
    
    # Create the full file path
    full_file_path = os.path.join(block_root_path, file_name)
    
    # Write the string to the file
    with open(full_file_path, 'w', encoding='utf-8') as f:
        f.write(Recognized_blocks_description)
    
    return full_file_path

def execute_agent(agent_prompt, agent, img=None):
    """
    Creates a user message with the given Investigator prompt and executes the investigator agent step.
    
    Args:
        Investigator_prompt (str): The prompt content to send.
        BaseMessage: The class or object used to create user messages.
        Investigator_agent: The agent object with a step() method to process the message.
        img (optional): An optional image to include in the message. If provided, it will be wrapped in a list and passed as image_list.
    
    Returns:
        str: The content of the first message in the response.
    """
    if img is not None:
        user_msg = BaseMessage.make_user_message(
            role_name="User", content=agent_prompt, image_list=[img]
        )
    else:
        user_msg = BaseMessage.make_user_message(
            role_name="User", content=agent_prompt
        )
    
    response = agent.step(user_msg)
    #print(response)
    result = response.msgs[0].content
    total_input_token = response.info['usage']['prompt_tokens']
    total_output_token = response.info['usage']['completion_tokens']
    return result,total_input_token,total_output_token

def load_investigator_vote_prompt(Investigator_vote_prompt_path, AutoSim_1, AutoSim_2, AutoSim_3):
    """
    Reads the investigator vote prompt template from the given file path and replaces 
    the placeholders '{ai1_description}', '{ai2_description}', and '{ai3_description}' with 
    the corresponding Investigator_result from AutoSim_1, AutoSim_2, and AutoSim_3.

    Args:
        Investigator_vote_prompt_path (str): The file path to the investigator vote prompt template.
        AutoSim_1: An object containing the attribute 'Investigator_result' to replace '{ai1_description}'.
        AutoSim_2: An object containing the attribute 'Investigator_result' to replace '{ai2_description}'.
        AutoSim_3: An object containing the attribute 'Investigator_result' to replace '{ai3_description}'.

    Returns:
        str: The processed investigator vote prompt.
    """
    with open(Investigator_vote_prompt_path, 'r', encoding='utf-8') as f:
        Investigator_vote_prompt_template = f.read()

    Investigator_vote_prompt = Investigator_vote_prompt_template.replace(
        '{ai1_description}', AutoSim_1.Investigator_result)
    Investigator_vote_prompt = Investigator_vote_prompt.replace(
        '{ai2_description}', AutoSim_2.Investigator_result)
    Investigator_vote_prompt = Investigator_vote_prompt.replace(
        '{ai3_description}', AutoSim_3.Investigator_result)
    
    return Investigator_vote_prompt


