# Space Invaders SDL — Guia Completo de Instalação e Execução

[![Build Status](https://img.shields.io/badge/build-passing-brightgreen)](https://github.com/Thiagouh/Jogo-estilo-Space-Invaders) [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

Este documento descreve como compilar e rodar o jogo **Space Invaders** em diferentes sistemas operacionais, utilizando a biblioteca SDL2 e suas extensões SDL2_image e SDL2_ttf.

---

## Funcionalidades

- **Menus Interativos**: Navegue por menus para iniciar o jogo, personalizar sua nave ou sair.
- **Níveis de Dificuldade**: Escolha entre Fácil, Médio e Difícil.
- **Personalização**: Escolha a cor da nave.
- **Progressão de Dificuldade**: A cada onda derrotada, inimigos ficam mais rápidos.
- **Interface Gráfica**: Renderização usando SDL2, imagens e fontes customizadas.

---

## 1. Ajustes no Código Fonte

No arquivo `space_invaders_sdl.c`, ajuste os includes para compatibilidade multiplataforma:

```c
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
```

> Isso garante que o código compile no Linux, macOS e Windows/MSYS2.

---

## 2. Pré-requisitos por Sistema

### Linux (Debian/Ubuntu)

```bash
sudo apt-get update && sudo apt-get install build-essential libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev git
```

### macOS (Homebrew)

```bash
brew install sdl2 sdl2_image sdl2_ttf git
```

### Windows (MSYS2 / MinGW64)

1. Instale o MSYS2: https://www.msys2.org
2. Abra o terminal **MSYS2 MinGW64**.
3. Atualize o sistema:

```bash
pacman -Syu
# feche o terminal se necessário e abra novamente
pacman -Su
```

4. Instale dependências:

```bash
pacman -S --needed mingw-w64-x86_64-toolchain \
    mingw-w64-x86_64-SDL2 \
    mingw-w64-x86_64-SDL2_image \
    mingw-w64-x86_64-SDL2_ttf \
    make \
    git
```

> ⚠️ Caso o `git clone` peça usuário/senha, use um **personal access token (PAT)** do GitHub ou configure chave SSH.

---

## 3. Clonar o Repositório

```bash
git clone https://github.com/Thiagouh/Jogo-estilo-Space-Invaders.git
cd Jogo-estilo-Space-Invaders
```

---

## 4. Compilar o Jogo

### Linux/macOS

```bash
gcc space_invaders_sdl.c -o space_invaders $(sdl2-config --cflags --libs) -lSDL2_image -lSDL2_ttf
```

### Windows (MSYS2 / MinGW64)

```bash
gcc space_invaders_sdl.c -o space_invaders \
    -IC:/msys64/mingw64/include \
    -Dmain=SDL_main \
    -LC:/msys64/mingw64/lib \
    -lmingw32 -mwindows -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image
```

> Se estiver usando o Makefile fornecido, ele já inclui as instruções portáveis.

---

## 5. Executar o Jogo

### Linux/macOS

```bash
./space_invaders
```

### Windows

```bash
./space_invaders.exe
```

> Certifique-se de que as DLLs SDL2, SDL2_image e SDL2_ttf estejam no mesmo diretório do executável caso rode fora do terminal.

---

## 6. Controles

- **Setas (esquerda/direita) ou S/D**: mover a nave  
- **Espaço**: atirar  
- **ESC ou Q**: sair do jogo  

---

## 7. Limpeza

```bash
make clean
```

Remove executável e arquivos objeto antigos.

---

## 8. Erros Comuns e Soluções

| Erro | Solução |
|------|--------|
| `fatal error: SDL_image.h: No such file or directory` | Ajuste include no código: `#include <SDL2/SDL_image.h>` ou ajuste path no Makefile/GCC |
| `undefined reference to WinMain` | Linkar `-lSDL2main` ou usar macro `SDL_main` |
| Jogo não inicia fora do terminal | Copie DLLs (SDL2.dll, SDL2_image.dll, SDL2_ttf.dll) para a pasta do executável |
| Git solicita usuário/senha | Use PAT no lugar da senha ou clone via SSH |
| Assets (imagens/fonte) não carregam | Verifique caminhos e nomes, mantenha a pasta `assets` junto do executável |

---

Este guia garante que o jogo compile e rode corretamente em Linux, macOS e Windows/MSYS2, com instruções detalhadas para compilação, DLLs e assets.
