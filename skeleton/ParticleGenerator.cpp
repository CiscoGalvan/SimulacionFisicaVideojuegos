#include "ParticleGenerator.h"
#include "ParticleSystem.h"

ParticleGenerator::ParticleGenerator(std::string name,Particle* emitter, int numParticles, float frecuency, ParticleSystem* pS)
{
	this->emitter = emitter;
	this->numParticles = numParticles;
	this->name = name;
	this->frecuency = frecuency;
	this->nextRespawn = frecuency;
	this->pS = pS;
	actualParticles = 0;


	int randomValue = std::rand() % 2;
    type = (randomValue == 0) ? -1 : 1;
}

ParticleGenerator::~ParticleGenerator()
{
	delete emitter;
}
void ParticleGenerator::update(double t)
{
	

	if (lastRespawn + frecuency > nextRespawn && numParticles> actualParticles)
	{
	
		std::mt19937 gen(rd1());

		std::mt19937 gen2(rd2());
		 
		
		
		if(type == -1)
		{
			int randomValue1 = std::rand() % 2;
			int result1 = (randomValue1 == 0) ? -1 : 1;

			int randomValue2 = std::rand() % 2;
			int result2 = (randomValue2 == 0) ? -1 : 1;

			int randomValue3 = std::rand() % 2;
			int result3 = (randomValue3 == 0) ? -1 : 1;

			Particle* particle;
			Vector3 vel(randomVel(gen2) * result1, randomVel(gen2) * result2, randomVel(gen2) * result3);
			float masa = 1;
			float liveTime = 3;
			particle = new Particle(*emitter->getPos(), vel, Vector3(0, -9.8, 0), masa, liveTime, DAMPING, false);
			particle->getRenderItem()->color = Vector4(distribution(gen), distribution(gen), distribution(gen), 1);
			particle->getRenderItem()->shape = CreateShape(physx::PxSphereGeometry(0.3));
			particle->getRenderItem()->transform = particle->getPos();
			RegisterRenderItem(particle->getRenderItem());
			pS->addParticle(particle);
		}
		else
		{
			int randomValue1 = std::rand() % 2;
			int result1 = (randomValue1 == 0) ? -1 : 1;

			int randomValue2 = std::rand() % 2;
			int result2 = (randomValue2 == 0) ? -1 : 1;

			int randomValue3 = std::rand() % 2;
			int result3 = (randomValue3 == 0) ? -1 : 1;

			Particle* particle;
			Vector3 vel(randomVel(gen2) * result1 * 0.1, randomVel(gen2) * result2, randomVel(gen2) * result3);
			float masa = 1;
			float liveTime = 3;
			particle = new Particle(*emitter->getPos(), vel, Vector3(0, -9.8, 0), masa, liveTime, DAMPING, false);
			particle->getRenderItem()->color = Vector4(distribution(gen), distribution(gen), distribution(gen), 1);
			particle->getRenderItem()->shape = CreateShape(physx::PxSphereGeometry(0.3));
			particle->getRenderItem()->transform = particle->getPos();
			RegisterRenderItem(particle->getRenderItem());
			pS->addParticle(particle);
		}
	

		nextRespawn += frecuency;
		actualParticles++;
	}
	else
	{
		lastRespawn += t;
	}
}
