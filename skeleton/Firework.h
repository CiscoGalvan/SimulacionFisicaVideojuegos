#pragma once
#include "Particle.h"

class ParticleGenerator;
class Firework : public Particle
{
private:
	float limit = 0;
	float numParticles = 0;
	bool explosion = false;
public:
	Firework(physx::PxTransform  pos, Vector3 vel, Vector3 acel, float masa, float liveTime, float damping,float limit, float numParticles,bool gaussian);
    ~Firework();
	virtual void integrate(double t);
	inline bool getStatus() { return explosion; }
	bool getGenerator();
	inline void setGaussian(bool _gaussian) { gaussianDistribution = _gaussian; }
};

