#pragma once
#include "ParticleDragGenerator.h"
class GeneradorTorbellino : public ParticleDragGenerator
{
public:
	GeneradorTorbellino(Vector3 fuerza, const float k, Vector3 WhirlPos, Vector3 tam_);
	~GeneradorTorbellino() {}
	void updateForce(Particle* particle, double t) override;
private:

};

