#include "OpenGLCode.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

glm::vec2 npcMovePos = glm::vec2(0.0f);
glm::vec2 monsterMovePos = glm::vec2(0.0f);
glm::vec2 event1MovePos = glm::vec2(0.0f);
glm::vec2 event2MovePos = glm::vec2(0.0f);

glm::vec2 npcPos;
glm::vec2 monsterPos;
glm::vec2 event1Pos;
glm::vec2 event2Pos;

OpenGLCode::OpenGLCode(unsigned int _width, unsigned int _height)
	: states(GAME_MENU), width(_width), height(_height) {
    init();
}

OpenGLCode::~OpenGLCode() {
	delete sRenderer;
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

	npcPos = glm::vec2(0.0f);
	monsterPos = glm::vec2(width - 200.0f, 0.0f);
	event1Pos = glm::vec2(width - 400.0f, height - 400.0f);
	event2Pos = glm::vec2(0.0f, height - 350.0f);
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

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}

void OpenGLCode::render() {
	Texture npcTex = ResourceManager::GetTexture("NPC");
    Texture monsterTex = ResourceManager::GetTexture("Monster");
    Texture eventTex1 = ResourceManager::GetTexture("Event");
    Texture eventTex2 = ResourceManager::GetTexture("Event");

	sRenderer->DrawSprite(npcTex, glm::vec2(npcPos), glm::vec2(200.0f), 0.0f, glm::vec3(0.1f, 0.5f, 1.0f));
    sRenderer->DrawSprite(monsterTex, glm::vec2(monsterPos), glm::vec2(200.0f), 0.0f, glm::vec3(1.0f, 0.2f, 0.1f));
    sRenderer->DrawSprite(eventTex1, glm::vec2(event1Pos), glm::vec2(400.0f), 0.0f, glm::vec3(0.7f, 0.1f, 1.0f));
    sRenderer->DrawSprite(eventTex2, glm::vec2(event2Pos), glm::vec2(350.0f), 0.0f, glm::vec3(0.4f, 0.1f, 1.0f));
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void OpenGLCode::MoveSelf(float dt) {
    if (changeMoveTime >= 2.5f) {
		npcMovePos.x = (rand() % 3) - 1;
        npcMovePos.y = (rand() % 3) - 1;
        monsterMovePos.x = (rand() % 3) - 1;
        monsterMovePos.y = (rand() % 3) - 1;
        event1MovePos.x = (rand() % 3) - 1;
        event1MovePos.y = (rand() % 3) - 1;
        event2MovePos.x = (rand() % 3) - 1;
        event2MovePos.y = (rand() % 3) - 1;

        changeMoveTime = 0;
    }


    if (!(npcPos.x < 0 && npcMovePos.x == -1) && !(npcPos.x > width - 200.0f && npcMovePos.x == 1)) npcPos.x += npcMovePos.x * 50 * dt;
    if (!(npcPos.y < 0 && npcMovePos.y == -1) && !(npcPos.y > height - 200.0f && npcMovePos.y == 1)) npcPos.y += npcMovePos.y * 50 * dt;

    if (!(monsterPos.x < 0 && monsterMovePos.x == -1) && !(monsterPos.x > width - 200.0f && monsterMovePos.x == 1)) monsterPos.x += monsterMovePos.x * 30.0f * dt;
    if (!(monsterPos.y < 0 && monsterMovePos.y == -1) && !(monsterPos.y > width - 200.0f && monsterMovePos.y == 1)) monsterPos.y += monsterMovePos.y * 30.0f * dt;

    if (!(event1Pos.x < 0 && event1MovePos.x == -1) && !(event1Pos.x > width - 400.0f && event1MovePos.x == 1)) event1Pos.x += event1MovePos.x * 30.0f * dt;
    if (!(event1Pos.y < 0 && event1MovePos.y == -1) && !(event1Pos.y > width - 400.0f && event1MovePos.y == 1)) event1Pos.y += event1MovePos.y * 30.0f * dt;

    if (!(event2Pos.x < 0 && event2MovePos.x == -1) && !(event2Pos.x > width - 350.0f && event1MovePos.x == 1)) event2Pos.x += event2MovePos.x * 30.0f * dt;
    if (!(event2Pos.y < 0 && event2MovePos.y == -1) && !(event2Pos.y > width - 350.0f && event1MovePos.y == 1)) event2Pos.y += event2MovePos.y * 30.0f * dt;
}