#include "SolidGenerator.h"
#include "RigidBodySystem.h"

SolidGenerator::SolidGenerator( Particle* emitter, int numParticles, float frecuency, RigidBodySystem* rS)
{
	this->emitter = emitter;
	this->numParticles = numParticles;
	this->frecuency = frecuency;
	this->nextRespawn = frecuency;
	this->rS = rS;
	actualParticles = 0;
}

SolidGenerator::~SolidGenerator()
{
	delete emitter;
}

void SolidGenerator::update(double t)
{


	if (lastRespawn + frecuency > nextRespawn && numParticles > actualParticles)
	{

		std::mt19937 gen(rd1());
		std::mt19937 gen2(rd2());

		int randomValue1 = std::rand() % 2;
		int result1 = (randomValue1 == 0) ? -1 : 1;

		int randomValue3 = std::rand() % 2;
		int result3 = (randomValue3 == 0) ? -1 : 1;
			
		//CHECKEAR VALORES.
		rS->addDynamicObject(0.2f, 0.1f, 0.3f, Vector3(1, 1, 1), Vector3(0.5, 0.5, 0.5), Vector4(distribution(gen), distribution(gen), distribution(gen), 1), Vector3(emitter->getPos()->p.x + appear(gen2) *result1, emitter->getPos()->p.y, emitter->getPos()->p.z + appear(gen2) * result3), Vector3(randomVel2(gen2), 0, randomVel2(gen2)), Vector3(0, 80, 80), 0.15, 10);
		nextRespawn += frecuency;
		actualParticles++;
	}
	else
	{
		lastRespawn += t;
	}
}
