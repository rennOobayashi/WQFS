#include "OpenGLCode.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

OpenGLCode::OpenGLCode(unsigned int _width, unsigned int _height)
	: states(GAME_MENU), width(_width), height(_height), changedir(5.0f), startResetTimer(false), resetTimer(0.0f) {
    init();
}

OpenGLCode::~OpenGLCode() {
	delete sRenderer;
	npcObjects.clear();
    monsterObjects.clear();
    eventObjects.clear();
    ResourceManager::Clear();

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

    ResourceManager::LoadTexture("Texture/NPC.png", true, "NPC");
    ResourceManager::LoadTexture("Texture/Monster.png", true, "Monster");
    ResourceManager::LoadTexture("Texture/Event.png", true, "Event");


	Shader spriteShader = ResourceManager::GetShader("sprite");
	sRenderer = new SpriteRenderer(spriteShader);

	WQFS::GetInstance().GetInstance().AddNPC("Normal", 0, 0.0f, 0.0f);
	WQFS::GetInstance().AddEvent("Monster", 0, 0.0f, 0.0f);
	WQFS::GetInstance().AddEvent("Earthquake", 1, 0.0f, 0.0f);
	WQFS::GetInstance().AddEvent("Landslide", 2, 0.0f, 0.0f);

    npcObjects["Normal"] = GameObject(ResourceManager::GetTexture("NPC"), glm::vec2(0.0f, 0.0f), glm::vec2(200.0f), 0.0f, glm::vec3(0.1f, 0.5f, 1.0f));
    monsterObjects["Monster"] = GameObject(ResourceManager::GetTexture("Monster"), glm::vec2(width - 200.0f, 0.0f), glm::vec2(200.0f), 0.0f, glm::vec3(1.0f, 0.2f, 0.1f));
    eventObjects["Earthquake"] = GameObject(ResourceManager::GetTexture("Event"), glm::vec2(width - 400.0f, height - 400.0f), glm::vec2(400.0f), 0.0f, glm::vec3(0.7f, 0.1f, 1.0f));
    eventObjects["Landslide"] = GameObject(ResourceManager::GetTexture("Event"), glm::vec2(0.0f, height - 350.0f), glm::vec2(350.0f), 0.0f, glm::vec3(0.4f, 0.1f, 1.0f));

    WQFS::GetInstance().AddItem("HP Posion", 0, 30, 0);
    WQFS::GetInstance().AddItem("GOOD HP Posion", 0, 50, 1);
    WQFS::GetInstance().AddItem("Stone Sword", 2, 30, 0);
    WQFS::GetInstance().AddItem("Iron", 3, 20, 0);
    WQFS::GetInstance().AddItem("Gold", 3, 50, 1);
}

void OpenGLCode::update() {
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = (float)glfwGetTime();

        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		changeMoveTime += deltaTime;

        if (startResetTimer) {
            resetTimer += deltaTime;

            if (resetTimer >= 5.0f) {
                Reset();
            }
        }

        render();
        MoveSelf(deltaTime);
		DoCollisions();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}

void OpenGLCode::render() {
    for (const auto& npc : WQFS::GetInstance().GetAllNPC()) {
		npcObjects[npc.first].Draw(*sRenderer);
	}

    for (const auto& monster : WQFS::GetInstance().GetAllEvent()) {
        if (monster.second.GetType() == 0) {
            monsterObjects[monster.first].Draw(*sRenderer);
        }
    }
    for (const auto& event : WQFS::GetInstance().GetAllEvent()) {
		//std::cout << eventObjects[event.first].GetType() << std::endl;
        if (event.second.GetType() != 0) {
            eventObjects[event.first].Draw(*sRenderer);
        }
    }
}

