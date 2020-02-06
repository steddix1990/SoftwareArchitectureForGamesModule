// w16016982

#include "Bullet.h"
#include "LoadBMP.h"

Bullet::Bullet() : GameObject(BULLET)
{}

void Bullet::initialise(Vector2D inPos, float inAngle)
{
	LoadBMP* loader = new LoadBMP();

	m_bullet = loader->Load(L"assets/sprites/bullet.bmp");

	m_position = inPos;
	m_angle = inAngle;
	m_velocity.setBearing(m_angle, 500.0f);

	loader->destroyLoader(loader);
}

void Bullet::render()
{
	MyDrawEngine::GetInstance()->DrawAt(m_position, m_bullet, 2.5f, m_angle);
}

void Bullet::update()
{
	m_position = m_position + m_velocity * m_frameTime;

	// Wrap the screen area
	const int BORDER = 16;
	Rectangle2D screenArea = MyDrawEngine::GetInstance()->GetViewport();

	// The area of the screen
	if (m_position.XValue + BORDER < screenArea.GetTopLeft().XValue ||
		m_position.XValue - BORDER > screenArea.GetBottomRight().XValue ||
		m_position.YValue - BORDER > screenArea.GetTopLeft().YValue ||
		m_position.YValue + BORDER < screenArea.GetBottomRight().YValue)
	{
		Deactivate();
	}
}

void Bullet::processCollision(GameObject* object)
{
	if (object->GetType() == ASTEROCK || object->GetType() == BOSS || object->GetType() == MINE)
	{
		Deactivate();
	}
}

IShape2D& Bullet::GetShape()
{
	m_angledRec.SetDimensions(8, 8);
	m_angledRec.SetCentre(m_position);
	m_angledRec.SetAngle(m_angle);

	return m_angledRec;
}

void Bullet::Deactivate()
{
	m_active = false;
}