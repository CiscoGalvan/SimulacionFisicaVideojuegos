#include "Particle.h"
Particle::Particle(physx::PxTransform pos, Vector3 vel,Vector3 acel,float masa,float liveTime,float damping,bool gaussian)
{
	item = new RenderItem();
	this->vel = vel;
	this->pos = pos;
	this->force = acel;
	this->damping = damping;
	this->masa = masa;
	this->liveTime = liveTime;
	this->gaussianDistribution = gaussian;
}

Particle::Particle()
{
	item = new RenderItem();
	this->vel = Vector3(0,0,0);
	this->pos = physx::PxTransform(Vector3(50,50,50));
	this->force = Vector3(0,0,0);
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
	// Get the accel considering the force accum
	Vector3 resulting_accel = force * (1/masa);
	vel += resulting_accel * t; // Ex. 1.3 --> add acceleration
	vel *= pow(damping, t); // Exercise 1.3 --> add damping
	pos.p += vel * t;
	this->timeAlive += t;
	clearForce();


	//MRUA
	//vel += force * t;
	//vel *= pow(damping,t);
	//pos.p += vel * t ;
	//this->timeAlive += t;
	
}
