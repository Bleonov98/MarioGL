#include "Game.h"

#include <irrklang/irrKlang.h>
using namespace irrklang;

TextRenderer* text;

ISoundEngine* sound = irrklang::createIrrKlangDevice();
ISoundSource* music;

GameObject* map;
Coin* menuCoin;

Mario* player;

 // Loading
void Game::Init()
{
    if (gmState != LOSS && gmState != WIN) {
    
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
    }

    cursorPos = glm::vec2(this->width / 2.0f - 50.0f, this->height / 2.0f);

    // background/map
    map = new GameObject(glm::vec2(0.0f), glm::vec2(21200.0f, this->height));
    map->SetTexture(ResourceManager::GetTexture("MainMap"));
    // 
    player = new Mario(glm::vec2(100.0f, this->height - 500.0f), glm::vec2(60.0f, 70.0f), 125.0f, false, 0.0f, glm::vec3(0.9f));
    player->SetTexture(ResourceManager::GetTexture("mario_right_stand"));
    moveableObj.push_back(player);

    menuCoin = new Coin(glm::vec2(515.0f, 48.0f), glm::vec2(30.0f), true);
    menuCoin->SetCoinType(COIN_MENU);
    animatedObj.push_back(menuCoin);

    // game objects
    InitLevelObjects();
    SpawnEnemies();
}

void Game::LoadResources()
{
    // shaders
    ResourceManager::LoadShader("../shaders/vShader.vx", "../shaders/fShader.ft", "spriteShader");

    // - map 
    ResourceManager::LoadTexture("map/MarioMap.png", false, "MainMap");
    ResourceManager::LoadTexture("map/Underground.png", true, "UndergroundMap");
    ResourceManager::LoadTexture("test.png", false, "test");

    // - bricks
    ResourceManager::LoadTexture("brick/brick.png", false, "brick");
    ResourceManager::LoadTexture("brick/underbrick.png", false, "underbrick");

    ResourceManager::LoadTexture("brick/destroyed_brick.png", true, "destroyed_brick");
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

    ResourceManager::LoadTexture("coin/menu_coin_0.png", true, "menu_coin_0");
    ResourceManager::LoadTexture("coin/menu_coin_1.png", true, "menu_coin_1");
    ResourceManager::LoadTexture("coin/menu_coin_2.png", true, "menu_coin_2");
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

    ResourceManager::LoadTexture("mario/lil/mario_death.png", true, "mario_death");
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

    // - bullet
    ResourceManager::LoadTexture("bullet/bullet_0.png", true, "bullet_0");
    ResourceManager::LoadTexture("bullet/bullet_1.png", true, "bullet_1");
    ResourceManager::LoadTexture("bullet/bullet_2.png", true, "bullet_2");
    ResourceManager::LoadTexture("bullet/bullet_3.png", true, "bullet_3");

    // - plants
    ResourceManager::LoadTexture("plant/plant_0.png", true, "plant_0");
    ResourceManager::LoadTexture("plant/plant_1.png", true, "plant_1");
    ResourceManager::LoadTexture("plant/plant_2.png", true, "plant_2");
    ResourceManager::LoadTexture("plant/plant_3.png", true, "plant_3");

    ResourceManager::LoadTexture("plant/mushroom_upgrade.png", true, "mushroom_upgrade");
    ResourceManager::LoadTexture("plant/mushroom_life.png", true, "mushroom_life");

    // - stars
    ResourceManager::LoadTexture("star/star_0.png", true, "star_0");
    ResourceManager::LoadTexture("star/star_1.png", true, "star_1");
    ResourceManager::LoadTexture("star/star_2.png", true, "star_2");
    ResourceManager::LoadTexture("star/star_3.png", true, "star_3");
    
    // - enemies
    ResourceManager::LoadTexture("goomba/goomba_0.png", true, "goomba_0");
    ResourceManager::LoadTexture("goomba/goomba_1.png", true, "goomba_1");
    ResourceManager::LoadTexture("goomba/goomba_death.png", true, "goomba_death");

    ResourceManager::LoadTexture("turtle/turtle_left_0.png", true, "turtle_left_0");
    ResourceManager::LoadTexture("turtle/turtle_left_1.png", true, "turtle_left_1");

    ResourceManager::LoadTexture("turtle/turtle_right_0.png", true, "turtle_right_0");
    ResourceManager::LoadTexture("turtle/turtle_right_1.png", true, "turtle_right_1");

    ResourceManager::LoadTexture("turtle/turtle_hidden.png", true, "turtle_hidden");

    // - flag
    ResourceManager::LoadTexture("flag/flag.png", true, "flag");
}

