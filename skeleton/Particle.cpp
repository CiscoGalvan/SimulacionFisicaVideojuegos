#include "Particle.h"
Particle::Particle(physx::PxTransform pos, Vector3 vel,Vector3 acel,float masa,float damping)
{
	item = new RenderItem();
	this->vel = vel;
	this->pos = pos;
	this->acel = acel;
	this->damping = damping;
	this->masa = masa;
}

Particle::~Particle()
{
	DeregisterRenderItem(item);
	delete item;
}

void Particle::integrate(double t)
{
	//MRUA
	vel += acel * t;
	vel *= pow(damping,t);
	pos.p += vel * t ;
}

void Particle::verticalShoot(double t)
{
	vel += acel * t;
	vel *= pow(damping, t);
	pos.p += vel * t;
}