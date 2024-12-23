#include "GeneradorTorbellino.h"
void GeneradorTorbellino::updateForce(Particle* particle, double t) {
	Vector3 particlePosition = particle->getPos()->p;
	if (fabs(1 / particle->getMass()) < 1e-10) return;
	Vector3 velocidadtorbellino = _k1 * Vector3(-(particlePosition.z - this->position.z), 75 - (particlePosition.y - this->position.y), particlePosition.x - this->position.x);
	Vector3 v = particle->getVel() - velocidadtorbellino;
	float drag_coef = v.normalize();
	drag_coef = _k1 * drag_coef + _k2 * drag_coef * drag_coef;
	Vector3 dragF = -v * drag_coef;

	particle->addForce(dragF);
}
void GeneradorTorbellino::updateForce(PxRigidBody* rb, double t) 
{
	Vector3 solidPosition = rb->getGlobalPose().p;
	if (fabs(1 / rb->getMass()) < 1e-10) return;
	Vector3 velocidadtorbellino = _k1 * Vector3(-(solidPosition.z - this->position.z), 75 - (solidPosition.y - this->position.y), solidPosition.x - this->position.x);
	Vector3 v = rb->getLinearVelocity() - velocidadtorbellino;
	float drag_coef = v.normalize();
	drag_coef = _k1 * drag_coef + _k2 * drag_coef * drag_coef;
	Vector3 dragF = -v * drag_coef;

	rb->addForce(dragF);
}

void GeneradorTorbellino::updateForce(Bola* bola, double t)
{
	Vector3 solidPosition = bola->getBola()->getGlobalPose().p;
	if (fabs(1 / bola->getBola()->getMass()) < 1e-10) return;
	Vector3 velocidadtorbellino = _k1 * Vector3(-(solidPosition.z - this->position.z), 75 - (solidPosition.y - this->position.y), solidPosition.x - this->position.x);
	Vector3 v = bola->getBola()->getLinearVelocity() - velocidadtorbellino;
	float drag_coef = v.normalize();
	drag_coef = _k1 * drag_coef + _k2 * drag_coef * drag_coef;
	Vector3 dragF = -v * drag_coef;

	bola->getBola()->addForce(dragF);
}


//Vector3 fuerzaViento, 
GeneradorTorbellino::GeneradorTorbellino(Vector3 fuerza, const float k, Vector3 WhirlPos, Vector3 tam_) : ParticleDragGenerator(fuerza,k,0, WhirlPos, tam_) {

}