void OpenGLCode::Reset() {
	npcObjects["Normal"].objPosition.x = 0.0f;
    npcObjects["Normal"].objPosition.y = 0.0f;
	WQFS::GetNPC("Normal").SetInDangerous(false);

	monsterObjects["Monster"].objPosition.x = width - 200.0f;
	monsterObjects["Monster"].objPosition.y = 0.0f;
	eventObjects["Earthquake"].objPosition.x = width - 400.0f;
	eventObjects["Earthquake"].objPosition.y = height - 400.0f;
	eventObjects["Landslide"].objPosition.x = 0.0f;
	eventObjects["Landslide"].objPosition.y = height - 350.0f;

	npcObjects["Normal"].objVelocity = glm::vec2(0.0f);
    monsterObjects["Monster"].objVelocity = glm::vec2(0.0f);
    eventObjects["Earthquake"].objVelocity = glm::vec2(0.0f);
    eventObjects["Landslide"].objVelocity = glm::vec2(0.0f);
	changeMoveTime = 5.0f;

	resetTimer = 0.0f;
    startResetTimer = false;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void OpenGLCode::MoveSelf(float dt) {
    if (changeMoveTime >= 2.5f) {
        changedir = true;

        changeMoveTime = 0;
    }

    for (auto& npc : WQFS::GetInstance().GetAllNPC()) {
        if (!npc.second.GetInDangerous()) {
            if (changedir) {
                npcObjects[npc.first].objVelocity = glm::vec2((rand() % 3) - 1, (rand() % 3) - 1);
                //std::cout << npcObjects[npc.first].objVelocity.x << " " << npcObjects[npc.first].objVelocity.y << std::endl;
            }

            if ((npcObjects[npc.first].objPosition.x < 0 && npcObjects[npc.first].objVelocity.x == -1) || (npcObjects[npc.first].objPosition.x > width - npcObjects[npc.first].objSize.x && npcObjects[npc.first].objVelocity.x == 1)) npcObjects[npc.first].objVelocity.x = 0;
            if ((npcObjects[npc.first].objPosition.y < 0 && npcObjects[npc.first].objVelocity.y == -1) || (npcObjects[npc.first].objPosition.y > height - npcObjects[npc.first].objSize.y && npcObjects[npc.first].objVelocity.y == 1)) npcObjects[npc.first].objVelocity.y = 0;

            npcObjects[npc.first].objPosition.x += npcObjects[npc.first].objVelocity.x * 50 * dt;
            npcObjects[npc.first].objPosition.y += npcObjects[npc.first].objVelocity.y * 50 * dt;

            npc.second.SetPosition(npcObjects[npc.first].objPosition.x, npcObjects[npc.first].objPosition.y);
        }
	}

    for (auto& monster : WQFS::GetInstance().GetAllEvent()) {
        if (monster.second.GetType() == 0) {
            if (changedir) {
                monsterObjects[monster.first].objVelocity = glm::vec2((rand() % 3) - 1, (rand() % 3) - 1);
            }

            if ((monsterObjects[monster.first].objPosition.x < 0 && monsterObjects[monster.first].objVelocity.x == -1) || (monsterObjects[monster.first].objPosition.x > width - monsterObjects[monster.first].objSize.x && monsterObjects[monster.first].objVelocity.x == 1)) monsterObjects[monster.first].objVelocity.x = 0;
            if ((monsterObjects[monster.first].objPosition.y < 0 && monsterObjects[monster.first].objVelocity.y == -1) || (monsterObjects[monster.first].objPosition.y > height - monsterObjects[monster.first].objSize.y && monsterObjects[monster.first].objVelocity.y == 1)) monsterObjects[monster.first].objVelocity.y = 0;

            monsterObjects[monster.first].objPosition.x += monsterObjects[monster.first].objVelocity.x * 30 * dt;
            monsterObjects[monster.first].objPosition.y += monsterObjects[monster.first].objVelocity.y * 30 * dt;

			monster.second.SetPosition(monsterObjects[monster.first].objPosition.x, monsterObjects[monster.first].objPosition.y);
        }
    }

    for (auto& event : WQFS::GetInstance().GetAllEvent()) {
        if (event.second.GetType() != 0) {
            if (changedir) {
                eventObjects[event.first].objVelocity = glm::vec2((rand() % 3) - 1, (rand() % 3) - 1);
            }

            if ((eventObjects[event.first].objPosition.x < 0 && eventObjects[event.first].objVelocity.x == -1) || (eventObjects[event.first].objPosition.x > width - eventObjects[event.first].objSize.x && eventObjects[event.first].objVelocity.x == 1)) eventObjects[event.first].objVelocity.x = 0;
            if ((eventObjects[event.first].objPosition.y < 0 && eventObjects[event.first].objVelocity.y == -1) || (eventObjects[event.first].objPosition.y > height - eventObjects[event.first].objSize.y && eventObjects[event.first].objVelocity.y == 1)) eventObjects[event.first].objVelocity.y = 0;

            eventObjects[event.first].objPosition.x += eventObjects[event.first].objVelocity.x * 10 * dt;
            eventObjects[event.first].objPosition.y += eventObjects[event.first].objVelocity.y * 10 * dt;

			event.second.SetPosition(eventObjects[event.first].objPosition.x, eventObjects[event.first].objPosition.y);
        }
	}

	if (changedir)  changedir = false;
}

bool OpenGLCode::CheckCollision(GameObject& object1, GameObject& object2) {
    bool collisionX = object1.objPosition.x + object1.objSize.x >= object2.objPosition.x &&
		object2.objPosition.x + object2.objSize.x >= object1.objPosition.x;
    bool collisionY = object1.objPosition.y + object1.objSize.y >= object2.objPosition.y &&
		object2.objPosition.y + object2.objSize.y >= object1.objPosition.y;

    return collisionX && collisionY;
}

void OpenGLCode::DoCollisions() {
    for (auto& npc : WQFS::GetInstance().GetAllNPC()) {
        if (!npc.second.GetInDangerous()) {
            for (auto& monster : monsterObjects) {
                if (CheckCollision(npcObjects[npc.first], monsterObjects[monster.first])) {
                    std::cout << npc.second.GetInDangerous() << std::endl;
					npc.second.SetInDangerous(true);
					WQFS::GetInstance().MakeQuest(npc.second, WQFS::GetInstance().GetEvent(monster.first));
					std::cout << "5초 뒤 리셋" << std::endl;
					startResetTimer = true;
                }
            }
            for (auto& event : eventObjects) {
                if (CheckCollision(npcObjects[npc.first], eventObjects[event.first])) {
                    std::cout << npc.second.GetInDangerous() << std::endl;
                    npc.second.SetInDangerous(true);
                    WQFS::GetInstance().MakeQuest(npc.second, WQFS::GetInstance().GetEvent(event.first));
                    std::cout << "5초 뒤 리셋" << std::endl;
                    startResetTimer = true;
                }
            }
        }
    }
    for (auto& monster : monsterObjects) {
        for (auto& event : eventObjects) {
            if (CheckCollision(monsterObjects[monster.first], eventObjects[event.first])) {
				monster.second.objVelocity = glm::vec2(0.0f);
            }
        }
    }
}