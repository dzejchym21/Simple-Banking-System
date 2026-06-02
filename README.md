# Simple Banking System

A lightweight, administrative desktop application for managing bank accounts, built using C++20. The project focuses on clean architecture, separating the core banking logic from the visual presentation layer.

## Project Structure
* `src/core/` – Core business logic (`Account` and `Bank` classes). Pure C++ without any GUI dependencies, making it fully portable and easy to test.
* `src/main.cpp` – Entry point, main application loop, and user interface layout.
* `tests/` – Unit tests covering account operations and edge cases.

## Key Features
* **Interactive Dashboard** – Live view of all registered accounts inside a responsive, scrollable list.
* **Real-time Counter** – Dynamic tracking of total active accounts directly from the internal registry.
* **Modal Operations** – Secure popup windows for Deposits and Withdrawals to prevent accidental inputs.
* **Instant Validation** – Built-in checks for negative values and overdrafts, complete with color-coded feedback (Green for success, Red for errors).
* **Automated Unit Tests** – Robust test coverage via Google Test (GTest) to guarantee backend reliability.

## Tech Stack
* **Language:** C++20
* **GUI Framework:** Dear ImGui (v1.90.4) with GLFW & OpenGL3 backend
* **Testing:** Google Test (GTest)
* **Build System:** CMake (Minimum Required: v3.20)
* **Environment:** Developed using CLion on WSL (Windows Subsystem for Linux)

## Setup & Build Instructions

### Prerequisites (Linux/WSL)
To compile the graphical interface on Linux or WSL, install the required development libraries:
```bash
sudo apt update && sudo apt install -y libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev xorg-dev libgl1-mesa-dev