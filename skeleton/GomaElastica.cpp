#include "GomaElastica.h"
GomaElastica::GomaElastica(float k, double length, Particle* other): SpringForceGenerator(k, length, other)
{}

void GomaElastica::updateForce(Particle* particle, double t)
{
	Vector3 f = particle->getPos()->p;
	f -= other->getPos()->p;

	// Length
	float length = f.normalize();
	length = (length - this->length);

	if (length > 0.0f) {
		f *= -(length * k);
		particle->addForce(f);
	}
}