void Game::Respawn()
{
    // game objects
    InitLevelObjects();
    SpawnEnemies();

    camera.cameraPos = glm::vec3(0.0f, 0.0f, 1.0f);
    camera.savePos = glm::vec3(0.0f);
}

void Game::ProcessPlayersDeath()
{
    ClearLevelData();

    player->Spawn();

    Respawn();

    deadOnce = false;
    respawnCheck = false;

    timeCount = 100;
}

void Game::ClearLevelData()
{
    for (auto i : objList)
    {
        i->DeleteObject();
    }

    DeleteObjects();
}

void Game::RefreshGameData()
{
    delete map;
    delete menuCoin;

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
    bullets.clear();
    plants.clear();
    stars.clear();

    enemies.clear();
    goombas.clear();
    turtles.clear();
    // ---------

    Init();

    gmState = MENU;
    underworld = false, respawnCheck = false, deadOnce = false;
    timeCount = 100;

    camera.cameraPos = glm::vec3(0.0f, 0.0f, 1.0f);
    camera.savePos = glm::vec3(0.0f);
}

// Actions
void Game::ProcessInput(float dt)
{
    if (gmState == ACTIVE) {

        // Player movement
        if (this->Keys[GLFW_KEY_DOWN]) player->Action(dt, DUCK);
        else if (this->Keys[GLFW_KEY_RIGHT]) player->Action(dt, DIR_RIGHT);
        else if (this->Keys[GLFW_KEY_LEFT] && player->GetPos().x > camera.cameraPos.x) player->Action(dt, DIR_LEFT);
        else player->Action(dt, STAND);

        // Acceleration
        if (this->Keys[GLFW_KEY_LEFT_CONTROL]) player->Accelerate(true);
        else player->Accelerate(false);

        // Jump
        if (this->Keys[GLFW_KEY_SPACE]) { 
            player->Jump(dt, this->KeysProcessed[GLFW_KEY_SPACE]); 

            if (!this->KeysProcessed[GLFW_KEY_SPACE]) sound->play2D("../sounds/jump.wav");
            this->KeysProcessed[GLFW_KEY_SPACE] = true;
        }

        // Gun
        if (this->Keys[GLFW_KEY_Z] && !this->KeysProcessed[GLFW_KEY_Z] && player->IsReload()) {
            
            player->Fire();

            Bullet* bullet = new Bullet(glm::vec2(player->GetPos().x + player->GetSize().x / 2.0f, player->GetPos().y + player->GetSize().y / 2.0f), glm::vec2(25.0f), player->GetLastDirection(), true, player->GetSpeed() + player->GetInertia() + 150.0f);
            objList.push_back(bullet);
            moveableObj.push_back(bullet);
            animatedObj.push_back(bullet);
            bullets.push_back(bullet);

            this->KeysProcessed[GLFW_KEY_Z] = true;
        }

        // Screen collision
        if (player->GetPos().x < camera.cameraPos.x) player->SetPos(glm::vec2(camera.cameraPos.x, player->GetPos().y));
        
        // Move screen
        float midScreenX = camera.cameraPos.x + this->width / 2.0f;
        if (player->GetPos().x > midScreenX && !underworld && camera.cameraPos.x + this->width < 21200.0f) camera.cameraPos.x += player->GetPos().x - midScreenX;

        if (this->Keys[GLFW_KEY_P]) gmState = MENU;
        
        if (this->Keys[GLFW_KEY_DOWN] && player->GroundCollision(*tubes[3])) ChangeLocation();
        else if (this->Keys[GLFW_KEY_RIGHT] && player->RightCollision(*tubes[6])) ChangeLocation();

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

            if (cursorPos.y == this->height / 2.0f && (gmState == WIN || gmState == LOSS)) {
                RefreshGameData();
            }
            else if (cursorPos.y == this->height / 2.0f && gmState == MENU) gmState = ACTIVE;
            else if (cursorPos.y == this->height / 2.0f + 40.0f) close = true;
        }
    }
}

