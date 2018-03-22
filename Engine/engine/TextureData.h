//
//  Author: Shervin Aflatooni
//

#pragma once
#include <vector>

#if defined(GLES2)
  #include <GLES2/gl2.h>
#elif defined(GLES3)
  #include <GLES3/gl3.h>
#else
#define GLEW_STATIC
#undef GLEW_BUILD
  #include <GL/glew.h>
#endif

class TextureData
{
public:
  TextureData(int width, int height, const unsigned char* data, GLenum textureTarget, GLfloat filter);
  virtual ~TextureData(void);

  void createTexture(int width, int height, const unsigned char* data, GLenum textureTarget, GLfloat filter);
  void bind(unsigned int unit) const;

  GLuint getTextureId();

  std::vector<unsigned char> data;
  int width();
  int height();
private:
  GLenum m_textureTarget;
  GLuint m_textureId;

  int m_height;
  int m_width;
};
