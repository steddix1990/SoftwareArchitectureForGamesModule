// w16016982

// When initialized, the asterocks will spawn
// at various places on screen with varying speeds.
// If the asterocks come into contact with a bullet, 
// missile or the players ship they will blow up
// and spawn an explosion sprite

#pragma once

#include "gameobject.h"
#include "Sprite.h"

class Asterock : public GameObject
{
public:

	Asterock();
	virtual ~Asterock() {}

	void initialise(Vector2D iniPos);
	void update();
	void render();
	void processCollision(GameObject* object);
	void Deactivate();

	Circle2D m_aCircle;
	IShape2D& Asterock::GetShape();

private:

	PictureIndex m_asteroid;

protected:

	Vector2D m_velocity;
};