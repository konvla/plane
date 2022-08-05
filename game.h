#ifndef GAME
#define GAME

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<map>
#include"object.h"

class game
{
public:
	object Plane;
	std::map<int, object> Missiles;
	std::map<int, object> Birds;
	std::map<int, object> Bombers;
	std::map<int, object> Fighters;
	std::map<int, object> FighterMissiles;
	object Meteor;

	Shader spriteShader;
	SpriteRender* spriteRender;
	std::map<std::string, Texture2D> Textures;

	game();

	void Plane_fire();
	void Fighter_fire(int ind);
	void add_Bird();
	void add_Bomber();
	void add_Fighter();
	void add_Meteor();

	void move(GLFWwindow* win,int* sc);
	void draw();

	void clear();

private:
	void move_plane(GLFWwindow* win);
	void move_missiles();
	void move_enemys(int* sc);
	bool collision(object A, object B);
};

#endif