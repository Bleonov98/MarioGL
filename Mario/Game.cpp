#include "Game.h"

#include <irrklang/irrKlang.h>
using namespace irrklang;

TextRenderer* text;

ISoundEngine* sound = irrklang::createIrrKlangDevice();
ISoundSource* music;

GameObject* map;
Mario* player;

 // Loading
void Game::Init()
{
    LoadResources();

    // sound resources
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
    // 
    player = new Mario(glm::vec2(100.0f, this->height - 500.0f), glm::vec2(70.0f), 500.0f, 0.0f, glm::vec3(0.9f));
    player->SetTexture(ResourceManager::GetTexture("mario_right_stand"));
    moveableObj.push_back(player);

    // game objects
    InitLevelObjects();
}

void Game::LoadResources()
{
    // shaders
    ResourceManager::LoadShader("../shaders/vShader.vx", "../shaders/fShader.ft", "spriteShader");

    // - map 
    ResourceManager::LoadTexture("map/MarioMap.png", true, "MainMap");
    ResourceManager::LoadTexture("map/Underground.png", true, "UndergroundMap");
    ResourceManager::LoadTexture("test.png", false, "test");

    // - bricks
    ResourceManager::LoadTexture("brick/brick.png", false, "brick");
    ResourceManager::LoadTexture("brick/underbrick.png", false, "underbrick");

    ResourceManager::LoadTexture("brick/destroyed.png", true, "destroyed_brick");
    ResourceManager::LoadTexture("brick/destroyed_underbrick.png", true, "destroyed_underbrick");
    ResourceManager::LoadTexture("brick/destroyed_solid.png", true, "destroyed_solid");

    ResourceManager::LoadTexture("brick/solid_0.png", true, "solid_0");
    ResourceManager::LoadTexture("brick/solid_1.png", true, "solid_1");
    ResourceManager::LoadTexture("brick/solid_2.png", true, "solid_2");
    // - coins
    ResourceManager::LoadTexture("coin/coin_0.png", true, "coin_0");
    ResourceManager::LoadTexture("coin/coin_1.png", true, "coin_1");
    ResourceManager::LoadTexture("coin/coin_2.png", true, "coin_2");

    ResourceManager::LoadTexture("coin/flip_coin_0.png", true, "flip_coin_0");
    ResourceManager::LoadTexture("coin/flip_coin_1.png", true, "flip_coin_1");
    ResourceManager::LoadTexture("coin/flip_coin_2.png", true, "flip_coin_2");
    // - mario
        // - lil Mario
    ResourceManager::LoadTexture("mario/lil/mario_left_stand.png", true, "mario_left_stand");
    ResourceManager::LoadTexture("mario/lil/mario_right_stand.png", true, "mario_right_stand");
                                        
    ResourceManager::LoadTexture("mario/lil/mario_left_0.png", true, "mario_left_0");
    ResourceManager::LoadTexture("mario/lil/mario_left_1.png", true, "mario_left_1");
    ResourceManager::LoadTexture("mario/lil/mario_left_2.png", true, "mario_left_2");
                                        
    ResourceManager::LoadTexture("mario/lil/mario_right_0.png", true, "mario_right_0");
    ResourceManager::LoadTexture("mario/lil/mario_right_1.png", true, "mario_right_1");
    ResourceManager::LoadTexture("mario/lil/mario_right_2.png", true, "mario_right_2");

    ResourceManager::LoadTexture("mario/lil/mario_left_jump.png", true, "mario_left_jump");
    ResourceManager::LoadTexture("mario/lil/mario_right_jump.png", true, "mario_right_jump");
        // - big Mario
    ResourceManager::LoadTexture("mario/big/big_left_stand.png", true, "big_left_stand");
    ResourceManager::LoadTexture("mario/big/big_right_stand.png", true, "big_right_stand");

    ResourceManager::LoadTexture("mario/big/big_left_duck.png", true, "big_left_duck");
    ResourceManager::LoadTexture("mario/big/big_right_duck.png", true, "big_right_duck");

    ResourceManager::LoadTexture("mario/big/big_left_jump.png", true, "big_left_jump");
    ResourceManager::LoadTexture("mario/big/big_right_jump.png", true, "big_right_jump");

    ResourceManager::LoadTexture("mario/big/big_left_0.png", true, "big_left_0");
    ResourceManager::LoadTexture("mario/big/big_left_1.png", true, "big_left_1");
    ResourceManager::LoadTexture("mario/big/big_left_2.png", true, "big_left_2");
                                        
    ResourceManager::LoadTexture("mario/big/big_right_0.png", true, "big_right_0");
    ResourceManager::LoadTexture("mario/big/big_right_1.png", true, "big_right_1");
    ResourceManager::LoadTexture("mario/big/big_right_2.png", true, "big_right_2");
        // - chief Mario
    ResourceManager::LoadTexture("mario/chief/chief_left_stand.png", true, "chief_left_stand");
    ResourceManager::LoadTexture("mario/chief/chief_right_stand.png", true, "chief_right_stand");
                                        
    ResourceManager::LoadTexture("mario/chief/chief_left_duck.png", true, "chief_left_duck");
    ResourceManager::LoadTexture("mario/chief/chief_right_duck.png", true, "chief_right_duck");
                                        
    ResourceManager::LoadTexture("mario/chief/chief_left_jump.png", true, "chief_left_jump");
    ResourceManager::LoadTexture("mario/chief/chief_right_jump.png", true, "chief_right_jump");
                                        
    ResourceManager::LoadTexture("mario/chief/chief_left_0.png", true, "chief_left_0");
    ResourceManager::LoadTexture("mario/chief/chief_left_1.png", true, "chief_left_1");
    ResourceManager::LoadTexture("mario/chief/chief_left_2.png", true, "chief_left_2");
                                        
    ResourceManager::LoadTexture("mario/chief/chief_right_0.png", true, "chief_right_0");
    ResourceManager::LoadTexture("mario/chief/chief_right_1.png", true, "chief_right_1");
    ResourceManager::LoadTexture("mario/chief/chief_right_2.png", true, "chief_right_2");

    // - smth
}

