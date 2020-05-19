#ifndef __ALIENSPACESHIP_H__
#define __ALIENSPACESHIP_H__

#include "GameUtil.h"
#include "GameObject.h"
#include "Shape.h"

class AlienSpaceship : public GameObject
{
public:
	AlienSpaceship();
	AlienSpaceship(GLVector3f p, GLVector3f v, GLVector3f a, GLfloat h, GLfloat r);
	AlienSpaceship(const AlienSpaceship& s);
	virtual ~AlienSpaceship(void);

	virtual void Update(int t);
	virtual void Render(void);

	virtual void Thrust(float t);
	virtual void Rotate(float r);
	virtual void Shoot(void);

	void SetAlienSpaceshipShape(shared_ptr<Shape> spaceship_shape) { mAlienSpaceshipShape = spaceship_shape; }
	void SetAlienThrusterShape(shared_ptr<Shape> thruster_shape) { mAlienThrusterShape = thruster_shape; }
	void SetAlienBulletShape(shared_ptr<Shape> bullet_shape) { mAlienBulletShape = bullet_shape; }

	bool CollisionTest(shared_ptr<GameObject> o);
	void OnCollision(const GameObjectList &objects);

private:
	float mAlienThrust;

	shared_ptr<Shape> mAlienSpaceshipShape;
	shared_ptr<Shape> mAlienThrusterShape;
	shared_ptr<Shape> mAlienBulletShape;
};

#endif
