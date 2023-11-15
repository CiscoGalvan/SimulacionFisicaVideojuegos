#include "ParticleDragGenerator.h"
ParticleDragGenerator::ParticleDragGenerator(Vector3 fuerzaViento,const float k1, const float k2, Vector3 origen, Vector3 tam)
{
	this->fuerzaViento = fuerzaViento;
	this->position = origen;
	this->tam = tam;
	_k1 = k1;
	_k2 = k2;
}

void ParticleDragGenerator::updateForce(Particle* particle, double t)
{
	Vector3 particlePosition = particle->getPos()->p;

	if((particlePosition.x >= position.x &&particlePosition.x <= position.x + tam.x) && (particlePosition.y >= position.y && particlePosition.y <= position.y + tam.y) && (particlePosition.z >= position.z && particlePosition.z <= position.z + tam.z))
	{
		if (fabs(1 / particle->getMass()) < 1e-10) return;



		//Vector3 v = particle->getVel();
		//Vector3 diff = f - v;
		//Vector3 dragF;
		//dragF = _k1 * diff + _k2 * diff.magnitude() * diff;

		//particle->addForce(dragF);

		Vector3 v = particle->getVel();

		Vector3 diff = fuerzaViento - v;

	
		Vector3 dragF;

		dragF = _k1 * diff + _k2 * diff * diff.magnitude();
		//Apply the drag force
		particle->addForce(dragF);
	}
}


