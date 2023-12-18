#pragma once
#include "Particle.h"
#include "Bola.h"
using namespace std;
class ForceGenerator
{
private:
	string name;
	double  _t = 0.0;
	double duration = -1;
public:
	virtual void updateForce(Particle* particle,double t) = 0;
	virtual void updateForce(physx::PxRigidBody* solid, double duration) {};
	virtual void updateForce(Bola* solid, double duration) {};
	inline bool update(double t)
	{
		_t += t;
		return _t < duration || duration < 0.0;
	}
	virtual ~ForceGenerator() {}

};

