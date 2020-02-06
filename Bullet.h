// w16016982

// The bullet class used by the spaceship
// When a new bullet is created it is initialized
// at the front of the ship with the angle that
// the ship is facing 

#pragma once

#include "gameobject.h"

class Bullet : public GameObject
{
public:

	Bullet();
	virtual ~Bullet() {}

	void initialise(Vector2D position, float angle);
	void update();
	void processCollision(GameObject* object);
	void render();
	void Deactivate();

	IShape2D& Bullet::GetShape();

	AngledRectangle2D m_angledRec;

private:

	PictureIndex m_bullet;

protected:

	Vector2D m_velocity;
};