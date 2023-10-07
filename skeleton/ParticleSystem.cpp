#include "ParticleSystem.h"
ParticleSystem::ParticleSystem()
{
	gravity = Vector3(0, -9.8, 0);	
	Firework* f = new Firework(physx::PxTransform(Vector3(50, 50, 50)), Vector3(0 ,150, 0), Vector3(0, -0.1, 0), 1, 100, DAMPING, 300, 1000);
	f->getRenderItem()->color = Vector4(1, 0, 0, 1);
	f->getRenderItem()->shape = CreateShape(physx::PxSphereGeometry(10));
	f->getRenderItem()->transform = f->getPos();
	RegisterRenderItem(f->getRenderItem());
	fireworks.push_back(f);
}

void ParticleSystem::update(double t)
{
	timeAlive += t;
	
	for(auto it : generators)
	{
		it->update(t);
	}
	

	auto ai = fireworks.begin();
	while(ai!=fireworks.end())
	{
		auto aux = ai;
		++aux;
		if ((*ai)->getStatus())
		{
			string name = "PAPA";
			physx::PxTransform p (Vector3((*ai)->getPos()->p.x, (*ai)->getPos()->p.y, (*ai)->getPos()->p.z));
			Particle* papa = new Particle( p, Vector3(0, 0, 0), Vector3(0, 0, 0), 1, 1000, DAMPING);
			addGenerator(name, papa, 1000, 0.001);
			delete* ai; fireworks.remove(*ai);	
		}
		else
		{
			(*ai)->integrate(t);
		}
		ai = aux;

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

void ParticleSystem::shootFirework(float vel, float radius, float liveTime, Vector3 gravity)
{
	Camera* cam = GetCamera();
	Firework* firework;
	float masa = 1;
	firework = new Firework(cam->getTransform(), cam->getDir() * vel, gravity, masa, liveTime,DAMPING,200,1000);
	firework->getRenderItem()->color = Vector4(1, 0.5, 0, 1);
	firework->getRenderItem()->shape = CreateShape(physx::PxSphereGeometry(radius));
	firework->getRenderItem()->transform = firework->getPos();
	RegisterRenderItem(firework->getRenderItem());
	fireworks.push_back(firework);
}

void ParticleSystem::addGenerator(std::string name, Particle* particle, int numParticles, float frecuency)
{
	ParticleGenerator* pG = new ParticleGenerator(name,particle,numParticles,frecuency,this);
	generators.push_back(pG);
}