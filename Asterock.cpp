// w16016982

#include "Asterock.h"
#include "Explosion.h"
#include "gamecode.h"
#include <stdlib.h>	    /* srand, rand */

Asterock::Asterock() : GameObject(ASTEROCK)
{}

void Asterock::initialise(Vector2D iniPos)
{
	m_active = true;

	LoadBMP* loader = new LoadBMP();
	m_asteroid = loader->Load(L"assets/sprites/rock4.bmp");
	loader->destroyLoader(loader);

	m_position = iniPos;

	float direction = rand() % 628 / 100.0f;
	float speed = float(rand() % 300 * 2);
	m_velocity.setBearing(direction, speed);
}

void Asterock::update()
{
	// Wrap the screen area
	const int BORDER = 16;
	Rectangle2D screenArea = MyDrawEngine::GetInstance()->GetViewport();

	// The left of the screen
	if (m_position.XValue + BORDER < screenArea.GetTopLeft().XValue)
	{
		m_position.XValue = screenArea.GetBottomRight().XValue + BORDER;
	}

	// The Right of the screen
	if (m_position.XValue - BORDER > screenArea.GetBottomRight().XValue)
	{
		m_position.XValue = screenArea.GetTopLeft().XValue - BORDER;
	}

	// The Top of the screen
	if (m_position.YValue - BORDER > screenArea.GetTopLeft().YValue)
	{
		m_position.YValue = screenArea.GetBottomRight().YValue - BORDER;
	}

	// The Bottom of the screen
	if (m_position.YValue + BORDER < screenArea.GetBottomRight().YValue)
	{
		m_position.YValue = screenArea.GetTopLeft().YValue + BORDER;
	}

	// Rotate the asteroid for some added animation
	m_angle -= 1.0f * m_frameTime;
	m_position = m_position + m_velocity * m_frameTime;
}

void Asterock::render()
{
	MyDrawEngine::GetInstance()->DrawAt(m_position, m_asteroid, 1.0f, m_angle);
}

void Asterock::processCollision(GameObject* object)
{
	if (object->GetType() == SHIP || object->GetType() == BULLET || object->GetType() == MISSILE)
	{
		// Create an explosion where the Asterock was
		Explosion* pExplosion = new Explosion();
		pExplosion->initialise(m_position);

		Game::instance.om.addObject(pExplosion);
		Game::instance.m_asteroids = Game::instance.m_asteroids - 1;

		object->m_active = false;
		Deactivate();
	}
}

IShape2D& Asterock::GetShape()
{
	m_aCircle.PlaceAt(Vector2D(m_position), 64);
	return m_aCircle;
}

void Asterock::Deactivate()
{
	m_active = false;
}