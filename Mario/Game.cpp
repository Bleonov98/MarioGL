#include "Game.h"

#include <irrklang/irrKlang.h>
using namespace irrklang;

TextRenderer* text;
ISoundEngine* sound = irrklang::createIrrKlangDevice();

GameObject* map;

void Game::Init()
{
    // resources
    ResourceManager::LoadShader("../shaders/vShader.vx", "../shaders/fShader.ft", "spriteShader");

    ResourceManager::LoadTexture("../textures/map/MarioMap.png", false, "MainMap");
    ResourceManager::LoadTexture("../textures/map/Underground.png", false, "UndergroundMap");

    ISoundSource* music = sound->addSoundSourceFromFile("../sounds/overworld.mp3");
    music->setDefaultVolume(0.5f);

    // tools
    projection = glm::ortho(0.0f, static_cast<float>(this->width), static_cast<float>(this->height), 0.0f, -1.0f, 1.0f);
    view = glm::lookAt(camera.cameraPos, camera.cameraPos + camera.cameraFront, camera.cameraUp);

    text = new TextRenderer(this->width, this->height);
    text->Load("../fonts/Teko-Bold.ttf", 32);

    sound->play2D(music, true);

    cursorPos = glm::vec2(this->width / 2.0f - 50.0f, this->height / 2.0f);

    // background/map
    map = new GameObject(glm::vec2(0.0f), glm::vec2(21200.0f, this->height));
    map->SetTexture(ResourceManager::GetTexture("MainMap"));

    // game objects
}

void Game::Menu()
{
    text->RenderText("MENU", glm::vec2(this->width / 2.0f - 65.0f, this->height / 2.0f - 116.0f), 1.75f, glm::vec3(0.75f));

    text->RenderText("Start", glm::vec2(this->width / 2.0f - 20.0f, this->height / 2.0f), 1.0f, glm::vec3(1.0f));
    text->RenderText("Exit", glm::vec2(this->width / 2.0f - 20.0f, this->height / 2.0f + 40.0f), 1.0f, glm::vec3(1.0f));

    text->RenderText("->", glm::vec2(cursorPos), 1.0f, glm::vec3(1.0f));
} 

void Game::ProcessInput(float dt)
{
    if (gmState == ACTIVE) {
        if (this->Keys[GLFW_KEY_RIGHT]) camera.cameraPos.x += 1.0f;
        if (this->Keys[GLFW_KEY_LEFT] && camera.cameraPos.x > 0.0f) camera.cameraPos.x -= 1.0f;
        if (this->Keys[GLFW_KEY_SPACE]) gmState = PAUSED;
    }
    else {
        if (this->Keys[GLFW_KEY_UP] && !this->KeysProcessed[GLFW_KEY_UP] && cursorPos.y > this->height / 2.0f) {
            cursorPos.y -= 40.0f;
            this->KeysProcessed[GLFW_KEY_UP] = true;
        }
        else if (this->Keys[GLFW_KEY_DOWN] && !this->KeysProcessed[GLFW_KEY_DOWN] && cursorPos.y < this->height / 2.0f + 40.0f) {
            cursorPos.y += 40.0f;
            this->KeysProcessed[GLFW_KEY_DOWN] = true;
        }
        else if (this->Keys[GLFW_KEY_ENTER]) {
            if (cursorPos.y == this->height / 2.0f) gmState = ACTIVE;
            else if (cursorPos.y == this->height / 2.0f + 40.0f) close = true;
        }
    }
}

void Game::Update(float dt)
{
    if (gmState == ACTIVE) {

        // actions

        // update borders after position changes
        for (auto i : objList)
        {
            i->UpdateAABB();
        }

        // interactions
    }
}

void Game::Render()
{
    // background/map/stats
    DrawObject(map);

    DrawStats();

    if (gmState != ACTIVE) Menu();
}

void Game::DrawObject(GameObject* obj)
{
    ResourceManager::GetShader("spriteShader").Use();

    ResourceManager::GetShader("spriteShader").SetMatrix4("projection", projection);

    view = glm::lookAt(camera.cameraPos, camera.cameraPos + camera.cameraFront, camera.cameraUp);
    ResourceManager::GetShader("spriteShader").SetMatrix4("view", view);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(obj->GetPos(), 1.0f));

    model = glm::translate(model, glm::vec3(0.5f * obj->GetSize().x, 0.5f * obj->GetSize().y, 0.0f));
    model = glm::rotate(model, glm::radians(obj->GetAngle()), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * obj->GetSize().x, -0.5f * obj->GetSize().y, 0.0f));

    model = glm::scale(model, glm::vec3(obj->GetSize(), 1.0f));

    ResourceManager::GetShader("spriteShader").SetMatrix4("model", model);
    ResourceManager::GetShader("spriteShader").SetVector3f("spriteColor", obj->GetColor());

    if (gmState != ACTIVE) ResourceManager::GetShader("spriteShader").SetBool("menu", true);
    else ResourceManager::GetShader("spriteShader").SetBool("menu", false);

    obj->DrawObject();
}

void Game::DrawStats()
{
    glm::vec3 color(1.0f);
    if (gmState != ACTIVE) color = glm::vec3(0.5f);

    text->RenderText("M A R I O", glm::vec2(150.0f, 20.0f), 1.25f, color);
    text->RenderText("0 0 0 0 0 0", glm::vec2(150.0f, 50.0f), 1.25f, color);
    
    
    text->RenderText("x 0 0", glm::vec2(550.0f, 50.0f), 1.25f, color);

    text->RenderText("T I M E", glm::vec2(this->width - 200.0f, 20.0f), 1.25f, color);
    text->RenderText("0 0 0", glm::vec2(this->width - 180.0f, 50.0f), 1.25f, color);
}

Game::~Game()
{
    delete text;
    delete sound;
    delete map;

    for (auto i : objList)
    {
        delete i;
    }
    objList.clear();
    // -----
}
