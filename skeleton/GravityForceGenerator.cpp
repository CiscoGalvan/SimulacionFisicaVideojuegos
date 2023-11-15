#include "GravityForceGenerator.h"
GravityForceGenerator::GravityForceGenerator(const Vector3& g) : ForceGenerator()
{
	_gravity = g;
}

void GravityForceGenerator::updateForce(Particle* p, double t)
{
	//Mira si la particula tiene masa infinita
	if(fabs( 1 /p->getMass()) < 1e-10)
		return;

	p->addForce(_gravity * p->getMass());
}