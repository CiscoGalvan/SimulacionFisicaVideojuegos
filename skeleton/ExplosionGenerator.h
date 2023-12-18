#pragma once
#include "ForceGenerator.h"
class ExplosionGenerator : public ForceGenerator
{
public:

	ExplosionGenerator(double K, double constant, Vector3 pos, double vel, double r) : k(K), timeConstant(constant), position(pos), velocity(vel), radius(r) {};

	virtual void updateForce(Particle* p, double t);
	virtual void updateForce(physx::PxRigidBody* solid, double duration);
	void setCoefficient(double K) { k = K; };

	void setConstant(double constant) { timeConstant = constant; };

	void setRadius(double r) { radius = r; };

protected:
	Vector3 position;
	double k;
	double timeConstant;
	double radius;
	double velocity;
private:
};