#include"game.h"
#include"keyboard.h"
#define _USE_MATH_DEFINES
#include<math.h>

game::game()
{
	// prepere SpriteRender
	glm::mat4 projection = glm::ortho(0.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f, -1.0f, 1.0f);
	spriteShader.Compile("sprite.vs", "sprite.fs", nullptr);
	spriteShader.SetInteger("sprite", 0, true);
	spriteShader.SetMatrix4("projection", projection);
	spriteRender = new SpriteRender(spriteShader);

	// prepere textures
	Texture2D MissileT, PlaneT, BirdT, BomberT, FighterT, MeteorT;
	MissileT.Generate("textures/missile.png", true);
	PlaneT.Generate("textures/plane.png", true);
	BirdT.Generate("textures/bird.png", true);
	BomberT.Generate("textures/bomber.png", true);
	FighterT.Generate("textures/fighter.png", true);
	MeteorT.Generate("textures/meteor.png", true);
	Textures["Missile"] = MissileT;
	Textures["Plane"] = PlaneT;
	Textures["Bird"] = BirdT;
	Textures["Bomber"] = BomberT;
	Textures["Fighter"] = FighterT;
	Textures["Meteor"] = MeteorT;

	// single objects 
	Plane.Compile(PLANE, Textures["Plane"]);
	Meteor.Compile(METEOR, Textures["Meteor"]);
	Meteor.isalive = false;
}

void game::Plane_fire()
{
	for (int i = 1; i < 30; i++)
	{
		if (Missiles.count(i) == 0)
		{
			// new object
			object Missile;
			Missile.Compile(MISSILE, Textures["Missile"]);
			Missile.position.x = Plane.position.x + PLANE_SIZE.x;
			Missile.position.y = Plane.position.y + PLANE_SIZE.y / 2;
			Missiles[i] = Missile;
			break;
		}
		else if (!Missiles[i].isalive)
		{ 
			// reset object
			Missiles[i].position.x = Plane.position.x + PLANE_SIZE.x;
			Missiles[i].position.y = Plane.position.y + PLANE_SIZE.y / 2;
			Missiles[i].isalive = true;
			break;
		}
	}
}
void game::Fighter_fire(int ind)
{
	for (int i = 1; i < 300; i++)
	{
		if (FighterMissiles.count(i) == 0)
		{
			// new object
			object FighterMissile;
			FighterMissile.Compile(ENEMYMISSILE, Textures["Missile"]);
			FighterMissile.position.x = Fighters[ind].position.x;
			FighterMissile.position.y = Fighters[ind].position.y + PLANE_SIZE.y/2;
			FighterMissiles[i] = FighterMissile;
			break;
		}
		else if (!FighterMissiles[i].isalive)
		{
			// reset object
			FighterMissiles[i].position.x = Fighters[ind].position.x;
			FighterMissiles[i].position.y = Fighters[ind].position.y + PLANE_SIZE.y/2;
			FighterMissiles[i].isalive = true;
			break;
		}
	}
}

void game::add_Bird()
{
	for (int i = 1; i < 100; i++)
	{
		if (Birds.count(i) == 0)
		{
			// new object
			object Bird;
			Bird.Compile(ENEMYBIRD, Textures["Bird"]);
			Birds[i] = Bird;
			break;
		}
		else if (!Birds[i].isalive)
		{
			// reset object
			Birds[i].Reset(ENEMYBIRD);
			break;
		}
	}
}
void game::add_Bomber()
{
	for (int i = 1; i < 50; i++)
	{
		if (Bombers.count(i) == 0)
		{
			// new object
			object Bomber;
			Bomber.Compile(ENEMYBOMBER, Textures["Bomber"]);
			Bombers[i] = Bomber;
			break;
		}
		else if (!Bombers[i].isalive)
		{
			// reset object
			Bombers[i].Reset(ENEMYBOMBER);
			break;
		}
	}
}
void game::add_Fighter()
{
	for (int i = 1; i < 20; i++)
	{
		if (Fighters.count(i) == 0)
		{ 
			// new object
			object Fighter;
			Fighter.Compile(ENEMYFIGHTER, Textures["Fighter"]);
			Fighters[i] = Fighter;
			break;
		}
		else if (!Fighters[i].isalive)
		{
			// reset object
			Fighters[i].Reset(ENEMYFIGHTER);
			break;
		}
	}
}
void game::add_Meteor()
{
	if (!Meteor.isalive)
	{
		Meteor.Reset(METEOR);
	}
}

void game::move(GLFWwindow* win, int* sc)
{
	move_plane(win);
	move_missiles();
	move_enemys(sc);
}
void game::draw()
{
	// draw plane
	Plane.Draw(*spriteRender);
	if (Meteor.isalive)
	{
		float rotate = (-180 / M_PI) * asin(Meteor.speed.x / Meteor.speed.y) - 35;
		Meteor.Draw(*spriteRender, rotate);
	}
	for (std::map<int, object>::iterator iter = Missiles.begin(); iter != Missiles.end(); ++iter)
	{
		if (iter->second.isalive)
			iter->second.Draw(*spriteRender);
	}
	for (std::map<int, object>::iterator iter = Birds.begin(); iter != Birds.end(); ++iter)
	{
		if (iter->second.isalive)
			iter->second.Draw(*spriteRender);
	}
	for (std::map<int, object>::iterator iter = Bombers.begin(); iter != Bombers.end(); ++iter)
	{
		if (iter->second.isalive)
			iter->second.Draw(*spriteRender);
	}
	for (std::map<int, object>::iterator iter = Fighters.begin(); iter != Fighters.end(); ++iter)
	{
		if (iter->second.isalive)
			iter->second.Draw(*spriteRender);
	}
	for (std::map<int, object>::iterator iter = FighterMissiles.begin(); iter != FighterMissiles.end(); ++iter)
	{
		if (iter->second.isalive)
			iter->second.Draw(*spriteRender);
	}
}

