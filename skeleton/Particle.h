#pragma once
#include "RenderUtils.hpp"
#include <iostream>
class Particle
{
private:
	Vector3 dir;
	physx::PxTransform pos;
	int velocity;
	RenderItem* item;
	
public:
	Particle(physx::PxTransform  pos,int vel);
	~Particle();
	void integrate(double t);	
	inline RenderItem* getRenderItem() { return item; }
	inline physx::PxTransform* getPos() { return &pos; }
};

