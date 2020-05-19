#ifndef __DEMOSPACESHIP_H__
#define __DEMOSPACESHIP_H__

#include "GameUtil.h"
#include "GameObject.h"
#include "Shape.h"

class DemoSpaceship : public GameObject
{
public:
	DemoSpaceship();
	DemoSpaceship(GLVector3f p, GLVector3f v, GLVector3f a, GLfloat h, GLfloat r);
	DemoSpaceship(const DemoSpaceship& s);
	virtual ~DemoSpaceship(void);

	virtual void Update(int t);
	virtual void Render(void);

	virtual void Thrust(float t);
	virtual void Rotate(float r);
	virtual void Shoot(void);

	void SetDemoSpaceshipShape(shared_ptr<Shape> spaceship_shape) { mDemoSpaceshipShape = spaceship_shape; }
	void SetDemoThrusterShape(shared_ptr<Shape> thruster_shape) { mDemoThrusterShape = thruster_shape; }
	void SetDemoBulletShape(shared_ptr<Shape> bullet_shape) { mDemoBulletShape = bullet_shape; }

	bool CollisionTest(shared_ptr<GameObject> o);
	void OnCollision(const GameObjectList &objects);

private:
	float mDemoThrust;

	shared_ptr<Shape> mDemoSpaceshipShape;
	shared_ptr<Shape> mDemoThrusterShape;
	shared_ptr<Shape> mDemoBulletShape;
};

#endif
