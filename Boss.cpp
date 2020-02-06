// w16016982

#include "Boss.h"
#include "gamecode.h"

Boss::Boss() : GameObject(BOSS)
{}

void Boss::initialise(Vector2D position)
{
	m_HP = 1000;

	m_active = true;

	m_boss->loadSprite(L"assets/sprites/boss.bmp");
	m_boss->loadSprite(L"assets/sprites/boss1.bmp");
	m_boss->loadSprite(L"assets/sprites/boss2.bmp");
	m_boss->loadSprite(L"assets/sprites/boss3.bmp");
	m_boss->loadSprite(L"assets/sprites/boss4.bmp");
	m_boss->loadSprite(L"assets/sprites/boss5.bmp");

	setDirection();
}

void Boss::update()
{
	// need to work out how to shoot the player from here

	m_bossTimer = m_bossTimer - m_bossDelay * m_frameTime;
	m_plasmaTimer = m_plasmaTimer - m_plasmaDelay * m_frameTime;
	m_mineTimer = m_mineTimer - m_mineDelay * m_frameTime;

	if (m_bossTimer <= 0)
	{
		m_bossTimer = 1.0f;
		setDirection();
	}

	if (m_plasmaTimer <= 0)
	{
		m_plasmaTimer = 1.0f;
		FirePlasma();
	}

	if (m_mineTimer <= 0)
	{
		m_mineTimer = 5.0f;
		DropMine(m_position);
	}

	// Wrap the screen
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

	if (m_HP <= 0)
	{
		Deactivate();
	}

	Vector2D friction = -0.5 * m_velocity;
	m_velocity = m_velocity + friction * m_frameTime;
	m_position = m_position + m_velocity * m_frameTime;
}

void Boss::render()
{
	m_boss->animatedSprite(m_position, 6.0f, 1.0f, 1.0f);

	if (m_HP < 100)
	{
		m_boss->Deactivate();
	}
}

void Boss::setDirection()
{
	float direction = rand() % 628 / 100.0f;
	float speed = float(20.0f);
	m_position.setBearing(direction, speed);
}

void Boss::FirePlasma()
{
	// Create a new plasma round and add it to the game loop
	Plasma* pPlasma = new Plasma();

	Vector2D plasmaPos;
	float direction = rand() % 628 / 100.0f;

	plasmaPos = m_position;
	plasmaPos.setBearing(direction, 150.0f);

	pPlasma->initialise(plasmaPos, direction);
	Game::instance.om.addObject(pPlasma);

	m_bossSound->PlayPlasma();
}

void Boss::DropMine(Vector2D minePos)
{
	Mine* mine = new Mine();

	Vector2D pos;

	pos = minePos;
	pos.setBearing(m_angle, 32.0f);

	mine->initialise(pos);
	Game::instance.om.addObject(mine);

	m_bossSound->PlayMine();
}

void Boss::processCollision(GameObject* object)
{
	if (object->GetType() == BULLET)
	{
		object->m_active = false;
		m_HP = m_HP - 25;
	}

	if (object->GetType() == MISSILE)
	{
		object->m_active = false;
		m_HP = m_HP - 100;
	}
}

IShape2D& Boss::GetShape()
{
	m_angledRec.SetDimensions(256, 100);
	m_angledRec.SetCentre(m_position);
	m_angledRec.SetAngle(m_angle);

	return m_angledRec;
}

void Boss::Deactivate()
{
	m_active = false;
}