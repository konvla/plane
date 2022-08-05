#ifndef OBJECT
#define OBJECT

#include<glad/glad.h>
#include"main.h"
#include"spriteRender.h"

const glm::vec2 PLANE_SIZE(180.0f, 80.0f);
const glm::vec2 BIRD_SIZE(60.0f);
const glm::vec2 BOMBER_SIZE(200.0f);
const glm::vec2 METEOR_SIZE(120.0f);
const glm::vec2 MISSILE_SIZE(30.0f);

class object
{
public:
	glm::vec2 position;
	glm::vec2 size;
	glm::vec2 speed;
	glm::vec3 color;

	bool isalive;
	int killScore;
	int reload;

	Texture2D Texture;

	void Compile(int Type, Texture2D Tex);

	void Delete();
	void Draw(SpriteRender& render, float rotate = 0.0f);
	void Reset(int Type);
private:
	void set_stat_param(int Type);
	void set_rnd_param(int Type);
};

#endif