void Game::Update(float dt)
{
    if (gmState == ACTIVE) {

        // actions
        ProcessAnimation(dt);

        MoveObjects(dt);

        // update borders after position changes
        for (auto i : moveableObj)
        {
            i->UpdateAABB();
        }

        // interactions
        ProcessCollision(dt);

        // Player death cases
        
            // - - - common death
        if (timeCount == 0) player->Death();

        if (player->IsDead() && player->GetLifes() > 0 && !deadOnce) {
            deadOnce = true;
            std::thread respawnTh([&]() {
                std::this_thread::sleep_for(std::chrono::seconds(5));
                respawnCheck = true;
                });
            respawnTh.detach();
        }
        else if (player->IsDead() && player->GetLifes() <= 0 && !deadOnce) gmState = LOSS;

            // - - - abyss death
        if (player->GetPos().y >= this->height && !underworld && !deadOnce) { 

            player->Death();

            if (player->GetLifes() > 0) {
                deadOnce = true;
                std::thread respawnTh([&]() {
                    std::this_thread::sleep_for(std::chrono::seconds(5));
                    respawnCheck = true;
                    });
                respawnTh.detach();

            }
            else gmState = LOSS;
        }

        if (respawnCheck) ProcessPlayersDeath();
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        player->Reload(bullets); // bullets are deleted after collision

        Timer();

        // delete
        DeleteObjects();
    }
    else if (gmState == WIN) {
        player->PlayEndAnimation(dt);
    }
    else if (gmState == MENU) Menu();
}

void Game::MoveObjects(float dt)
{
    for (auto i : bullets)
    {
        i->Move(dt);
    }

    for (auto i : coins)
    {
        i->Move(dt);
    }

    for (auto i : plants)
    {
        if (!i->IsSprouted()) i->Sprout(dt);
        else if (i->IsSprouted() && (i->GetPlantType() == MUSHROOM_LIFE || i->GetPlantType() == MUSHROOM_UPGRADE)) i->Move(dt);
    }

    for (auto i : stars)
    {
        if (!i->IsSprouted()) i->Sprout(dt);
        else i->Move(dt);
    }
    
    for (auto i : goombas)
    {
        if (!i->IsDead()) i->Move(dt, i->IsOnScreen(camera.cameraPos, glm::vec2(this->width, this->height)));
    }

    for (auto i : turtles)
    {
        if (!i->IsDead()) i->Move(dt, i->IsOnScreen(camera.cameraPos, glm::vec2(this->width, this->height)));
    }
}

