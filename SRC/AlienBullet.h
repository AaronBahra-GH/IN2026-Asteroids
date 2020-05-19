#ifndef __ALIENBULLET_H__
#define __ALIENBULLET_H__

#include "GameUtil.h"
#include "GameObject.h"

class AlienBullet : public GameObject
{
public:
	AlienBullet();
	AlienBullet(GLVector3f p, GLVector3f v, GLVector3f a, GLfloat h, GLfloat r, int ttl);
	AlienBullet(const AlienBullet& b);
	virtual ~AlienBullet(void);

	virtual void Update(int t);

	void SetTimeToLive(int ttl) { mTimeToLive = ttl; }
	int GetTimeToLive(void) { return mTimeToLive; }

	bool CollisionTest(shared_ptr<GameObject> o);
	void OnCollision(const GameObjectList& objects);

protected:
	int mTimeToLive;
};

#endif
