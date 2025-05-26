from args import load_config
import os

from camel.models import ModelFactory
from camel.types import ModelPlatformType, ModelType
from camel.configs import ChatGPTConfig

from agents.utils import *
from agents.AutoSim_ import autosim

def create_model(model_type_str):
    return ModelFactory.create(
        model_platform=ModelPlatformType.OPENAI,
        model_type=getattr(ModelType, model_type_str),
        model_config_dict=ChatGPTConfig(temperature=1).as_dict(),
    )

def create_azure_model(model_type_str):
    return ModelFactory.create(
        model_platform=ModelPlatformType.AZURE,
        model_type=getattr(ModelType, model_type_str)
    )

if __name__ == "__main__":
    config = load_config()

    # 创建模型实例
    Investigator_model = create_model(config.pop("Investigator_model_type"))
    Investigator_reviewer_model = create_model(config.pop("Investigator_reviewer_model_type"))
    Block_builder_model = create_model(config.pop("Block_builder_model_type"))
    Debug_locator_model = create_model(config.pop("Debug_locator_model_type"))
    Report_writer_model = create_model(config.pop("Report_writer_model_type"))

    # 初始化 autosim
    sim = autosim(
        Investigator_model=Investigator_model,
        Investigator_reviewer_model=Investigator_reviewer_model,
        Block_builder_model=Block_builder_model,
        Debug_locator_model=Debug_locator_model,
        Report_writer_model=Report_writer_model,
        **config
    )

    sim.run()
