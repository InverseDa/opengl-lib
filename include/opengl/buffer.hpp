#pragma once

#include "glad/glad.h"

#include <iostream>


class FrameBuffer {
  protected:
    int m_width;
    int m_height;
    GLuint m_fbo;
    GLuint m_rbo;
    GLuint m_texture;

  public:
    FrameBuffer(int width, int height);
    ~FrameBuffer();

    void bind();
    void unbind();

    void resize(int width, int height);

    GLuint getTexture() const;
};

class GBuffer {
  protected:
    int m_width;
    int m_height;
    GLuint m_fbo;
    GLuint m_rbo;
    GLuint m_position;
    GLuint m_normal;
    GLuint m_albedoSpec;

  public:
    GBuffer(int width, int height);
    ~GBuffer();

    void bind();
    void unbind();

    void resize(int width, int height);

    GLuint getPosition() const;
    GLuint getNormal() const;
    GLuint getAlbedoSpec() const;
};