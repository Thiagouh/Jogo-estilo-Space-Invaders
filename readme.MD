# Space Invaders SDL

[![Build Status](https://img.shields.io/badge/build-passing-brightgreen)](https://github.com/Thiagouh/Jogo-estilo-Space-Invaders) [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

Este é um clone do clássico jogo Space Invaders, desenvolvido em C utilizando a biblioteca Simple DirectMedia Layer 2 (SDL2). O projeto foi criado como um exercício prático de programação e desenvolvimento de jogos, incorporando uma estrutura baseada em estados para gerenciar diferentes telas como menus e o gameplay.

## Funcionalidades

* **Menus Interativos**: Navegue por menus para iniciar o jogo, personalizar sua nave ou sair.
* **Níveis de Dificuldade**: Escolha entre os modos Fácil, Médio e Difícil, cada um com diferentes velocidades de inimigos, cadência de tiro e vidas para o jogador.
* **Personalização**: Escolha a cor da sua nave antes de começar a partida.
* **Progressão de Dificuldade**: A cada onda de inimigos derrotada, a dificuldade aumenta com naves mais rápidas.
* **Interface Gráfica**: Utiliza SDL2 para renderização, incluindo imagens e fontes customizadas.

---

## Como Compilar e Rodar

Para compilar e rodar este projeto, você precisa ter o compilador GCC e as bibliotecas de desenvolvimento do SDL2 instaladas no seu sistema.

### Pré-requisitos (Instalação das Bibliotecas)

As instruções variam de acordo com o seu sistema operacional:

#### **Para sistemas baseados em Debian/Ubuntu (Linux):**
```bash
sudo apt-get update && sudo apt-get install build-essential libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev
```

#### **Para macOS (usando Homebrew):**
```bash
brew install sdl2 sdl2_image sdl2_ttf
```

#### **Para Windows (usando MSYS2/MinGW):**
Primeiro, instale o [MSYS2/MinGW](https://www.msys2.org/).

Depois, abra o terminal MSYS2 MINGW64 e execute o seguinte comando para instalar todas as ferramentas necessárias:
```bash
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-SDL2 mingw-w64-x86_64-SDL2_image mingw-w64-x86_64-SDL2_ttf make git
```
Este comando instalará:
- **gcc**: O compilador para a linguagem C.
- **SDL2, SDL2_image, SDL2_ttf**: A biblioteca gráfica principal e suas extensões para imagem e fontes.
- **make**: A ferramenta que automatiza a compilação a partir do Makefile.
- **git**: O sistema de controle de versão, necessário para clonar o repositório.

---

### Compilação

Com as dependências instaladas, clone este repositório e navegue até a pasta do projeto:
```bash
git clone https://github.com/Thiagouh/Jogo-estilo-Space-Invaders.git
cd Jogo-estilo-Space-Invaders
```

Compile o jogo usando o Makefile:
```bash
make
```
Isso criará um arquivo executável chamado `space_invaders`.

---

### Rodando o Jogo

Após a compilação, execute o seguinte comando no terminal para iniciar o jogo:
```bash
./space_invaders
```

---

## Controles

- **Setas (esquerda e direita) ou SD**: Mover a nave
- **Espaço**: Atirar
- **ESC ou Q**: Sair do jogo
