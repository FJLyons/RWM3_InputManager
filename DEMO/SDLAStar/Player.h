#pragma once
#include "GameObject.h"
#include "BasicTypes.h"
#include "FLInputManager.h"
#include <vector>


class Player : GameObject
{
public:
	//Player(std::vector<Tile*> path);
	Player();
	Player::~Player();

	void Update(float dt);

	void Render(Renderer& r) override;
	Rect getRect();


	void movePlayerUp();
	void movePlayerLeft();
	void movePlayerDown();
	void movePlayerRight();

	void changeColour();
	void resetColour();

	Vector2f velocity;
	Vector2f position;

	void setSticks();
	void setDeadZone();


private:

	InputManager* inputManager = InputManager::GetInstance();

	Rect rect;
	Colour colour;

	float elapsedTime = 0;

	bool sticks = false;
};
