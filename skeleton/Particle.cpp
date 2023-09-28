#include "Particle.h"
Particle::Particle(physx::PxTransform pos,int vel)
{
	item = new RenderItem();
	dir = Vector3(1, 0, 0);
	this->pos = pos;
	velocity = vel;
}

Particle::~Particle()
{
	DeregisterRenderItem(item);
}

void Particle::integrate(double t)
{
	pos.p += physx::PxVec3(dir.x, dir.y, dir.z) * velocity * t ;
	
}