#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "TextRenderer.h"
#include "ResourceManager.h"

#include "GameObject.h"
#include "DynamicObject.h"

#include "Brick.h"
#include "Coin.h"
#include "Bullet.h"
#include "Plant.h"
#include "Star.h"

#include "Mario.h"
#include "Goomba.h"
#include "Turtle.h"

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
	
	// resources
	void LoadResources();

	// actions, collisions
	void MoveObjects(float dt);

	void ProcessCollision(float dt);
	void ProcessAnimation(float dt);

	// level
	void InitLevelObjects();
	void InitSolidObjects();
	void InitTubes();
	void InitBricks();
	void InitCoins();

	void SpawnBonus(Brick* brick);
	void SpawnPlant(Brick* brick);
	void SpawnStar(Brick* brick);
	void SpawnCoin(Brick* brick);

	void SpawnEnemies();
	void SpawnGoomba(glm::vec2 position);
	void SpawnTurtle(glm::vec2 position);

	// pub vars
	bool Keys[1024], KeysProcessed[1024], close = false;
	
	// delete, destruct
	void DeleteObjects();

	template <typename T>
	void DeleteObjectFromVector(std::vector<T*>& vector, bool deleteMemory);

	~Game();

private:

	glm::mat4 projection, view = glm::mat4(1.0f);
	Camera camera;

	std::vector<GameObject*> objList;

	std::vector<DynamicObject*> moveableObj;
	std::vector<DynamicObject*> animatedObj;

	std::vector<GameObject*> grounds;
	std::vector<Tube*> tubes;
	std::vector<Brick*> bricks;
	std::vector<Coin*> coins;
	std::vector<Bullet*> bullets;
	std::vector<Plant*> plants;
	std::vector<Star*> stars;

	std::vector<Person*> enemies;
	std::vector<Goomba*> goombas;
	std::vector<Turtle*> turtles;

	int width, height;
	bool toggle = false;
	glm::vec2 cursorPos;

	GameState gmState = MENU;
};

#endif // !GAME_H