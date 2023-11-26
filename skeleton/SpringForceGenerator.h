#pragma once
#include "ForceGenerator.h"
class SpringForceGenerator : public ForceGenerator
{
protected:
	float k;
	double length;
	Particle* other;
public:
	SpringForceGenerator( float k, double Length, Particle* Other);
	~SpringForceGenerator(){}
	virtual void updateForce(Particle* particle,double t) ;

	
};

