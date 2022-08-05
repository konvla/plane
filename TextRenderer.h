#ifndef TEXTRENDER
#define TEXTRENDER

#include <ft2build.h>
#include FT_FREETYPE_H
#include <map>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "texture.h"
#include "shader.h"

struct Character
{
    unsigned int TextureID; // ID handle of the glyph texture
    glm::ivec2   Size;      // size of glyph
    glm::ivec2   Bearing;   // offset from baseline to left/top of glyph
    unsigned int Advance;   // horizontal offset to advance to next glyph
};

class TextRenderer
{
public:
    // holds a list of pre-compiled Characters
    std::map<char, Character> Characters;
    Shader TextShader;
    
    TextRenderer(unsigned int width, unsigned int height);
    
    void Load(std::string font, unsigned int fontSize);
    void RenderText(std::string text, float x, float y, float scale, glm::vec3 color = glm::vec3(1.0f));

private:
    unsigned int VAO, VBO;
};

extern TextRenderer* Text;
extern TextRenderer* Text2;

#endif