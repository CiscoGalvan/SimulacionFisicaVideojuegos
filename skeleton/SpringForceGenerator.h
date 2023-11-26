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

	/*inline float getK() const { return k; }
	inline void setK(const float k) { this->k = k; }
	inline double getLength() const { return length; }
	inline void setLength(double Length) { length = Length; }
	inline Particle* getOther() const { return other; }
	inline void setOther(Particle* Other) { other = Other; }*/
};

