#include "ParticleSystem.h"
ParticleSystem::ParticleSystem(float frecuency)
{
	gravity = Vector3(0, -9.8, 0);
	this->frecuency = frecuency;
	this->nextRespawn = frecuency;
}

void ParticleSystem::update(double t)
{
	if (lastRespawn + frecuency > nextRespawn)
	{
		float vX = rand() % 20;
		float vY = rand() % 20;
		float vZ = rand() % 20;

		int randomValue1 = std::rand() % 2;	
		int result1 = (randomValue1 == 0) ? -1 : 1;

		int randomValue2 = std::rand() % 2;	
		int result2 = (randomValue2 == 0) ? -1 : 1;

		int randomValue3 = std::rand() % 2;
		int result3 = (randomValue3 == 0) ? -1 : 1;

		Particle* particle;
		Vector3 vel(float(rand() % 10 / 10.0) *vX * result1, float(rand() % 10 / 10.0) * vY* result2, float(rand() % 10 / 10.0) * vZ * result3);
		physx::PxTransform transform(Vector3(55, 50, 50));
		float masa = 1;
		float liveTime = 3;
		particle = new Particle(transform,vel , Vector3(0, -9.8, 0), masa,liveTime, DAMPING);
		particle->getRenderItem()->color = Vector4(1, 0.5, 0, 1);
		particle->getRenderItem()->shape = CreateShape(physx::PxSphereGeometry(0.3));
		particle->getRenderItem()->transform = particle->getPos();
		RegisterRenderItem(particle->getRenderItem());
		v.push_back(particle);

		nextRespawn += frecuency;
	}
	else
	{
		lastRespawn += t;
	}

	auto it = v.begin();
	while (it != v.end())
	{
		auto aux = it;
		++aux;
		physx::PxTransform* trans = (*it)->getPos();
		if (trans->p.y < 20 || (*it)->getTimeAlive() >(*it)->getDeathTime())
		{
			delete* it; v.remove(*it);
		}
		else
		{
			(*it)->integrate(t);
		}
		it = aux;
	}
}

void ParticleSystem::cleanupPhysics()
{
	auto it = v.begin();
	while (it != v.end())
	{
		auto aux = it;
		++aux;
		delete* it; v.remove(*it);
		it = aux;
	}
}

void ParticleSystem::shootParticle(float vel, float radius,float liveTime ,Vector3 gravity)
{
	Camera* cam = GetCamera();
	Particle* particle;
	float masa = 1;
	particle = new Particle(cam->getTransform(), cam->getDir() * vel,gravity, masa,liveTime, DAMPING);
	particle->getRenderItem()->color = Vector4(1, 0.5, 0, 1);
	particle->getRenderItem()->shape = CreateShape(physx::PxSphereGeometry(radius));
	particle->getRenderItem()->transform = particle->getPos();
	RegisterRenderItem(particle->getRenderItem());
	v.push_back(particle);
}