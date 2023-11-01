#include "Game.h"

#include <irrklang/irrKlang.h>
using namespace irrklang;

TextRenderer* text;

ISoundEngine* sound = irrklang::createIrrKlangDevice();
ISoundSource* music;

GameObject* map;

void Game::Init()
{
    // resources
    ResourceManager::LoadShader("../shaders/vShader.vx", "../shaders/fShader.ft", "spriteShader");

    ResourceManager::LoadTexture("../textures/map/MarioMap.png", true, "MainMap");
    ResourceManager::LoadTexture("../textures/map/Underground.png", true, "UndergroundMap");
    ResourceManager::LoadTexture("../textures/test.png", false, "test");

    music = sound->addSoundSourceFromFile("../sounds/underworld.mp3");
    music = sound->addSoundSourceFromFile("../sounds/overworld.mp3");
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
    InitLevelObjects();
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
        if (this->Keys[GLFW_KEY_RIGHT] && camera.cameraPos.x < 19530.0f && !toggle) camera.cameraPos.x += 1.0f;
        if (this->Keys[GLFW_KEY_LEFT] && camera.cameraPos.x > 0.0f) camera.cameraPos.x -= 1.0f;
        if (this->Keys[GLFW_KEY_SPACE]) gmState = PAUSED;
        if (this->Keys[GLFW_KEY_L] && !this->KeysProcessed[GLFW_KEY_L]) {
            
            toggle = !toggle;
            this->KeysProcessed[GLFW_KEY_L] = true;

            sound->stopAllSoundsOfSoundSource(music);

            if (toggle) {
                map->SetSize(glm::vec2(this->width, this->height));
                map->SetPos(glm::vec2(0.0f, this->height));
                map->SetTexture(ResourceManager::GetTexture("UndergroundMap"));

                music = sound->getSoundSource("../sounds/underworld.mp3");

                camera.savePos = camera.cameraPos;
                camera.cameraPos = glm::vec3(0.0f, this->height, 1.0f);
            }
            else {
                map->SetSize(glm::vec2(21200.0f, this->height));
                map->SetPos(glm::vec2(0.0f));
                map->SetTexture(ResourceManager::GetTexture("MainMap"));

                music = sound->getSoundSource("../sounds/overworld.mp3");

                camera.cameraPos = camera.savePos;
            }

            sound->play2D(music, true);
        }
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
    
    // static objects test
    //for (auto i : staticObj)
    //{
    //    DrawObject(i);
    //}

    // objects
    for (auto i : objList)
    {
        DrawObject(i);
    }

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


    text->RenderText(std::to_string(camera.cameraPos.x), glm::vec2(this->width - 180.0f, 100.0f), 1.0f, color);
}

void Game::InitLevelObjects()
{
    InitSolidObjects();
    InitTubes();
}

