#include "OpenGLCode.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

OpenGLCode::OpenGLCode(unsigned int _width, unsigned int _height)
	: states(GAME_MENU), width(_width), height(_height) {
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

    changeMoveTime = 5.0f;

	npcObjects.push_back(GameObject(ResourceManager::GetTexture("NPC"), glm::vec2(0.0f, 0.0f), glm::vec2(200.0f), 0.0f, glm::vec3(0.1f, 0.5f, 1.0f)));
    monsterObjects.push_back(GameObject(ResourceManager::GetTexture("Monster"), glm::vec2(width - 200.0f, 0.0f), glm::vec2(200.0f), 0.0f, glm::vec3(1.0f, 0.2f, 0.1f)));
    eventObjects.push_back(GameObject(ResourceManager::GetTexture("Event"), glm::vec2(width - 400.0f, height - 400.0f), glm::vec2(400.0f), 0.0f, glm::vec3(0.7f, 0.1f, 1.0f)));
    eventObjects.push_back(GameObject(ResourceManager::GetTexture("Event"), glm::vec2(0.0f, height - 350.0f), glm::vec2(350.0f), 0.0f, glm::vec3(0.4f, 0.1f, 1.0f)));
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
    for (auto npc : npcObjects) {
		npc.Draw(*sRenderer);
	}
    for (auto monster : monsterObjects) {
        monster.Draw(*sRenderer);
    }
    for (auto event : eventObjects) {
        event.Draw(*sRenderer);
    }

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

    for (auto& npc : npcObjects) {
        if (changedir) {
            npc.objVelocity = glm::vec2((rand() % 3) - 1, (rand() % 3) - 1);
            std::cout << npc.objVelocity.x << " " << npc.objVelocity.y << std::endl;
        }


		if ((npc.objPosition.x < 0 && npc.objVelocity.x == -1) || (npc.objPosition.x > width - npc.objSize.x && npc.objVelocity.x == 1)) npc.objVelocity.x = 0;
		if ((npc.objPosition.y < 0 && npc.objVelocity.y == -1) || (npc.objPosition.y > height - npc.objSize.y && npc.objVelocity.y == 1)) npc.objVelocity.y = 0;

        npc.objPosition.x += npc.objVelocity.x * 50 * dt;
        npc.objPosition.y += npc.objVelocity.y * 50 * dt;
	}

    for (auto& monster : monsterObjects) {
        if (changedir) {
            monster.objVelocity = glm::vec2((rand() % 3) - 1, (rand() % 3) - 1);
        }

        if ((monster.objPosition.x < 0 && monster.objVelocity.x == -1) || (monster.objPosition.x > width - monster.objSize.x && monster.objVelocity.x == 1)) monster.objVelocity.x = 0;
        if ((monster.objPosition.y < 0 && monster.objVelocity.y == -1) || (monster.objPosition.y > height - monster.objSize.y && monster.objVelocity.y == 1)) monster.objVelocity.y = 0;

        monster.objPosition.x += monster.objVelocity.x * 30 * dt;
        monster.objPosition.y += monster.objVelocity.y * 30 * dt;
    }

    for (auto& event : eventObjects) {
        if (changedir) {
            event.objVelocity = glm::vec2((rand() % 3) - 1, (rand() % 3) - 1);
        }

        if ((event.objPosition.x < 0 && event.objVelocity.x == -1) || (event.objPosition.x > width - event.objSize.x && event.objVelocity.x == 1)) event.objVelocity.x = 0;
        if ((event.objPosition.y < 0 && event.objVelocity.y == -1) || (event.objPosition.y > height - event.objSize.y && event.objVelocity.y == 1)) event.objVelocity.y = 0;

        event.objPosition.x += event.objVelocity.x * 10 * dt;
        event.objPosition.y += event.objVelocity.y * 10 * dt;
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
    for (auto& npc : npcObjects) {
        if ()
        for (auto& monster : monsterObjects) {
            if (CheckCollision(npc, monster)) {
				std::cout << "collision npc and monster" << std::endl;
            }
        }
        for (auto& event : eventObjects) {
            if (CheckCollision(npc, event)) {
                std::cout << "collision npc and event" << std::endl;
            }
        }
    }
    for (auto& monster : monsterObjects) {
        for (auto& event : eventObjects) {
            if (CheckCollision(monster, event)) {
                std::cout << "collision monster and event" << std::endl;
            }
        }
    }
}