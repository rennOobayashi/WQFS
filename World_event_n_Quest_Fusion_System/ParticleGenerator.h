#ifndef PARTICLEGENERATOR_H
#define PARTICLEGENERATOR_H

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <iostream>
#include <vector>

#include "Shader.h"
#include "Texture.h"
#include "GameObject.h"

struct Particle
{
	glm::vec2 Position;
	glm::vec2 Velocity;
	glm::vec4 Color;
	float life;

	Particle() : Position(0.0f), Velocity(0.0f), Color(1.0f), life(0.0f) {}
};

class ParticleGenerator
{
private:
	std::vector<Particle> particles;
	Shader pShader;
	Texture pTexture;
	unsigned int amount;
	unsigned int pao;
	unsigned int lastUsedParticle;
	float respawnDelay = 1.0f;

	void init();
	unsigned int FirstUnusedParticle();
	void RespawnParticle(Particle& particle, GameObject& object, glm::vec2 offset, glm::vec2 direction);
public:
	ParticleGenerator(Shader shader, Texture texture, unsigned int _amount);
	void Update(float dt, GameObject& object, unsigned int newParticle, glm::vec2 offset = glm::vec2(0.0f), glm::vec2 direction = glm::vec2(0.0f, 1.0f));
	void Draw();
};

#endif