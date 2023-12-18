#pragma once
#include "SpringForceGenerator.h"
class AnchoredSpringFG : public SpringForceGenerator
{
private:
	bool multiply;
public:
	AnchoredSpringFG(double k, double length,const Vector3& v);
	virtual void updateForce(Particle* p, double t);
	inline void biggerK() { if(k < 2000)k += 10; }
	inline void smallerK() { if(k > 0) k -= 10; }
	inline bool getMul() { return multiply; }
	inline float getK() { return k; }
	~AnchoredSpringFG();
};

