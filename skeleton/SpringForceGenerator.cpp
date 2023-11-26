#include "SpringForceGenerator.h"
SpringForceGenerator::SpringForceGenerator( float k, double length, Particle* other)
{
	this->k = k;
	this->length = length;
	this->other = other;
}

void SpringForceGenerator::updateForce(Particle* particle,double t)
{
	Vector3 relativePos = Vector3(other->getPos() - particle->getPos());
	Vector3 force;

	const float length = relativePos.normalize();
	const float deltaX = length - this->length;

	force = relativePos * deltaX * k;

	particle->addForce(force);
}