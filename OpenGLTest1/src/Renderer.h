#pragma once

#include <GL/glew.h>

#define ASSERT(x) if (!(x)) __debugbreak();

#define GLCall(x) GLClearError();x;ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();

// int will be returned but the errors can be found in glew.h but in hexadecimal format :: convert error code to hexadecimal 
bool GLLogCall(const char* function, const char* file, int line);
