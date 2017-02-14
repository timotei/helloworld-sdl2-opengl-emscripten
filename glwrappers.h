// Copyright 2015 Red Blob Games <redblobgames@gmail.com>
// License: Apache v2.0 <http://www.apache.org/licenses/LICENSE-2.0.html>

/** Convenience functions, plus RAII wrappers for SDL and GL objects that
 * come in construct/destroy pairs.
 */
#ifndef GLWRAPPERS_H
#define GLWRAPPERS_H

// NOTE(amitp): Mac doesn't have OpenGL ES headers, and the path to GL
// headers is different. This header file handles the
// platform-specific paths.

#include <SDL2/SDL.h>
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glext.h>
#else
#include <SDL2/SDL_opengles2.h>
#endif

#include "common.h"

// Check for any OpenGL errors and print them
void GLERRORS(const char* label);


SDL_Surface* CreateRGBASurface(int width, int height);


struct ShaderProgram: nocopy {
  GLuint id;
  ShaderProgram(const char* vertex_shader, const char* fragment_shader);
  ~ShaderProgram();
  
private:
  void AttachShader(GLenum type, const GLchar* source);
};


struct Texture: nocopy {
  GLuint id;
  Texture(SDL_Surface* surface = nullptr);
  ~Texture();
  void CopyFromPixels(int width, int height, GLenum format, void* pixels);
  void CopyFromSurface(SDL_Surface* surface);
};


struct VertexBuffer: nocopy {
  GLuint id;
  VertexBuffer();
  ~VertexBuffer();
};


struct GlContext: nocopy {
  SDL_GLContext id;
  GlContext(SDL_Window* window);
  ~GlContext();
};


#endif
