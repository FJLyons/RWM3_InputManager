#include "stdafx.h"

#include <iostream>
using namespace std;
#include <chrono>
#include <thread>

#include "LTimer.h"
#include "Game.h"

const int SCREEN_FPS = 1000000;
const int SCREEN_TICKS_PER_FRAME = 1 / SCREEN_FPS;

Game::Game()
{
	quit = false;
}

Game::~Game()
{
}

bool Game::init(Renderer rend) {	
	// Set Window Size
	Size2D winSize(2000, 2000);
	renderer = rend;

	// Time
	lastTime = LTimer::gameTime();

	// Player
	player = new Player();
	
	// Events
	Event testEvent = Event::ESCAPE;
	Command* test = new SpaceCommand(std::bind(&Game::progressTest, this), Press);//////////////////////////////////////////
	inputManager->AddKey(testEvent, test, this);


	Command* one = new SpaceCommand(std::bind(&Game::keyBindOne, this), Press);
	inputManager->AddKey(Event::NUM_1, one, this);

	Command* two = new SpaceCommand(std::bind(&Game::keyBindTwo, this), Press);
	inputManager->AddKey(Event::NUM_2, two, this);

	Command* three = new SpaceCommand(std::bind(&Game::keyBindThree, this), Press);
	inputManager->AddKey(Event::NUM_3, three, this);

	// Bools
	quit = false;
	progress = false;

	return true;
}

void Game::update()
{
	unsigned int currentTime = LTimer::gameTime();//millis since game started
	float deltaTime = (currentTime - lastTime) / 1000.0;//time since last update

	//save the curent time for next frame
	lastTime = currentTime;

	player->Update(deltaTime);
}

void Game::render()
{
	renderer.clear(Colour(0,0,0));// prepare for new frame

	player->Render(renderer);

	renderer.present();// display the new frame (swap buffers)
}

void Game::loop()
{
	LTimer capTimer; // cap framerate

	while (!quit) 
	{ 
		//game loop
		capTimer.start();

		inputManager->ProcessInput();////////////////////////////////////////////////////////////////////////////////////////////

		update();
		render();

		int frameTicks = capTimer.getTicks();//time since start of frame
		if (frameTicks < SCREEN_TICKS_PER_FRAME)
		{
			//Wait remaining time before going to next frame
			SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
		}

		if (progress == true)
		{
			break;
		}
	}
}


// Event manager
void Game::onEvent(EventListener::Event evt)
{
	switch (evt)
	{
	}
}

// Close app
void Game::destroy()
{
	renderer.destroy();
	exit(0);
}

void Game::progressTest()
{
	progress = true;
}

void Game::keyBindOne()
{
	Command* w = new SpaceCommand(std::bind(&Player::movePlayerUp, player), Press);
	Command* a = new SpaceCommand(std::bind(&Player::movePlayerLeft, player), Press);
	Command* s = new SpaceCommand(std::bind(&Player::movePlayerDown, player), Press);
	Command* d = new SpaceCommand(std::bind(&Player::movePlayerRight, player), Press);


	Command* wdp = new SpaceCommand(std::bind(&Player::movePlayerUp, player), Hold);
	Command* adp = new SpaceCommand(std::bind(&Player::movePlayerLeft, player), Hold);
	Command* sdp = new SpaceCommand(std::bind(&Player::movePlayerDown, player), Hold);
	Command* ddp = new SpaceCommand(std::bind(&Player::movePlayerRight, player), Hold);

	Command* left = new SpaceCommand(std::bind(&Player::changeColour, player), Press);

	inputManager->AddKey(Event::w, w, this);
	inputManager->AddKey(Event::a, a, this);
	inputManager->AddKey(Event::s, s, this);
	inputManager->AddKey(Event::d, d, this);

	inputManager->AddKey(Event::BUTTON_DPAD_UP, wdp, this);
	inputManager->AddKey(Event::BUTTON_DPAD_LEFT, adp, this);
	inputManager->AddKey(Event::BUTTON_DPAD_DOWN, sdp, this);
	inputManager->AddKey(Event::BUTTON_DPAD_RIGHT, ddp, this);

	inputManager->AddKey(Event::MOUSE_LEFT, left, this);
}

void Game::keyBindTwo()
{
	Command* w = new SpaceCommand(std::bind(&Player::movePlayerUp, player), Release);
	Command* a = new SpaceCommand(std::bind(&Player::movePlayerLeft, player), Release);
	Command* s = new SpaceCommand(std::bind(&Player::movePlayerDown, player), Release);
	Command* d = new SpaceCommand(std::bind(&Player::movePlayerRight, player), Release);

	Command* right = new SpaceCommand(std::bind(&Player::resetColour, player), Press);

	Command* wheelu = new SpaceCommand(std::bind(&Player::movePlayerUp, player), Press);
	Command* wheeld = new SpaceCommand(std::bind(&Player::movePlayerDown, player), Press);

	inputManager->AddKey(Event::ARROW_UP, w, this);
	inputManager->AddKey(Event::ARROW_LEFT, a, this);
	inputManager->AddKey(Event::ARROW_DOWN, s, this);
	inputManager->AddKey(Event::ARROW_RIGHT, d, this);

	inputManager->AddKey(Event::MOUSE_RIGHT, right, this);

	inputManager->AddKey(Event::MOUSE_WHEEL_UP, wheelu, this);
	inputManager->AddKey(Event::MOUSE_WHEEL_DOWN, wheeld, this);
}

void Game::keyBindThree()
{
	Command* left = new SpaceCommand(std::bind(&Player::setSticks, player), Release);
	Command* dead = new SpaceCommand(std::bind(&Player::setDeadZone, player), Release);

	inputManager->AddKey(Event::v, left, this);
	inputManager->AddKey(Event::b, dead, this);
}