void Game::InitSolidObjects()
{
    // overworld
    GameObject* ground = new GameObject(glm::vec2(0.0f, this->height - 115.0f), glm::vec2(6935.0f, 100.0f), 0.0f, glm::vec3(1.0f));
    ground->SetTexture(ResourceManager::GetTexture("test"));
    staticObj.push_back(ground);

    ground = new GameObject(glm::vec2(7130.0f, this->height - 115.0f), glm::vec2(1512.0f, 100.0f), 0.0f, glm::vec3(1.0f));
    ground->SetTexture(ResourceManager::GetTexture("test"));
    staticObj.push_back(ground);

    ground = new GameObject(glm::vec2(8942.0f, this->height - 115.0f), glm::vec2(6430.0f, 100.0f), 0.0f, glm::vec3(1.0f));
    ground->SetTexture(ResourceManager::GetTexture("test"));
    staticObj.push_back(ground);

    ground = new GameObject(glm::vec2(15572.0f, this->height - 115.0f), glm::vec2(5500.0f, 100.0f), 0.0f, glm::vec3(1.0f));
    ground->SetTexture(ResourceManager::GetTexture("test"));
    staticObj.push_back(ground);

    GameObject* brick;
    int st = 0;

    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = st; j < 4; j++)
        {
            brick = new GameObject(glm::vec2(13465.0f + (100 * j), this->height - 180.0f - 65 * i), glm::vec2(100.0f, 65.0f), 0.0f, glm::vec3(1.0f));
            brick->SetTexture(ResourceManager::GetTexture("test"));
            staticObj.push_back(brick);
        }
        st++;
    }

    st = 4;
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < st; j++)
        {
            brick = new GameObject(glm::vec2(14065.0f + (100 * j), this->height - 180.0f - 65 * i), glm::vec2(100.0f, 65.0f), 0.0f, glm::vec3(1.0f));
            brick->SetTexture(ResourceManager::GetTexture("test"));
            staticObj.push_back(brick);
        }
        st--;
    }

    st = 0;
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = st; j < 5; j++)
        {
            brick = new GameObject(glm::vec2(14870.0f + (100 * j), this->height - 180.0f - 65 * i), glm::vec2(100.0f, 65.0f), 0.0f, glm::vec3(1.0f));
            brick->SetTexture(ResourceManager::GetTexture("test"));
            staticObj.push_back(brick);
        }
        st++;
    }

    st = 4;
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < st; j++)
        {
            brick = new GameObject(glm::vec2(15570.0f + (100 * j), this->height - 180.0f - 65 * i), glm::vec2(100.0f, 65.0f), 0.0f, glm::vec3(1.0f));
            brick->SetTexture(ResourceManager::GetTexture("test"));
            staticObj.push_back(brick);
        }
        st--;
    }


    st = 0;
    for (size_t i = 0; i < 8; i++)
    {
        for (size_t j = st; j < 9; j++)
        {
            brick = new GameObject(glm::vec2(18185.0f + (100 * j), this->height - 180.0f - 65 * i), glm::vec2(100.0f, 65.0f), 0.0f, glm::vec3(1.0f));
            brick->SetTexture(ResourceManager::GetTexture("test"));
            staticObj.push_back(brick);
        }
        st++;
    }

    // underworld
    ground = new GameObject(glm::vec2(0.0f, this->height * 2 - 55.0f), glm::vec2(this->width, 50.0f), 0.0f, glm::vec3(1.0f));
    ground->SetTexture(ResourceManager::GetTexture("test"));
    staticObj.push_back(ground);

    ground = new GameObject(glm::vec2(0.0f, this->height + 130.0f), glm::vec2(95.0f, this->height - 190.0f), 0.0f, glm::vec3(1.0f));
    ground->SetTexture(ResourceManager::GetTexture("test"));
    staticObj.push_back(ground);

    ground = new GameObject(glm::vec2(395.0f, this->height + 650.0f), glm::vec2(700.0f, 180.0f), 0.0f, glm::vec3(1.0f));
    ground->SetTexture(ResourceManager::GetTexture("test"));
    staticObj.push_back(ground);

    ground = new GameObject(glm::vec2(this->width - 95.0f, this->height + 120.0f), glm::vec2(85.0f, 600.0f), 0.0f, glm::vec3(1.0f));
    ground->SetTexture(ResourceManager::GetTexture("test"));
    staticObj.push_back(ground);
}

void Game::InitTubes()
{
    // overworld
    Tube* tube = new Tube(glm::vec2(2820.0f, this->height - 240.0f),  glm::vec2(190.0f, 130.0f));
    tube->SetTexture(ResourceManager::GetTexture("test"));
    staticObj.push_back(tube);

    tube = new Tube(glm::vec2(3825.0f, this->height - 300.0f), glm::vec2(190.0f, 190.0f));
    tube->SetTexture(ResourceManager::GetTexture("test"));
    staticObj.push_back(tube);

    tube = new Tube(glm::vec2(4625.0f, this->height - 370.0f), glm::vec2(190.0f, 260.0f));
    tube->SetTexture(ResourceManager::GetTexture("test"));
    staticObj.push_back(tube);

    tube = new Tube(glm::vec2(5730.0f, this->height - 370.0f), glm::vec2(190.0f, 260.0f));
    tube->SetTexture(ResourceManager::GetTexture("test"));
    staticObj.push_back(tube);

    tube = new Tube(glm::vec2(16385.0f, this->height - 240.0f), glm::vec2(190.0f, 125.0f));
    tube->SetTexture(ResourceManager::GetTexture("test"));
    staticObj.push_back(tube);

    tube = new Tube(glm::vec2(17990.0f, this->height - 240.0f), glm::vec2(190.0f, 125.0f));
    tube->SetTexture(ResourceManager::GetTexture("test"));
    staticObj.push_back(tube);

    // underworld
    tube = new Tube(glm::vec2(this->width - 300.0f, this->height * 2 - 180.0f), glm::vec2(300.0f, 125.0f));
    tube->SetTexture(ResourceManager::GetTexture("test"));
    staticObj.push_back(tube);
}

Game::~Game()
{
    // tools
    delete text;
    delete sound;

    // objects
    delete map;

    // lists
    for (auto i : staticObj)
    {
        delete i;
    }
    staticObj.clear();
    
    for (auto i : objList)
    {
        delete i;
    }
    objList.clear();
    // ---------
}
