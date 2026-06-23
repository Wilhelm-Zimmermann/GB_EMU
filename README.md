<h1 align="center">GB_EMU</h1>

<p align="center">
  Emulador de Game Boy desenvolvido em C para estudo de arquitetura de computadores, CPU, memória e renderização gráfica.
</p>

<p align="center">
  <img src="https://img.shields.io/badge/C-99.0%25-00599C?style=for-the-badge&logo=c&logoColor=white" alt="C" />
  <img src="https://img.shields.io/badge/CMake-Build-064F8C?style=for-the-badge&logo=cmake&logoColor=white" alt="CMake" />
  <img src="https://img.shields.io/badge/SDL2-Graphics-2C2D72?style=for-the-badge" alt="SDL2" />
  <img src="https://img.shields.io/badge/Status-Em%20desenvolvimento-yellow?style=for-the-badge" alt="Status" />
</p>

<p align="center">
  <a href="#visão-geral">Visão geral</a> •
  <a href="#status-atual">Status atual</a> •
  <a href="#tecnologias-utilizadas">Tecnologias</a> •
  <a href="#arquitetura">Arquitetura</a> •
  <a href="#como-executar">Como executar</a>
</p>

## Visão geral

O **GB_EMU** é um emulador de Game Boy desenvolvido em C com foco em aprendizado de baixo nível.

O projeto tem como objetivo estudar, na prática, conceitos como execução de instruções da CPU, organização de memória, carregamento de ROMs, ciclos de máquina, interrupções e renderização gráfica por meio da PPU.

Este repositório ainda está em desenvolvimento e não representa um emulador finalizado. A implementação atual está evoluindo principalmente na parte gráfica, com foco na **PPU**.

## Objetivo do projeto

Este projeto foi criado com fins educacionais, servindo como base para estudar:

* arquitetura do Game Boy;
* emulação de CPU;
* manipulação de memória em C;
* leitura de ROMs `.gb`;
* implementação de instruções e opcodes;
* funcionamento da PPU;
* renderização com SDL2;
* depuração usando ROMs de teste.

## Status atual

O projeto ainda está em desenvolvimento.

Estado geral:

* CPU parcialmente implementada.
* Sistema de memória implementado em módulos separados.
* Carregamento de ROMs `.gb`.
* Execução baseada em ciclos.
* Integração inicial entre CPU e PPU.
* Janela SDL2 com resolução base de Game Boy.
* PPU em desenvolvimento.
* Renderização gráfica ainda em evolução.
* ROMs comerciais podem não funcionar corretamente.
* Compatibilidade geral ainda não é garantida.

> O foco atual do projeto é avançar na implementação da **PPU** e melhorar a renderização dos frames.

## Principais recursos

* Emulador escrito em C.
* Build configurado com CMake.
* Renderização de vídeo usando SDL2.
* Carregamento de ROMs no formato `.gb`.
* Estrutura modular para CPU, memória, ROM, instruções, opcodes e PPU.
* Loop principal baseado em ciclos por frame.
* Suporte inicial a janela gráfica com escala.
* Logs e pontos de depuração para auxiliar o desenvolvimento.
* Referências a ROMs de teste para validação manual.

## Tecnologias utilizadas

| Categoria | Tecnologias                                             |
| --------- | ------------------------------------------------------- |
| Linguagem | C                                                       |
| Build     | CMake, Make                                             |
| Gráficos  | SDL2                                                    |
| Emulação  | CPU, memória, ROM, PPU                                  |
| Depuração | Logs e ROMs de teste                                    |
| Ambiente  | Linux/Unix-like ou ambiente compatível com CMake e SDL2 |

## Arquitetura

O projeto está organizado em módulos de baixo nível, separando as principais responsabilidades do emulador.

Fluxo principal:

```text
ROM -> Memory -> CPU Cycle -> PPU Step -> SDL Texture -> Window
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

Para compilar e executar o projeto, é necessário ter instalado:

* compilador C, como `gcc` ou `clang`;
* CMake;
* Make;
* SDL2;
* uma ROM `.gb` para teste.

Em distribuições baseadas em Debian/Ubuntu, as dependências podem ser instaladas com:

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

Também existe um script auxiliar:

```bash
./run.sh
```

> O script `run.sh` possui caminhos de ROM configurados diretamente no arquivo. Ajuste o caminho da ROM conforme o seu ambiente local.

## ROMs

Este repositório não inclui ROMs de jogos.

Para executar o emulador, forneça uma ROM `.gb` própria, obtida de forma legal. ROMs comerciais protegidas por direitos autorais não devem ser distribuídas junto com o projeto.

## Testes e validação

O projeto não possui uma suíte automatizada de testes unitários no momento.

A validação durante o desenvolvimento é feita principalmente por:

* execução manual de ROMs `.gb`;
* ROMs de teste;
* logs de CPU;
* comparação do comportamento esperado da CPU, memória e PPU.

## Limitações atuais

Como o projeto ainda está em desenvolvimento, algumas limitações são esperadas:

* compatibilidade incompleta com ROMs comerciais;
* PPU ainda em implementação;
* renderização gráfica em evolução;
* suporte a cartuchos/MBCs ainda limitado;
* áudio ainda não implementado;
* entrada/controles ainda não finalizados;
* testes automatizados ainda não estruturados.

## Próximos passos

Possíveis evoluções do projeto:

* finalizar a implementação da PPU;
* melhorar renderização de background, window e sprites;
* validar modos da PPU e timing por scanline;
* melhorar tratamento de interrupções;
* implementar suporte mais completo a cartuchos/MBCs;
* adicionar suporte a input;
* adicionar áudio;
* organizar uma suíte de testes automatizados;
* documentar melhor o progresso de compatibilidade.

## Status do projeto

Projeto em evolução, desenvolvido para fins de estudo e aprofundamento em programação C, emulação, arquitetura de computadores e funcionamento interno do Game Boy.

O foco atual está na implementação da **PPU**.

## Autor

**Wilhelm Henrique Zimmermann**

GitHub: [Wilhelm-Zimmermann](https://github.com/Wilhelm-Zimmermann)
