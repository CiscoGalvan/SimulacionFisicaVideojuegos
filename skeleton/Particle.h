#pragma once
#include "RenderUtils.hpp"
#include <iostream>
class Particle
{
private:
	Vector3 vel;
	physx::PxTransform pos;
	RenderItem* item;
	Vector3 acel;
	float damping; float masa;
	bool destroy = false;
public:
	Particle(physx::PxTransform  pos, Vector3 vel, Vector3 acel, float masa,float damping);
	~Particle();
	void integrate(double t);	
	void verticalShoot(double t);
	inline RenderItem* getRenderItem() { return item; }
	inline physx::PxTransform* getPos() { return &pos; }
	inline bool getDestroy() { return destroy; }
	inline void setDestroy() { destroy = true; }
};

