# Nome do executável que será criado
EXEC=space_invaders

# Arquivos-fonte do projeto
SRCS=space_invaders_sdl.c

# Flags do compilador e das bibliotecas necessárias
# O comando sdl2-config cuida das flags do SDL2 principal
# Adicionamos as flags para as bibliotecas ttf (fontes) e image (imagens)
CFLAGS=$(shell sdl2-config --cflags)
LIBS=$(shell sdl2-config --libs) -lSDL2_ttf -lSDL2_image

# Comando de compilação
CC=gcc

# Regra principal: o que acontece quando você digita "make"
all: $(EXEC)

# Como criar o executável a partir dos fontes
$(EXEC): $(SRCS)
	$(CC) $(SRCS) -o $(EXEC) $(CFLAGS) $(LIBS)

# Regra para limpar os arquivos compilados
clean:
	rm -f $(EXEC)