void Game::ProcessCollision(float dt)
{
    std::vector<GameObject*> groundObjects;
    groundObjects.insert(groundObjects.end(), grounds.begin(), grounds.end());
    groundObjects.insert(groundObjects.end(), tubes.begin(), tubes.end());
    groundObjects.insert(groundObjects.end(), bricks.begin(), bricks.end());

    // ground collision
    for (auto i : moveableObj)
    {
        for (auto j : groundObjects)
        {
            if (i->ProcessGroundCollision(*j)) break;
        }

        i->Drop(dt);
    }

    // player top collision with bricks
    for (auto i : bricks)
    {
        if (player->ProcessTopCollision(*i)) {
            i->Push(player->GetMarioType() > LITTLE);
            SpawnBonus(i);
            if (!(i->GetType() == MONEY)) i->PickBonus();
            break;
        }
    }

    // side collision 
    for (auto i : moveableObj)
    {
        for (auto j : groundObjects)
        {
            if (i->ProcessSideCollision(*j)) break;
        }
    }

    // bullets are deleted after collision with sides
    for (auto i : bullets)
    {
        for (auto j : groundObjects)
        {
            if (i->ProcessSideCollision(*j)) {
                i->DeleteObject();
                break;
            }
        }
    }

    // side collisions behaviour
    for (auto i : plants)
    {
        for (auto j : groundObjects)
        {
            if (i->ProcessSideCollision(*j) && i->IsSprouted()) {
                i->GetDirection() == DIR_RIGHT ? i->SetDirection(DIR_LEFT) : i->SetDirection(DIR_RIGHT);
                break;
            }
        }
    }

    for (auto i : stars)
    {
        for (auto j : groundObjects)
        {
            if (i->ProcessSideCollision(*j) && i->IsSprouted()) {
                i->GetDirection() == DIR_RIGHT ? i->SetDirection(DIR_LEFT) : i->SetDirection(DIR_RIGHT);
                break;
            }
        }
    }

    for (auto i : enemies)
    {
        for (auto j : groundObjects)
        {
            if (i->ProcessSideCollision(*j)) {
                i->GetDirection() == DIR_RIGHT ? i->SetDirection(DIR_LEFT) : i->SetDirection(DIR_RIGHT);
                break;
            }
        }
    }

    // enemies with player collisions
    for (auto i : bullets)
    {
        for (auto j : enemies)
        {
            if (i->ObjectCollision(*j)) {
                player->AddScore(500);
                j->Death();
                i->DeleteObject();
            }
        }
    }

    for (auto i : enemies) // if enemies fall on mario's head mario dies (if he isn't immortal)
    {
        if (i->IsDead()) break;

        if (player->ProcessTopCollision(*i) && !i->IsDead()) {
            if (!player->IsImmortal()) player->Hit();
            else { 
                i->Death();
                player->AddScore(500);
            }
            break;
        }
    }

    for (auto i : goombas)
    {
        if (i->IsDead()) break;

        if (player->ProcessKillCollision(*i)) {
            i->Death();
            player->AddScore(100);
            break;
        }
        else if (player->ProcessSideCollision(*i)) {
            if (!player->IsImmortal()) player->Hit();
            else {
                i->Death();
                player->AddScore(100);
            }
            break;
        }
    }

    for (auto i : turtles)
    {
        if (i->IsDead()) break;

        if (player->ProcessKillCollision(*i)) { // top collision
            i->Hide();
            break;
        }
        else if (player->ProcessSideCollision(*i)) {

            if (player->IsImmortal()) {
                player->AddScore(500);
                i->Death(); // if mario's immortal turtle dies 
                break;
            }
            
            if (!i->IsHidden() || i->GetDirection() != STAND) player->Hit();
            else i->SetDirection(player->GetLastDirection());
            break;
        }
    }

    for (auto i : turtles)
    {
        for (auto j : goombas)
        {
            if (j->IsAppear()) if (i->IsHidden() && j->ProcessSideCollision(*i)) {  // if goombas haven't appeared they can't die
                player->AddScore(100);
                j->DeleteObject();
            }
        }
    }

    // gameplay collisions
    for (auto i : coins)
    {
        if (player->ObjectCollision(*i)) {
            player->CollectCoin();
            i->DeleteObject();
            break;
        }
    }

    for (auto i : plants)
    {
        if (player->ObjectCollision(*i) && i->IsSprouted()) {
            if (i->GetPlantType() == MUSHROOM_LIFE) player->CollectLife();
            else player->Upgrade();

            i->DeleteObject();
            break;
        }
    }

    for (auto i : stars)
    {
        if (player->ObjectCollision(*i) && i->IsSprouted()) {
            player->Immortal();
            i->DeleteObject();
            break;
        }
    }

    // end game collision
    if (player->GetPos().x >= 19880.0f) gmState = WIN;
}

void Game::ProcessAnimation(float dt)
{
    for (auto i : animatedObj)
    {
        if (i->IsAnimated() && i->AnimationPlayed(dt)) i->PlayAnimation();
    }

    for (auto i : bricks)
    {
        if (i->IsMoving()) i->Move(dt);
        else if (i->GetType() == COMMON && i->IsDestroyed()) i->DestroyAnimation(dt);
    }

    for (auto i : coins) 
    {
        if (i->GetCoinType() == COIN_BRICK) i->FlipAnimation();
    }

    for (auto i : goombas)
    {
        if (i->IsDead()) i->DeathAnimation(dt);
    }
}

