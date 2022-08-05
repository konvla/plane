#include "texture.h"

Texture2D::Texture2D(): Width(0), Height(0), Internal_Format(GL_RGB), Image_Format(GL_RGB),
                        Wrap_S(GL_REPEAT), Wrap_T(GL_REPEAT), Filter_Min(GL_LINEAR), Filter_Max(GL_LINEAR)
{
    glGenTextures(1, &ID);
}

void Texture2D::Generate(const char* file, bool alpha)
{
    if (alpha)
    {
        Internal_Format = GL_RGBA;
        Image_Format = GL_RGBA;
    }
    // load image
    int width, height, nrChannels;
    unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);
   
    // generate texture
    Width = width;
    Height = height;
    // create Texture
    glBindTexture(GL_TEXTURE_2D, ID);
    glTexImage2D(GL_TEXTURE_2D, 0, Internal_Format, width, height, 0, Image_Format, GL_UNSIGNED_BYTE, data);
    // set Texture wrap and filter modes
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, Wrap_S);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, Wrap_T);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, Filter_Min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, Filter_Max);
    // unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);

    // free image data
    stbi_image_free(data);
}

void Texture2D::Bind() const
{
    glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture2D::UnBind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
