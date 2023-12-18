#include "AnchoredSpringFG.h"
AnchoredSpringFG::AnchoredSpringFG(double k, double length,const Vector3&v) : SpringForceGenerator(k, length,nullptr)
{
	other = new Particle(physx::PxTransform(v), Vector3(0, 0, 0), Vector3(0, 0, 0), 1, 100, DAMPING, false);
	other->getRenderItem()->color = Vector4(1, 0.5, 0, 1);
	other->getRenderItem()->shape = CreateShape(physx::PxSphereGeometry(2));
	other->getRenderItem()->transform = other->getPos();
	RegisterRenderItem(other->getRenderItem());
}
AnchoredSpringFG::~AnchoredSpringFG()
{
	delete other;
}

void AnchoredSpringFG::updateForce(Particle* p, double t)
{
	Vector3 f = p->getPos()->p;
	f -= other->getPos()->p;

	// Length
	float length = f.normalize();
	length = (length - this->length);
	if (length > 3.46133e+17)
	{
		multiply = true;
	}
	else if (length > 0.0f) {
		f *= -(length * k);
		p->addForce(f);
	}
	
}