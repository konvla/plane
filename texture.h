#ifndef TEXTURE
#define TEXTURE

#include <glad/glad.h>
#include "stb_image.h"

class Texture2D
{
public:
    unsigned int ID;
    unsigned int Width, Height; // width and height of loaded image in pixels
    unsigned int Internal_Format; // format of texture object
    unsigned int Image_Format; // format of loaded image
    unsigned int Wrap_S; // wrapping mode on S axis
    unsigned int Wrap_T; // wrapping mode on T axis
    unsigned int Filter_Min; // filtering mode if texture pixels < screen pixels
    unsigned int Filter_Max; // filtering mode if texture pixels > screen pixels
    
    Texture2D();
    
    void Generate(const char* file, bool alpha);
    void Bind() const;
    void UnBind();
};

#endif