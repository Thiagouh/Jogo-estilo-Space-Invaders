# Guia de Instalação e Execução — Space Invaders SDL (Windows / MSYS2)

Este documento descreve como compilar e rodar o jogo Space Invaders em Windows utilizando **MSYS2/MinGW**.

---

## Pré-requisitos

1. Baixe o MSYS2 em: https://msys2.org e instale.
2. Abra o terminal **MSYS2 MinGW-64** (não use o MSYS2 puro).
3. Atualize o sistema:

   ```sh
   pacman -Syu
   # Se o terminal fechar, abra novamente e execute:
   pacman -Su
   ```

4. Instale as dependências necessárias:

   ```sh
   pacman -S --needed mingw-w64-x86_64-toolchain mingw-w64-x86_64-SDL2 mingw-w64-x86_64-SDL2_image mingw-w64-x86_64-SDL2_ttf make git
   ```

---

## Clonar e Compilar

Clone o repositório e compile o projeto:

```sh
git clone https://github.com/Thiagouh/Jogo-estilo-Space-Invaders.git
cd Jogo-estilo-Space-Invaders
make
```

> **Atenção:**  
> Verifique no `Makefile` se as flags de include/liberação apontam para `/mingw64/include/SDL2` e `/mingw64/lib`.  
> Se necessário, adicione `-lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2main` às flags de compilação.

---

## Rodando o Jogo

- No terminal MinGW-64:

  ```sh
  ./space_invaders.exe
  ```

- Fora do terminal:  
  Copie as DLLs necessárias para junto do executável. Exemplos:
  - SDL2.dll
  - SDL2_image.dll
  - SDL2_ttf.dll
  - Outras dependências como libpng, libjpeg, etc.

Certifique-se de que os arquivos de imagem e fontes (assets) estejam no local correto.

---

## Controles

- **Setas ou WASD:** Mover a nave
- **Espaço:** Atirar
- **ESC ou Q:** Sair do jogo

---

## Erros Comuns e Soluções

- **undefined reference to WinMain**  
  → Adicione `-lSDL2main` às flags de link ou use a macro `SDL_main` no código.
- **Falha ao encontrar imagens/fontes**  
  → Verifique caminhos, diferenciação de maiúsculas/minúsculas e a pasta `assets`.
- **Jogo não inicia fora do terminal**  
  → Copie todas as DLLs para a pasta do executável. Use ferramentas como *Dependency Walker* para identificar dependências faltantes.

---

## Limpeza

Adicione no `Makefile` a regra de limpeza:

```make
make clean
```

Isso remove arquivos objeto e executáveis antigos.

---
