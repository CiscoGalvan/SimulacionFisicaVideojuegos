#include "BuoyancyForceGenerator.h"

BuoyancyForceGenerator::BuoyancyForceGenerator(Particle* liquidParticle, float h, float v, float d, float g)
{
	this->liquidParticle = liquidParticle;
	this->height = h;
	this->volume = v;
	this->liquidDensity = d;
	this->gravity = g;
}

void BuoyancyForceGenerator::updateForce(Particle* particle, double t) {
	float h = particle->getPos()->p.y;
	float h0 = liquidParticle->getPos()->p.y;

	Vector3 f(0.0f, 0.0f, 0.0f);
	float immersed = 0.0f;
	if (h - h0 > height * 0.5f) {
		immersed = 0.0f;
	}
	else if (h0 - h > height * 0.5f) {
		// Totally immersed
		immersed = 1.0f;
	}
	else {
		immersed = (h0 - h) / height + 0.5f;
	}
	f.y = liquidDensity * volume * immersed * gravity;

	cout << f.y << endl;
	particle->addForce(f);
}