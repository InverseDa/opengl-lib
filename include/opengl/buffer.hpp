#pragma once

#include <glad/glad.h>

class Buffer {
private:
  unsigned int m_id;

public:
  Buffer();
  ~Buffer();
};

class G_Buffer : Buffer {};