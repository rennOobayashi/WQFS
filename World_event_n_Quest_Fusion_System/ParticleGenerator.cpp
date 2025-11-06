#include "ParticleGenerator.h"

ParticleGenerator::ParticleGenerator(Shader shader, Texture texture, unsigned int _amount) 
	: pShader(shader), pTexture(texture), amount(_amount), lastUsedParticle(0) {
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
	glBindBuffer(GL_ARRAY_BUFFER, pbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(particleQuad), particleQuad, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glBindVertexArray(0);

	for (unsigned int i = 0; i < amount; ++i) {
		particles.push_back(Particle());
	}
}

void ParticleGenerator::Update(float dt, GameObject& object, unsigned int newParticle, glm::vec2 offset, glm::vec2 direction) {
	if (respawnDelay < 0.4f) {
		respawnDelay += dt;
	}

	for (unsigned int i = 0; i < newParticle; ++i) {
		if (respawnDelay >= 0.4f) {
			int unusedParticle = FirstUnusedParticle();
			RespawnParticle(particles[unusedParticle], object, offset, direction);
			respawnDelay = 0;
		}
	}

	for (unsigned int i = 0; i < amount; ++i) {
		Particle& p = particles[i];
		p.life -= dt;

		if (p.life > 0.0f) {
			p.Position += p.Velocity * dt;
			//p.Color.a -= dt * 2.5f;
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

void ParticleGenerator::RespawnParticle(Particle& particle, GameObject& object, glm::vec2 offset, glm::vec2 direction) {
	float randomX = (rand() % (int)object.objPosition.x);
	float randomY = rand() % 10;
	float randomVelX = (rand() & 2) - 0.5f;
	std::cout << randomVelX << std::endl;
	float color = 0.3f + ((rand() % 100) / 100.0f);
	glm::vec2 random = glm::vec2(randomX, randomY);

	particle.Position = object.objPosition + random + offset;
	particle.Color = glm::vec4(color, color, color, 1.0f);
	particle.Velocity = glm::vec2(randomVelX, direction.y) * 500.0f;
	particle.life = 2.5f;
}

void ParticleGenerator::Draw() {
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	float scale;

	pShader.use();

	for (Particle particle : particles) {
		if (particle.life > 0.0f) {
			scale = (rand() % 50) + 50;
			pShader.SetVec2("offset", particle.Position);
			pShader.SetVec4("color", particle.Color);
			pShader.SetFloat("scale", scale);
			pTexture.Bind();
			glBindVertexArray(pao);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			glBindVertexArray(0);
		}
	}

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}