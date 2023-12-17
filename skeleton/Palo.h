#pragma once

#include <string>
#include "RenderUtils.hpp"
#include <PxScene.h>
#include <PxPhysics.h>
#include "PxShape.h"
#include <iostream>
#include "PxPhysics.h"
#include "PxRigidDynamic.h"
#include "Bola.h"
using namespace physx;
using namespace std;


const float CESTATICO_PALO = 100000000000;
const float CDINAMICO_PALO = 0;
const float CELASTICO_PALO = 0;

class Palo
{
private:

	PxRigidDynamic* palo;
	Vector3 position;
	PxTransform* transform;
	Bola* blanca;
	PxPhysics* _gPhysics;
	PxScene* _gScene;
	float radius;
	float angle;
	float newRotationAngle;
	Vector3 relativePos;
public:
	Palo(Vector3 position, PxPhysics* _gPhysics, PxScene* _gScene,Bola* blanca,float radius);
	void updateBlanca();
	void rotateAroundBola();
	inline float getAngles() { return newRotationAngle; }
	inline PxTransform* getPos() { return transform; }
};

