# Space Invaders SDL

Este é um clone do clássico jogo Space Invaders, desenvolvido em C utilizando a biblioteca Simple DirectMedia Layer 2 (SDL2). O projeto foi criado como um exercício prático de programação e desenvolvimento de jogos, incorporando uma estrutura baseada em estados para gerenciar diferentes telas como menus e o gameplay.

## Funcionalidades

* **Menus Interativos**: Navegue por menus para iniciar o jogo, personalizar sua nave ou sair.
* **Níveis de Dificuldade**: Escolha entre os modos Fácil, Médio e Difícil, cada um com diferentes velocidades de inimigos, cadência de tiro e vidas para o jogador.
* **Personalização**: Escolha a cor da sua nave antes de começar a partida.
* **Progressão de Dificuldade**: A cada onda de inimigos derrotada, a dificuldade aumenta com naves mais rápidas.
* **Interface Gráfica**: Utiliza SDL2 para renderização, SDL2_ttf para textos e fontes, e SDL2_image para carregar imagens de fundo.

## Como Compilar e Rodar

Para compilar e rodar este projeto, você precisa ter o compilador GCC e as bibliotecas de desenvolvimento do SDL2 instaladas no seu sistema.

### Pré-requisitos (Instalação das Bibliotecas)

As instruções variam de acordo com o seu sistema operacional.

---

#### **Para sistemas baseados em Debian/Ubuntu (Linux):**

Para a maioria das distribuições Linux baseadas em Debian, como o Ubuntu, você pode instalar todas as dependências necessárias com um único comando no terminal:
```bash
sudo apt-get update && sudo apt-get install build-essential libsdl2-dev libsdl2-ttf-dev libsdl2-image-dev

#### **Para macOS (usando Homebrew):**