// Render
void Game::Render()
{
    static int tick = 0;

    if (gmState == ACTIVE) {
        DrawObject(map);

        // objects
        for (auto i : plants)
        {
            if (i->IsOnScreen(camera.cameraPos, glm::vec2(this->width, this->height))) DrawObject(i);
        }

        for (auto i : coins)
        {
            if (i->IsOnScreen(camera.cameraPos, glm::vec2(this->width, this->height))) DrawObject(i);
        }

        for (auto i : stars)
        {
            if (i->IsOnScreen(camera.cameraPos, glm::vec2(this->width, this->height))) DrawObject(i);
        }

        for (auto i : bricks)
        {
            if (i->GetType() != INVISIBLE && i->IsOnScreen(camera.cameraPos, glm::vec2(this->width, this->height))) DrawObject(i);
        }

        for (auto i : bullets)
        {
            if (i->IsOnScreen(camera.cameraPos, glm::vec2(this->width, this->height))) DrawObject(i);
        }

        for (auto i : enemies)
        {
            if (i->IsOnScreen(camera.cameraPos, glm::vec2(this->width, this->height))) DrawObject(i);
        }

        if (player->HitDelay()) {
            if (tick % 2 == 0) DrawObject(player);
        }
        else DrawObject(player);
    }
    else if (gmState == WIN) {
        DrawObject(map);
        if (player->GetPos().x < 20500.0f) DrawObject(player);
        else EndMenu();
    }
    else if (gmState == LOSS) EndMenu();
    else Menu();

    DrawStats();
    DrawObject(menuCoin);

    tick++;
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
    text->RenderText(std::to_string(player->GetScore()), glm::vec2(150.0f, 50.0f), 1.25f, color);
    
    text->RenderText("x ", glm::vec2(550.0f, 50.0f), 1.25f, color);
    text->RenderText(std::to_string(player->GetCoins()), glm::vec2(580.0f, 50.0f), 1.25f, color);

    text->RenderText("Lifes: ", glm::vec2(850.0f, 50.0f), 1.25f, color);
    text->RenderText(std::to_string(player->GetLifes()), glm::vec2(950.0f, 50.0f), 1.25f, color);

    text->RenderText("T I M E", glm::vec2(this->width - 200.0f, 20.0f), 1.25f, color);
    text->RenderText(std::to_string(timeCount), glm::vec2(this->width - 150.0f, 50.0f), 1.25f, color);

    menuCoin->SetPos(glm::vec2(camera.cameraPos.x + 515.0f, 48.0f));
}

void Game::Timer()
{
    std::time_t currentTime = std::time(nullptr);

    std::tm timeinfo;
    localtime_s(&timeinfo, &currentTime);

    float newSeconds = static_cast<float>(timeinfo.tm_sec);

    if (newSeconds > seconds) timeCount--;
    seconds = newSeconds;
}

void Game::Menu()
{
    text->RenderText("MENU", glm::vec2(this->width / 2.0f - 65.0f, this->height / 2.0f - 116.0f), 1.75f, glm::vec3(0.75f));

    text->RenderText("Start", glm::vec2(this->width / 2.0f - 20.0f, this->height / 2.0f), 1.0f, glm::vec3(1.0f));
    text->RenderText("Exit", glm::vec2(this->width / 2.0f - 20.0f, this->height / 2.0f + 40.0f), 1.0f, glm::vec3(1.0f));

    text->RenderText("->", glm::vec2(cursorPos), 1.0f, glm::vec3(1.0f));
}

