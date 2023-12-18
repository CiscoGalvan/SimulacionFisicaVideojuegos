#include "SolidGenerator.h"
#include "RigidBodySystem.h"

SolidGenerator::SolidGenerator( Particle* emitter, int numParticles, float frecuency, RigidBodySystem* rS,bool solid,int clase)
{
	this->clase = clase;
	this->emitter = emitter;
	this->numParticles = numParticles;
	this->frecuency = frecuency;
	this->nextRespawn = frecuency;
	this->rS = rS;
	this->solid = solid;
	actualParticles = 0;
}

SolidGenerator::~SolidGenerator()
{
	//delete emitter;
}

void SolidGenerator::update(double t)
{


	if (lastRespawn + frecuency > nextRespawn && numParticles > actualParticles)
	{
		std::mt19937 gen(rd1());
		std::mt19937 gen2(rd2());
		if(solid)
		{
			

			int randomValue1 = std::rand() % 2;
			int result1 = (randomValue1 == 0) ? -1 : 1;

			int randomValue3 = std::rand() % 2;
			int result3 = (randomValue3 == 0) ? -1 : 1;

			//CHECKEAR VALORES.
			switch (type)
			{
			case 1:
				rS->addDynamicObject(0.2f, 0.1f, 0.3f, Vector3(1, 1, 1), Vector3(0.5, 0.5, 0.5), Vector4(1, 0, 0, 1), Vector3(emitter->getPos()->p.x + appear(gen2) * result1, emitter->getPos()->p.y, emitter->getPos()->p.z + appear(gen2) * result3), Vector3(randomVel2(gen2), 0, randomVel2(gen2)), Vector3(0, 40, 40), 0.15, 10);
				break;
			case 2:
				rS->addDynamicObject(0.2f, 0.1f, 0.3f, Vector3(1, 1, 1), Vector3(0.5, 0.5, 0.5), Vector4(1, 1, 0, 1), Vector3(emitter->getPos()->p.x + appear(gen2) * result1, emitter->getPos()->p.y, emitter->getPos()->p.z + appear(gen2) * result3), Vector3(randomVel2(gen2), 0, randomVel2(gen2)), Vector3(0, 0, 0), 0.15, 10);
				break;
			case 3:
				rS->addDynamicObject(0.8f, 0.9f, 0.7f, Vector3(0.5, 0.5, 0.5), Vector3(0.5, 0.5, 0.5), Vector4(1, 0, 1, 1), Vector3(emitter->getPos()->p.x + appear(gen2) * result1, emitter->getPos()->p.y, emitter->getPos()->p.z + appear(gen2) * result3), Vector3(randomVel2(gen2), 0, randomVel2(gen2)), Vector3(100, 0, 0), 0.15, 10);
				break;
			case 4:
				//NO INERTIA
				rS->addDynamicObject(0.8f, 0.9f, 1, Vector3(0, 0, 0), Vector3(0.5, 0.5, 0.5), Vector4(0, 0, 1, 1), Vector3(emitter->getPos()->p.x + appear(gen2) * result1, emitter->getPos()->p.y, emitter->getPos()->p.z + appear(gen2) * result3), Vector3(randomVel2(gen2), 0, randomVel2(gen2)), Vector3(100, 0, 0), 0.15, 10);
				break;
			case 5:
				//NO INERTIA, LOW ELASTIC COEF AND HIGH FALL SPEED
				rS->addDynamicObject(0.8f, 0.9f, 0.01f, Vector3(0, 0, 0), Vector3(0.5, 0.5, 0.5), Vector4(0, 1, 0, 1), Vector3(emitter->getPos()->p.x + appear(gen2) * result1, emitter->getPos()->p.y, emitter->getPos()->p.z + appear(gen2) * result3), Vector3(randomVel2(gen2), -100, randomVel2(gen2)), Vector3(100, 0, 0), 0.15, 10);
				break;
			default:
				break;
			}
		}
		else
		{
			
			if(clase == 0)
			{
				int randomValue1 = std::rand() % 2;
				int result1 = (randomValue1 == 0) ? -1 : 1;

				int randomValue2 = std::rand() % 2;
				int result2 = (randomValue2 == 0) ? -1 : 1;

				int randomValue3 = std::rand() % 2;
				int result3 = (randomValue3 == 0) ? -1 : 1;

				Particle* particle;
				Vector3 vel(randomVel2(gen2) * result1, randomVel2(gen2) * result2, randomVel2(gen2) * result3);
				float masa = 1;
				float liveTime = 1;
				particle = new Particle(*emitter->getPos(), vel, Vector3(0, -9.8, 0), masa, liveTime, DAMPING, false);
				particle->getRenderItem()->color = Vector4(distribution(gen), distribution(gen), distribution(gen), 1);
				particle->getRenderItem()->shape = CreateShape(physx::PxSphereGeometry(0.1));
				particle->getRenderItem()->transform = particle->getPos();
				RegisterRenderItem(particle->getRenderItem());

				rS->addParticle(particle);
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
				Vector3 vel(randomVel(gen2) * result1, randomVel(gen2) * result2, randomVel(gen2) * result3);
				float masa = 1;
				float liveTime = 1;
				particle = new Particle(*emitter->getPos(), vel, Vector3(0, -9.8, 0), masa, liveTime, DAMPING, false);
				particle->getRenderItem()->color = Vector4(distribution(gen), distribution(gen), distribution(gen), 1);
				particle->getRenderItem()->shape = CreateShape(physx::PxSphereGeometry(0.3));
				particle->getRenderItem()->transform = particle->getPos();
				RegisterRenderItem(particle->getRenderItem());
			
				rS->addParticle(particle);
			}
		
		}
		
		type = type % 5 + 1;
		nextRespawn += frecuency;
		actualParticles++;
	}
	else
	{
		lastRespawn += t;
	}
}
