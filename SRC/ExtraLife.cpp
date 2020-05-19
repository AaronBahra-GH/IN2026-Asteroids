#include <stdlib.h>
#include "GameUtil.h"
#include "ExtraLife.h"
#include "BoundingShape.h"

// constructor
ExtraLife::ExtraLife(void) : GameObject("ExtraLife")
{
	mAngle = rand() % 360;
	mRotation = rand() % 90;
	mPosition.x = rand() / 2;
	mPosition.y = rand() / 2;
	mPosition.z = 0.0;
	mVelocity.x = 4.0 * cos(DEG2RAD*mAngle);
	mVelocity.y = 4.0 * sin(DEG2RAD*mAngle);
	mVelocity.z = 0.0;
}

// destructor
ExtraLife::~ExtraLife(void)
{
}

void ExtraLife::Render(void)
{
	glBegin(GL_LINE_LOOP);
	//set colour to white
	glColor3f(0.9, 0.9, 0.9);
	//add vertices make a square
	glVertex3f(-3, -3, 0.0);
	glVertex3f(-3, 3, 0.0);
	glVertex3f(3, 3, 0.0);
	glVertex3f(3, -3, 0.0);
	glEnd();
	//enable lighting
	glEnable(GL_LIGHTING);
}

bool ExtraLife::CollisionTest(shared_ptr<GameObject> o)
{
	if (o->GetType() == GameObjectType("Asteroid")) return false;
	if (o->GetType() == GameObjectType("Bullet")) return false;
	if (mBoundingShape.get() == NULL) return false;
	if (o->GetBoundingShape().get() == NULL) return false;
	return mBoundingShape->CollisionTest(o->GetBoundingShape());
}

void ExtraLife::OnCollision(const GameObjectList& objects)
{
	mWorld->FlagForRemoval(GetThisPtr());
}