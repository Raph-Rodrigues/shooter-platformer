#include <SDL2/SDL_stdinc.h>
#include <glad/glad.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "../io/io.h"
#include "../util.h"
#include "render_internal.h"

u32 render_shader_create(const char *path_vert, const char *path_frag) {
  int success;
  char log[512];

  File file_vertex = io_file_read(path_vert);
  if (!file_vertex.is_valid) {
    ERROR_EXIT("ERRO ao ler shader: %s\n", path_vert);
  }

  u32 shader_vertex = glCreateShader(GL_VERTEX_SHADER);
  const char *vertex_source = file_vertex.data;
  glShaderSource(shader_vertex, 1, &vertex_source, NULL);
  glCompileShader(shader_vertex);
  glGetShaderiv(shader_vertex, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader_vertex, 512, NULL, log);
    ERROR_EXIT("ERRO ao compilar vertex shader: %s\n", log);
  }

  File file_fragment = io_file_read(path_frag);
  if (!file_fragment.is_valid) {
    ERROR_EXIT("ERRO ao ler shader: %s\n", path_frag);
  }

  u32 shader_fragment = glCreateShader(GL_FRAGMENT_SHADER);
  const char *fragment_source = file_fragment.data;
  glShaderSource(shader_fragment, 1, &fragment_source, NULL);
  glCompileShader(shader_fragment);
  glGetShaderiv(shader_fragment, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader_fragment, 512, NULL, log);
    ERROR_EXIT("ERRO ao compilar fragment shader: %s\n", log);
  }

  u32 shader = glCreateProgram();
  glAttachShader(shader, shader_vertex);
  glAttachShader(shader, shader_fragment);
  glLinkProgram(shader);
  glGetProgramiv(shader, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shader, 512, NULL, log);
    ERROR_EXIT("ERRO ao linkar o shader: %s\n", log);
  }

  free(file_vertex.data);
  free(file_fragment.data);

  return shader;
}
