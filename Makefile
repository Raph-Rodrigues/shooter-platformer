# Nome do executável final
TARGET = shooter-platformer

# Compilador
CC = gcc

# Opções de compilação (indica onde estão os arquivos .h da pasta include)
CFLAGS = -I./include

# Bibliotecas necessárias (Trocado GLFW por SDL2 e mantido OpenGL/dl)
LIBS = -lSDL2 -lGL -ldl

# Arquivos de código do projeto (Agora ambos estão dentro da pasta src)
SRCS = src/main.c src/glad.c src/engine/global.c src/engine/render/render.c src/engine/render/render_init.c

# Regra principal para compilar
all:
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET) $(LIBS)

# Regra para limpar o executável gerado
clean:
	rm -f $(TARGET)