void Game::EndMenu()
{
    if (gmState == WIN) {
        text->RenderText("YOU'VE WON!", glm::vec2(this->width / 2.0f - 125.0f, this->height / 2.0f - 116.0f), 1.75f, glm::vec3(0.75f));

        text->RenderText("Restart", glm::vec2(this->width / 2.0f - 20.0f, this->height / 2.0f), 1.0f, glm::vec3(1.0f));
        text->RenderText("Exit", glm::vec2(this->width / 2.0f - 20.0f, this->height / 2.0f + 40.0f), 1.0f, glm::vec3(1.0f));

        text->RenderText("->", glm::vec2(cursorPos), 1.0f, glm::vec3(1.0f));
    }
    else {
        text->RenderText("YOU'VE LOST!", glm::vec2(this->width / 2.0f - 135.0f, this->height / 2.0f - 116.0f), 1.75f, glm::vec3(0.75f));

        text->RenderText("Restart", glm::vec2(this->width / 2.0f - 20.0f, this->height / 2.0f), 1.0f, glm::vec3(1.0f));
        text->RenderText("Exit", glm::vec2(this->width / 2.0f - 20.0f, this->height / 2.0f + 40.0f), 1.0f, glm::vec3(1.0f));

        text->RenderText("->", glm::vec2(cursorPos), 1.0f, glm::vec3(1.0f));
    }
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

    tube = new Tube(glm::vec2(5730.0f, this->height - 370.0f), glm::vec2(190.0f, 260.0f), true);
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
    tube = new Tube(glm::vec2(this->width - 300.0f, this->height * 2 - 180.0f), glm::vec2(300.0f, 125.0f), true);
    tube->SetTexture(ResourceManager::GetTexture("test"));
    tubes.push_back(tube);
    objList.push_back(tube);
}

void Game::InitBricks()
{
    BrickType type = COMMON;
    BrickBonus bonus = BONUS_NONE;
    float addHeight = 0.0f, addWidth = 0.0f;

    Brick* brick = new Brick(glm::vec2(1605.0f, 525.0f), glm::vec2(102.0f, 65.0f), SOLID, BONUS_COIN, true);
    bricks.push_back(brick);
    animatedObj.push_back(brick);
    objList.push_back(brick);

    brick = new Brick(glm::vec2(2210.0f, 267.0f), glm::vec2(102.0f, 65.0f), SOLID, BONUS_COIN, true);
    bricks.push_back(brick);
    animatedObj.push_back(brick);
    objList.push_back(brick);

    for (size_t i = 0; i < 5; i++)
    {
        if (i == 1) bonus = BONUS_UPGRADE;
        else if (i == 3) bonus = BONUS_COIN;
        else bonus = BONUS_NONE;

        if (i == 1 || i == 3) type = SOLID;
        else type = COMMON;

        brick = new Brick(glm::vec2(2010.0f + 102.0f * i, 525.0f), glm::vec2(102.0f, 65.0f), type, bonus, type == SOLID);
        objList.push_back(brick);
        bricks.push_back(brick);
        if (type == SOLID) animatedObj.push_back(brick);
    }

    brick = new Brick(glm::vec2(6430.0f, 462.0f), glm::vec2(102.0f, 65.0f), INVISIBLE, BONUS_LIFE);
    bricks.push_back(brick);
    objList.push_back(brick);

    for (size_t i = 0; i < 15; i++)
    {
        if (i == 1) bonus = BONUS_UPGRADE;
        else if (i == 14) bonus = BONUS_COIN;
        else bonus = BONUS_NONE;

        if (i == 1 || i == 14) type = SOLID;
        else type = COMMON;

        if (i == 3) addHeight = 255.0f;
        if (i == 11) addWidth = 295.0f;

        brick = new Brick(glm::vec2(7730.0f + 102.0f * i + addWidth, 525.0f - addHeight), glm::vec2(102.0f, 65.0f), type, bonus, type == SOLID);
        bricks.push_back(brick);
        objList.push_back(brick);
        if (type == SOLID) animatedObj.push_back(brick);
    }

    brick = new Brick(glm::vec2(9445.0f, 525.0f), glm::vec2(102.0f, 65.0f), MONEY);
    bricks.push_back(brick);
    objList.push_back(brick);

    for (size_t i = 0; i < 2; i++)
    {
        if (i == 1) type = HIDDEN, bonus = BONUS_STAR;
        else type = COMMON, bonus = BONUS_NONE;

        brick = new Brick(glm::vec2(10045.0f + 102.0f * i, 525.0f), glm::vec2(102.0f, 65.0f), type, bonus);
        bricks.push_back(brick);
        objList.push_back(brick);
    }

    for (size_t i = 0; i < 3; i++)
    {
        brick = new Brick(glm::vec2(10650.0f + 300.0f * i, 525.0f), glm::vec2(102.0f, 65.0f), SOLID, BONUS_COIN, true);
        bricks.push_back(brick);
        objList.push_back(brick);
        animatedObj.push_back(brick);
    }

    brick = new Brick(glm::vec2(10950.0f, 267.0f), glm::vec2(102.0f, 65.0f), SOLID, BONUS_UPGRADE, true);
    bricks.push_back(brick);
    objList.push_back(brick);
    animatedObj.push_back(brick);

    brick = new Brick(glm::vec2(11860.0f, 525.0f), glm::vec2(102.0f, 65.0f));
    bricks.push_back(brick);
    objList.push_back(brick);
    animatedObj.push_back(brick);

    addWidth = 0.0f;
    for (size_t i = 0; i < 7; ++i)
    {
        if (i == 3) addWidth = 400.0f;
        if (i == 4 || i == 5) type = SOLID, bonus = BONUS_COIN;
        else type = COMMON, bonus = BONUS_NONE;

        brick = new Brick(glm::vec2(12155.0f + 102.0f * i + addWidth, 267.0f), glm::vec2(102.0f, 65.0f), type, bonus, type == SOLID);
        bricks.push_back(brick);
        objList.push_back(brick);
        if (type == SOLID) animatedObj.push_back(brick);
    }

    for (size_t i = 0; i < 2; ++i)
    {
        brick = new Brick(glm::vec2(12960.0f + 102.0f * i, 525.0f), glm::vec2(102.0f, 65.0f));
        bricks.push_back(brick);
        objList.push_back(brick);
    }

    for (size_t i = 0; i < 4; ++i)
    {
        if (i == 2) type = SOLID, bonus = BONUS_COIN;
        else type = COMMON, bonus = BONUS_NONE;

        brick = new Brick(glm::vec2(16880.0f + 102.0f * i, 525.0f), glm::vec2(102.0f, 65.0f), type, bonus, type == SOLID);
        bricks.push_back(brick);
        objList.push_back(brick);
        if (type == SOLID) animatedObj.push_back(brick);
    }

    // underworld
    for (size_t i = 0; i < 7; i++)
    {
        brick = new Brick(glm::vec2(398.0f + 102.0f * i, this->height + 121.0f), glm::vec2(102.0f, 65.0f));
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

            coin = new Coin(glm::vec2(415.0f + 100.0f * j, this->height + 325.0f + 130.0f * i), glm::vec2(60.0f, 60.0f), 100.0f, true);
            objList.push_back(coin);
            animatedObj.push_back(coin);
            coins.push_back(coin);
        }
    }
   
}

