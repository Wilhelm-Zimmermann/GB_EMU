<h1 align="center">GB_EMU</h1>

<p align="center">
  A Game Boy emulator written in C, built to study CPU execution, memory management, machine cycles, and low-level graphics rendering.
</p>

<p align="center">
  <img src="https://img.shields.io/badge/C-Language-00599C?style=for-the-badge&logo=c&logoColor=white" alt="C" />
  <img src="https://img.shields.io/badge/CMake-Build-064F8C?style=for-the-badge&logo=cmake&logoColor=white" alt="CMake" />
  <img src="https://img.shields.io/badge/SDL2-Graphics-2C2D72?style=for-the-badge" alt="SDL2" />
  <img src="https://img.shields.io/badge/WSL-Linux%20Environment-4EAA25?style=for-the-badge&logo=linux&logoColor=white" alt="WSL" />
  <img src="https://img.shields.io/badge/Focus-PPU-8BAC0F?style=for-the-badge" alt="Focus PPU" />
  <img src="https://img.shields.io/badge/Status-In%20Development-yellow?style=for-the-badge" alt="Status" />
</p>

<p align="center">
  <a href="#overview">Overview</a> •
  <a href="#progress">Progress</a> •
  <a href="#architecture">Architecture</a> •
  <a href="#running-the-project">Running</a> •
  <a href="#next-steps">Next steps</a>
</p>

---

> This project is still in development. The current focus is the **PPU implementation** and the evolution of the graphics rendering pipeline.

## Overview

**GB_EMU** is a Game Boy emulator written in C with a strong focus on low-level learning.

The goal of this project is to understand, in practice, how a classic handheld system works internally: CPU instruction execution, memory organization, ROM loading, machine cycles, interrupts, and graphics rendering through the PPU.

This repository does not represent a finished emulator yet. It is a work in progress, and the current development effort is focused mainly on the **Picture Processing Unit**, which is responsible for a significant part of the Game Boy's visual behavior.

## Project purpose

This project was created for educational purposes and serves as a practical study of emulation and computer architecture.

Main topics explored:

* Game Boy internal architecture;
* CPU emulation;
* instruction and opcode execution;
* memory manipulation in C;
* `.gb` ROM loading;
* PPU behavior;
* graphics rendering with SDL2;
* machine cycles and synchronization;
* debugging with logs and test ROMs.

## Progress

| Component                | Status                |
| ------------------------ | --------------------- |
| ROM loading              | In development        |
| CPU                      | Partially implemented |
| Memory                   | Partially implemented |
| Instructions and opcodes | Evolving              |
| Interrupts               | Evolving              |
| PPU                      | Current focus         |
| SDL2 rendering           | Initial               |
| Audio                    | Not implemented       |
| Input/controls           | Not finished          |
| Automated tests          | Not structured yet    |
| General compatibility    | Not guaranteed yet    |

## Current status

Current project state:

* emulator written in C;
* build configured with CMake;
* execution through a Linux/WSL environment;
* `.gb` ROM loading;
* modular structure for CPU, memory, ROM, instructions, opcodes, and PPU;
* cycle-based main loop;
* initial integration between CPU and PPU;
* SDL2 window using the original Game Boy base resolution;
* graphics rendering still evolving;
* commercial ROMs may not work correctly;
* general compatibility is not guaranteed yet.

## Main features

* C implementation focused on low-level programming.
* Modular organization of the emulator's core components.
* `.gb` ROM loading.
* CPU cycle execution.
* Structure for regular and prefixed instructions.
* Dedicated memory module.
* Initial PPU integration.
* Graphics rendering using SDL2.
* Logs and debugging points to track execution.
* Foundation for future compatibility improvements and validation with test ROMs.

## Tech stack

| Category    | Technologies          |
| ----------- | --------------------- |
| Language    | C                     |
| Build       | CMake, Make           |
| Graphics    | SDL2                  |
| Environment | WSL / Linux           |
| Emulation   | CPU, memory, ROM, PPU |
| Debugging   | Logs and test ROMs    |

## Architecture

The project is organized into low-level modules, keeping the main responsibilities of the emulator separated.

Simplified flow:

```text
ROM -> Memory -> CPU Cycle -> PPU Step -> SDL Texture -> Window
```

General diagram:

```mermaid
flowchart LR
    ROM[ROM .gb] --> MEM[Memory]
    MEM --> CPU[CPU]
    CPU --> PPU[PPU]
    PPU --> SDL[SDL2 Texture]
    SDL --> WIN[Window]
```

