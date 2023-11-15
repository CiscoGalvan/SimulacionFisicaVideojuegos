#include "ParticleGenerator.h"
#include "ParticleSystem.h"

ParticleGenerator::ParticleGenerator(std::string name,Particle* emitter, int numParticles, float frecuency,int type, ParticleSystem* pS)
{
	this->emitter = emitter;
	this->numParticles = numParticles;
	this->name = name;
	this->frecuency = frecuency;
	this->nextRespawn = frecuency;
	this->type = type;
	this->pS = pS;
	actualParticles = 0;
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
			float liveTime = 30;
			particle = new Particle(*emitter->getPos(), vel, Vector3(0, -9.8, 0), masa, liveTime, DAMPING, false);
			particle->getRenderItem()->color = Vector4(distribution(gen), distribution(gen), distribution(gen), 1);
			particle->getRenderItem()->shape = CreateShape(physx::PxSphereGeometry(0.3));
			particle->getRenderItem()->transform = particle->getPos();
			RegisterRenderItem(particle->getRenderItem());
			for (auto it : pS->getForces())
			{
				pS->getRegistry()->addRegistry(it, particle);
			}
			pS->addParticle(particle);
		}
		else if(type == 1)
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
			float liveTime = 30;
			particle = new Particle(*emitter->getPos(), vel, Vector3(0, -9.8, 0), masa, liveTime, DAMPING, false);
			particle->getRenderItem()->color = Vector4(distribution(gen), distribution(gen), distribution(gen), 1);
			particle->getRenderItem()->shape = CreateShape(physx::PxSphereGeometry(0.3));
			particle->getRenderItem()->transform = particle->getPos();
			RegisterRenderItem(particle->getRenderItem());
			for (auto it : pS->getForces())
			{

				pS->getRegistry()->addRegistry(it, particle);
			}
			pS->addParticle(particle);
		}
		else if(type == 2)
		{

			int randomValue1 = std::rand() % 2;
			int result1 = (randomValue1 == 0) ? -1 : 1;

			int randomValue3 = std::rand() % 2;
			int result3 = (randomValue3 == 0) ? -1 : 1;


		


			Particle* particle;
			Camera* cam = GetCamera();

			float masa = emitter->getMass();
			

			
			float liveTime = 30;
			
		
			particle = new Particle(*emitter->getPos(), Vector3(randomVel2(gen2) , 0, randomVel2(gen2) ) , Vector3(0, -9.8, 0), masa, liveTime, DAMPING, false);
			particle->getRenderItem()->color = Vector4(distribution(gen), distribution(gen), distribution(gen), 1);
			particle->getRenderItem()->shape = CreateShape(physx::PxSphereGeometry(2));
			particle->getRenderItem()->transform = particle->getPos();
			RegisterRenderItem(particle->getRenderItem());
			//Anadimos cada fuerza a cada particula creada
			for(auto it : pS->getForces())
			{
				
				pS->getRegistry()->addRegistry(it, particle);
			}
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
