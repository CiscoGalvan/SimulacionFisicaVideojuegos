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
void Particle::clearForce()
{
	force *= 0;
}
void Particle::integrate(double t)
{
	// Get the accel considering the force accum
	Vector3 resulting_accel = force * (pow(masa,-1));
	
	/*#pragma region EULER SEMI-IMPLICITO
	vel += resulting_accel * t; 
	vel *= powf(damping, t);
	pos.p += vel * t;
	this->timeAlive += t;
	clearForce();
	#pragma endregion*/

	//Este va acelerando con el tiempo, por lo que se sale de los limites del generador de fuerza por muelles y desaparece
	#pragma region EULER 
	pos.p += vel * t;
	vel += resulting_accel * t;
	this->timeAlive += t;
	clearForce();
	#pragma endregion



}