Main responsibilities:

| Module                   | Responsibility                                                      |
| ------------------------ | ------------------------------------------------------------------- |
| `main.c`                 | Application initialization, SDL2 setup, ROM loading, and main loop. |
| `rom.c`                  | ROM file reading and cartridge information extraction.              |
| `memory.c`               | Memory space organization and read/write operations.                |
| `cpu.c`                  | Main CPU cycle, interrupts, and opcode dispatching.                 |
| `instructions.c`         | CPU instruction implementation.                                     |
| `opcodes.c`              | Opcode organization and routing.                                    |
| `prefixedInstructions.c` | Prefixed CPU instructions.                                          |
| `bit.c` / `bitwise.c`    | Bit-level helper operations.                                        |
| `register.c`             | Register organization and manipulation.                             |
| `ppu.c`                  | Picture Processing Unit implementation and video rendering.         |
| `logger.c`               | Debug logging.                                                      |
| `src/headers/`           | Shared header files used across modules.                            |

## Repository structure

```text
.
├── src/
│   ├── headers/
│   ├── bit.c
│   ├── bitwise.c
│   ├── cpu.c
│   ├── instructions.c
│   ├── logger.c
│   ├── memory.c
│   ├── opcodes.c
│   ├── ppu.c
│   ├── prefixedInstructions.c
│   ├── register.c
│   └── rom.c
├── CMakeLists.txt
├── main.c
├── run.sh
└── .gitignore
```

## Prerequisites

The project was developed to run in a Linux/WSL environment.

To build and run it, you need:

* a C compiler, such as `gcc` or `clang`;
* CMake;
* Make;
* SDL2;
* a `.gb` ROM for testing.

On Debian/Ubuntu-based distributions, including WSL Ubuntu, the dependencies can be installed with:

```bash
sudo apt update
sudo apt install build-essential cmake libsdl2-dev
```

## Running the project

Clone the repository:

```bash
git clone https://github.com/Wilhelm-Zimmermann/GB_EMU.git
cd GB_EMU
```

Create the build directory:

```bash
mkdir -p build
cd build
```

Generate the build files with CMake:

```bash
cmake -DCMAKE_BUILD_TYPE=Debug ..
```

Compile the project:

```bash
make
```

Run the emulator by providing the path to a `.gb` ROM:

```bash
./main.out "../ROMS/your-file.gb"
```

There is also a helper script in the project root:

```bash
./run.sh
```

> The `run.sh` script contains local ROM paths configured directly in the file. Adjust the ROM path according to your local environment.

If the script does not have execution permission:

```bash
chmod +x run.sh
```

## ROMs

This repository does not include game ROMs.

To run the emulator, provide your own legally obtained `.gb` ROM. Commercial ROMs protected by copyright must not be distributed with this project.

## Testing and validation

The project does not currently have an automated unit test suite.

Validation during development is mainly done through:

* manual execution of `.gb` ROMs;
* test ROMs;
* CPU logs;
* comparison against expected CPU, memory, and PPU behavior;
* incremental debugging of execution cycles.

## Current limitations

Because the project is still in development, some limitations are expected:

* incomplete compatibility with commercial ROMs;
* PPU still under implementation;
* graphics rendering still evolving;
* limited cartridge/MBC support;
* audio not implemented yet;
* input/controls not finished yet;
* automated tests not structured yet;
* general compatibility not guaranteed yet.

## Next steps

* [ ] Continue the PPU implementation.
* [ ] Improve background rendering.
* [ ] Evolve window and sprite rendering.
* [ ] Validate PPU modes.
* [ ] Improve scanline timing.
* [ ] Review interrupt handling.
* [ ] Improve cartridge/MBC support.
* [ ] Implement input/controls.
* [ ] Add audio support.
* [ ] Structure automated tests.
* [ ] Document compatibility progress.

## About the development process

**GB_EMU** is a continuous study project focused on deep technical learning.

The main idea is not only to build a working emulator, but to understand each part of the process: how the CPU executes instructions, how memory is accessed, how cycles are synchronized, and how the PPU transforms data into pixels.

This project represents a practical journey through C programming, computer architecture, and emulation.

## Project status

Project in progress, developed for studying C programming, emulation, computer architecture, and the internal behavior of the Game Boy.

Current focus: **PPU implementation**.

## Author

**Wilhelm Henrique Zimmermann**

GitHub: [Wilhelm-Zimmermann](https://github.com/Wilhelm-Zimmermann)
