#include "FuerzaInstantanea.h"

FuerzaInstantanea::FuerzaInstantanea(Bola* p, Vector3 force)
{
	this->bola = p;
	this->force = force;
	updateForce(bola->getBola(), 0);
}

FuerzaInstantanea::~FuerzaInstantanea()
{
}

void FuerzaInstantanea::updateForce(PxRigidBody* rb, double dt)
{
	rb->addForce(force);
}