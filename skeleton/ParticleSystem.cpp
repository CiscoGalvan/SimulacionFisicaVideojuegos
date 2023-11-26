#include "ParticleSystem.h"
#include <math.h>
const int INF = MAXINT;

ParticleSystem::ParticleSystem()
{
	pfR = new ParticleForceRegistry();
	gravedad = new GravityForceGenerator(Vector3(0, -9.8, 0));
	fG.push_back(gravedad);
	
	windZone = new Particle(physx::PxTransform(Vector3(20, 39, 15)), Vector3(0, 0, 0), Vector3(0, 0, 0), 0, INF, 0, false);
	windZone->getRenderItem()->color = physx::PxVec4(1.0, 0.0, 0.0, 1);
	windZone->getRenderItem()->shape = CreateShape(physx::PxBoxGeometry(15,15,15));
	windZone->getRenderItem()->transform = windZone->getPos();
	RegisterRenderItem(windZone->getRenderItem());
	
	wind = new ParticleDragGenerator(Vector3(0, 200, 0), 0.01, 0, windZone->getPos()->p, Vector3(30, 30, 30) * 3);
	torbellino = new GeneradorTorbellino(Vector3(0,50,0),5,windZone->getPos()->p,Vector3(30,30,30)*3);
	explosion_tai = new ExplosionGenerator(1000000, 300, Vector3{ 0,20,0 }, 900, 100);
}

void ParticleSystem::update(double t)
{
	timeAlive += t;
#pragma region Square
	if (!showSquare && registered)
	{
		registered = false;
		DeregisterRenderItem(windZone->getRenderItem());
	}
	else if (showSquare && !registered)
	{
		registered = true;
		RegisterRenderItem(windZone->getRenderItem());
	}
#pragma endregion
	

#pragma region ParticlesGeneration
	if (generateParticles)
	{
		std::mt19937 gen(rd1());
		int randomValue1 = std::rand() % 2;
		int result1 = (randomValue1 == 0) ? -1 : 1;

		int randomValue2 = std::rand() % 2;
		int result2 = (randomValue2 == 0) ? -1 : 1;

		int randomValue3 = std::rand() % 2;
		int result3 = (randomValue3 == 0) ? -1 : 1;

		Particle* particle;
		Vector3 pos(randomVel(gen) * result1, randomVel(gen) * result2, randomVel(gen) * result3);
		Vector3 vel(randomVel(gen) * result1, randomVel(gen) * result2, randomVel(gen) * result3);
		generaParticula(physx::PxTransform(pos), vel, Vector3(0, 0, 0), 1, Vector3(0, -9.8, 0));
	}
#pragma endregion

#pragma region DelayExplosion
	if (explosionTime > 0)
	{
		explosionTime--;
	}
	else
	{
		quitExplosion = true;
		explosionTime = 0;
	}

	
	if (quitExplosion)
	{
		fG.remove(explosion_tai);
		quitExplosion = false;
	}
#pragma endregion

	
	if(temporaryGravedad)
	{
		gravityTime--;
	}

	if (gravityTime <= 0)
	{
		temporaryGravedad = false;
		gravityTime = 1000;
		pfR->deleteForceRegistry(temporaryGravity);
	}

#pragma region ShootingDelay
	if (shot)delay--;
	if (delay <= 0)
	{
		delay = 10;
		shot = false;
	}
#pragma endregion

	
#pragma region Updates
	for (auto it : generators)
	{
		it->update(t);
	}

	auto ai = fireworks.begin();
	while (ai != fireworks.end())
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

			physx::PxTransform p(Vector3((*ai)->getPos()->p.x, (*ai)->getPos()->p.y, (*ai)->getPos()->p.z));

			if (!(*ai)->getGenerator())
			{
				string name = "UNIFORM";
				Particle* papa = new Particle(p, Vector3(0), Vector3(0, -3.0, 0), 1, 1000, DAMPING, false);
				addGenerator(name, papa, 100, 0.001, -1);
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

		if (trans->p.y < -100 || trans->p.y > 250 || (*it)->getTimeAlive() > (*it)->getDeathTime())
		{
			pfR->deleteParticleRegistry(*it);
			delete* it; particles.remove(*it);
		}
		else
		{
			(*it)->integrate(t);


		}
		it = aux;






	}
	pfR->updateForces(t);
	if(f3 != nullptr)
		cout << f3->getK() << endl;
#pragma endregion

	
}
void ParticleSystem::allowWind()
{
	fG.push_back(wind);
	
}
void ParticleSystem::denyWind()
{
	fG.remove(wind);
}


