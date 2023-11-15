#include "ExplosionGenerator.h"
#include <numbers>

void ExplosionGenerator::updateForce(Particle* p, double t)
{
	if (fabs(1 / p->getMass()) < 1e-10) return;

	radius += velocity * t; // El radio aumenta con el tiempo

	Vector3 aux = p->getPos()->p - position;
	double r = sqrt((aux.x * aux.x + aux.y * aux.y + aux.z * aux.z));

	if (r < radius)
	{
		Vector3 f = (k / (r * r)) * aux * exp(-t / timeConstant);
		p->addForce(f);
	}
}
