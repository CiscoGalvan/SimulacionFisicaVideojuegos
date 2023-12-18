#include "Palo.h"
Palo::Palo(Vector3 pos, PxPhysics* _gPhysics, PxScene* _gScene,Bola* blanca,float radius)
{
	this->blanca = blanca;
	this->position = pos;
	this->_gPhysics = _gPhysics;
	this->_gScene = _gScene;
	this->radius = radius;


	PxMaterial* gMaterial = _gPhysics->createMaterial(CESTATICO_PALO, CDINAMICO_PALO, CELASTICO_PALO);


	palo = _gPhysics->createRigidDynamic(PxTransform(this->position));
	palo->setMass(1001);
	PxShape* shape = CreateShape(PxBoxGeometry(4,0.3,0.3), gMaterial);
	PxFilterData filterData;
	filterData.word0 = 1;
	shape->setSimulationFilterData(filterData);
	palo->attachShape(*shape);

	
	palo->setMassSpaceInertiaTensor(Vector3(0,0,0));
	palo->setActorFlag(PxActorFlag::eDISABLE_GRAVITY,true);
	_gScene->addActor(*palo);
	RenderItem* item;
	item = new RenderItem(shape, palo, Vector4(1, 1, 1, 1));
	

	transform = new PxTransform(position);
	transform->q = PxQuat(PxPi/2, Vector3(0, 1, 0));
	palo->setGlobalPose(*transform); 
	
	relativePos = transform->p - blanca->getPos();
	angle = atan2(relativePos.z, relativePos.x);
	float newX = blanca->getPos().x + radius * cos(angle);
	float newZ = blanca->getPos().z + radius * sin(angle);
	newRotationAngle = atan2(newZ - blanca->getPos().z, newX - blanca->getPos().x);
	
}

void Palo::rotateAroundBola()
{

	

	//Posicionamos el palo en su nuevo lugar
	float newX = blanca->getPos().x + radius* cos(angle);
	float newZ = blanca->getPos().z + radius* sin(angle);
	angle = PxPi / 90 + angle;

	transform->p.x = newX;
	transform->p.z = newZ;


	// Ajustamos la orientación para que la esquina inicial siga mirando a la bola blanca
	 newRotationAngle = atan2(newZ - blanca->getPos().z, newX - blanca->getPos().x);
	

	transform->q = PxQuat(-newRotationAngle, PxVec3(0, 1, 0));

	palo->setGlobalPose(*transform);
}
void Palo::updateBlanca()
{
	float newX = blanca->getPos().x + radius * cos(angle);
	float newZ = blanca->getPos().z + radius * sin(angle);
	

	transform->p.x = newX;
	transform->p.z = newZ;
}