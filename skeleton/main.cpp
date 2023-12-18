#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"
#include "ParticleSystem.h"
#include "RigidBodySystem.h"
#include <iostream>
#include <list>
#include "Bola.h"

std::string display_text = "Snooker Francisco Galvan";


using namespace physx;


PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;


PxMaterial*				gMaterial	= NULL;

PxPvd*                  gPvd        = NULL;

RigidBodySystem* rS = NULL;
PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene      = NULL;
ContactReportCallback gContactReportCallback;

bool pulsed = false;
bool shot = false;
int cont = 0;
// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport,PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(),true,gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	
	GetCamera()->setDir(&PxTransform(-0.00002, -1, -0.002222));
	GetCamera()->setTransform(&PxTransform(0, 200,0));

	
	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);

	rS = new RigidBodySystem(gPhysics, gScene);

}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);
	gScene->simulate(t);
	rS->update(t);
	gScene->fetchResults(true);

	if (pulsed && rS->poderDisparar())
	{
		cont++;
		rS->setHoldValue(cont);
	}
	else
	{
		rS->revientaPelota();
		cont = 0;	
		rS->setHoldValue(0);
	}


	
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);
	delete rS;
	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();	
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	//pS->cleanupPhysics();
	
	gFoundation->release();
}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	switch(toupper(key))
	{
	case '1':
	{
		rS->configuraCamara();
		break;
	}
	case '6':
	{
		if(rS->firstMoved())rS->moveBlanca(Direcciones::RIGHT);
		break;
	}
	case '4':
	{
		if (rS->firstMoved())rS->moveBlanca(Direcciones::LEFT);
		break;
	}
	case '8':
	{
		if (rS->firstMoved())rS->moveBlanca(Direcciones::UP);
		break;
	}
	case '2':
	{
		if (rS->firstMoved())rS->moveBlanca(Direcciones::DOWN);
		break;
	}
	case ' ':
	{
		if(rS->poderDisparar())rS->rotatePalo();
		break;
	}
	case'F':
	{
		rS->ExplotaTodo();
		break;
	}
	default:
		break;
	}
}

void mousePressed(int button, int state)
{
	if (state == 0 && button == 0) pulsed = true;
	else pulsed = false;
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
}



int main(int, const char*const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}