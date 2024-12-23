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


void ExplosionGenerator::updateForce(physx::PxRigidBody* solid, double t)
{
	if (fabs(1 / solid->getMass()) < 1e-10 || solid == nullptr) return;

	radius += velocity * t; // El radio aumenta con el tiempo

	Vector3 aux = solid->getGlobalPose().p - position;
	double r = sqrt((aux.x * aux.x + aux.y * aux.y + aux.z * aux.z));

	if (r < radius)
	{
		Vector3 f = (k / (r * r)) * aux * exp(-t / timeConstant);
		if (f == Vector3(0, 0, 0))return;
		try {
			solid->addForce(f);
		}
		catch (const std::exception& e) {
			// Manejo de la excepci�n
			std::cerr << "Excepci�n en addForce: " << e.what() << std::endl;
		}
	}
}
