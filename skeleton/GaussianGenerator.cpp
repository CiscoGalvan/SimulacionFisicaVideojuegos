#include "GaussianGenerator.h"
#include "ParticleSystem.h"
GaussianGenerator::GaussianGenerator(std::string name, Particle* emitter, int numParticles, float frecuency, ParticleSystem* pS) : ParticleGenerator(name,emitter,numParticles,frecuency,pS){}

GaussianGenerator::~GaussianGenerator()
{
	delete emitter;
}
void GaussianGenerator::update(double t)
{
	if (lastRespawn + frecuency > nextRespawn && numParticles > actualParticles)
	{

		

		/*int randomValue1 = std::rand() % 2;
		int result1 = (randomValue1 == 0) ? -1 : 1;

		int randomValue2 = std::rand() % 2;
		int result2 = (randomValue2 == 0) ? -1 : 1;

		int randomValue3 = std::rand() % 2;
		int result3 = (randomValue3 == 0) ? -1 : 1;*/

		Particle* particle;
		Vector3 vel(d(generator) * side(generator), d(generator) * side(generator), d(generator) * side(generator));
		float masa = 1;
		float liveTime = 3;
		particle = new Particle(*emitter->getPos(), vel, Vector3(0, -9.8, 0), masa, liveTime, DAMPING, true);
		particle->getRenderItem()->color = Vector4(d(generator), d(generator), d(generator), 1);
		particle->getRenderItem()->shape = CreateShape(physx::PxSphereGeometry(0.3));
		particle->getRenderItem()->transform = particle->getPos();
		RegisterRenderItem(particle->getRenderItem());
		pS->addParticle(particle);

		nextRespawn += frecuency;
		actualParticles++;
	}
	else
	{
		lastRespawn += t;
	}
}
