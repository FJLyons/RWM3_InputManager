#include "stdafx.h"
#include "Player.h"


Player::Player()
{
	rect = Rect(600, 600, 20, 20);
	colour = Colour(0, 255, 0);
	velocity = Vector2f(0, 0);
	position = Vector2f(600, 600);
}

Player::~Player()
{
}

void Player::Update(float dt)
{
	if (sticks == true)
	{
		position.x += velocity.x / 100;
		position.y += velocity.y / 100;

		rect.pos.x = position.x;
		rect.pos.y = position.y;

		velocity = inputManager->GetLeftStickVectorNormal();

	}
}

void Player::Render(Renderer & r)
{
	r.drawRect(rect, colour);
}

Rect Player::getRect()
{
	return rect;
}

void Player::movePlayerUp()
{
	rect.pos.x = rect.pos.x;
	rect.pos.y = rect.pos.y - rect.size.h;
}

void Player::movePlayerLeft()
{
	rect.pos.x = rect.pos.x - rect.size.w;
	rect.pos.y = rect.pos.y;
}

void Player::movePlayerDown()
{
	rect.pos.x = rect.pos.x;
	rect.pos.y = rect.pos.y + rect.size.h;
}

void Player::movePlayerRight()
{
	rect.pos.x = rect.pos.x + rect.size.w;
	rect.pos.y = rect.pos.y;
}

void Player::changeColour()
{
	colour = Colour(rand() % 255, rand() % 255, rand() % 255);
}

void Player::resetColour()
{
	colour = Colour(0, 255, 0);
}

void Player::setSticks()
{
	sticks = true;
}

void Player::setDeadZone()
{
	inputManager->SetStickDeadZone(8000);
}