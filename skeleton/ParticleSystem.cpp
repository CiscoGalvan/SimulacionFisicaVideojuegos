#include "ParticleSystem.h"
ParticleSystem::ParticleSystem()
{
	gF = new GravityForceGenerator(Vector3(0, -9.8, 0));	
	pfR = new ParticleForceRegistry();
	fG.push_back(gF);
	
}

void ParticleSystem::update(double t)
{
	timeAlive += t;
	if (shot)delay--;

	if(delay <= 0)
	{
		delay = 10;
		shot = false;
	}

	if (!pfR->empty()) 
	{
		pfR->updateForces(t);

	}
	

	for(auto it : generators)
	{
		it->update(t);
	}

	auto ai = fireworks.begin();
	while(  ai != fireworks.end())
	{
	
		auto aux = ai;
		++aux;


		physx::PxTransform* trans = (*ai)->getPos();
		if (trans->p.y < 20 || (*ai)->getTimeAlive() >(*ai)->getDeathTime())
		{
			delete* ai; fireworks.remove(*ai);
		}
		else if ((*ai)->getStatus())
		{
			
			physx::PxTransform p (Vector3((*ai)->getPos()->p.x, (*ai)->getPos()->p.y, (*ai)->getPos()->p.z));
			
			if(!(*ai)->getGenerator())
			{
				string name = "UNIFORM";
				Particle* papa = new Particle(p, Vector3(0), Vector3(0, -3.0, 0), 1, 1000, DAMPING, false);
				addGenerator(name, papa, 100, 0.001,-1);
			}
			else
			{
				string name = "GAUSS";
				Particle* papa = new Particle(p, Vector3(0), Vector3(0, -3.0, 0), 1, 1000, DAMPING, true);
				addGaussianGenerator(name, papa, 100, 0.001);
			}
			delete* ai; fireworks.remove(*ai);	
			shot = true;
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

void ParticleSystem::shootParticle(float vel, float radius,float liveTime, float masa,Vector3 gravity)
{
	Camera* cam = GetCamera();
	Particle* particle;
	particle = new Particle(cam->getTransform(), cam->getDir() * vel,gravity, masa,liveTime, DAMPING,false);
	particle->getRenderItem()->color = Vector4(1, 0.5, 0, 1);
	particle->getRenderItem()->shape = CreateShape(physx::PxSphereGeometry(radius));
	particle->getRenderItem()->transform = particle->getPos();
	RegisterRenderItem(particle->getRenderItem());
	pfR->addRegistry(new GravityForceGenerator(gravity), particle);
	particles.push_back(particle);
}

void ParticleSystem::shootFirework(float vel, float radius, float liveTime, float masa, Vector3 gravity,bool gaussian)
{
	Camera* cam = GetCamera();
	Firework* firework;
	firework = new Firework(cam->getTransform(), cam->getDir() * vel, gravity, masa, liveTime,DAMPING,300,1000,gaussian);
	firework->getRenderItem()->color = Vector4(1, 0.5, 0, 1);
	firework->getRenderItem()->shape = CreateShape(physx::PxSphereGeometry(radius));
	firework->getRenderItem()->transform = firework->getPos();
	RegisterRenderItem(firework->getRenderItem());
	pfR->addRegistry(new GravityForceGenerator(Vector3(0, -9.8, 0)), firework);
	fireworks.push_back(firework);
}

void ParticleSystem::addGenerator(std::string name, Particle* particle, int numParticles, float frecuency,int type)
{
	if(shot==false)
	{
		if(type == -1)
		{
			int randomValue = std::rand() % 2;
			type = (randomValue == 0) ? -1 : 1;
		}
		
		ParticleGenerator* pG = new ParticleGenerator(name, particle, numParticles, frecuency, type,this);
		generators.push_back(pG);
		shot = true;
	}
	
}

void ParticleSystem::addGaussianGenerator(std::string name, Particle* particle, int numParticles, float frecuency)
{
	if (shot == false)
	{
		GaussianGenerator* pG = new GaussianGenerator(name, particle, numParticles, frecuency, this);
		generators.push_back(pG);
		shot = true;
	}
}