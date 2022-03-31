#pragma once
#include "btBulletDynamicsCommon.h"
#include "../../common/Header.h"
#include <stdio.h>
#include <vector>
class BulletPhysics
{
public:
	BulletPhysics(float gravity = -10.0f);
	~BulletPhysics();

	void Update(float dt);

	void CreateBox(float xHalfSize, float yHalfSize, float zHalfSize, float xPos, float yPos, float zPos, float xRota, float yRota, float zRota, float wRota, float Mass);
	void CreateSphere(float radius, float xPos, float yPos, float zPos, float Mass);
	void CreatePlane();

	void SetGravity(float gravity);
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

	std::vector<btRigidBody*> rigidbodies;
};