void Game::SpawnBonus(Brick* brick)
{
    if (brick->GetBonusType() == BONUS_NONE) return;

    if (brick->GetBonusType() == BONUS_COIN) SpawnCoin(brick);
    else if (brick->GetBonusType() == BONUS_LIFE || brick->GetBonusType() == BONUS_UPGRADE) SpawnPlant(brick);
    else if (brick->GetBonusType() == BONUS_STAR) SpawnStar(brick);
}

void Game::SpawnPlant(Brick* brick)
{
    PlantType type;
    if (brick->GetBonusType() == BONUS_UPGRADE && player->GetMarioType() == LITTLE) type = MUSHROOM_UPGRADE;
    else if (brick->GetBonusType() == BONUS_UPGRADE && player->GetMarioType() > LITTLE) type = PLANT_UPGRADE;
    else if (brick->GetBonusType() == BONUS_LIFE) type = MUSHROOM_LIFE;

    Plant* plant = new Plant(brick->GetPos(), brick->GetSize(), type, type == PLANT_UPGRADE, 250.0f);
    objList.push_back(plant);
    moveableObj.push_back(plant);
    if (type == PLANT_UPGRADE) animatedObj.push_back(plant);
    plants.push_back(plant);
}

void Game::SpawnStar(Brick* brick)
{
    Star* star = new Star(brick->GetPos(), brick->GetSize(), true);
    objList.push_back(star);
    animatedObj.push_back(star);
    moveableObj.push_back(star);
    stars.push_back(star);
}

void Game::SpawnCoin(Brick* brick)
{
    Coin* coin = new Coin(brick->GetPos() + brick->GetSize() / 4.0f, brick->GetSize() / 2.0f);
    coin->SetCoinType(COIN_BRICK);
    objList.push_back(coin);
    coins.push_back(coin);

    player->CollectCoin();
}

