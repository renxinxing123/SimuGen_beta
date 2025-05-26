# **SimuGen: Scalable, Accurate Simulink Simulation Generation via Multi-Agent Large Language Models**

![Concept Diagram](AgentDiagram.png)

## Overview

Recent advances in Large Language Models (LLMs) have demonstrated remarkable capabilities in mathematical reasoning and code generation. However, LLMs still perform poorly in the simulation domain, especially when tasked with generating Simulink models—an essential tool in engineering and scientific research. Our preliminary experiments reveal that LLM agents struggle to produce reliable and complete Simulink simulation codes from text-only inputs, likely due to insufficient Simulink-specific data during pre-training.

**SimuGen** addresses this gap with a multi-modal agentic framework that automatically generates accurate Simulink simulation code by leveraging both the visual Simulink diagram image and domain knowledge. SimuGen coordinates several specialized agents—including an Investigator, a Unit Test Reviewer, a Block Builder, an Executor, a Debug Locator, and a Report Writer—supported by a domain-specific block database. This collaborative, modular architecture enables robust, interpretable, and extensible Simulink simulation generation.

---


## Framework Overview

The SimuGen pipeline consists of the following agents:

* **Investigator**: Uses multimodal LLMs to extract block and connection relationships from the Simulink diagram image.
* **Unit Test Reviewer**: Validates whether all blocks and connections conform to Simulink standards.
* **Block Builder**: Converts block and connection descriptions into executable Python code with `matlab.engine`.
* **Executor**: Runs generated code and reports execution results.
* **Debug Locator**: Diagnoses errors, providing targeted feedback for code or connection revision.
* **Report Writer**: Compiles a comprehensive simulation report, including theoretical context and implementation details.
* **Block Database**: Supplies agents with structured, domain-specific knowledge for accurate code synthesis.



## 🚧 Coming Soon
- Code release
- Documentation and setup guide