void game::clear()
{
	Plane.Delete();
	Meteor.Delete();
	for (std::map<int, object>::iterator iter = Missiles.begin(); iter != Missiles.end(); ++iter)
	{
		iter->second.Delete();
	}
	for (std::map<int, object>::iterator iter = Birds.begin(); iter != Birds.end(); ++iter)
	{
		iter->second.Delete();
	}
	for (std::map<int, object>::iterator iter = Bombers.begin(); iter != Bombers.end(); ++iter)
	{
		iter->second.Delete();
	}
	for (std::map<int, object>::iterator iter = Fighters.begin(); iter != Fighters.end(); ++iter)
	{
		iter->second.Delete();
	}
	for (std::map<int, object>::iterator iter = FighterMissiles.begin(); iter != FighterMissiles.end(); ++iter)
	{
		iter->second.Delete();
	}
	Missiles.clear();
	Birds.clear();
	Bombers.clear();
	Fighters.clear();
	FighterMissiles.clear();
}

void game::move_plane(GLFWwindow* win)
{
	// move plane to mouse position
	Plane.position += Plane.speed;
	if (Plane.position.y > WINDOW_HEIGHT - PLANE_SIZE.y - 40)
	{
		Plane.position.y = WINDOW_HEIGHT - PLANE_SIZE.y - 40;
		Plane.speed.y = 0.0f;
	}
	else if (Plane.position.y < 0.0f)
	{
		Plane.position.y = 0.0f;
		Plane.speed.y = 0.0f;
	}
	else Plane_speed_change(win, &Plane);

	if (is_fire && !Plane.reload)
	{
		Plane_fire();
		Plane.reload = 7;
	}
	if (Plane.reload)
		Plane.reload--;
}
void game::move_missiles()
{
	for (std::map<int, object>::iterator iter = Missiles.begin(); iter != Missiles.end(); ++iter)
	{
		iter->second.position += iter->second.speed;
		if (iter->second.position.x >= WINDOW_WIDTH)
			iter->second.Delete();
	}
}
void game::move_enemys(int* sc)
{
	if (Meteor.isalive)
	{
		Meteor.position += Meteor.speed;
		if (Meteor.position.y >= WINDOW_HEIGHT || Meteor.position.x <= -METEOR_SIZE.x ||
			Meteor.position.x >= WINDOW_WIDTH)
			Meteor.Delete();
		else if (collision(Meteor, Plane))
			Plane.isalive = false;
	}
	for (std::map<int, object>::iterator iter = Birds.begin(); iter != Birds.end(); ++iter)
	{
		if (iter->second.isalive)
		{
			iter->second.position.x += iter->second.speed.x;
			iter->second.position.y += 5*sin(iter->second.speed.y);
			iter->second.speed.y *= 1.01;
			if (iter->second.position.x <= -BIRD_SIZE.x)
				iter->second.Delete();
			else if (collision(iter->second, Plane))
				Plane.isalive = false;
		}
	}
	for (std::map<int, object>::iterator iter = Bombers.begin(); iter != Bombers.end(); ++iter)
	{
		if (iter->second.isalive)
		{
			iter->second.position += iter->second.speed;
			if (iter->second.position.x <= -BOMBER_SIZE.x)
				iter->second.Delete();
			else if (collision(iter->second, Plane))
				Plane.isalive = false;
			else if (collision(iter->second, Meteor) && Meteor.isalive)
				iter->second.Delete();
			for (std::map<int, object>::iterator iter2 = Missiles.begin(); iter2 != Missiles.end(); ++iter2)
			{
				if (collision(iter->second, iter2->second) && iter2->second.isalive)
				{
					*sc += iter->second.killScore;
					iter->second.Delete();
					iter2->second.Delete();
				}
			}
		}
	}
	for (std::map<int, object>::iterator iter = Fighters.begin(); iter != Fighters.end(); ++iter)
	{
		if (iter->second.isalive)
		{
			iter->second.position += iter->second.speed;
			if (iter->second.position.x <= -PLANE_SIZE.x)
				iter->second.Delete();
			else if (collision(iter->second, Plane))
				Plane.isalive = false;
			else if (collision(iter->second, Meteor) && Meteor.isalive)
				iter->second.Delete();
			for (std::map<int, object>::iterator iter2 = Missiles.begin(); iter2 != Missiles.end(); ++iter2)
			{
				if (collision(iter->second, iter2->second) && iter2->second.isalive)
				{
					*sc += iter->second.killScore;
					iter->second.Delete();
					iter2->second.Delete();
				}
			}
			if (!iter->second.reload)
			{
				Fighter_fire(iter->first);
				iter->second.reload = 50;
			}
			else iter->second.reload--;
		}
	}
	for (std::map<int, object>::iterator iter = FighterMissiles.begin(); iter != FighterMissiles.end(); ++iter)
	{
		if (iter->second.isalive)
		{
			iter->second.position += iter->second.speed;
			if (iter->second.position.x <= -MISSILE_SIZE.x)
				iter->second.Delete();
			else if (collision(iter->second, Plane))
				Plane.isalive = false;
		}
	}
}

bool game::collision(object A, object B)
{
	bool Xcollision, Ycollision;
	Xcollision = A.position.x + A.size.x >= B.position.x &&
				 B.position.x + B.size.x >= A.position.x;
	Ycollision = A.position.y + A.size.y >= B.position.y &&
				 B.position.y + B.size.y >= A.position.y;
	return Xcollision && Ycollision;
}

