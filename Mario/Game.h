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

struct Camera {
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 savePos = glm::vec3(0.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
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
	void DrawStats();

	//void Restart();

	// level
	void InitLevelObjects();
	void InitSolidObjects();
	void InitTubes();

	// pub vars
	bool Keys[1024], KeysProcessed[1024], close = false;

	~Game();

private:

	glm::mat4 projection, view = glm::mat4(1.0f);
	Camera camera;

	std::vector<GameObject*> staticObj;
	std::vector<GameObject*> objList;

	int width, height;
	bool toggle = false;
	glm::vec2 cursorPos;

	GameState gmState = MENU;
};

#endif // !GAME_H