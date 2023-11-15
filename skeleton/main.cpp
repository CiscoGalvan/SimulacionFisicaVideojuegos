#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"
#include "ParticleSystem.h"
#include <iostream>
#include <list>

std::string display_text = "This is a test";


using namespace physx;


PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;


PxMaterial*				gMaterial	= NULL;

PxPvd*                  gPvd        = NULL;

ParticleSystem* pS = NULL;
PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene      = NULL;
ContactReportCallback gContactReportCallback;

bool shot = false;
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

	pS = new ParticleSystem();


	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);
}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);
	gScene->simulate(t);
	pS->update(t);
	gScene->fetchResults(true);
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();	
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	pS->cleanupPhysics();
	gFoundation->release();
}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	switch(toupper(key))
	{
	case 'R':	//BOLA DE MASA GRANDE
	{	

		pS->shootParticle(10, 0.2,20, 1000,Vector3(0, -9.8, 0));
		break;
	}

	case 'T':	//BOLA DE MASA PEQUEÑA
	{	
		pS->shootParticle(25, 0.2, 20,0.1,Vector3(0, -9.8, 0));
		break;
	}	

	case 'Y':	//FIREWORK 1
	{
		pS->shootFirework(250, 0.2, 2, 1,Vector3(0, -9.8, 0),false);
		break;
	}
	case 'U':	//FIREWORK 2
	{
		pS->shootFirework(250, 0.2, 2,1, Vector3(0, -9.8, 0), true);
		break;
	}
	case 'Q':
	{
		pS->showSquareFunction();
		break;
	}
	case 'I':
	{

		cout << GetCamera()->getTransform().p.x<<" "<< GetCamera()->getTransform().p.y<<" "<< GetCamera()->getTransform().p.z<<endl;
		physx::PxTransform pT(20.1391, 89.0057 ,19.4672);
		Particle* particle;
		float masa = 0.1;
		float vel = 2;
		float liveTime = 10000;
		particle = new Particle(pT, Vector3(0,0,0) * vel, Vector3(0,0,0 ), masa, liveTime, DAMPING, false);
		pS->addGenerator("fuente", particle, 1, 0.01,2);
		break;
	}

	case 'P': pS->anadeFuerza();
		break;

	case 'L': 
	{
		Camera* cam = GetCamera();
		pS->generaParticula(physx::PxTransform(-34, 200, -47), Vector3(0, 0, 0), Vector3(0, 0, 0), 10, Vector3(0, -9.8, 0));
		pS->generaParticula(physx::PxTransform(-34, 200, -27), Vector3(0, 0, 0), Vector3(0, 0, 0), 0.001, Vector3(0, -9.8, 0));
	}
	case'K':
	{
		pS->allowWind();
		break;
	}
	case 'J':
	{
		pS->denyWind();
		break;
	}
	case 'N':
	{
		pS->allowTorbellino();
		break;
	}
	case 'M':
	{
		pS->denyTorbellino();
		break;
	}
	case 'B':
	{
		pS->explode();
		break;
	}
	case 'V':
	{
		pS->setGeneration();
	}
	default:
		break;
	}
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