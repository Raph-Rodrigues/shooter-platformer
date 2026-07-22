#include <glad/glad.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

int main(int argc, char *argv[]) {
  // Inicializa o subsistema de video do SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("ERRO: nao pode iniciar SDL: %s\n", SDL_GetError());
    exit(1);
  }

  // Configura os atributos do OpenGL após SDL_Init
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

  // Cria a janela
  SDL_Window *window =
      SDL_CreateWindow("Shooter Platformer", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);

  if (!window) {
    printf("ERRO: não pode criar janela: %s\n", SDL_GetError());
    SDL_Quit();
    exit(1);
  }

  // salva o contexto na variável e verifica se houve erro
  SDL_GLContext gl_context = SDL_GL_CreateContext(window);
  if (!gl_context) {
    printf("ERRO: não pode criar o contexto OpenGL: %s\n", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    exit(1);
  }

  // Carrega os ponteiros do OpenGL usando glad
  if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
    printf("ERRO: não pode carregar o GL: %s\n", SDL_GetError());
    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    exit(1);
  }

  puts("OpenGL Carregou");
  printf("Vendor:   %s\n", glGetString(GL_VENDOR));
  printf("Renderer:   %s\n", glGetString(GL_RENDERER));
  printf("Version:   %s\n", glGetString(GL_VERSION));

  bool should_quit = false;

  // loop principal
  while (!should_quit) {
    SDL_Event event;

    // processamento de eventos
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT:
        should_quit = true;
        break;
      default:
        break;
      }
    }

    // renderização básica
    // define a cor de fundo (cinza/azul escuro)
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    // limpa o buffer de cor
    glClear(GL_COLOR_BUFFER_BIT);

    // troca os buffers, enviando a imagem gerada para a janela (BUGFIX para
    // Linux Desktops com Wayland)
    SDL_GL_SwapWindow(window);
  }
  // Finalização e limpeza de memória
  SDL_GL_DeleteContext(gl_context);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