void ParticleSystem::allowTorbellino()
{
	fG.push_back(torbellino);
}
void ParticleSystem::denyTorbellino()
{
	fG.remove(torbellino);
}

void ParticleSystem::explode()
{	if(explosionTime <=0)
	{
		for (auto it : particles)
		{
			pfR->addRegistry(explosion_tai, it);
		}
		explosionTime = 1000;
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

void ParticleSystem::generateSpringDemo()
{
	Particle* particle1 = new Particle(physx::PxTransform(-34, 180, -47), Vector3(0, 0, 0), Vector3(0, 0, 0), 1, 200, DAMPING, false);
	particle1->getRenderItem()->color = Vector4(1, 1, 0, 1);
	particle1->getRenderItem()->shape = CreateShape(physx::PxSphereGeometry(2));
	particle1->getRenderItem()->transform = particle1->getPos();
	RegisterRenderItem(particle1->getRenderItem());

	Particle* particle2 = new Particle(physx::PxTransform(-34, 190, -47), Vector3(0, 0, 0), Vector3(0, 0, 0), 2, 200, DAMPING, false);

	particle2->getRenderItem()->color = Vector4(1, 0.5, 0, 1);
	particle2->getRenderItem()->shape = CreateShape(physx::PxSphereGeometry(2));
	particle2->getRenderItem()->transform = particle2->getPos();
	RegisterRenderItem(particle2->getRenderItem());


	SpringForceGenerator* f1 = new SpringForceGenerator(1, 0, particle2);
	pfR->addRegistry(f1, particle1);
	
	SpringForceGenerator* f2 = new SpringForceGenerator(1, 0, particle1);
	pfR->addRegistry(f2, particle2);


	particles.push_back(particle1);
	particles.push_back(particle2);


	//Enganche
	////Solo funciona si: la posición pasada a Anchored - la pasada a la partícula tiene todas sus coordenadas > 0.
	//f3= new AnchoredSpringFG(2000, 10, Vector3(-34, 200, -47));
	//Particle* p3 = new Particle(physx::PxTransform(-34, 180, -47), Vector3(0, 0, 0), Vector3(0, 0, 0), 10, 200, DAMPING, false);

	//pfR->addRegistry(new GravityForceGenerator(Vector3(0, -9.8, 0)), p3);
	//p3->getRenderItem()->color = Vector4(1, 0.5, 0, 1);
	//p3->getRenderItem()->shape = CreateShape(physx::PxSphereGeometry(2));
	//p3->getRenderItem()->transform = p3->getPos();
	//RegisterRenderItem(p3->getRenderItem());

	//pfR->addRegistry(f3, p3);
	//fG.push_back(f3);
	//particles.push_back(p3);

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
	for (auto it : fG)
	{
		pfR->addRegistry(it, particle);
	}
	particles.push_back(particle);
}

void ParticleSystem::temporalGravity(Vector3 v)
{
	if(gravityTime == 1000)
	{
		temporaryGravity = new GravityForceGenerator(Vector3(v));
		for (auto it : particles)
		{
			pfR->addRegistry(temporaryGravity, it);
		}
		temporaryGravedad = true;
	}
	
}
void ParticleSystem::generaParticula(physx::PxTransform pos, Vector3 vel, Vector3 acel, float masa, Vector3 gravity)
{
	
	Particle* particle;
	particle = new Particle(pos, vel, gravity, masa, 200, DAMPING, false);
	particle->getRenderItem()->color = Vector4(1, 0.5, 0, 1);
	particle->getRenderItem()->shape = CreateShape(physx::PxSphereGeometry(2));
	particle->getRenderItem()->transform = particle->getPos();
	RegisterRenderItem(particle->getRenderItem());
	for (auto it : fG)
	{
		pfR->addRegistry(it, particle);
	}
	particles.push_back(particle);
}
void ParticleSystem::shootFirework(float vel, float radius, float liveTime, float masa, Vector3 gravity,bool gaussian)
{
	Camera* cam = GetCamera();
	Firework* firework;
	firework = new Firework(cam->getTransform(), cam->getDir() * vel, gravity, masa, liveTime,DAMPING,100,1000,gaussian);
	firework->getRenderItem()->color = Vector4(1, 0.5, 0, 1);
	firework->getRenderItem()->shape = CreateShape(physx::PxSphereGeometry(radius));
	firework->getRenderItem()->transform = firework->getPos();
	RegisterRenderItem(firework->getRenderItem());
	pfR->addRegistry(new GravityForceGenerator(gravity), firework);
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