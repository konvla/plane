#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include"game.h"
#include"keyboard.h"
#include"TextRenderer.h"

int main()
{
	// Prepare
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	GLFWwindow* win = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "fly", NULL, NULL);
	if (win == NULL)
	{
		std::cout << "Fail" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(win);
	gladLoadGL();
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// callbacks
	glfwSetMouseButtonCallback(win, mouse_button_callback);
	//glfwSetCursorPosCallback(win, cursor_position_callback);

	// Game
	game Game;
	srand(time(NULL));
	int score = 0;
	// weights for random enemy create
	UINT32 wNone=10000, wBird=125, wBomber=10, wFighter=0, wMeteor=0, wsum, rnd;

	Text = new TextRenderer(700, 700);
	Text->Load("fonts/OCRAEXT.TTF", 20);

	while (!glfwWindowShouldClose(win) && Game.Plane.isalive)
	{
		// cleanup
		glClearColor(0.1f, 0.1f, 0.6f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// enemy
		wsum = wNone + wBird + wBomber + wFighter + wMeteor;
		rnd = rand() % wsum;
		if (rnd < wBird)
		{
			Game.add_Bird();
			wBird -= 40;		// do not create too often
			if (wBird < 0)
				wBird = 0;
		}
		else if (rnd < wBird + wBomber)
		{
			Game.add_Bomber();
			wBomber -= 50;
			if (wBomber < 0)
				wBomber = 0;
		}
		else if (rnd < wBird + wBomber + wFighter)
		{
			Game.add_Fighter();
			wFighter -= 50;
			if (wFighter < 0)
				wFighter = 0;
		}
		else if (rnd < wBird + wBomber + wFighter + wMeteor)
		{
			Game.add_Meteor();
			wMeteor -= 100;
			if (wMeteor < 0)
				wMeteor = 0;
		}
		wBird += 2;
		wBomber += 5;
		wFighter++;
		wMeteor++;
		
		Game.move(win, &score);

		Game.draw();

		// score
		std::stringstream ss; ss << score;
		Text->RenderText("score:" + ss.str(), 5.0f, 5.0f, 1.0f);

		// tick
		Sleep(50);
		glfwSwapBuffers(win);
		glfwPollEvents();
	}

	// End
	Game.clear();

	GLFWwindow* Endwin = glfwCreateWindow(400, 200, "END", NULL, NULL);
	if (Endwin == NULL)
	{
		std::cout << "Fail" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(Endwin);
	gladLoadGL();
	Text2 = new TextRenderer(900, 900);
	Text2->Load("fonts/OCRAEXT.TTF", 70);
	glViewport(0, 0, 400, 200);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	while (!glfwWindowShouldClose(Endwin))
	{
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		std::stringstream ss; ss << score;
		Text2->RenderText("SCORE:" + ss.str(), 50, 300, 2.0f, glm::vec3(0.0f));
		glfwSwapBuffers(Endwin);
		glfwPollEvents();
	}

	glfwDestroyWindow(win);
	glfwDestroyWindow(Endwin);
	glfwTerminate();
	return 0;
}