#include "ParticleSystem.h"
ParticleSystem::ParticleSystem()
{
	gravity = Vector3(0, -9.8, 0);	
}

void ParticleSystem::update(double t)
{
	timeAlive += t;
	
	for(auto it : generators)
	{
		it->update(t);
	}

	auto it = particles.begin();
	while (it != particles.end())
	{
		auto aux = it;
		++aux;
		physx::PxTransform* trans = (*it)->getPos();
		if (trans->p.y < 20 || (*it)->getTimeAlive() >(*it)->getDeathTime())
		{
			delete* it; particles.remove(*it);
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
	auto it = particles.begin();
	while (it != particles.end())
	{
		auto aux = it;
		++aux;
		delete* it; particles.remove(*it);
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
	particles.push_back(particle);
}

void ParticleSystem::addGenerator(std::string name, Particle* particle, int numParticles, float frecuency)
{
	ParticleGenerator* pG = new ParticleGenerator(name,particle,numParticles,frecuency,this);
	generators.push_back(pG);
}