// Actions
void Game::ProcessInput(float dt)
{
    if (gmState == ACTIVE) {

        // player movement
        if (this->Keys[GLFW_KEY_RIGHT]) player->Action(dt, MOVERIGHT);
        else if (this->Keys[GLFW_KEY_LEFT] && player->GetPos().x > camera.cameraPos.x) player->Action(dt, MOVELEFT);
        else if (this->Keys[GLFW_KEY_DOWN] && player->IsOnGround()) player->Action(dt, DUCK);
        else player->Action(dt, STAND);

        if (this->Keys[GLFW_KEY_SPACE]) player->Jump(dt);

        // collision
        if (player->GetPos().x < camera.cameraPos.x) player->SetPos(glm::vec2(camera.cameraPos.x, player->GetPos().y));
        
        // move screen
        float midScreenX = camera.cameraPos.x + this->width / 2.0f;
        if (player->GetPos().x > midScreenX) camera.cameraPos.x += player->GetPos().x - midScreenX;

        if (this->Keys[GLFW_KEY_P]) gmState = PAUSED;
        
        // Temp - - - - - - - - - - - - - - - - -
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
    else { // - - - - - - - - MENU OR PAUSE
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
        for (auto i : animatedObj)
        {
            if (i->AnimationPlayed(dt) && i->IsOnScreen(camera.cameraPos, glm::vec2(this->width, this->height))) i->PlayAnimation();
        }

        for (auto i : bricks)
        {
            if (i->GetType() == COMMON && i->IsMoving()) i->Move(dt);
        }

        // update borders after position changes
        for (auto i : moveableObj)
        {
            i->UpdateAABB();
        }

        // interactions

        // collisions
        std::vector<GameObject*> groundObjects;
        groundObjects.insert(groundObjects.end(), grounds.begin(), grounds.end());
        groundObjects.insert(groundObjects.end(), tubes.begin(), tubes.end());
        groundObjects.insert(groundObjects.end(), bricks.begin(), bricks.end());

        // ground collision
        for (auto i : moveableObj)
        {
            for (auto j : groundObjects)
            {
                if (i->ProccesGroundCollision(*j)) break;
            }

            i->Drop(dt);
        }

        // top collision
        for (auto i : bricks)
        {
            if (player->ProccesTopCollision(*i)) i->Push(player->GetMarioType() > LITTLE);
        }

        // delete

    }
}

// Render
void Game::Render()
{
    // background/map/stats
    DrawObject(map);
    DrawStats();
    
    // objects
    for (auto i : bricks)
    {
        if (i->GetType() != INVISIBLE && i->IsOnScreen(camera.cameraPos, glm::vec2(this->width, this->height))) DrawObject(i);
    }
    
    for (auto i : coins)
    {
        if (i->IsOnScreen(camera.cameraPos, glm::vec2(this->width, this->height))) DrawObject(i);
    }

    DrawObject(player);

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

void Game::Menu()
{
    text->RenderText("MENU", glm::vec2(this->width / 2.0f - 65.0f, this->height / 2.0f - 116.0f), 1.75f, glm::vec3(0.75f));

    text->RenderText("Start", glm::vec2(this->width / 2.0f - 20.0f, this->height / 2.0f), 1.0f, glm::vec3(1.0f));
    text->RenderText("Exit", glm::vec2(this->width / 2.0f - 20.0f, this->height / 2.0f + 40.0f), 1.0f, glm::vec3(1.0f));

    text->RenderText("->", glm::vec2(cursorPos), 1.0f, glm::vec3(1.0f));
}

// Level  
void Game::InitLevelObjects()
{
    InitSolidObjects();
    InitTubes();
    InitBricks();
    InitCoins();
}

void Game::InitSolidObjects()
{
    // overworld
    GameObject* ground = new GameObject(glm::vec2(0.0f, this->height - 115.0f), glm::vec2(6935.0f, 100.0f), 0.0f, glm::vec3(1.0f));
    ground->SetTexture(ResourceManager::GetTexture("test"));
    objList.push_back(ground);
    grounds.push_back(ground);

    ground = new GameObject(glm::vec2(7130.0f, this->height - 115.0f), glm::vec2(1512.0f, 100.0f), 0.0f, glm::vec3(1.0f));
    ground->SetTexture(ResourceManager::GetTexture("test"));
    objList.push_back(ground);
    grounds.push_back(ground);

    ground = new GameObject(glm::vec2(8942.0f, this->height - 115.0f), glm::vec2(6430.0f, 100.0f), 0.0f, glm::vec3(1.0f));
    ground->SetTexture(ResourceManager::GetTexture("test"));
    objList.push_back(ground);
    grounds.push_back(ground);

    ground = new GameObject(glm::vec2(15572.0f, this->height - 115.0f), glm::vec2(5500.0f, 100.0f), 0.0f, glm::vec3(1.0f));
    ground->SetTexture(ResourceManager::GetTexture("test"));
    objList.push_back(ground);
    grounds.push_back(ground);

    GameObject* brick;
    int st = 0;

    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = st; j < 4; j++)
        {
            brick = new GameObject(glm::vec2(13465.0f + (100 * j), this->height - 180.0f - 65 * i), glm::vec2(100.0f, 65.0f), 0.0f, glm::vec3(1.0f));
            brick->SetTexture(ResourceManager::GetTexture("test"));
            objList.push_back(brick);
            grounds.push_back(brick);
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
            objList.push_back(brick);
            grounds.push_back(brick);
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
            objList.push_back(brick);
            grounds.push_back(brick);
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
            objList.push_back(brick);
            grounds.push_back(brick);
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
            objList.push_back(brick);
            grounds.push_back(brick);
        }
        st++;
    }

    // underworld
    ground = new GameObject(glm::vec2(0.0f, this->height * 2 - 55.0f), glm::vec2(this->width, 50.0f), 0.0f, glm::vec3(1.0f));
    ground->SetTexture(ResourceManager::GetTexture("test"));
    objList.push_back(ground);
    grounds.push_back(ground);

    ground = new GameObject(glm::vec2(0.0f, this->height + 130.0f), glm::vec2(95.0f, this->height - 190.0f), 0.0f, glm::vec3(1.0f));
    ground->SetTexture(ResourceManager::GetTexture("test"));
    objList.push_back(ground);
    grounds.push_back(ground);

    ground = new GameObject(glm::vec2(395.0f, this->height + 650.0f), glm::vec2(700.0f, 180.0f), 0.0f, glm::vec3(1.0f));
    ground->SetTexture(ResourceManager::GetTexture("test"));
    objList.push_back(ground);
    grounds.push_back(ground);

    ground = new GameObject(glm::vec2(this->width - 95.0f, this->height + 120.0f), glm::vec2(85.0f, 600.0f), 0.0f, glm::vec3(1.0f));
    ground->SetTexture(ResourceManager::GetTexture("test"));
    objList.push_back(ground);
    grounds.push_back(ground);
}

