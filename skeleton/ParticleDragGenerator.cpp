#include "ParticleDragGenerator.h"
ParticleDragGenerator::ParticleDragGenerator(const float k1, const float k2)
{
	_k1 = k1;
	_k2 = k2;
}

void ParticleDragGenerator::updateForce(Particle* particle, double t)
{
	if (fabs(1 / particle->getMass()) < 1 / (pow(10, 10)))
		return;

	Vector3 v = particle->getVel();
	float drag_coef = v.normalize();

	Vector3 dragF;
	drag_coef = _k1 * drag_coef + _k2 * drag_coef * drag_coef;
	dragF = -v * drag_coef;
	//Apply the drag force
	particle->addForce(dragF);
}