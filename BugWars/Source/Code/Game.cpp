#include "pch.h"
#include "Game.h"
#include "GameBase/Log.h"
#include "Tank.h"
#include "Bug.h"
#include "Bullet.h"

Game* g_Game;

Game::Game()
	: GameBase({ [] {return new Tank; },
				 [] {return new Bug; },
				 [] {return new Bullet; } })
{
	g_Game = this;
}

Game::~Game()
{
	for (auto& object : objects) {
		delete(object);
	}
}

void Game::OnUpdate(float dt)
{
	PIXScopedEvent(PIX_COLOR_INDEX(5), __FUNCTION__);
	for (auto& object : objects)
		if (!object->disabled)
			object->Update(dt);
}

void Game::OnRender() const
{
	for (auto& object : objects)
		if (object->visible)
			DoRender(object);
}

void Game::AddObject(GameObject* object)
{
	if (object->GetRTTI() == Bug::s_RTTI) {

		object->visible = true;
		object->disabled = false;
		Log("I'm a bug");

	}

	else if (object->GetRTTI() == Bullet::s_RTTI) {

		object->visible = true;
		object->disabled = false;
		Log("I'm a bullet");

	}

	objects.push_back(object);
}

void Game::OnBugsSpawned()
{
}