void Game::InitTubes()
{
    // overworld
    Tube* tube = new Tube(glm::vec2(2820.0f, this->height - 240.0f),  glm::vec2(190.0f, 130.0f));
    tube->SetTexture(ResourceManager::GetTexture("test"));
    tubes.push_back(tube);
    objList.push_back(tube);

    tube = new Tube(glm::vec2(3825.0f, this->height - 300.0f), glm::vec2(190.0f, 190.0f));
    tube->SetTexture(ResourceManager::GetTexture("test"));
    tubes.push_back(tube);
    objList.push_back(tube);

    tube = new Tube(glm::vec2(4625.0f, this->height - 370.0f), glm::vec2(190.0f, 260.0f));
    tube->SetTexture(ResourceManager::GetTexture("test"));
    tubes.push_back(tube);
    objList.push_back(tube);

    tube = new Tube(glm::vec2(5730.0f, this->height - 370.0f), glm::vec2(190.0f, 260.0f));
    tube->SetTexture(ResourceManager::GetTexture("test"));
    tubes.push_back(tube);
    objList.push_back(tube);

    tube = new Tube(glm::vec2(16385.0f, this->height - 240.0f), glm::vec2(190.0f, 125.0f));
    tube->SetTexture(ResourceManager::GetTexture("test"));
    tubes.push_back(tube);
    objList.push_back(tube);

    tube = new Tube(glm::vec2(17990.0f, this->height - 240.0f), glm::vec2(190.0f, 125.0f));
    tube->SetTexture(ResourceManager::GetTexture("test"));
    tubes.push_back(tube);
    objList.push_back(tube);

    // underworld
    tube = new Tube(glm::vec2(this->width - 300.0f, this->height * 2 - 180.0f), glm::vec2(300.0f, 125.0f));
    tube->SetTexture(ResourceManager::GetTexture("test"));
    tubes.push_back(tube);
    objList.push_back(tube);
}

