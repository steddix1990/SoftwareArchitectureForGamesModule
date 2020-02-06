// w16016982

// The boss class, when the 10 asteroids spawned at
// the start of the game are destroyed, the boss will
// spawn near the player and start spawning mines / 
// firing plasma in random directions.

#pragma once

#include "gameobject.h"
#include "Sprite.h"
#include "Plasma.h"
#include "Mine.h"
#include "LoadBMP.h"
#include "Sound.h"

class Boss : public GameObject
{
public:

	Boss();
	virtual ~Boss() {}

	void initialise(Vector2D position);
	void render();
	void update();

	void setDirection();
	void processCollision(GameObject* object);
	void Deactivate();

	IShape2D& Boss::GetShape();

	void FirePlasma();
	void DropMine(Vector2D position);

	float m_bossTimer = 0.0f;
	float m_plasmaTimer = 0.0f;
	float m_mineTimer = 0.0f;

	const float m_bossDelay = 0.1f;
	const float m_plasmaDelay = 0.2f;
	const float m_mineDelay = 0.5f;

	AngledRectangle2D m_angledRec;

private:

	Sprite* m_boss = new Sprite();
	Sound* m_bossSound = new Sound();

protected:

	Vector2D m_velocity;
};