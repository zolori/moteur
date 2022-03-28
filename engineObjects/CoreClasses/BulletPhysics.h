#pragma once
#include "btBulletDynamicsCommon.h"
#include <stdio.h>
class BulletPhysics
{
public:
	BulletPhysics();
	~BulletPhysics();

	void Update();

	void CreateBox(float xHalfSize, float yHalfSize, float zHalfSize, float xPos, float yPos, float zPos, float Mass);
	void CreateSphere(float radius, float xPos, float yPos, float zPos, float Mass);

	///collision configuration contains default setup for memory
	btDefaultCollisionConfiguration* collisionConfiguration;
	///use the default collision dispatcher.
	btCollisionDispatcher* dispatcher;
	///btDbvtBroadphase is a good general purpose broadphase.
	btBroadphaseInterface* overlappingPairCache;
	///the default constraint solver.
	btSequentialImpulseConstraintSolver* solver;

	btDiscreteDynamicsWorld* dynamicsWorld;

	btAlignedObjectArray<btCollisionShape*> collisionShapes;
};