void Game::InitBricks()
{
    BrickType type = COMMON;
    float addHeight = 0.0f, addWidth = 0.0f;

    Brick* brick = new Brick(glm::vec2(1605.0f, 525.0f), glm::vec2(102.0f, 65.0f), SOLID);
    bricks.push_back(brick);
    animatedObj.push_back(brick);
    objList.push_back(brick);

    brick = new Brick(glm::vec2(2210.0f, 267.0f), glm::vec2(102.0f, 65.0f), SOLID);
    bricks.push_back(brick);
    animatedObj.push_back(brick);
    objList.push_back(brick);

    for (size_t i = 0; i < 5; i++)
    {
        if (i == 1 || i == 3) type = SOLID;
        else type = COMMON;

        brick = new Brick(glm::vec2(2010.0f + 102.0f * i, 525.0f), glm::vec2(102.0f, 65.0f), type);
        objList.push_back(brick);
        bricks.push_back(brick);
        if (type == SOLID) animatedObj.push_back(brick);
    }

    brick = new Brick(glm::vec2(6430.0f, 462.0f), glm::vec2(102.0f, 65.0f), INVISIBLE);
    bricks.push_back(brick);
    objList.push_back(brick);

    for (size_t i = 0; i < 15; i++)
    {
        if (i == 1 || i == 14) type = SOLID;
        else type = COMMON;

        if (i == 3) addHeight = 255.0f;
        if (i == 11) addWidth = 295.0f;

        brick = new Brick(glm::vec2(7730.0f + 102.0f * i + addWidth, 525.0f - addHeight), glm::vec2(102.0f, 65.0f), type);
        bricks.push_back(brick);
        objList.push_back(brick);
        if (type == SOLID) animatedObj.push_back(brick);
    }

    brick = new Brick(glm::vec2(9445.0f, 525.0f), glm::vec2(102.0f, 65.0f), COMMON);
    bricks.push_back(brick);
    objList.push_back(brick);

    for (size_t i = 0; i < 2; i++)
    {
        brick = new Brick(glm::vec2(10045.0f + 102.0f * i, 525.0f), glm::vec2(102.0f, 65.0f), COMMON);
        bricks.push_back(brick);
        objList.push_back(brick);
    }

    for (size_t i = 0; i < 3; i++)
    {
        brick = new Brick(glm::vec2(10650.0f + 300.0f * i, 525.0f), glm::vec2(102.0f, 65.0f), SOLID);
        bricks.push_back(brick);
        objList.push_back(brick);
        animatedObj.push_back(brick);
    }

    brick = new Brick(glm::vec2(10950.0f, 267.0f), glm::vec2(102.0f, 65.0f), SOLID);
    bricks.push_back(brick);
    objList.push_back(brick);
    animatedObj.push_back(brick);

    brick = new Brick(glm::vec2(11860.0f, 525.0f), glm::vec2(102.0f, 65.0f), SOLID);
    bricks.push_back(brick);
    objList.push_back(brick);
    animatedObj.push_back(brick);

    addWidth = 0.0f;
    for (size_t i = 0; i < 7; ++i)
    {
        if (i == 3) addWidth = 400.0f;
        if (i == 4 || i == 5) type = SOLID;
        else type = COMMON;

        brick = new Brick(glm::vec2(12155.0f + 102.0f * i + addWidth, 267.0f), glm::vec2(102.0f, 65.0f), type);
        bricks.push_back(brick);
        objList.push_back(brick);
        if (type == SOLID) animatedObj.push_back(brick);
    }

    for (size_t i = 0; i < 2; ++i)
    {
        brick = new Brick(glm::vec2(12960.0f + 102.0f * i, 525.0f), glm::vec2(102.0f, 65.0f), COMMON);
        bricks.push_back(brick);
        objList.push_back(brick);
    }

    for (size_t i = 0; i < 4; ++i)
    {
        if (i == 2) type = SOLID;
        else type = COMMON;

        brick = new Brick(glm::vec2(16880.0f + 102.0f * i, 525.0f), glm::vec2(102.0f, 65.0f), type);
        bricks.push_back(brick);
        objList.push_back(brick);
        if (type == SOLID) animatedObj.push_back(brick);
    }

    // underworld
    for (size_t i = 0; i < 7; i++)
    {
        brick = new Brick(glm::vec2(398.0f + 102.0f * i, this->height + 121.0f), glm::vec2(102.0f, 65.0f), COMMON);
        bricks.push_back(brick);
        objList.push_back(brick);
    }
}

