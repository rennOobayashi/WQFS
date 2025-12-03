#include "OpenGLCode.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

glm::vec2 cameraPos(0.0f, 0.0f);
glm::vec2 cameraNextPos(0.0f, 0.0f);
glm::vec3 cameraFront(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp(0.0f, 1.0f, 0.0f);
glm::vec2 attackCollidePos(0.0f, 0.0f);
const glm::vec2 inventoryItemPos[] = {
    glm::vec2(125.0f, 110.0f),
    glm::vec2(290.0f, 110.0f),
    glm::vec2(445.0f, 110.0f),
    glm::vec2(610.0f, 110.0f),
    glm::vec2(770.0f, 110.0f),
};
const glm::vec2 compass[]{
    glm::vec2( 0.0f,  1.0f), //Up
    glm::vec2( 0.0f, -1.0f), //Down
    glm::vec2(-1.0f,  0.0f), //Left
    glm::vec2( 1.0f,  0.0f), //Right
};
const glm::vec2 playerSize(70.0f);
const float playerVelocity(300.0f);
const float CameraVelocity(2000.0f);

glm::vec2 obstaclePosition[5] = {
    glm::vec2(-80.0f, 60.0f),
    glm::vec2(50.0f, -40.0f),
    glm::vec2(-100.0f, -60.0f),
    glm::vec2(90.0f, 50.0f),
    glm::vec2(40.0f, 65.0f),
};

glm::vec3 obstacleColors[5] = {
    glm::vec3(220 / 255.0f, 220 / 255.0, 220 / 255.0),
    glm::vec3(199 / 255.0f, 199 / 255.0, 199 / 255.0),
    glm::vec3(107 / 255.0f, 107 / 255.0, 107 / 255.0),
    glm::vec3(125 / 255.0f, 125 / 255.0, 125 / 255.0),
    glm::vec3( 77 / 255.0f,  77 / 255.0,  77 / 255.0),
};

glm::vec2 eventPosition[] = {
    glm::vec2(220 / 255.0f, 220 / 255.0),
};

OpenGLCode::OpenGLCode(unsigned int _width, unsigned int _height)
	: states(GAME_MAIN_MENU), playerLastDir(LEFT), width(_width), height(_height), hp(3), damage(1), changedir(false), showDangerousTime(1.0f), dangerousDelay(5.0f), mapLoading(false), mapLoadingDelay(0.0f), getItemFirstTime(false), attackDelay(0.0f), isAttacked(false), isMoving(false), useWQFS(true), moveAnimationTimer(0.0f), playerHitDelay(1.0f) {
    init();
    srand((unsigned int)time(NULL));

}

OpenGLCode::~OpenGLCode() {
    delete player;
	delete sRenderer;
    delete attackBox;
    delete questGameObject;
    delete InventoryObject;
    delete hpObjects;
    delete soundEngine;
    delete effects;

	npcObjects.clear();
    monsterObjects.clear();
    eventObjects.clear();
    ResourceManager::Clear();
    WQFS::Clear();
	level.Clear();
}

void OpenGLCode::init() {
	srand((unsigned int)time(0));

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 8);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    glfwWindowHint(GLFW_RESIZABLE, false);

    window = glfwCreateWindow(width, height, "WQFS Tech Demo", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glm::mat4 projection = glm::ortho(0.0f, (float)width, (float)height, 0.0f, -1.0f, 1.0f);

    ResourceManager::LoadShader("verfrag/vertex.vs", "verfrag/fragment.fs", nullptr, "sprite");
    ResourceManager::LoadShader("verfrag/postprocessing_vertex.vs", "verfrag/postprocessing_fragment.fs", nullptr, "effects");

    ResourceManager::GetShader("sprite").use().SetInt("sprite", 0);
    ResourceManager::GetShader("sprite").use().SetMat4("projection", projection);

    ResourceManager::GetShader("Particle").use().SetInt("sprite", 0);
    ResourceManager::GetShader("Particle").use().SetMat4("projection", projection);

    ResourceManager::LoadTexture("Texture/Player.png", true, "Player");
    ResourceManager::LoadTexture("Texture/PlayerMove.png", true, "PlayerMove");
    ResourceManager::LoadTexture("Texture/NPC_1.png", true, "NPC1");
    ResourceManager::LoadTexture("Texture/NPC_1_Move.png", true, "NPC1Move");
    ResourceManager::LoadTexture("Texture/Monster.png", true, "Monster");
    ResourceManager::LoadTexture("Texture/Event.png", true, "Event");
    ResourceManager::LoadTexture("Texture/Tree.png", true, "Tree");
    ResourceManager::LoadTexture("Texture/Tide_by_Gemini.png", true, "Tsunami");
    ResourceManager::LoadTexture("Texture/GroundTile.png", true, "GroundTile");
    ResourceManager::LoadTexture("Texture/Mountain.png", true, "MountainTile");
    ResourceManager::LoadTexture("Texture/Mountain_Left.png", true, "MountainLeftTile");
    ResourceManager::LoadTexture("Texture/Mountain_Right.png", true, "MountainRightTile");
    ResourceManager::LoadTexture("Texture/Mountain_Left_Top.png", true, "MountainLeftTopTile");
    ResourceManager::LoadTexture("Texture/Mountain_Right_Top.png", true, "MountainRightTopTile");
    ResourceManager::LoadTexture("Texture/Mountain_Top.png", true, "MountainTopTile");
    ResourceManager::LoadTexture("Texture/Rockfall_by_Gemini.png", true, "Rockfall");
    ResourceManager::LoadTexture("Texture/Inventory.png", true, "Inventory");
    ResourceManager::LoadTexture("Texture/HP_Posion.png", true, "HP Posion");
    ResourceManager::LoadTexture("Texture/Good_HP_Posion.png", true, "Good HP Posion");
    ResourceManager::LoadTexture("Texture/Mana_Up_Posion.png", true, "Mana Up Posion");
    ResourceManager::LoadTexture("Texture/Iron.png", true, "Iron");
    ResourceManager::LoadTexture("Texture/Gold.png", true, "Gold");
    ResourceManager::LoadTexture("Texture/Heart.png", true, "Heart");

	Shader spriteShader = ResourceManager::GetShader("sprite");
	sRenderer = new SpriteRenderer(spriteShader);
	effects = new PostProcessing(ResourceManager::GetShader("effects"), width, height);

    glm::vec2 playerPos(width / 2, height / 2);
    attackCollidePos = glm::vec2(playerPos.x + 20.0f, playerPos.y);

    npcObjects["Normal"] = std::make_pair(GameObject(ResourceManager::GetTexture("NPC1"), glm::vec2(0.0f, 0.0f), glm::vec2(70.0f), 0.0f, glm::vec3(1.0f), 1.0f), 1.0f);
    std::get<0>(monsterObjects["Monster"]) = GameObject(ResourceManager::GetTexture("Monster"), glm::vec2(0.0f), glm::vec2(200.0f), 0.0f, glm::vec3(1.0f, 0.2f, 0.1f));
    std::get<1>(monsterObjects["Monster"]) = 0.5f;
    eventObjects["Landslide1"] = GameObject(ResourceManager::GetTexture("GroundTile"), glm::vec2(100.0f), glm::vec2(300.0f), 0.0f, glm::vec3(190 / 255.0f));
	eventObjects["Landslide1"].visible = false;
    eventObjects["Landslide2"] = GameObject(ResourceManager::GetTexture("GroundTile"), glm::vec2(100.0f), glm::vec2(300.0f), 0.0f, glm::vec3(190 / 255.0f));
    eventObjects["Landslide2"].visible = false;
    eventObjects["Earthquake1"] = GameObject(ResourceManager::GetTexture("GroundTile"), glm::vec2(0.0f), glm::vec2(400.0f), 0.0f, glm::vec3(180 / 255.0f));
    eventObjects["Earthquake2"] = GameObject(ResourceManager::GetTexture("GroundTile"), glm::vec2(0.0f), glm::vec2(500.0f), 0.0f, glm::vec3(180 / 255.0f));
    eventObjects["Earthquake3"] = GameObject(ResourceManager::GetTexture("GroundTile"), glm::vec2(0.0f), glm::vec2(550.0f), 0.0f, glm::vec3(180 / 255.0f));
    eventObjects["Tsunami"] = GameObject(ResourceManager::GetTexture("Tsunami"), glm::vec2(0.0f), glm::vec2(120.0f), 0.0f, glm::vec3(1.0f));
    eventObjects["Tornado1"] = GameObject(ResourceManager::GetTexture("GroundTile"), glm::vec2(0.0f), glm::vec2(400.0f), 0.0f, glm::vec3(190 / 255.0f));
    player = new GameObject(ResourceManager::GetTexture("Player"), playerPos, playerSize, 0.0f, glm::vec3(1.0f), 1.0f, glm::vec2(playerVelocity));
	attackBox = new GameObject(ResourceManager::GetTexture("GroundTile"), attackCollidePos, glm::vec2(75.0f, 75.0f), 0.0f, glm::vec3(1.0f, 0.3f, 0.3f));
    questGameObject = new GameObject(ResourceManager::GetTexture("GroundTile"), glm::vec2(0.0f), glm::vec2(25.0f), 0.0f, glm::vec3(1.0f));
	InventoryObject = new GameObject(ResourceManager::GetTexture("Inventory"), glm::vec2(100.0f, 80.0f), glm::vec2(800.0f, 160.0f), 0.0f, glm::vec3(1.0f), 0.5f);
	hpObjects = new GameObject(ResourceManager::GetTexture("Heart"), glm::vec2(10.0f), glm::vec2(50.0f), 0.0f, glm::vec3(1.0f), 0.7f);

    itemObjects["HP Posion"] = GameObject(ResourceManager::GetTexture("HP Posion"), glm::vec2(125.0f, 110.0f), glm::vec2(100.0f), 0.0f, glm::vec3(1.0f), 0.8f);
    itemObjects["Good HP Posion"] = GameObject(ResourceManager::GetTexture("Good HP Posion"), glm::vec2(290.0f, 110.0f), glm::vec2(100.0f), 0.0f, glm::vec3(1.0f), 0.8f);
    itemObjects["Mana Up Posion"] = GameObject(ResourceManager::GetTexture("Mana Up Posion"), glm::vec2(445.0f, 110.0f), glm::vec2(100.0f), 0.0f, glm::vec3(1.0f), 0.8f);
    itemObjects["Iron"] = GameObject(ResourceManager::GetTexture("Iron"), glm::vec2(610.0f, 110.0f), glm::vec2(100.0f), 0.0f, glm::vec3(1.0f), 0.8f);
    itemObjects["Gold"] = GameObject(ResourceManager::GetTexture("Gold"), glm::vec2(770.0f, 110.0f), glm::vec2(100.0f), 0.0f, glm::vec3(1.0f), 0.8f);

    WQFS::GetInstance().AddNPC("Normal", 0, 0, 0.0f, 0.0f, npcObjects["Normal"].first.objSize.x, npcObjects["Normal"].first.objSize.y, 5.0f);
    WQFS::GetInstance().AddEvent("Monster", 0, 0, 2, 0.0f, 0.0f, std::get<0>(monsterObjects["Monster"]).objSize.x, std::get<0>(monsterObjects["Monster"]).objSize.y, -1.0f, -1.0f, 0.0f, 0.0f);
    WQFS::GetInstance().AddEvent("Landslide1", 1, 0, 0, 0.0f, 0.0f, eventObjects["Landslide1"].objSize.x, eventObjects["Landslide1"].objSize.y, 10.0f, 5.0f, 0.5f, 3.0f);
    WQFS::GetInstance().AddEvent("Landslide2", 1, 1, 0, 0.0f, 0.0f, eventObjects["Landslide2"].objSize.x, eventObjects["Landslide2"].objSize.y, 10.0f, 5.0f, 0.5f, 0.0f);
    WQFS::GetInstance().AddEvent("Earthquake1", 1, 0, 0, 0.0f, 0.0f, eventObjects["Earthquake1"].objSize.x, eventObjects["Earthquake1"].objSize.y, 5.0f, 3.0f, 0.0f, 2.0f);
    WQFS::GetInstance().AddEvent("Earthquake2", 1, 1, 0, 0.0f, 0.0f, eventObjects["Earthquake2"].objSize.x, eventObjects["Earthquake2"].objSize.y, 5.0f, 3.0f, 0.0f, 0.0f);
    WQFS::GetInstance().AddEvent("Earthquake3", 1, 2, 0, 0.0f, 0.0f, eventObjects["Earthquake3"].objSize.x, eventObjects["Earthquake3"].objSize.y, 5.0f, 3.0f, 0.0f, 1.0f);
    WQFS::GetInstance().AddEvent("Tornado1",    1, 0, 0, 0.0f, 0.0f, eventObjects["Tornado1"].objSize.x,    eventObjects["Tornado1"].objSize.y,    5.0f, 3.0f, 0.0f, 0.0f);
    WQFS::GetInstance().AddEvent("Tsunami1", 2, 0, 0, 0.0f, 0.0f, eventObjects["Tsunami1"].objSize.x, eventObjects["Tsunami1"].objSize.y, 10.0f, 3.0f, 0.0f, 2.0f);
    
	WQFS::GetInstance().GetEvent("Earthquake1").SetIsMove(true);
    WQFS::GetInstance().GetEvent("Earthquake2").SetIsMove(true);
    WQFS::GetInstance().GetEvent("Earthquake3").SetIsMove(true);
    //WQFS::GetInstance().GetEvent("Tornado1").SetIsMove(true);
     
    mapWidth = width * 5;
    mapHeight = height * 5;

    level.Load("level/1.lvl", mapWidth, mapHeight);

    for (auto npc : WQFS::GetInstance().npcs) {
	    npcObjects[npc.first].first.objPosition.x = npc.second.GetPositionX();
        npcObjects[npc.first].first.objPosition.y = npc.second.GetPositionY();
    }

    for (auto e : WQFS::GetInstance().worldEvents) {
        if (e.second.GetType() != 0) {
            eventObjects[e.first].objPosition.x = e.second.GetPositionX();
            eventObjects[e.first].objPosition.y = e.second.GetPositionY();
        }
    }

    for (auto e : WQFS::GetInstance().worldEvents) {
        if (e.second.GetType() == 0) {
            std::get<0>(monsterObjects[e.first]).objPosition.x = e.second.GetPositionX();
            std::get<0>(monsterObjects[e.first]).objPosition.y = e.second.GetPositionY();
        }
    }

    for (const auto& def : WQFS::GetInstance().worldEvents) {
        if (def.second.GetType() == 2) {
            defaultPosition[def.first] = std::make_pair(eventObjects[def.first].objPosition, 0);
		}
    }

    for (const auto& npc : WQFS::GetInstance().npcs) {
        defaultColors[npc.first] = npcObjects[npc.first].first.objColor;
	}

    for (const auto& event : WQFS::GetInstance().worldEvents) {
        defaultColors[event.first] = eventObjects[event.first].objColor;
    }


    WQFS::GetInstance().AddItem("HP Posion", 0, 1, 1);
    WQFS::GetInstance().AddItem("Good HP Posion", 0, 2, 1);
    WQFS::GetInstance().AddItem("Mana Up Posion", 1, 2, 0);
    WQFS::GetInstance().AddItem("Iron", 2, 20, 0);
    WQFS::GetInstance().AddItem("Gold", 2, 50, 1);
    
    for (auto item : WQFS::GetInstance().comps) {
        if (item.first.find("HP") != std::string::npos) {
            inventory[item.second] = 1;
            continue;
        }
        inventory[item.second] = 0;
    }

    view = glm::mat4(0.0f);

    std::cout << "All width / height" <<std::endl << mapWidth << " / " << mapHeight << std::endl;

    textRenderer = new TextRenderer(width, height);
    textRenderer->load("fonts/arial.ttf", 64);

    for (auto event : WQFS::GetInstance().worldEvents) {
        if (event.first.find("Landslide") != std::string::npos) {
			std::cout << "Create particle generator for " << event.first << std::endl;
            particleGenerators[event.first] = ParticleGenerator(ResourceManager::GetShader("sprite"), ResourceManager::GetTexture("Rockfall"), 40);
        }        
    }

    pauseDelay = 0.25f;
    pauseDelayTimer = 0.0f;

    attackBox->objPosition.x = player->objPosition.x - 50.0f;
    attackBox->objPosition.y = player->objPosition.y;

    soundEngine = irrklang::createIrrKlangDevice();
    soundEngine->setSoundVolume(0.1f);

    stopDir = NONE;

    if (!useWQFS) {
        QuestList["Eliminate 1 Monster"] = std::make_tuple(0, glm::vec2(0.0f), false);
        QuestList["Eliminate 2 Monster"] = std::make_tuple(1, glm::vec2(0.0f), false);
        QuestList["Return 1 Item"] = std::make_tuple(2, glm::vec2(0.0f), false);
        QuestList["Return 2 Item"] = std::make_tuple(3, glm::vec2(0.0f), false);
        QuestList["Return 3 Item"] = std::make_tuple(4, glm::vec2(0.0f), false);
    }
}

void OpenGLCode::update() {
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = (float)glfwGetTime();

        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;


        glClearColor(170 / 255.0f, 170 / 255.0f, 170 / 255.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        view = glm::lookAt(glm::vec3(cameraPos, 0.0f), glm::vec3(cameraPos, 0.0f) + cameraFront, cameraUp);
        ResourceManager::GetShader("sprite").use().SetMat4("view", view);

        if (pauseDelayTimer <= pauseDelay) {
			pauseDelayTimer += deltaTime;
        }

        render();

        if (!mapLoading) {
            ProcessInput(window, deltaTime);
        }

        if (states == GAME_ACTIVE) {
            DoCollisions();

            CameraMove(deltaTime);

            if (useWQFS) {
                WQFS::GetInstance().CheckQuest(inventory, player->objSize.x, player->objSize.y, player->objPosition.x, player->objPosition.y);
                WQFS::GetInstance().CheckEvent();
            }

            for (const auto& event : WQFS::GetInstance().worldEvents) {
                if (event.second.GetType() == 1) {
                    if (event.first.find("Landslide") != std::string::npos) {
                        if (event.second.getDoEvent()) {
                            particleGenerators[event.first].Update(deltaTime, eventObjects[event.first], 1, glm::vec2(100.0f, 0.0f));
                        }
                        else {
                            particleGenerators[event.first].Idle(deltaTime);
                        }
                    }
                }
            }

            if (!mapLoading) {
                MoveSelf(deltaTime);
            }

            if (dangerousDelay < 5.0f) {
                dangerousDelay += deltaTime;
            }

            if (playerHitDelay < 1.5f) {
                playerHitDelay += deltaTime;

                if (playerHitDelay < 0.3f) {
                    player->alpha = 0.5f;
                }
                else if (playerHitDelay < 0.2f) {
                    player->alpha = 0.25f;
                }
                else if (playerHitDelay < 0.1f) {
                    player->alpha = 0.5f;
                }
                else {
                    player->alpha = 0.25f;
                }
            }
            else if (player->alpha != 1.0f) {
                player->alpha = 1.0f;
            }
            
            if (attackDelay < 0.7f) {
                attackDelay += deltaTime;
            }
            else if (attackDelay >= 0.5f) {
                isAttacked = false;
            }

            if (isMoving) {
                moveAnimationTimer += deltaTime;
            }
            else {
                moveAnimationTimer = 0.0f;
            }

            for (auto& monster : monsterObjects) {
                if (std::get<1>(monster.second) < 0.5f) {
                    std::get<1>(monster.second) += deltaTime;
                }

                if (std::get<1>(monster.second) < 0.3f) {
                    std::get<0>(monster.second).alpha = 1.0f;
                }
                else if (std::get<1>(monster.second) < 0.2f) {
                    std::get<0>(monster.second).alpha = 0.0f;
                }
                else if (std::get<1>(monster.second) < 0.1f) {
                    std::get<0>(monster.second).alpha = 1.0f;
                }
                else if (std::get<1>(monster.second) < 0.0f) {
                    std::get<0>(monster.second).alpha = 0.0f;
                }
            }
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}

void OpenGLCode::render() {
	effects->BeginRender();
    level.Draw(*sRenderer, cameraPos, glm::vec2(width, height));

    for (auto& event : WQFS::GetInstance().worldEvents) {
        if (event.second.GetType() == 1) {

            if (event.second.GetIsCanCollid()) {
                if (CheckCollision(cameraPos, glm::vec2(width, height), glm::vec2(event.second.GetPositionX(), event.second.GetPositionY()), glm::vec2(10 * 32 * 2, 32 * 2))) {
                    eventObjects[event.first].Draw(*sRenderer);

                    if (event.first.find("Earthquake") != std::string::npos) {
                        effects->shake = true;
                    }
                    else if (event.first.find("Tornado") != std::string::npos) {
                        eventObjects[event.first].objRotation += 10.0f * deltaTime;
                    }
                }
            }
            else if (event.first.find("Earthquake") != std::string::npos && !CheckCollision(cameraPos, glm::vec2(width, height), glm::vec2(event.second.GetPositionX(), event.second.GetPositionY()), glm::vec2(10 * 32 * 2, 32 * 2)) && !event.second.GetIsCanCollid()) {
                effects->shake = false;
            }
        }
        else if (event.second.GetType() == 2) {
            if (event.second.GetIsCanCollid()) {
                eventObjects[event.first].Draw(*sRenderer);
            }
        }
    }
    for (const auto& monster : WQFS::GetInstance().worldEvents) {
        //std::cout << monster.second.getVisible() << std::endl;
        if (monster.second.GetType() == 0 && monster.second.getVisible()) {
            if (std::get<1>(monsterObjects[monster.first]) >= 0.5f) {
                std::get<0>(monsterObjects[monster.first]).objColor = glm::vec3(1.0f, 0.2f, 0.1f);
            }
            else if (std::get<1>(monsterObjects[monster.first]) > 0.2f) {
                std::get<0>(monsterObjects[monster.first]).objColor = glm::vec3(1.0f, 0.0f, 0.0f);
            }
            else {
                std::get<0>(monsterObjects[monster.first]).objColor = defaultColors[monster.first];
            }

            std::get<0>(monsterObjects[monster.first]).Draw(*sRenderer);
        }
    }

    for (const auto& npc : WQFS::GetInstance().npcs) {
        for (auto& remainingObject : WQFS::GetInstance().questRemaining) {
            if (npc.second.getQuestNumber() == remainingObject.first && !std::get<1>(QuestObjects[remainingObject.first])) {
                MakeQusetObject(remainingObject.first, glm::vec2(npc.second.GetPositionX(), npc.second.GetPositionY()));
            }
		}

        npcObjects[npc.first].first.Draw(*sRenderer);

        if (npc.second.GetInDangerous()) {
            if (CheckCollision(glm::vec2(cameraPos.x + (width / 2), cameraPos.y + (height / 2)), glm::vec2(width, height), glm::vec2(npc.second.GetPositionX(), npc.second.GetPositionY()), glm::vec2(11 * 32 * 2, 32 * 2))) {
                textRenderer->renderText("HELP!", npc.second.GetPositionX() - cameraPos.x, npc.second.GetPositionY() - 64.0f - cameraPos.y, 0.5f, glm::vec3(0.0f));
            }

            showDangerousTime += deltaTime;
            npcObjects[npc.first].second += deltaTime;

            if (npcObjects[npc.first].second > 0.4f) {
                npcObjects[npc.first].second = 0.0f;
            }
            else if (npcObjects[npc.first].second > 0.2f) {
                npcObjects[npc.first].first.objSprite = ResourceManager::GetTexture("NPC1");
                npcObjects[npc.first].first.flipX *= -1;
            }
            else if (npcObjects[npc.first].second > 0.0f) {
                npcObjects[npc.first].first.objSprite = ResourceManager::GetTexture("NPC1Move");
                npcObjects[npc.first].first.flipX *= -1;
            }

            if (showDangerousTime >= 1.0f) {
                npcObjects[npc.first].first.objColor = glm::vec3(1.0f, 0.0f, 0.0f);
                showDangerousTime = 0.0f;
            }
            else if (showDangerousTime >= 0.5f) {
                npcObjects[npc.first].first.objColor = glm::vec3(0.0f, 0.0f, 1.0f);
            }
        }
        else {
            npcObjects[npc.first].first.objColor = glm::vec3(1.0f);
            showDangerousTime = 1.0f;
			npcObjects[npc.first].second += deltaTime;

            if (npcObjects[npc.first].first.objVelocity != glm::vec2(0.0f)) {
                if (npcObjects[npc.first].second > 0.5f) {
                    npcObjects[npc.first].second = 0.0f;
                }
                else if (npcObjects[npc.first].second > 0.25f) {
                    npcObjects[npc.first].first.objSprite = ResourceManager::GetTexture("NPC1");
                }
                else if (npcObjects[npc.first].second > 0.0f) {
                    npcObjects[npc.first].first.objSprite = ResourceManager::GetTexture("NPC1Move");
                }
            }

            if (npcObjects[npc.first].first.objVelocity.x > 0) {
                npcObjects[npc.first].first.flipX = true;
            }
            else if (npcObjects[npc.first].first.objVelocity.x < 0) {
                npcObjects[npc.first].first.flipX = false;
            }
        }

    }

    if (attackDelay < 0.5f) {
        attackBox->Draw(*sRenderer);
    }

    if (moveAnimationTimer > 0.5f) {
        moveAnimationTimer = 0.0f;
    }
    else if (moveAnimationTimer > 0.25f) {
        player->objSprite = ResourceManager::GetTexture("Player");
    }
    else if (moveAnimationTimer > 0.0f) {
		player->objSprite = ResourceManager::GetTexture("PlayerMove");
    }


    player->Draw(*sRenderer);

    for (auto particle : particleGenerators) {
        particle.second.Draw(*sRenderer);
    }

	effects->EndRender();

    effects->Render((float)glfwGetTime());

    for (int i = 0; i < hp; i++) {
        hpObjects->objPosition.x = 10.0f + (i * 60.0f) + cameraPos.x;
        hpObjects->objPosition.y = 10.0f + cameraPos.y;
        hpObjects->Draw(*sRenderer);
	}

    int cnt = 0;

    if (states == GAME_ACTIVE) {
        InventoryObject->objPosition.x = 100.0f + cameraPos.x;
        InventoryObject->objPosition.y = 80.0f + cameraPos.y;
        InventoryObject->Draw(*sRenderer);

        for (auto item : inventory) {
            std::stringstream itemCnt;
            itemCnt << item.second;
            itemObjects[item.first.GetName()].objPosition.x = inventoryItemPos[cnt].x + cameraPos.x;
            itemObjects[item.first.GetName()].objPosition.y = inventoryItemPos[cnt].y + cameraPos.y;
            itemObjects[item.first.GetName()].Draw(*sRenderer);
            textRenderer->renderText(itemCnt.str(), inventoryItemPos[cnt].x + 100.0f, inventoryItemPos[cnt].y + 90.0f, 0.5f, glm::vec3(0.95f));

            if (cnt < 2){
                std::stringstream itemInput;
                itemInput << (cnt + 1);
                textRenderer->renderText(itemInput.str(), inventoryItemPos[cnt].x + 50.0f, inventoryItemPos[cnt].y + 150.0f, 0.5f, glm::vec3(0.95f));
            }
            ++cnt;
        }
    }
    else if (states == GAME_MENU) {
        textRenderer->renderText("Pause", (width / 2) - 100.0f, 10.0f, 1.5f, glm::vec3(0.0f));

        textRenderer->renderText("Quest List", (width / 2) - 110.0f, 100.0f, 1.0f, glm::vec3(0.0f));

        int cnt = 1;
        for (std::string s : WQFS::GetInstance().GetQuestListByString(5)) {
            if ((cnt + 1) % 2 == 1) {
                textRenderer->renderText("Reward(" + s + ")", 150.0f, 150.0f + (40.0f * cnt++), 0.5f, glm::vec3(0.0f));
            }
            else {
                textRenderer->renderText(s, 50.0f, 150.0f + (40.0f * cnt++), 0.6f, glm::vec3(0.0f));
            }
        }
    }
    else if (states == GAME_MAIN_MENU) {
        textRenderer->renderText("WQFS", (width / 2) - 150.0f, 100.0f, 1.5f, glm::vec3(0.0f));
        textRenderer->renderText("Tech Demo Game", (width / 2) - 250.0f, 200.0f, 1.0f, glm::vec3(0.0f));

    }
}

void OpenGLCode::ProcessInput(GLFWwindow* window, float dt) {
    if (states == GAME_MENU && glfwGetKey(window, GLFW_KEY_SPACE)) {
        std::cout << "<<<EXIT>>>" << std::endl;
        glfwSetWindowShouldClose(window, true);
    }

    if (states == GAME_MAIN_MENU) {
        if (glfwGetKey(window, GLFW_KEY_SPACE)) {
            soundEngine->play2D("audio/background.wav", true);
            states = GAME_ACTIVE;
        }
        if (glfwGetKey(window, GLFW_KEY_ESCAPE)) {
            std::cout << "<<<EXIT>>>" << std::endl;
            glfwSetWindowShouldClose(window, true);
        }
    }
    else if (states != GAME_MAIN_MENU && glfwGetKey(window, GLFW_KEY_ESCAPE) && pauseDelayTimer > pauseDelay) {
        if (states == GAME_ACTIVE) {
            states = GAME_MENU;
			WQFS::GetInstance().Pause();
        }
        else if (states == GAME_MENU) {
            states = GAME_ACTIVE;
            WQFS::GetInstance().Resume();
        }

        pauseDelayTimer = 0.0f;
    }
    else if (states == GAME_ACTIVE) {
        float velocityX = player->objVelocity.x * dt;
        float velocityY = player->objVelocity.y * dt;

        //Up
        if (!stopInput[0] && (glfwGetKey(window, GLFW_KEY_W) || glfwGetKey(window, GLFW_KEY_UP)) && player->objPosition.y > 0) {
            playerLastDir = UP;
            player->objPosition.y -= velocityY;
			isMoving = true;
        }
        //Down
        if (!stopInput[1] && (glfwGetKey(window, GLFW_KEY_S) || glfwGetKey(window, GLFW_KEY_DOWN)) && player->objPosition.y < mapHeight - player->objSize.x) {
            playerLastDir = DOWN;
            player->objPosition.y += velocityY;
            isMoving = true;
        }
        //Left
        if (!stopInput[2] && (glfwGetKey(window, GLFW_KEY_A) || glfwGetKey(window, GLFW_KEY_LEFT)) && player->objPosition.x > 0) {
            playerLastDir = LEFT;
            player->objPosition.x -= velocityX;
            isMoving = true;
			player->flipX = false;
        }
        //Right
        if (!stopInput[3] && (glfwGetKey(window, GLFW_KEY_D) || glfwGetKey(window, GLFW_KEY_RIGHT)) && player->objPosition.x < mapWidth - player->objSize.y) {
            playerLastDir = RIGHT;
            player->objPosition.x += velocityX;
            isMoving = true;
            player->flipX = true;
        }
        //Attack
        if (glfwGetKey(window, GLFW_KEY_SPACE) && attackDelay >= 0.7f) {
            if (playerLastDir == UP) {
                attackBox->objPosition.x = player->objPosition.x + 10.0f;
                attackBox->objPosition.y = player->objPosition.y - 80.0f;
            }
            else if (playerLastDir == DOWN) {
                attackBox->objPosition.x = player->objPosition.x + 10.0f;
                attackBox->objPosition.y = player->objPosition.y + 100.0f;
            }
            else if (playerLastDir == LEFT) {
                attackBox->objPosition.x = player->objPosition.x - 80.0f;
                attackBox->objPosition.y = player->objPosition.y + 10.0f;
            }
            else if (playerLastDir == RIGHT) {
                attackBox->objPosition.x = player->objPosition.x + 100.0f;
                attackBox->objPosition.y = player->objPosition.y + 10.0f;
            }

            attackDelay = 0.0f;
			isAttacked = true;
			soundEngine->play2D("audio/attack.wav", false);
        }

        if (glfwGetKey(window, GLFW_KEY_1) && pauseDelayTimer > pauseDelay && inventory[WQFS::GetInstance().GetItem("HP Posion")] > 0) {
            --inventory[WQFS::GetInstance().GetItem("HP Posion")];
            ++hp;
            pauseDelayTimer = 0;
        }
        if (glfwGetKey(window, GLFW_KEY_2) && pauseDelayTimer > pauseDelay && inventory[WQFS::GetInstance().GetItem("Good HP Posion")] > 0) {
            --inventory[WQFS::GetInstance().GetItem("Good HP Posion")];
            hp += 2;
            pauseDelayTimer = 0;
        }

        if (!(glfwGetKey(window, GLFW_KEY_W) || glfwGetKey(window, GLFW_KEY_UP)) && !(glfwGetKey(window, GLFW_KEY_S) || glfwGetKey(window, GLFW_KEY_DOWN))&& !(glfwGetKey(window, GLFW_KEY_A) || glfwGetKey(window, GLFW_KEY_LEFT))&& !(glfwGetKey(window, GLFW_KEY_D) || glfwGetKey(window, GLFW_KEY_RIGHT))) {
            isMoving = false;
            moveAnimationTimer = 0.0f;
        }
    }
}

void OpenGLCode::Reset() {
    player->objPosition = glm::vec2(width / 2, height / 2);
    cameraPos = glm::vec2(0.0f);

    states = GAME_MAIN_MENU;

}

void OpenGLCode::MakeQusetObject(int questNumber, glm::vec2 offset) {
    std::vector<std::string> itemSpriteName;

    for (auto name : WQFS::GetInstance().comps) {
        itemSpriteName.push_back(name.first);
    }

    if (std::get<1>(WQFS::GetInstance().questList[questNumber]) == 3) {
        std::get<2>(QuestObjects[questNumber]) = true;
		questGameObject->objSize = glm::vec2(40.0f);
    }

    for (int i = 0; i < WQFS::GetInstance().questRemaining[questNumber]; i++) {
        int r = rand() % 5;

        questGameObject->objSprite = ResourceManager::GetTexture(itemSpriteName[r]);

        questGameObject->objPosition = obstaclePosition[i] + offset;
        questGameObject->objColor = obstacleColors[i];
        std::get<0>(QuestObjects[questNumber]).push_back(*questGameObject);
		std::cout << "Generate Quest Object at (" << questGameObject->objPosition.x << ", " << questGameObject->objPosition.y << ")" << std::endl;
    }
    std::get<1>(QuestObjects[questNumber]) = true;

    questGameObject->objSize = glm::vec2(25.0f);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void OpenGLCode::MoveSelf(float dt) {
    float timeScale = 1.0f;

    if (changeMoveTime >= 5.0f) {
        changedir = true;

        changeMoveTime = 0;
    }
    else {
        changeMoveTime += deltaTime * timeScale;
    }

    for (auto& npc : WQFS::GetInstance().npcs) {
        if (!npc.second.GetInDangerous()) {
            if (changedir) {
                npcObjects[npc.first].first.objVelocity = glm::vec2((rand() % 3) - 1, (rand() % 3) - 1);
                //std::cout << npcObjects[npc.first].objVelocity.x << " " << npcObjects[npc.first].objVelocity.y << std::endl;
            }

            if ((npcObjects[npc.first].first.objPosition.x < 0 && npcObjects[npc.first].first.objVelocity.x == -1)) npcObjects[npc.first].first.objVelocity.x = 0;
            if ((npcObjects[npc.first].first.objPosition.y < 0 && npcObjects[npc.first].first.objVelocity.y == -1)) npcObjects[npc.first].first.objVelocity.y = 0;

            npcObjects[npc.first].first.objPosition.x += npcObjects[npc.first].first.objVelocity.x * 50 * dt * timeScale;
            npcObjects[npc.first].first.objPosition.y += npcObjects[npc.first].first.objVelocity.y * 50 * dt * timeScale;
            
            
            
            //Up
            /*if (glfwGetKey(window, GLFW_KEY_I)) {
                npcObjects[npc.first].first.objPosition.y -= 100 * dt * timeScale;
            }
            //Down
            if (glfwGetKey(window, GLFW_KEY_K)) {
                npcObjects[npc.first].first.objPosition.y += 100 * dt * timeScale;
            }
            //Left
            if (glfwGetKey(window, GLFW_KEY_J)) {
                npcObjects[npc.first].first.objPosition.x -= 100 * dt * timeScale;
            }
            //Right
            if (glfwGetKey(window, GLFW_KEY_L)) {
                npcObjects[npc.first].first.objPosition.x += 100 * dt * timeScale;
            }*/

            npc.second.SetPosition(npcObjects[npc.first].first.objPosition.x, npcObjects[npc.first].first.objPosition.y);
        }
	}

    for (auto& monster : WQFS::GetInstance().worldEvents) {
        if (monster.second.GetType() == 0) {
            if (changedir) {
                std::get<0>(monsterObjects[monster.first]).objVelocity = glm::vec2((rand() % 3) - 1, (rand() % 3) - 1);
            }

            if ((std::get<0>(monsterObjects[monster.first]).objPosition.x < 0 && std::get<0>(monsterObjects[monster.first]).objVelocity.x == -1)) std::get<0>(monsterObjects[monster.first]).objVelocity.x = 0;
            if ((std::get<0>(monsterObjects[monster.first]).objPosition.y < 0 && std::get<0>(monsterObjects[monster.first]).objVelocity.y == -1)) std::get<0>(monsterObjects[monster.first]).objVelocity.y = 0;

            std::get<0>(monsterObjects[monster.first]).objPosition.x += std::get<0>(monsterObjects[monster.first]).objVelocity.x * 30 * dt * timeScale;
            std::get<0>(monsterObjects[monster.first]).objPosition.y += std::get<0>(monsterObjects[monster.first]).objVelocity.y * 30 * dt * timeScale;

			monster.second.SetPosition(std::get<0>(monsterObjects[monster.first]).objPosition.x, std::get<0>(monsterObjects[monster.first]).objPosition.y);
        }
    }

    for (auto& event : WQFS::GetInstance().worldEvents) {
        if (changedir) {
            if (event.second.GetType() == 1) {
                if (event.second.GetIsMove()) {
                    unsigned int x = rand() % mapWidth;
                    unsigned int y = rand() % mapHeight;

                    eventObjects[event.first].objPosition = glm::vec2(x - eventObjects[event.first].objSize.x, y - eventObjects[event.first].objSize.y);

                    if (eventObjects[event.first].objPosition.x <= 0) {
						eventObjects[event.first].objPosition.x = 0.0f;
                    }
                    if (eventObjects[event.first].objPosition.y <= 0) {
						eventObjects[event.first].objPosition.y = 0.0f;
                    }
                }
                event.second.SetPosition(eventObjects[event.first].objPosition.x, eventObjects[event.first].objPosition.y);
            }
        }
	}


    for (auto& def : defaultPosition) {
        if (WQFS::GetInstance().GetEvent(def.first).GetIsCanCollid()) {
            switch (std::get<1>(def.second)) {
                case 0: eventObjects[def.first].objPosition.x -= 300 * dt * timeScale; break;
                case 1: eventObjects[def.first].objPosition.x += 300 * dt * timeScale; break;
                case 2: eventObjects[def.first].objPosition.y -= 300 * dt * timeScale; break;
                case 3: eventObjects[def.first].objPosition.y += 300 * dt * timeScale; break;
            }

            WQFS::GetInstance().GetEvent(def.first).SetPosition(eventObjects[def.first].objPosition.x, eventObjects[def.first].objPosition.y);
		}
        else {
			eventObjects[def.first].objPosition = std::get<0>(def.second);
            WQFS::GetInstance().GetEvent(def.first).SetPosition(eventObjects[def.first].objPosition.x, eventObjects[def.first].objPosition.y);
        }
    }

	if (changedir)  changedir = false;
}

void OpenGLCode::CameraMove(float dt) {
    float nextX = -1;
    float nextY = -1;

    if (!mapLoading) {
        if (player->objPosition.x > 0 && player->objPosition.x < cameraNextPos.x - (player->objSize.x / 2)) {
            nextX = cameraNextPos.x - (float)width;
            std::cout << "-X" << std::endl <<
                player->objPosition.x << " " << cameraNextPos.x + 1.0f << std::endl;
        }
        else if (player->objPosition.x < mapWidth - (player->objSize.x / 2) && player->objPosition.x > cameraNextPos.x + (float)width - (player->objSize.x / 2)) {
            nextX = cameraNextPos.x + (float)width;
            std::cout << "+X" << std::endl << 
                player->objPosition.x << " " << cameraNextPos.x + (float)width - (player->objSize.x / 2) << std::endl;
        }
        else if (player->objPosition.y > 0 && player->objPosition.y < cameraNextPos.y - (player->objSize.y / 2)) {
            nextY = cameraNextPos.y - (float)height;
            std::cout << "-Y" << std::endl <<
                player->objPosition.y << " " << cameraNextPos.y + 1.0f << std::endl;
        }
        else if (player->objPosition.y < mapHeight - (player->objSize.y / 2) && player->objPosition.y > cameraNextPos.y + (float)height - (player->objSize.y / 2)) {
            nextY = cameraNextPos.y + (float)height;
            std::cout << "+Y" << std::endl <<
                player->objPosition.y << " " << cameraNextPos.y + (float)height - (player->objSize.y / 2) << std::endl;
        }

        if (nextX != -1 || nextY != -1) {
			if (nextX == -1) nextX = cameraNextPos.x;
			if (nextY == -1) nextY = cameraNextPos.y;
            cameraNextPos = glm::vec2(nextX, nextY);

            mapLoading = true;
        }
    }
    else {
        WQFS::GetInstance().Pause();
        if (cameraPos.x != cameraNextPos.x) {
            if (cameraPos.x < cameraNextPos.x) {
                cameraPos.x += CameraVelocity * dt;

                if (cameraPos.x > cameraNextPos.x) {
                    cameraPos.x = cameraNextPos.x;
                    player->objPosition.x = cameraPos.x;
                }
            }
            else {
                cameraPos.x -= CameraVelocity * dt;

                if (cameraPos.x < cameraNextPos.x) {
                    cameraPos.x = cameraNextPos.x;
                    player->objPosition.x = cameraPos.x + (float)width - player->objSize.x;
                }
            }
        }
        else if (cameraPos.y != cameraNextPos.y) {
            if (cameraPos.y < cameraNextPos.y) {
                cameraPos.y += CameraVelocity * dt;

                if (cameraPos.y > cameraNextPos.y) {
                    cameraPos.y = cameraNextPos.y;
                    player->objPosition.y = cameraPos.y;
                }
            }
            else {
                cameraPos.y -= CameraVelocity * dt;

                if (cameraPos.y < cameraNextPos.y) {
                    cameraPos.y = cameraNextPos.y;
                    player->objPosition.y = cameraPos.y + (float)height - player->objSize.y;
                }
            }
        }
        else {
            mapLoadingDelay += dt;

            if (mapLoadingDelay > 0.25f) {
				mapLoadingDelay = 0.0f;
                mapLoading = false;
                WQFS::GetInstance().Resume();
            }
		}

		//std::cout << cameraPos.x << " " << cameraPos.y << std::endl;
    }
}

bool OpenGLCode::CheckCollision(GameObject& object1, GameObject& object2) {
    bool collisionX = object1.objPosition.x + object1.objSize.x >= object2.objPosition.x &&
		object2.objPosition.x + object2.objSize.x >= object1.objPosition.x;
    bool collisionY = object1.objPosition.y + object1.objSize.y >= object2.objPosition.y &&
		object2.objPosition.y + object2.objSize.y >= object1.objPosition.y;

    return collisionX && collisionY;
}

bool OpenGLCode::CheckCollision(glm::vec2 object1Pos, glm::vec2 object1Size, glm::vec2 object2Pos, glm::vec2 object2Size) {
    bool collisionX = object1Pos.x + object1Size.x >= object2Pos.x &&
        object2Pos.x + object2Size.x >= object1Pos.x;
    bool collisionY = object1Pos.y + object1Size.y >= object2Pos.y &&
        object2Pos.y + object2Size.y >= object1Pos.y;

    return collisionX && collisionY;
}

Direction OpenGLCode::CheckCollisionDirection(GameObject& object1, GameObject& object2, bool isPlayer) {
    bool collisionX = object1.objPosition.x + object1.objSize.x >= object2.objPosition.x &&
        object2.objPosition.x + object2.objSize.x >= object1.objPosition.x;
    bool collisionY = object1.objPosition.y + object1.objSize.y >= object2.objPosition.y &&
        object2.objPosition.y + object2.objSize.y >= object1.objPosition.y;

    if (collisionX && collisionY) {
        glm::vec2 centerA = object1.objPosition + object1.objSize / 2.0f;
        glm::vec2 centerB = object2.objPosition + object2.objSize / 2.0f;
        glm::vec2 distance = centerB - centerA;

        glm::vec2 halfExtentsA = object1.objSize / 2.0f;
        glm::vec2 halfExtentsB = object2.objSize / 2.0f;

        glm::vec2 minSeparation = halfExtentsA + halfExtentsB;
        
        glm::vec2 penetrations = minSeparation - glm::abs(distance);

        if (penetrations.x < penetrations.y) {
            if (distance.x < 0) {
                if (isPlayer) {
                    stopInput[2] = true;
                }
                return LEFT;
            }
            else {
                if (isPlayer) {
                    stopInput[3] = true;
                }
                return RIGHT;
            }
        }
        else {
            if (distance.y < 0) {
                if (isPlayer) {
                    stopInput[0] = true;
                }
                return UP;
            }
            else {
                if (isPlayer) {
                    stopInput[1] = true;
                }
                return DOWN;
            }
        }
    }
    else {
        return NONE;
    }
}

void OpenGLCode::DoCollisions() {
    Direction lastDir;
    Direction npcDir;
    Direction monsterDir;
    stopDir = NONE;
    for (auto& tile : level.walls) {
        Direction lastDir = CheckCollisionDirection(*player, tile);

        if (stopDir == NONE) {
            stopDir = lastDir;
        }

        for (auto& npc : npcObjects) {
            npcDir = CheckCollisionDirection(npc.second.first, tile, false);
            if ((npcDir == LEFT || npcDir == RIGHT) && npc.second.first.objVelocity.x != 0) {
                npc.second.first.objVelocity.x = 0.0f;
            }
            if ((npcDir == UP || npcDir == DOWN) && npc.second.first.objVelocity.y != 0) {
                npc.second.first.objVelocity.y = 0.0f;
            }
        }

        for (auto& monster : monsterObjects) {
            monsterDir = CheckCollisionDirection(std::get<0>(monster.second), tile, false);
            if ((monsterDir == LEFT || monsterDir == RIGHT) && std::get<0>(monster.second).objVelocity.x != 0) {
                std::get<0>(monster.second).objVelocity.x = 0.0f;
            }
            if ((monsterDir == UP || monsterDir == DOWN) && std::get<0>(monster.second).objVelocity.y != 0) {
                std::get<0>(monster.second).objVelocity.y = 0.0f;
            }
        }
    }

    if (stopDir == NONE) {
        stopInput[0] = false;
        stopInput[1] = false;
        stopInput[2] = false;
        stopInput[3] = false;
    }

    for (auto& monster : monsterObjects) {
        if (WQFS::GetInstance().GetEvent(monster.first).getVisible()) {
            for (auto& event : eventObjects) {
                if (std::get<1>(monster.second) >= 5.0f && WQFS::GetInstance().GetEvent(event.first).GetIsCanCollid() && CheckCollision(std::get<0>(monster.second), event.second)) {
                    monsterHp = WQFS::GetInstance().GetEvent(monster.first).takeDamage(1);

                    if (monsterHp <= 0) {
                        soundEngine->play2D("audio/death.wav", false);
                    }
                    std::get<1>(monster.second) = -1.0f;
                }

                if (WQFS::GetInstance().GetEvent(event.first).GetIsCanCollid() && playerHitDelay >= 1.5f && CheckCollision(*player, event.second)) {
                    --hp;
                    playerHitDelay = 0.0f;
                }
            }
            
            if (std::get<1>(monster.second) >= 0.5f && attackDelay < 0.5f && CheckCollision(*attackBox, std::get<0>(monster.second))) {
                monsterHp = WQFS::GetInstance().GetEvent(monster.first).takeDamage(damage + inventory[WQFS::GetInstance().GetItem("Mana Up Posion")]);

                if (monsterHp <= 0) {
                    soundEngine->play2D("audio/death.wav", false);
                }

                std::get<1>(monster.second) = 0.0f;
            }

            if (playerHitDelay >= 1.5f && CheckCollision(*player, std::get<0>(monster.second))) {
                --hp;
                playerHitDelay = 0.0f;
            }
        }
    }


    for (auto& questObject : QuestObjects) {
        for (int i = 0; i < std::get<0>(questObject.second).size(); i++) {
            if (attackDelay < 0.5f && std::get<2>(questObject.second) && CheckCollision(std::get<0>(questObject.second)[i], *attackBox)) {
                std::get<0>(questObject.second).erase(std::get<0>(questObject.second).begin() + i);
                WQFS::GetInstance().DiscountRemainingObstacles(questObject.first);
                i = 0;
                continue;
            }
            else if (!std::get<2>(questObject.second) && CheckCollision(std::get<0>(questObject.second)[i], *player)) {
                std::get<0>(questObject.second).erase(std::get<0>(questObject.second).begin() + i);
                WQFS::GetInstance().DiscountRemainingObstacles(questObject.first);
                i = 0;
                continue;
            }
            std::get<0>(questObject.second)[i].Draw(*sRenderer);
        }
    }

    for (auto npc : WQFS::GetInstance().npcs) {
        for (auto event : WQFS::GetInstance().worldEvents) {
            if (event.first.find("Tornado") != std::string::npos && event.second.GetIsCanCollid() && CheckCollision(npcObjects[npc.first].first, eventObjects[event.first])) {
                if (npcObjects[npc.first].first.objPosition.x >= eventObjects[event.first].objPosition.x + (eventObjects[event.first].objSize.x / 2) - (npcObjects[npc.first].first.objSize.x / 2)) {
                    npcObjects[npc.first].first.objPosition.x -= 50 * deltaTime;
                }
                else {
                    npcObjects[npc.first].first.objPosition.x += 50 * deltaTime;
                }
                if (event.second.GetIsCanCollid() && CheckCollision(npcObjects[npc.first].first, eventObjects[event.first])) {
                    if (npcObjects[npc.first].first.objPosition.y >= eventObjects[event.first].objPosition.y + (eventObjects[event.first].objSize.y / 2) - (npcObjects[npc.first].first.objSize.y / 2)) {
                        npcObjects[npc.first].first.objPosition.y -= 50 * deltaTime;
                    }
                    else {
                        npcObjects[npc.first].first.objPosition.y += 50 * deltaTime;
                    }
                }
            }
		}
    }
}