void Game::SpawnEnemies()
{
    // goombas
    SpawnGoomba(glm::vec2(2100.0f, this->height - 250.0f));
    SpawnGoomba(glm::vec2(4200.0f, this->height - 250.0f));
    SpawnGoomba(glm::vec2(5300.0f, this->height - 250.0f));
    SpawnGoomba(glm::vec2(5420.0f, this->height - 250.0f));
    SpawnGoomba(glm::vec2(8100.0f, 200.0f));
    SpawnGoomba(glm::vec2(8220.0f, 200.0f));
    SpawnGoomba(glm::vec2(9500.0f, this->height - 250.0f));
    SpawnGoomba(glm::vec2(9620.0f, this->height - 250.0f));
    SpawnGoomba(glm::vec2(12400.0f, this->height - 250.0f));
    SpawnGoomba(glm::vec2(12520.0f, this->height - 250.0f));
    SpawnGoomba(glm::vec2(12700.0f, this->height - 250.0f));
    SpawnGoomba(glm::vec2(12820.0f, this->height - 250.0f));
    SpawnGoomba(glm::vec2(17400.0f, this->height - 250.0f));
    SpawnGoomba(glm::vec2(17520.0f, this->height - 250.0f));

    // turtles
    SpawnTurtle(glm::vec2(10620.0f, this->height - 250.0f));
}

void Game::SpawnGoomba(glm::vec2 position)
{
    Goomba* goomba = new Goomba(position, player->GetSize(), true, 125.0f);
    objList.push_back(goomba);
    moveableObj.push_back(goomba);
    animatedObj.push_back(goomba);
    
    enemies.push_back(goomba);
    goombas.push_back(goomba);
}

void Game::SpawnTurtle(glm::vec2 position)
{
    Turtle* turtle = new Turtle(position, player->GetSize(), true, 125.0f);
    objList.push_back(turtle);
    moveableObj.push_back(turtle);
    animatedObj.push_back(turtle);

    enemies.push_back(turtle);
    turtles.push_back(turtle);
}

void Game::ChangeLocation()
{
    sound->stopAllSoundsOfSoundSource(music);

    if (!underworld) {
        map->SetSize(glm::vec2(this->width, this->height));
        map->SetPos(glm::vec2(00.0f, this->height));
        map->SetTexture(ResourceManager::GetTexture("UndergroundMap"));

        music = sound->getSoundSource("../sounds/underworld.mp3");

        camera.savePos = camera.cameraPos;
        camera.cameraPos = glm::vec3(0.0f, this->height, 1.0f);

        player->SetPos(glm::vec2(150.0f, this->height + 15.0f));
    }
    else {
        map->SetSize(glm::vec2(21200.0f, this->height));
        map->SetPos(glm::vec2(0.0f));
        map->SetTexture(ResourceManager::GetTexture("MainMap"));

        music = sound->getSoundSource("../sounds/overworld.mp3");

        camera.cameraPos = camera.savePos;

        player->SetPos(glm::vec2(tubes[4]->GetPos().x + tubes[4]->GetSize().x / 2.0f, tubes[4]->GetPos().y - player->GetSize().y));
    }

    underworld = !underworld;
    sound->play2D(music, true);
}
// - - - - - - - - - - - - - - -

void Game::DeleteObjects()
{
    DeleteObjectFromVector(animatedObj, false);
    DeleteObjectFromVector(moveableObj, false);

    DeleteObjectFromVector(grounds, false);
    DeleteObjectFromVector(tubes, false);
    DeleteObjectFromVector(coins, false);
    DeleteObjectFromVector(bricks, false);
    DeleteObjectFromVector(bullets, false);
    DeleteObjectFromVector(plants, false);
    DeleteObjectFromVector(stars, false);

    DeleteObjectFromVector(enemies, false);
    DeleteObjectFromVector(goombas, false);
    DeleteObjectFromVector(turtles, false);

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
    delete menuCoin;

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
    bullets.clear();
    plants.clear();
    stars.clear();

    enemies.clear();
    goombas.clear();
    turtles.clear();
    // ---------
}