void Game::InitCoins()
{
    Coin* coin;

    for (size_t i = 0; i < 3; ++i)
    {
        for (size_t j = 0; j < 7; ++j)
        {
            if (i == 0 && (j == 0 || j == 6)) continue;

            coin = new Coin(glm::vec2(415.0f + 100.0f * j, this->height + 325.0f + 130.0f * i), glm::vec2(60.0f, 60.0f));
            objList.push_back(coin);
            animatedObj.push_back(coin);
            coins.push_back(coin);
        }
    }
   
}
// - - - - - - - - - - - - - - -

void Game::DeleteObjects()
{
    DeleteObjectFromVector(animatedObj, false);
    DeleteObjectFromVector(moveableObj, false);

    DeleteObjectFromVector(tubes, false);
    DeleteObjectFromVector(coins, false);
    DeleteObjectFromVector(bricks, false);

    DeleteObjectFromVector(objList, true);
}

template <typename T>
void Game::DeleteObjectFromVector(std::vector<T*>& vector, bool deleteMemory)
{
    for (auto i = vector.begin(); i != vector.end();)
    {
        if ((*i)->IsDeleted()) {
            if (deleteMemory) delete *i;
            i = vector.erase(i);
        }
        else ++i;
    }
}

Game::~Game()
{
    // tools
    delete text;
    delete sound;

    delete map;

    // objects
    delete player;

    // lists
    for (size_t i = 0; i < objList.size(); ++i)
    {
        delete objList[i];
    }
    objList.clear();
    animatedObj.clear();
    moveableObj.clear();

    grounds.clear();
    tubes.clear();
    bricks.clear();
    coins.clear();
    // ---------
}
