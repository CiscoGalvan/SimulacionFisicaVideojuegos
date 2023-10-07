#include "Particle.h"
Particle::Particle(physx::PxTransform pos, Vector3 vel,Vector3 acel,float masa,float liveTime,float damping)
{
	item = new RenderItem();
	this->vel = vel;
	this->pos = pos;
	this->acel = acel;
	this->damping = damping;
	this->masa = masa;
	this->liveTime = liveTime;
	
}

Particle::Particle()
{
	item = new RenderItem();
	this->vel = Vector3(0,0,0);
	this->pos = physx::PxTransform(Vector3(50,50,50));
	this->acel = Vector3(0,0,0);
	this->damping = DAMPING;
	this->masa = 1;
	this->liveTime = 1000000;
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
	this->timeAlive += t;
	
}

void Particle::verticalShoot(double t)
{
	vel += acel * t;
	vel *= pow(damping, t);
	pos.p += vel * t;
}