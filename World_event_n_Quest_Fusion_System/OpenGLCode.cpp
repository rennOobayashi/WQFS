#include "OpenGLCode.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

glm::vec2 cameraPos(0.0f, 0.0f);
glm::vec2 cameraNextPos(0.0f, 0.0f);
glm::vec3 cameraFront(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp(0.0f, 1.0f, 0.0f);
glm::vec2 attackCollidePos(0.0f, 0.0f);
const glm::vec2 playerSize(100.0f, 100.0f);
const float playerVelocity(500.0f);
const float CameraVelocity(1000.0f);

OpenGLCode::OpenGLCode(unsigned int _width, unsigned int _height)
	: states(GAME_MENU), width(_width), height(_height), hp(3), changedir(false), showDangerousTime(1.0f), dangerousDelay(5.0f), mapLoading(false), mapLoadingDelay(0.0f), getItemFirstTime(false), attackDelay(1.0f), isAttacked(false) {
    init();
    srand((unsigned int)time(NULL));

}

OpenGLCode::~OpenGLCode() {
    delete player;
	delete sRenderer;
	npcObjects.clear();
    monsterObjects.clear();
    eventObjects.clear();
    ResourceManager::Clear();
    WQFS::Clear();
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

    window = glfwCreateWindow(width, height, "test", nullptr, nullptr);
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

    ResourceManager::GetShader("sprite").use().SetInt("sprite", 0);
    ResourceManager::GetShader("sprite").use().SetMat4("projection", projection);

    ResourceManager::GetShader("Particle").use().SetInt("sprite", 0);
    ResourceManager::GetShader("Particle").use().SetMat4("projection", projection);

    ResourceManager::LoadTexture("Texture/Player.png", true, "Player");
    ResourceManager::LoadTexture("Texture/PlayerMove.png", true, "PlayerMove");
    ResourceManager::LoadTexture("Texture/NPC.png", true, "NPC");
    ResourceManager::LoadTexture("Texture/Monster.png", true, "Monster");
    ResourceManager::LoadTexture("Texture/Event.png", true, "Event");
    ResourceManager::LoadTexture("Texture/Tree.png", true, "Tree");
    ResourceManager::LoadTexture("Texture/Tide_by_Gemini.png", true, "Tsunami");

	Shader spriteShader = ResourceManager::GetShader("sprite");
	sRenderer = new SpriteRenderer(spriteShader);

    glm::vec2 playerPos(width / 2, height / 2);
    attackCollidePos = glm::vec2(playerPos.x + 20.0f, playerPos.y);

    npcObjects["Normal"] = GameObject(ResourceManager::GetTexture("NPC"), glm::vec2(0.0f, 0.0f), glm::vec2(200.0f), 0.0f, glm::vec3(0.1f, 0.5f, 1.0f));
    std::get<0>(monsterObjects["Monster"]) = GameObject(ResourceManager::GetTexture("Monster"), glm::vec2(width - 200.0f, 0.0f), glm::vec2(200.0f), 0.0f, glm::vec3(1.0f, 0.2f, 0.1f));
    std::get<1>(monsterObjects["Monster"]) = 0.5f;
    eventObjects["Landslide"] = GameObject(ResourceManager::GetTexture("Event"), glm::vec2((width / 2) - 250.0f, (height / 2) - 250.0f), glm::vec2(500.0f), 0.0f, glm::vec3(0.4f, 0.1f, 1.0f));
    eventObjects["Earthquake"] = GameObject(ResourceManager::GetTexture("Event"), glm::vec2(0.0f, height - 400.0f), glm::vec2(400.0f), 0.0f, glm::vec3(0.7f, 0.1f, 1.0f));
    eventObjects["Tsunami"] = GameObject(ResourceManager::GetTexture("Tsunami"), glm::vec2(width * 2 - 250.0f, height / 2), glm::vec2(250.0f, 250.0f), 0.0f, glm::vec3(0.7f, 0.1f, 1.0f));
    player = new GameObject(ResourceManager::GetTexture("Player"), playerPos, playerSize, 0.0f, glm::vec3(1.0f), glm::vec2(playerVelocity));
	attackBox = new GameObject(ResourceManager::GetTexture("NPC"), attackCollidePos, glm::vec2(50.0f, 100.0f), 0.0f, glm::vec3(1.0f, 0.3f, 0.3f));

    WQFS::GetInstance().AddNPC("Normal", 0, npcObjects["Normal"].objPosition.x, npcObjects["Normal"].objPosition.y, npcObjects["Normal"].objSize.x, npcObjects["Normal"].objSize.y, 5.0f);

    WQFS::GetInstance().AddEvent("Monster", 0, 2, std::get<0>(monsterObjects["Monster"]).objPosition.x, std::get<0>(monsterObjects["Monster"]).objPosition.y, std::get<0>(monsterObjects["Monster"]).objSize.x, std::get<0>(monsterObjects["Monster"]).objSize.y, -1.0f, -1.0f, 0.0f);
    WQFS::GetInstance().AddEvent("Landslide", 1, 2, eventObjects["Landslide"].objPosition.x, eventObjects["Landslide"].objPosition.y, eventObjects["Landslide"].objSize.x, eventObjects["Landslide"].objSize.y, 10.0f, 5.0f, 0.3f);
    WQFS::GetInstance().AddEvent("Earthquake", 1, 2, eventObjects["Earthquake"].objPosition.x, eventObjects["Earthquake"].objPosition.y, eventObjects["Earthquake"].objSize.x, eventObjects["Earthquake"].objSize.y, 5.0f, 3.0f, 0.0f);
    WQFS::GetInstance().AddEvent("Tsunami", 2, 2, eventObjects["Tsunami"].objPosition.x, eventObjects["Tsunami"].objPosition.y, eventObjects["Tsunami"].objSize.x, eventObjects["Tsunami"].objSize.y, 10.0f, 3.0f, 0.0f);

	WQFS::GetInstance().GetEvent("Earthquake").SetIsMove(true);

    landslide.push_back("Landslide");

    for (const auto& def : WQFS::GetInstance().worldEvents) {
        if (def.second.GetType() == 2) {
            defaultPosition[def.first] = std::make_pair(eventObjects[def.first].objPosition, 0);
		}
    }

    for (const auto& npc : WQFS::GetInstance().npcs) {
        defaultColors[npc.first] = npcObjects[npc.first].objColor;
	}

    for (const auto& event : WQFS::GetInstance().worldEvents) {
        defaultColors[event.first] = eventObjects[event.first].objColor;
    }


    WQFS::GetInstance().AddItem("HP Posion", 0, 30, 0);
    WQFS::GetInstance().AddItem("GOOD HP Posion", 0, 50, 1);
    WQFS::GetInstance().AddItem("Stone Sword", 2, 30, 0);
    WQFS::GetInstance().AddItem("Iron", 3, 20, 0);
    WQFS::GetInstance().AddItem("Gold", 3, 50, 1);

    states = GAME_ACTIVE;

    view = glm::mat4(0.0f);

    mapWidth = width * 10;
    mapHeight = height * 10;

    std::cout << "All width / height" <<std::endl << mapWidth << " / " << mapHeight << std::endl;

    textRenderer = new TextRenderer(width, height);
    textRenderer->load("fonts/arial.ttf", 32);

    particleGenerator = new ParticleGenerator(ResourceManager::GetShader("sprite"), ResourceManager::GetTexture("Event"), 40);

    pauseDelay = 0.15f;
    pauseDelayTimer = 1.0f;

	level.Load("level/1.lvl", width, height);
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

        if (states != GAME_MENU) {
            DoCollisions();
            CameraMove(deltaTime);

            WQFS::GetInstance().CheckQuest(inventory, player->objSize.x, player->objSize.y, player->objPosition.x, player->objPosition.y);
            WQFS::GetInstance().CheckEvent();


            for (const auto& event : WQFS::GetInstance().worldEvents) {
                if (event.second.GetType() == 1) {
                    for (const auto& ls : landslide) {
                        if (ls == event.first) {
                            if (event.second.getDoEvent()) {
                                particleGenerator->Update(deltaTime, eventObjects[event.first], 1, glm::vec2(100.0f, 0.0f));
                            }
                            else {
                                particleGenerator->Idle(deltaTime);
                            }
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

            if (attackDelay < 0.7f) {
                attackDelay += deltaTime;
            }
            else if (attackDelay >= 0.5f) {
                isAttacked = false;
            }

            for (auto& monster : monsterObjects) {
                if (std::get<1>(monster.second) < 0.5f) {
                    std::get<1>(monster.second) += deltaTime;
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
	level.Draw(*sRenderer);

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

            std::get<0>(monsterObjects[monster.first]).Draw(*sRenderer, true);
        }
    }

    for (const auto& event : WQFS::GetInstance().worldEvents) {
        eventObjects[event.first].Draw(*sRenderer, true);

        if (event.second.GetType() != 0) {
            if (event.second.GetIsCanCollid()) {
                if (CheckCollision(glm::vec2(cameraPos.x + (width / 2), cameraPos.y + (height / 2)), glm::vec2(width, height), glm::vec2(event.second.GetPositionX(), event.second.GetPositionY()), glm::vec2(10 * 32 * 2, 32 * 2))) {
                    textRenderer->renderText("Dangerous!", event.second.GetPositionX() - cameraPos.x, event.second.GetPositionY() - cameraPos.y, 2.0f, glm::vec3(0.0f));
                }
                eventObjects[event.first].objColor = glm::vec3(1.0f, 0.0f, 0.0f);
            }
            else {
                eventObjects[event.first].objColor = defaultColors[event.first];
            }

        }
    }

    for (const auto& npc : WQFS::GetInstance().npcs) {
        npcObjects[npc.first].Draw(*sRenderer, true);

        if (npc.second.GetInDangerous()) {
            if (CheckCollision(glm::vec2(cameraPos.x + (width / 2), cameraPos.y + (height / 2)), glm::vec2(width, height), glm::vec2(npc.second.GetPositionX(), npc.second.GetPositionY()), glm::vec2(11 * 32 * 2, 32 * 2))) {
                textRenderer->renderText("Quest Here!", npc.second.GetPositionX() - cameraPos.x, npc.second.GetPositionY() - cameraPos.y, 2.0f, glm::vec3(0.0f));
            }

            showDangerousTime += deltaTime;

            if (showDangerousTime >= 1.0f) {
                npcObjects[npc.first].objColor = glm::vec3(1.0f, 0.0f, 0.0f);
                showDangerousTime = 0.0f;
            }
            else if (showDangerousTime >= 0.5f) {
                npcObjects[npc.first].objColor = glm::vec3(0.0f, 0.0f, 1.0f);
            }
        }
        else {
            if (!npc.second.GetCanDangerous()) {
                if (CheckCollision(glm::vec2(cameraPos.x + (width / 2), cameraPos.y + (height / 2)), glm::vec2(width, height), glm::vec2(npc.second.GetPositionX(), npc.second.GetPositionY()), glm::vec2(6 * 32 * 2, 32 * 2))) {
                    textRenderer->renderText("Delay!", npc.second.GetPositionX() - cameraPos.x, npc.second.GetPositionY() - cameraPos.y, 2.0f, glm::vec3(0.0f));
                }
            }
            npcObjects[npc.first].objColor = glm::vec3(0.1f, 0.5f, 1.0f);
            showDangerousTime = 1.0f;
        }

    }

    if (attackDelay < 0.5f) {
        attackBox->Draw(*sRenderer);
    }


    player->Draw(*sRenderer, true);

    particleGenerator->Draw(*sRenderer);

    std::stringstream sHp;
    sHp << hp;

    textRenderer->renderText("HP - " + sHp.str(), 1.0f, 5.0f, 2.0f);


    if (states == GAME_MENU) {
        textRenderer->renderText("Pause", (width / 2) - 100.0f, 10.0f, 3.0f, glm::vec3(0.0f));

        textRenderer->renderText("Quest List", (width / 2) - 110.0f, 100.0f, 2.0f, glm::vec3(0.0f, 0.7f, 1.0f));

        int cnt = 1;
        for (std::string s : WQFS::GetInstance().GetQuestListByString(5)) {
            textRenderer->renderText(s, 100.0f, 150.0f * cnt++, 1.25f, glm::vec3(0.3f, 0.9f, 1.0f));
        }
    }
}

void OpenGLCode::ProcessInput(GLFWwindow* window, float dt) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) && pauseDelayTimer > pauseDelay) {
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

    if (states == GAME_ACTIVE) {
        float velocityX = player->objVelocity.x * dt;
        float velocityY = player->objVelocity.y * dt;

        //Up
        if ((glfwGetKey(window, GLFW_KEY_W) || glfwGetKey(window, GLFW_KEY_UP)) && player->objPosition.y > 0) {
            player->objPosition.y -= velocityY;
			attackBox->objPosition.y = player->objPosition.y - 70.0f;
            attackBox->objPosition.x = player->objPosition.x + 25.0f;
            attackBox->objRotation = 90.0f;
        }
        //Down
        if ((glfwGetKey(window, GLFW_KEY_S) || glfwGetKey(window, GLFW_KEY_DOWN)) && player->objPosition.y < mapHeight - player->objSize.x) {
            player->objPosition.y += velocityY;
            attackBox->objPosition.y = player->objPosition.y + player->objSize.y - 30.0f;
            attackBox->objPosition.x = player->objPosition.x + 25.0f;
            attackBox->objRotation = 90.0f;
        }
        //Left
        if ((glfwGetKey(window, GLFW_KEY_A) || glfwGetKey(window, GLFW_KEY_LEFT)) && player->objPosition.x > 0) {
            player->objPosition.x -= velocityX;
            attackBox->objPosition.x = player->objPosition.x - 50.0f;
            attackBox->objPosition.y = player->objPosition.y;
            attackBox->objRotation = 0.0f;
			player->flipX = false;
        }
        //Right
        if ((glfwGetKey(window, GLFW_KEY_D) || glfwGetKey(window, GLFW_KEY_RIGHT)) && player->objPosition.x < mapWidth - player->objSize.y) {
            player->objPosition.x += velocityX;
            attackBox->objPosition.x = player->objPosition.x + player->objSize.x;
            attackBox->objPosition.y = player->objPosition.y;
            attackBox->objRotation = 0.0f;
            player->flipX = true;
        }
        //Attack, Interept
        if (glfwGetKey(window, GLFW_KEY_SPACE) && attackDelay >= 0.7f) {
            attackDelay = 0.0f;
			isAttacked = true;
        }
    }
    else {
        if (glfwGetKey(window, GLFW_KEY_SPACE)) {
            std::cout << "<<<EXIT>>>" << std::endl;
            glfwSetWindowShouldClose(window, true);
        }
    }
}

void OpenGLCode::Reset() {
	npcObjects["Normal"].objPosition.x = 0.0f;
    npcObjects["Normal"].objPosition.y = 0.0f;
	WQFS::GetNPC("Normal").SetInDangerous(false);

	std::get<0>(monsterObjects["Monster"]).objPosition.x = width - 200.0f;
    std::get<0>(monsterObjects["Monster"]).objPosition.y = 0.0f;
	eventObjects["Earthquake"].objPosition.x = width - 400.0f;
	eventObjects["Earthquake"].objPosition.y = height - 400.0f;
	eventObjects["Landslide"].objPosition.x = 0.0f;
	eventObjects["Landslide"].objPosition.y = height - 350.0f;

	npcObjects["Normal"].objVelocity = glm::vec2(0.0f);
    std::get<0>(monsterObjects["Monster"]).objVelocity = glm::vec2(0.0f);
    eventObjects["Earthquake"].objVelocity = glm::vec2(0.0f);
    eventObjects["Landslide"].objVelocity = glm::vec2(0.0f);
	changeMoveTime = 5.0f;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void OpenGLCode::MoveSelf(float dt) {
    float timeScale = 1.0f;

    if (changeMoveTime >= 30.0f) {
        changedir = true;

        changeMoveTime = 0;
    }
    else {
        changeMoveTime += deltaTime * timeScale;
    }

    for (auto& npc : WQFS::GetInstance().npcs) {
        if (!npc.second.GetInDangerous()) {
            /*if (changedir) {
                npcObjects[npc.first].objVelocity = glm::vec2((rand() % 3) - 1, (rand() % 3) - 1);
                //std::cout << npcObjects[npc.first].objVelocity.x << " " << npcObjects[npc.first].objVelocity.y << std::endl;
            }

            if ((npcObjects[npc.first].objPosition.x < 0 && npcObjects[npc.first].objVelocity.x == -1)) npcObjects[npc.first].objVelocity.x = 0;
            if ((npcObjects[npc.first].objPosition.y < 0 && npcObjects[npc.first].objVelocity.y == -1)) npcObjects[npc.first].objVelocity.y = 0;

            npcObjects[npc.first].objPosition.x += npcObjects[npc.first].objVelocity.x * 50 * dt * timeScale;
            npcObjects[npc.first].objPosition.y += npcObjects[npc.first].objVelocity.y * 50 * dt * timeScale;
            */
            
            //Up
            if (glfwGetKey(window, GLFW_KEY_I)) {
                npcObjects[npc.first].objPosition.y -= 100 * dt * timeScale;
            }
            //Down
            if (glfwGetKey(window, GLFW_KEY_K)) {
                npcObjects[npc.first].objPosition.y += 100 * dt * timeScale;
            }
            //Left
            if (glfwGetKey(window, GLFW_KEY_J)) {
                npcObjects[npc.first].objPosition.x -= 100 * dt * timeScale;
            }
            //Right
            if (glfwGetKey(window, GLFW_KEY_L)) {
                npcObjects[npc.first].objPosition.x += 100 * dt * timeScale;
            }

            npc.second.SetPosition(npcObjects[npc.first].objPosition.x, npcObjects[npc.first].objPosition.y);
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

void OpenGLCode::DoCollisions() {
    for (auto& monster : monsterObjects) {
        for (auto& event : eventObjects) {
            if (std::get<1>(monster.second) >= 5.0f && WQFS::GetInstance().GetEvent(event.first).getDoEvent() && CheckCollision(std::get<0>(monster.second), eventObjects[event.first])) {
                WQFS::GetInstance().GetEvent(monster.first).takeDamage(1);
                std::get<1>(monster.second) = 0.0f;
            }
        }
            
        if (std::get<1>(monster.second) >= 0.5f && attackDelay < 0.5f && CheckCollision(std::get<0>(monster.second), *attackBox)) {
            WQFS::GetInstance().GetEvent(monster.first).takeDamage(1);
            std::get<1>(monster.second) = 0.0f;
        }
    }
}