#include "ParticleGenerator.h"

ParticleGenerator::ParticleGenerator(Shader shader, Texture texture, unsigned int _amount) 
	: pShader(shader), pTexture(texture), amount(_amount) {
	init();
}

void ParticleGenerator::init() {
	unsigned int pbo;

	float particleQuad[] = {
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};

	glGenVertexArrays(1, &pao);
	glGenBuffers(1, &pbo);
	glBindVertexArray(pao);
	glBindBuffer(GL_VERTEX_ARRAY, pbo);
	glBufferData(GL_VERTEX_ARRAY, sizeof(particleQuad), particleQuad, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glBindVertexArray(0);

	for (unsigned int i = 0; i < amount; ++i) {
		particles.push_back(Particle());
	}
}

void ParticleGenerator::Update(float dt, GameObject& object, unsigned int newParticle, glm::vec2 offset) {
	for (unsigned int i = 0; i < newParticle; ++i) {
		int unusedParticle = FirstUnusedParticle();
		RespawnParticle(particles[unusedParticle], object, offset);
	}

	for (unsigned int i = 0; i < amount; ++i) {
		Particle& p = particles[i];
		p.life -= dt;

		if (p.life > 0.0f) {
			p.Position -= p.Velocity * dt;
			p.Color.a -= dt * 2.5f;
		}
	}
}

unsigned int ParticleGenerator::FirstUnusedParticle() {
	for (unsigned int i = lastUsedParticle; i < amount; ++i) {
		if (particles[i].life <= 0.0f) {
			lastUsedParticle = i;
			return i;
		}
	}

	for (unsigned int i = 0; i < lastUsedParticle; ++i) {
		if (particles[i].life <= 0.0f) {
			lastUsedParticle = i;
			return i;
		}
	}

	lastUsedParticle = 0;
	return 0;
}

void ParticleGenerator::RespawnParticle(Particle& particle, GameObject& object, glm::vec2 offset) {
	float random = ((rand() % 100) - 50) / 7.0f;
	float color = 0.7f + ((rand() % 100) / 100.0f);

	particle.Position = object.objPosition + random + offset;
	particle.Color = glm::vec4(color, color, color, 1.0f);
	particle.life = 0.15f;
	particle.Velocity = object.objVelocity * 0.1f;
}

void ParticleGenerator::Draw() {
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	pShader.use();

	for (Particle particle : particles) {
		if (particle.life > 0.0f) {
			pShader.SetVec2("offset", particle.Position);
			pShader.SetVec4("color", particle.Color);
			pTexture.Bind();
			glBindVertexArray(pao);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			glBindVertexArray(0);
		}
	}

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_CONSTANT_ALPHA);
}