#pragma once
#include "ForceGenerator.h"
#include "core.hpp"
class ParticleDragGenerator : public ForceGenerator
{
public:
	ParticleDragGenerator();
	ParticleDragGenerator(Vector3 fuerzaViento,const float k1, const float k2,Vector3 origen, Vector3 tam);	
protected:
	virtual void updateForce(Particle* particle, double t);
	inline void setDrag(float k1, float k2) { _k1 = k1; _k2 = k2; }
	inline float getK1() { return _k1; }
	inline float getK2() { return _k2; }
	Vector3 fuerzaViento;
	Vector3 position;
	Vector3 tam;

	float _k1, _k2;
};

