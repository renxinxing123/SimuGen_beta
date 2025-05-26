# args.py

import yaml
import argparse

def load_config():
    parser = argparse.ArgumentParser(description="Load autosim config with optional overrides.")
    parser.add_argument("--config", type=str, default="autosim_config.yaml", help="Path to YAML config file.")

    # 自动构建 explanation/diagram 路径
    parser.add_argument("--example_name", type=str, help="Name of the simulation example folder")

    # 模型覆盖参数
    parser.add_argument("--Investigator_model_type", type=str)
    parser.add_argument("--Block_builder_model_type", type=str)
    parser.add_argument("--Debug_locator_model_type", type=str)
    parser.add_argument("--Investigator_reviewer_model_type", type=str)
    parser.add_argument("--Report_writer_model_type", type=str)

    args = parser.parse_args()

    with open(args.config, "r") as f:
        config = yaml.safe_load(f)

    # 根据 example_name 自动生成路径
    if args.example_name:
        base = f"./references/simulation_examples/{args.example_name}/{args.example_name}"
        config["simulation_explanation_path"] = base + ".txt"
        config["simulation_diagram_path"] = base + ".png"

    # 用命令行参数覆盖配置文件
    for key, value in vars(args).items():
        if value is not None and key not in ["config", "example_name"]:
            config[key] = value

    return config
