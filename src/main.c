#include <SDL2/SDL_events.h>
#include <glad/glad.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

int main(int argc, char *argv[]) {
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("ERRO: nao pode iniciar SDL: %s\n", SDL_GetError());
    exit(1);
  }

  SDL_Window *window =
      SDL_CreateWindow("Shooter Platformer", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);

  if (!window) {
    printf("ERRO: não pode criar janela: %s\n", SDL_GetError());
    exit(1);
  }

  SDL_GL_CreateContext(window);
  if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
    printf("ERRO: não pode carregar o GL: %s\n", SDL_GetError());
    exit(1);
  }

  puts("OpenGL Carregou");
  printf("Vendor:   %s\n", glGetString(GL_VENDOR));
  printf("Renderer:   %s\n", glGetString(GL_RENDERER));
  printf("Version:   %s\n", glGetString(GL_VERSION));

  bool should_quit = false;
  while (!should_quit) {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT:
        should_quit = true;
        break;
      default:
        break;
      }
    }
  }

  return 0;
}
