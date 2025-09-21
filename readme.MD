# Space Invaders SDL

Este é um clone do clássico jogo Space Invaders, desenvolvido em C utilizando a biblioteca Simple DirectMedia Layer 2 (SDL2). O projeto foi criado como um exercício prático de programação e desenvolvimento de jogos, incorporando uma estrutura baseada em estados para gerenciar diferentes telas como menus e o gameplay.

## Funcionalidades

* *Menus Interativos*: Navegue por menus para iniciar o jogo, personalizar sua nave ou sair.  
* *Níveis de Dificuldade*: Escolha entre os modos Fácil, Médio e Difícil, cada um com diferentes velocidades de inimigos, cadência de tiro e vidas para o jogador.  
* *Personalização*: Escolha a cor da sua nave antes de começar a partida.  
* *Progressão de Dificuldade*: A cada onda de inimigos derrotada, a dificuldade aumenta com naves mais rápidas.  
* *Interface Gráfica*: Utiliza SDL2 para renderização, SDL2_ttf para textos e fontes, e SDL2_image para carregar imagens de fundo.  

---

## Como Compilar e Rodar

Para compilar e rodar este projeto, você precisa ter o compilador GCC e as bibliotecas de desenvolvimento do SDL2 instaladas no seu sistema.  

### Pré-requisitos (Instalação das Bibliotecas)

As instruções variam de acordo com o seu sistema operacional:

#### **Para sistemas baseados em Debian/Ubuntu (Linux):**
```bash
sudo apt-get update && sudo apt-get install build-essential libsdl2-dev libsdl2-ttf-dev libsdl2-image-dev
```

#### **Para macOS (usando Homebrew):**
```bash
brew install sdl2 sdl2_ttf sdl2_image
```

#### **Para Windows (usando MSYS2/MinGW):**

Primeiro, instale o [MSYS2/MinGW](https://www.msys2.org/).  
Depois, no terminal do MSYS2, execute:

```bash
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-SDL2 mingw-w64-x86_64-SDL2_ttf mingw-w64-x86_64-SDL2_image
```

---

### Compilação

Com as dependências instaladas, clone este repositório e navegue até a pasta do projeto.  
A compilação é simplificada pelo `Makefile` incluso.

1. Clone o repositório (exemplo):
```bash
git clone [https://github.com/Thiagouh/Jogo-estilo-Space-Invaders.git](https://github.com/Thiagouh/Jogo-estilo-Space-Invaders.git
cd Jogo-estilo-Space-Invaders
```

2. Compile o jogo:
```bash
make
```

Isso criará um arquivo executável chamado `space_invaders`.

---

### Rodando o Jogo

Após a compilação, certifique-se de que a imagem de fundo (ex: `background.png`) está na mesma pasta do executável.  

Para iniciar o jogo, execute o seguinte comando no terminal:

```bash
./space_invaders
```

---
