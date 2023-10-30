#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "TextRenderer.h"
#include "ResourceManager.h"
#include "GameObject.h"

enum GameState {
	MENU,
	ACTIVE,
	PAUSED
};

class Game
{
public:

	Game(const int width, const int height) {
		this->width = width, this->height = height;
	}

	// basics
	void Init();
	void Menu();

	void ProcessInput(float dt);
	void Update(float dt);

	void Render();
	void DrawObject(GameObject* obj);
	//void DrawStats();

	//void Restart();

	// game

	// pub vars
	bool Keys[1024], KeysProcessed[1024], close = false;

	~Game();

private:

	glm::mat4 projection;

	std::vector<GameObject*> objList;

	int width, height;
	glm::vec2 cursorPos;

	GameState gmState = MENU;
};

#endif // !GAME_H