#include "Firework.h"
#include "ParticleGenerator.h"
Firework::Firework(physx::PxTransform  pos, Vector3 vel, Vector3 acel, float masa, float liveTime, float damping, float limit, float numParticles, bool gaussian)
{
	item = new RenderItem();
	this->vel = vel;
	this->pos = pos;
	this->force = acel;
	this->damping = damping;
	this->masa = masa;
	this->liveTime = liveTime;
	this->gaussianDistribution = gaussian;
	this->limit = limit;
	this->numParticles = numParticles;
}

Firework::~Firework()
{

}

void Firework::integrate(double t)
{
	Particle::integrate(t);

	if(pos.p.y > limit)
	{
		explosion = true;
	}
}

bool Firework::getGenerator()
{
	return gaussianDistribution;
}