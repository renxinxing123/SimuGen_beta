from PIL import Image
from camel.agents import ChatAgent
from camel.messages import BaseMessage

from agents.utils import *
import os
import time

class autosim:
    def __init__(
        self,
        Investigator_model,
        Investigator_reviewer_model,
        Block_builder_model,
        Debug_locator_model,
        Report_writer_model,
        simulation_explanation_path,
        simulation_diagram_path,
        Blocks_list_path,
        Code_templates_path,
        Functions_path,
        Block_root_path,
        Block_4_report_root_path,
        Block_images_root_path,
        Investigator_round0_prompt_path,
        Investigator_round1_prompt_path,
        Investigator_round2_prompt_path,
        Investigator_round3_prompt_path,
        Investigator_round4_prompt_path,
        Investigator_vote_prompt_path,
        Investigator_reviewer_prompt_path,
        Investigator_reviewer_round1_prompt_path,
        Block_builder_with_interpretor_reviewer_prompt_path,
        Block_builder_with_interpretor_reviewer_round1_prompt_path,
        Debug_locator_prompt_path,
        Report_writer_prompt_path,
    ):
        # ---------------------------------------------------------------------
        # Initialize system message used by agents.
        # ---------------------------------------------------------------------
        self.sys_msg = BaseMessage.make_assistant_message(
            role_name="Assistant",
            content="You are a helpful assistant.",
        )

        self.agent_model_type = {
            'Investigator': Investigator_model.model_type,
            'Unit_test_reviewer': Investigator_reviewer_model.model_type,
            'Block_builder': Block_builder_model.model_type,
            'Debug_locator': Debug_locator_model.model_type,
            'Report_writer': Report_writer_model.model_type,
        }

        # 存储每个 agent 的累计运行时间
        self.agent_times = {
            'Investigator': 0.0,
            'Unit_test_reviewer': 0.0,
            'Block_builder': 0.0,
            'Debug_locator': 0.0,
            'Report_writer': 0.0,
        }

        # 统计每个 agent 被调用的次数
        self.agent_counts = {
            'Investigator': 0,
            'Unit_test_reviewer': 0,
            'Block_builder': 0,
            'Debug_locator': 0,
            'Report_writer': 0,
        }

        self.agent_token = {
            'Investigator': {'total_input_token':0, 'total_output_token':0},
            'Unit_test_reviewer': {'total_input_token':0, 'total_output_token':0},
            'Block_builder': {'total_input_token':0, 'total_output_token':0},
            'Debug_locator': {'total_input_token':0, 'total_output_token':0},
            'Report_writer': {'total_input_token':0, 'total_output_token':0},
        }

        self.price = {"o3-mini": {'input_token_price':1.1, 'output_token_price':4.4},
                      "o4-mini": {'input_token_price':1.1, 'output_token_price':4.4},
                      "gpt-4.1-2025-04-14": {'input_token_price':2, 'output_token_price':8},
                      "gpt-4.5-preview": {'input_token_price':75, 'output_token_price':150},
                     }
        
        # 用于记录每个 agent 输出的完整日志
        self.full_output = []
        # ---------------------------------------------------------------------
        # Create various agent instances with corresponding models and system messages.
        # ---------------------------------------------------------------------
        self.Investigator_agent = ChatAgent(system_message=self.sys_msg, model=Investigator_model, message_window_size=16)
        self.Investigator_reviewer_agent = ChatAgent(model=Investigator_reviewer_model, message_window_size=6)
        self.Block_builder = ChatAgent(system_message=self.sys_msg, model=Block_builder_model)
        self.Debug_locator = ChatAgent(system_message=self.sys_msg, model=Debug_locator_model)
        self.Report_writer = ChatAgent(system_message=self.sys_msg, model=Report_writer_model)

        self.max_debug = 6
        
        # ---------------------------------------------------------------------
        # Configuration for file paths used throughout the simulation.
        # ---------------------------------------------------------------------
        self.simulation_explanation_path = simulation_explanation_path
        self.simulation_diagram_path = simulation_diagram_path
        self.Blocks_list_path = Blocks_list_path
        self.Code_templates_path = Code_templates_path
        self.Functions_path = Functions_path
        self.Block_root_path = Block_root_path
        self.Block_4_report_root_path = Block_4_report_root_path
        self.Block_images_root_path = Block_images_root_path

        self.Investigator_round0_prompt_path = Investigator_round0_prompt_path
        self.Investigator_round1_prompt_path = Investigator_round1_prompt_path
        self.Investigator_round2_prompt_path = Investigator_round2_prompt_path
        self.Investigator_round3_prompt_path = Investigator_round3_prompt_path
        self.Investigator_round4_prompt_path = Investigator_round4_prompt_path
        self.Investigator_vote_prompt_path = Investigator_vote_prompt_path
        self.Investigator_reviewer_prompt_path = Investigator_reviewer_prompt_path
        self.Investigator_reviewer_round1_prompt_path = Investigator_reviewer_round1_prompt_path

        self.Block_builder_with_interpretor_reviewer_prompt_path = Block_builder_with_interpretor_reviewer_prompt_path
        self.Block_builder_with_interpretor_reviewer_round1_prompt_path = Block_builder_with_interpretor_reviewer_round1_prompt_path
        self.Debug_locator_prompt_path = Debug_locator_prompt_path

        self.Report_writer_prompt_path = Report_writer_prompt_path

    def _time_agent(self, agent_name, func, *args, **kwargs):
        start = time.time()
        result, total_input_token, total_output_token = func(*args, **kwargs)
        elapsed = time.time() - start
        self.agent_times[agent_name] += elapsed
        self.agent_counts[agent_name] += 1
        self.agent_token[agent_name]['total_input_token'] += total_input_token
        self.agent_token[agent_name]['total_output_token'] += total_output_token

        # 记录该 agent 的输出
        self.full_output.append(f"[{agent_name}] {result}")

        return result

    def Investigator_round0(self, img):
        Investigator_round0_prompt = load_investigator_prompt(
            investigator_prompt_path=self.Investigator_round0_prompt_path,
            simulation_explanation_path=self.simulation_explanation_path,
            blocks_list_path=self.Blocks_list_path)

        Investigator_round0_result = self._time_agent(
            'Investigator', execute_agent,
            agent_prompt=Investigator_round0_prompt,
            agent=self.Investigator_agent,
            img=img)

        request_blocks = extract_json_from_text(Investigator_round0_result)
        request_blocks_description = merge_block_texts(
            request_blocks=request_blocks,
            Block_root_path=self.Block_root_path)
        Recognized_blocks_path = save_recognized_blocks_description(request_blocks_description)

        request_blocks_description_4_report = merge_block_texts(
            request_blocks=request_blocks,
            Block_root_path=self.Block_4_report_root_path)
        Recognized_blocks_path_4_report = save_recognized_blocks_description_4_report(request_blocks_description_4_report)

        Investigator_round1_prompt = load_investigator_round1_prompt(
            investigator_round1_prompt_path=self.Investigator_round1_prompt_path,
            request_blocks_description=request_blocks_description)

        Investigator_round1_result = self._time_agent(
            'Investigator', execute_agent,
            agent_prompt=Investigator_round1_prompt,
            agent=self.Investigator_agent)

        Investigator_result = Investigator_round0_result + Investigator_round1_result

        return Investigator_result, request_blocks_description, Recognized_blocks_path, Recognized_blocks_path_4_report

    def Investigator_round1(self, img, Investigator_reviewer_result):
        Investigator_round2_prompt = load_investigator_round2_prompt(
            investigator_round2_prompt_path=self.Investigator_round2_prompt_path,
            blocks_list_path=self.Blocks_list_path,
            investigator_reviewer_result=Investigator_reviewer_result)

        Investigator_round2_result = self._time_agent(
            'Investigator', execute_agent,
            agent_prompt=Investigator_round2_prompt,
            agent=self.Investigator_agent,
            img=img)

        request_blocks = extract_json_from_text(Investigator_round2_result)
        request_blocks_description = merge_block_texts(
            request_blocks=request_blocks,
            Block_root_path=self.Block_root_path)
        Recognized_blocks_path = save_recognized_blocks_description(request_blocks_description)

        request_blocks_description_4_report = merge_block_texts(
            request_blocks=request_blocks,
            Block_root_path=self.Block_4_report_root_path)
        Recognized_blocks_path_4_report = save_recognized_blocks_description_4_report(request_blocks_description_4_report)

        Investigator_round3_prompt = load_investigator_round3_prompt(
            Investigator_round3_prompt_path=self.Investigator_round3_prompt_path,
            request_blocks_description=request_blocks_description,
            Investigator_reviewer_result=Investigator_reviewer_result)

        Investigator_round3_result = self._time_agent(
            'Investigator', execute_agent,
            agent_prompt=Investigator_round3_prompt,
            agent=self.Investigator_agent)

        Investigator_result = Investigator_round2_result + Investigator_round3_result

        return Investigator_result, request_blocks_description, Recognized_blocks_path, Recognized_blocks_path_4_report

    def Investigator_round2(self, execution_code):
        Investigator_round2_prompt = load_investigator_round4_prompt(
            self.Investigator_round4_prompt_path,
            execution_code)

        return self._time_agent(
            'Investigator', execute_agent,
            agent_prompt=Investigator_round2_prompt,
            agent=self.Investigator_agent)

    def Investigator_reviewer_round0(self, request_blocks_description, Investigator_result):
        Reviewer_prompt = load_investigator_reviewer_prompt(
            Investigator_reviewer_prompt_path=self.Investigator_reviewer_prompt_path,
            request_blocks_description=request_blocks_description,
            Investigator_result=Investigator_result)

        return self._time_agent(
            'Unit_test_reviewer', execute_agent,
            agent_prompt=Reviewer_prompt,
            agent=self.Investigator_reviewer_agent)

    def Investigator_reviewer_round1(self, Debug_locator_result):
        Investigator_reviewer_round1_prompt = load_investigator_reviewer_round1_prompt(
            investigator_reviewer_round1_prompt_path=self.Investigator_reviewer_round1_prompt_path,
            debug_locator_issues=Debug_locator_result)

        return self._time_agent(
            'Unit_test_reviewer', execute_agent,
            agent_prompt=Investigator_reviewer_round1_prompt,
            agent=self.Investigator_reviewer_agent)

    def Block_builder_round0(self, Recognized_blocks_path, Investigator_result):
        Block_builder_prompt = load_block_builder_prompt(
            block_builder_with_interpretor_reviewer_prompt_path=self.Block_builder_with_interpretor_reviewer_prompt_path,
            code_templates_path=self.Code_templates_path,
            functions_path=self.Functions_path,
            blocks_list_path=Recognized_blocks_path,
            investigator_reviewer_result=Investigator_result)
        
        #print(Block_builder_prompt)

        return self._time_agent(
            'Block_builder', execute_agent,
            agent_prompt=Block_builder_prompt,
            agent=self.Block_builder)

    def Block_builder_round1(self, execute_result, Debug_locator_result):
        Block_builder_round1_prompt = load_block_builder_round1_prompt(
            block_builder_round1_prompt_path=self.Block_builder_with_interpretor_reviewer_round1_prompt_path,
            error_message=execute_result,
            debug_locator_result=Debug_locator_result)
        
        #print(Block_builder_round1_prompt)

        return self._time_agent(
            'Block_builder', execute_agent,
            agent_prompt=Block_builder_round1_prompt,
            agent=self.Block_builder)

    def Debug_locator_round0(self, Block_builder_result, execute_result, Recognized_blocks_path, Investigator_result):
        Debug_locator_prompt = load_debug_locator_prompt(
            debug_locator_prompt_path=self.Debug_locator_prompt_path,
            block_builder_result=Block_builder_result,
            execute_result=execute_result,
            functions_path=self.Functions_path,
            blocks_description_path=Recognized_blocks_path,
            investigator_reviewer_result=Investigator_result)
        
        #print(Debug_locator_prompt)

        return self._time_agent(
            'Debug_locator', execute_agent,
            agent_prompt=Debug_locator_prompt,
            agent=self.Debug_locator)

    def Report_writer_round0(self, execution_code, Recognized_blocks_path, simulation_description_path, Investigator_result):
        Report_writer_prompt = load_report_writer_round0_prompt(
            report_writer_prompt_path=self.Report_writer_prompt_path,
            execution_code=execution_code,
            blocks_description_path=Recognized_blocks_path,
            simulation_description_path=simulation_description_path,
            Investigator_result=Investigator_result)

        return self._time_agent(
            'Report_writer', execute_agent,
            agent_prompt=Report_writer_prompt,
            agent=self.Report_writer)

    def debug_branch(self, Block_builder_result, execute_result, Recognized_blocks_path, Recognized_blocks_path_4_report, Investigator_result, img):
        debug_iteration = 1  # 初始化调试迭代计数
        while True:
            Debug_locator_result = self.Debug_locator_round0(Block_builder_result, execute_result, Recognized_blocks_path, Investigator_result)
            print('\n')
            print(f"\033[92m[Debug Iteration {debug_iteration}] Debug locator result: {Debug_locator_result}\033[0m")

            Investigator_pass_data = extract_json_from_text(Debug_locator_result)
            if Investigator_pass_data["Investigator_error"] == True:
                Investigator_reviewer_round1_result = self.Investigator_reviewer_round1(Debug_locator_result)
                print('\n')
                print(f"\033[94m[Debug Iteration {debug_iteration}] Unit test reviewer round1 result: {Investigator_reviewer_round1_result}\033[0m")

                Investigator_result, request_blocks_description, Recognized_blocks_path, Recognized_blocks_path_4_report = self.Investigator_round1(img, Investigator_reviewer_round1_result)
                print('\n')
                print(f"\033[91m[Debug Iteration {debug_iteration}] Investigator result: {Investigator_result}\033[0m")
                return Investigator_result, Investigator_result, Recognized_blocks_path_4_report
            else:
                Block_builder_result = self.Block_builder_round1(execute_result, Debug_locator_result)
                print('\n')
                print(f"\033[95m[Debug Iteration {debug_iteration}] Block builder round1 result: {Block_builder_result}\033[0m")

                execute_result = execute_in_subprocess(Block_builder_result)
                print('\n')
                print(execute_result)
                if (execute_result == '' or 'Warning: The model name' in execute_result) and 'Traceback' not in execute_result:
                    return "success", Investigator_result, Recognized_blocks_path_4_report
                else:
                    debug_iteration += 1
                    continue

    def run(self):
        from PIL import Image
        img = Image.open(self.simulation_diagram_path)

        # 初始 Investigator 轮次
        Investigator_result, request_blocks_description, Recognized_blocks_path, Recognized_blocks_path_4_report = self.Investigator_round0(img)
        print('\n')
        print(f"\033[91m[Iteration 0] Investigator result: {Investigator_result}\033[0m")

        iteration = 1  # 主循环迭代计数
        while True:
            Investigator_reviewer_result = self.Investigator_reviewer_round0(request_blocks_description, Investigator_result)
            print('\n')
            print(f"\033[94m[Iteration {iteration}] Unit test reviewer result: {Investigator_reviewer_result}\033[0m")

            Investigator_pass_data = extract_json_from_text(Investigator_reviewer_result)
            Investigator_pass = Investigator_pass_data["Investigator_unit_test_pass"]

            if Investigator_pass == False:
                Investigator_result, request_blocks_description, Recognized_blocks_path, Recognized_blocks_path_4_report = self.Investigator_round1(img, Investigator_reviewer_result)
                print('\n')
                print(f"\033[91m[Iteration {iteration}] Investigator result: {Investigator_result}\033[0m")
                iteration += 1
                continue

            # Block 构建
            Block_builder_result = self.Block_builder_round0(Recognized_blocks_path, Investigator_result)
            print('\n')
            print(f"\033[95m[Iteration {iteration}] Block builder result: {Block_builder_result}\033[0m")

            execute_result = execute_in_subprocess(Block_builder_result)
            print('\n')
            print(execute_result)
            if (execute_result == '' or 'Warning: The model name' in execute_result) and 'Traceback' not in execute_result:
                print('\n')
                print('Simulation generated successfully!')
                self.report = self.Report_writer_round0(Block_builder_result, Recognized_blocks_path_4_report, self.simulation_explanation_path, Investigator_result)
                with open("output.txt", "w") as f:
                    f.write(str(self.report))
                # 写 full_output.txt
                with open("full_output.txt", "w", encoding="utf-8") as f:
                    f.write("\n".join(self.full_output))
                print(f"\033[93m Simulation report: {self.report} \033[0m")
                break

            # 调试分支
            result, Investigator_result, Recognized_blocks_path_4_report = self.debug_branch(
                Block_builder_result=Block_builder_result,
                execute_result=execute_result,
                Recognized_blocks_path=Recognized_blocks_path,
                Recognized_blocks_path_4_report=Recognized_blocks_path_4_report,
                Investigator_result=Investigator_result,
                img=img)

            if result == 'success':
                print('\n')
                print('Simulation generated successfully!')
                self.report = self.Report_writer_round0(Block_builder_result, Recognized_blocks_path_4_report, self.simulation_explanation_path, Investigator_result)
                with open("output.txt", "w") as f:
                    f.write(str(self.report))
                # 写 full_output.txt
                with open("full_output.txt", "w", encoding="utf-8") as f:
                    f.write("\n".join(self.full_output))
                print(f"\033[93m Simulation report: {self.report} \033[0m")
                break
            iteration += 1

        # 最终打印各 agent 的累计运行时间
        print("\nAgent run times summary:")
        for agent, elapsed in self.agent_times.items():
            print(f"{agent}: {elapsed:.2f} seconds")
        
        print('\n')
        print("Agent call counts summary:")
        for agent, count in self.agent_counts.items():
            if agent == 'Investigator':
                count = int(count/2)
            print(f"{agent}: {count} calls")

        print('\n')
        print("Agent token costs summary:")
        for agent, tokens in self.agent_token.items():
            input_tokens = tokens['total_input_token']
            output_tokens = tokens['total_output_token']
            total_tokens = input_tokens + output_tokens

            model_type = self.agent_model_type.get(agent)
            pricing = self.price.get(model_type, {'input_token_price': 0, 'output_token_price': 0})

            # 成本单位是 $ / 1M token
            input_cost = input_tokens * pricing['input_token_price'] / 1000000
            output_cost = output_tokens * pricing['output_token_price'] / 1000000
            total_cost = input_cost + output_cost
            print(f"{agent:<22} | Model: {model_type:<17} | Input: {input_tokens:<8} | Output: {output_tokens:<8} | "
                f"Total: {total_tokens:<8} | InCost: ${input_cost:<8.4f} | OutCost: ${output_cost:<8.4f} | TotalCost: ${total_cost:.4f}")

        # 保存到 statistic.txt
        with open("statistic.txt", "w", encoding="utf-8") as f:
            f.write("Agent run times summary:\n")
            for agent, elapsed in self.agent_times.items():
                f.write(f"{agent}: {elapsed:.2f} seconds\n")
            f.write("\nAgent call counts summary:\n")
            for agent, count in self.agent_counts.items():
                if agent == 'Investigator':
                    count = int(count/2)
                f.write(f"{agent}: {count} calls\n")
            f.write("\nAgent token costs summary:\n")
            for agent, tokens in self.agent_token.items():
                input_tokens = tokens['total_input_token']
                output_tokens = tokens['total_output_token']
                total_tokens = input_tokens + output_tokens
                model_type = self.agent_model_type.get(agent)
                pricing = self.price.get(model_type, {'input_token_price': 0, 'output_token_price': 0})
                input_cost = input_tokens * pricing['input_token_price'] / 1000000
                output_cost = output_tokens * pricing['output_token_price'] / 1000000
                total_cost = input_cost + output_cost
                f.write(f"{agent:<22} | Model: {model_type:<17} | Input: {input_tokens:<8} | Output: {output_tokens:<8} | "
                        f"Total: {total_tokens:<8} | InCost: ${input_cost:<8.4f} | OutCost: ${output_cost:<8.4f} | TotalCost: ${total_cost:.4f}\n")

    def vote(self, AutoSim_1, AutoSim_2, AutoSim_3):
        img = Image.open(self.simulation_diagram_path)

        Investigator_vote_prompt = load_investigator_vote_prompt(
            self.Investigator_vote_prompt_path,
            AutoSim_1=AutoSim_1,
            AutoSim_2=AutoSim_2,
            AutoSim_3=AutoSim_3)

        Investigator_vote_result = execute_agent(
            agent_prompt=Investigator_vote_prompt,
            agent=self.Investigator_agent,
            img=img)

        print(Investigator_vote_result)
        return extract_json_from_text(Investigator_vote_result)
