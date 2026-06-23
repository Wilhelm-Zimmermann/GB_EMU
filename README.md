<h1 align="center">GB_EMU</h1>

<p align="center">
  Um emulador de Game Boy escrito em C, criado para estudar CPU, memória, ciclos de máquina e renderização gráfica em baixo nível.
</p>

<p align="center">
  <img src="https://img.shields.io/badge/C-Language-00599C?style=for-the-badge&logo=c&logoColor=white" alt="C" />
  <img src="https://img.shields.io/badge/CMake-Build-064F8C?style=for-the-badge&logo=cmake&logoColor=white" alt="CMake" />
  <img src="https://img.shields.io/badge/SDL2-Graphics-2C2D72?style=for-the-badge" alt="SDL2" />
  <img src="https://img.shields.io/badge/WSL-Linux%20Environment-4EAA25?style=for-the-badge&logo=linux&logoColor=white" alt="WSL" />
  <img src="https://img.shields.io/badge/Focus-PPU-8BAC0F?style=for-the-badge" alt="Focus PPU" />
  <img src="https://img.shields.io/badge/Status-Em%20desenvolvimento-yellow?style=for-the-badge" alt="Status" />
</p>

<p align="center">
  <a href="#visão-geral">Visão geral</a> •
  <a href="#progresso">Progresso</a> •
  <a href="#arquitetura">Arquitetura</a> •
  <a href="#como-executar">Como executar</a> •
  <a href="#próximos-passos">Próximos passos</a>
</p>

---

> Projeto em desenvolvimento. O foco atual está na implementação da **PPU** e na evolução da renderização gráfica.

## Visão geral

O **GB_EMU** é um emulador de Game Boy desenvolvido em C com foco em aprendizado de baixo nível.

O objetivo do projeto é entender, na prática, como um sistema clássico funciona internamente: execução de instruções da CPU, organização de memória, leitura de ROMs, ciclos de máquina, interrupções e renderização gráfica por meio da PPU.

Este repositório ainda não representa um emulador finalizado. Ele está em evolução contínua e atualmente a principal frente de desenvolvimento é a implementação da **Picture Processing Unit**, responsável por grande parte do comportamento visual do Game Boy.

## Objetivo do projeto

O projeto foi criado com fins educacionais, servindo como um estudo prático sobre emulação e arquitetura de computadores.

Principais temas estudados:

* arquitetura interna do Game Boy;
* emulação de CPU;
* execução de instruções e opcodes;
* manipulação de memória em C;
* leitura de ROMs `.gb`;
* funcionamento da PPU;
* renderização gráfica com SDL2;
* ciclos de máquina e sincronização;
* depuração usando logs e ROMs de teste.

## Progresso

| Componente            | Status                    |
| --------------------- | ------------------------- |
| Carregamento de ROM   | Em desenvolvimento        |
| CPU                   | Parcialmente implementada |
| Memória               | Parcialmente implementada |
| Instruções e opcodes  | Em evolução               |
| Interrupções          | Em evolução               |
| PPU                   | Foco atual                |
| Renderização com SDL2 | Inicial                   |
| Áudio                 | Não implementado          |
| Input/controles       | Não finalizado            |
| Testes automatizados  | Não estruturados          |
| Compatibilidade geral | Ainda não garantida       |

## Status atual

Estado geral do projeto:

* emulador escrito em C;
* build configurado com CMake;
* execução em ambiente Linux/WSL;
* carregamento de ROMs `.gb`;
* estrutura modular para CPU, memória, ROM, instruções, opcodes e PPU;
* loop principal baseado em ciclos;
* integração inicial entre CPU e PPU;
* janela SDL2 com resolução base de Game Boy;
* renderização gráfica ainda em evolução;
* ROMs comerciais podem não funcionar corretamente;
* compatibilidade geral ainda não é garantida.

## Principais recursos

* Implementação em C com foco em baixo nível.
* Separação dos módulos principais do emulador.
* Carregamento de ROMs no formato `.gb`.
* Execução de ciclos da CPU.
* Estrutura para instruções normais e prefixadas.
* Manipulação de memória em módulo dedicado.
* Integração inicial com PPU.
* Renderização usando SDL2.
* Logs e pontos de depuração para acompanhar a execução.
* Base preparada para evoluir compatibilidade e validação com ROMs de teste.

## Tecnologias utilizadas

| Categoria | Tecnologias            |
| --------- | ---------------------- |
| Linguagem | C                      |
| Build     | CMake, Make            |
| Gráficos  | SDL2                   |
| Ambiente  | WSL / Linux            |
| Emulação  | CPU, memória, ROM, PPU |
| Depuração | Logs e ROMs de teste   |

## Arquitetura

O projeto é organizado em módulos de baixo nível, mantendo cada responsabilidade principal separada.

Fluxo simplificado:

```text
ROM -> Memory -> CPU Cycle -> PPU Step -> SDL Texture -> Window
```

Diagrama geral:

