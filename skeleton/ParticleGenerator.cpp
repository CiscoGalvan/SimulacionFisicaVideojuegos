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
}

ParticleGenerator::~ParticleGenerator()
{
	delete emitter;
}
void ParticleGenerator::update(double t)
{
	if (lastRespawn + frecuency > nextRespawn && numParticles> actualParticles)
	{
		float vX = rand() % 20;
		float vY = rand() % 20;
		float vZ = rand() % 20;


		
		int numero_aleatorio1 = std::rand() % 10001;
		double colorX = static_cast<double>(numero_aleatorio1) / 100.0;
			
		int numero_aleatorio2 = std::rand() % 10001;
		double colorY = static_cast<double>(numero_aleatorio2) / 100.0;
			
		int numero_aleatorio3 = std::rand() % 10001;
		double colorZ = static_cast<double>(numero_aleatorio3) / 100.0;

		
		
		int randomValue1 = std::rand() % 2;
		int result1 = (randomValue1 == 0) ? -1 : 1;

		int randomValue2 = std::rand() % 2;
		int result2 = (randomValue2 == 0) ? -1 : 1;

		int randomValue3 = std::rand() % 2;
		int result3 = (randomValue3 == 0) ? -1 : 1;

		Particle* particle;
		Vector3 vel(float(rand() % 10 / 10.0) * vX * result1, float(rand() % 10 / 10.0) * vY * result2, float(rand() % 10 / 10.0) * vZ * result3);
		float masa = 1;
		float liveTime = 3;
		particle = new Particle(*emitter->getPos(), vel, Vector3(0, -9.8, 0), masa, liveTime, DAMPING);
		particle->getRenderItem()->color = Vector4(colorX, colorY, colorZ, 1);
		particle->getRenderItem()->shape = CreateShape(physx::PxSphereGeometry(0.3));
		particle->getRenderItem()->transform = particle->getPos();
		RegisterRenderItem(particle->getRenderItem());
		pS->addParticle(particle);

		nextRespawn += frecuency;
		actualParticles++;
		std::cout << actualParticles << std::endl;
	}
	else
	{
		lastRespawn += t;
	}
}
