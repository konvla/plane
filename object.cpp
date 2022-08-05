#include"object.h"

void object::Compile(int Type, Texture2D Tex)
{
	// set texture
	Texture = Tex;

	// set other parameters depends on object type
	set_stat_param(Type);
	if (Type != PLANE && Type != MISSILE && Type != ENEMYMISSILE)
	{
		set_rnd_param(Type);
	}
	
	isalive = true;
}

void object::Delete()
{
	Texture.UnBind();
	isalive = false;
}

void object::Draw(SpriteRender& render, float rotate)
{
	render.DrawSprite(Texture, position, size, rotate, color);
}

void object::Reset(int Type)
{
	Texture.Bind();
	set_rnd_param(Type);
	isalive = true;
}

void object::set_stat_param(int Type)
{
	switch (Type)
	{
	case PLANE:
	{
		position.x = WINDOW_WIDTH / 7;
		position.y = WINDOW_HEIGHT / 2;
		speed.x = speed.y = 0.0f;
		size = PLANE_SIZE;
		color = glm::vec3(0.4f, 1.0f, 0.7f);
		reload = 1;
		break;
	}
	case ENEMYBIRD:
	{
		size = BIRD_SIZE;
		color = glm::vec3(0.4f, 0.2f, 1.0f);
		killScore = 1;	//not used
		break;
	}
	case ENEMYBOMBER:
	{
		size = BOMBER_SIZE;
		color = glm::vec3(0.6f, 0.6f, 0.0f);
		killScore = 10;
		break;
	}
	case ENEMYFIGHTER:
	{
		size = PLANE_SIZE;
		color = glm::vec3(0.5f, 0.0f, 0.5f);
		killScore = 25;
		reload = 10;
		break;
	}
	case METEOR:
	{
		size = METEOR_SIZE;
		color = glm::vec3(1.0f, 0.7f, 0.7f);
		break;
	}
	case MISSILE:
	{
		// position depends on curent plane position
		speed.x = 20.0f;
		speed.y = 1.0f;
		size = MISSILE_SIZE;
		color = glm::vec3(0.0f, 1.0f, 0.0f);
		break;
	}
	case ENEMYMISSILE:
	{
		// position depends on curent owner position
		speed.x = -20.0f;
		speed.y = 1.0f;
		size = MISSILE_SIZE;
		color = glm::vec3(1.0f, 0.0f, 0.0f);
		break;
	}
	default:
		break;
	}
}

void object::set_rnd_param(int Type)
{
	float minX, minY, maxX, maxY;  // random speed
	float minH, maxH, minG, maxG;  // random start hight and gorisontal position
	switch (Type)
	{
	case ENEMYBIRD:
	{
		minX = -4.0f;
		minY = -10.0f; // will be in sin
		maxX = maxY = -1.0f;
		minH = WINDOW_HEIGHT / 1.4f;
		maxH = WINDOW_HEIGHT - BIRD_SIZE.y;
		minG = maxG = WINDOW_WIDTH;
		break;
	}
	case ENEMYBOMBER:
	{
		minY = maxY = 0.0f;
		minX = -15.0f;
		maxX = -5.0f;
		minH = 1.0f;
		maxH = WINDOW_HEIGHT / 2;
		minG = maxG = WINDOW_WIDTH;
		break;
	}
	case ENEMYFIGHTER:
	{
		minY = maxY = 0.0f;
		minX = -10.0f;
		maxX = -2.0f;
		minH = 2.0f;
		maxH = WINDOW_HEIGHT - 2 * PLANE_SIZE.y;
		minG = maxG = WINDOW_WIDTH;
		break;
	}
	case METEOR:
	{
		minY = 30.0f;
		maxY = 10.0f;
		minX = -1.0f;
		maxX = 10.0f;
		minH = maxH = -METEOR_SIZE.y;
		minG = WINDOW_WIDTH / 4;
		maxG = WINDOW_WIDTH - 2 * METEOR_SIZE.x;
		break;
	}
	default:
		break;
	}
	position.x = minG + static_cast<float>(rand()) * static_cast<float>(maxG - minG) / RAND_MAX;;
	position.y = minH + static_cast<float>(rand()) * static_cast<float>(maxH - minH) / RAND_MAX;;
	speed.x = minX + static_cast<float>(rand()) * static_cast<float>(maxX - minX) / RAND_MAX;;
	speed.y = minY + static_cast<float>(rand()) * static_cast<float>(maxY - minY) / RAND_MAX;;
}