```mermaid
flowchart LR
    ROM[ROM .gb] --> MEM[Memory]
    MEM --> CPU[CPU]
    CPU --> PPU[PPU]
    PPU --> SDL[SDL2 Texture]
    SDL --> WIN[Window]
```

Responsabilidades principais:

| Módulo                   | Responsabilidade                                                        |
| ------------------------ | ----------------------------------------------------------------------- |
| `main.c`                 | Inicialização da aplicação, SDL2, carregamento da ROM e loop principal. |
| `rom.c`                  | Leitura do arquivo de ROM e extração de informações do cartucho.        |
| `memory.c`               | Organização dos espaços de memória e operações de leitura/escrita.      |
| `cpu.c`                  | Ciclo principal da CPU, interrupções e despacho de opcodes.             |
| `instructions.c`         | Implementação de instruções da CPU.                                     |
| `opcodes.c`              | Organização e roteamento de opcodes.                                    |
| `prefixedInstructions.c` | Instruções prefixadas do processador.                                   |
| `bit.c` / `bitwise.c`    | Operações auxiliares de bits.                                           |
| `register.c`             | Manipulação e organização dos registradores.                            |
| `ppu.c`                  | Implementação da Picture Processing Unit e renderização do vídeo.       |
| `logger.c`               | Geração de logs para depuração.                                         |
| `src/headers/`           | Arquivos de cabeçalho compartilhados entre os módulos.                  |

## Estrutura do repositório

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

## Pré-requisitos

O projeto foi desenvolvido para execução em ambiente Linux/WSL.

Para compilar e executar, é necessário ter instalado:

* compilador C, como `gcc` ou `clang`;
* CMake;
* Make;
* SDL2;
* uma ROM `.gb` para teste.

Em distribuições baseadas em Debian/Ubuntu, incluindo WSL Ubuntu, as dependências podem ser instaladas com:

```bash
sudo apt update
sudo apt install build-essential cmake libsdl2-dev
```

## Como executar

Clone o repositório:

```bash
git clone https://github.com/Wilhelm-Zimmermann/GB_EMU.git
cd GB_EMU
```

Crie a pasta de build:

```bash
mkdir -p build
cd build
```

Gere os arquivos de build com CMake:

```bash
cmake -DCMAKE_BUILD_TYPE=Debug ..
```

Compile o projeto:

```bash
make
```

Execute informando o caminho de uma ROM `.gb`:

```bash
./main.out "../ROMS/seu-arquivo.gb"
```

Também existe um script auxiliar na raiz do projeto:

```bash
./run.sh
```

> O script `run.sh` possui caminhos de ROM configurados diretamente no arquivo. Ajuste o caminho da ROM conforme o seu ambiente local.

Caso o script não tenha permissão de execução:

```bash
chmod +x run.sh
```

## ROMs

Este repositório não inclui ROMs de jogos.

Para executar o emulador, forneça uma ROM `.gb` própria, obtida de forma legal. ROMs comerciais protegidas por direitos autorais não devem ser distribuídas junto com o projeto.

## Testes e validação

O projeto ainda não possui uma suíte automatizada de testes unitários.

A validação durante o desenvolvimento é feita principalmente por:

* execução manual de ROMs `.gb`;
* ROMs de teste;
* logs de CPU;
* comparação do comportamento esperado da CPU, memória e PPU;
* depuração incremental dos ciclos de execução.

## Limitações atuais

Como o projeto ainda está em desenvolvimento, algumas limitações são esperadas:

* compatibilidade incompleta com ROMs comerciais;
* PPU ainda em implementação;
* renderização gráfica em evolução;
* suporte a cartuchos/MBCs ainda limitado;
* áudio ainda não implementado;
* input/controles ainda não finalizados;
* testes automatizados ainda não estruturados;
* compatibilidade geral ainda não garantida.

## Próximos passos

* [ ] Avançar na implementação da PPU.
* [ ] Melhorar a renderização de background.
* [ ] Evoluir renderização de window e sprites.
* [ ] Validar modos da PPU.
* [ ] Melhorar o timing por scanline.
* [ ] Revisar tratamento de interrupções.
* [ ] Evoluir suporte a cartuchos/MBCs.
* [ ] Implementar input/controles.
* [ ] Adicionar áudio.
* [ ] Estruturar testes automatizados.
* [ ] Documentar progresso de compatibilidade.

## Sobre o desenvolvimento

O **GB_EMU** é um projeto de estudo contínuo e aprofundamento técnico.

A ideia principal não é apenas criar um emulador funcional, mas entender cada parte do processo: como a CPU executa instruções, como a memória é acessada, como os ciclos são sincronizados e como a PPU transforma dados em imagem.

Esse projeto representa uma jornada prática em programação C, arquitetura de computadores e emulação.

## Status do projeto

Projeto em evolução, desenvolvido para fins de estudo e aprofundamento em programação C, emulação, arquitetura de computadores e funcionamento interno do Game Boy.

Foco atual: **implementação da PPU**.

## Autor

**Wilhelm Henrique Zimmermann**

GitHub: [Wilhelm-Zimmermann](https://github.com/Wilhelm-Zimmermann)
