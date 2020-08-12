// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "pch.h"
#include <SDL_image.h>
#include "Graphics/Texture.h"
#include "Engine.h"
#include "Objects/GameObject.h"
#include "Components/PhysicsComponent.h"
#include "Components/SpriteComponent.h"

nc::Engine engine;
nc::GameObject player;

int main(int, char**)
{
	//profile
	for (size_t i = 0; i < 100; i++) { std::sqrt(rand() % 100); }

	std::cout << engine.GetTimer().ElapsedSeconds() << std::endl;

	engine.Startup();
	
	player.Create(&engine);
	player.m_transform.position = { 400, 300 };
	player.m_transform.angle = 45;
	nc::Component* component = new nc::PhysicsComponent;
	player.AddComponent(component);
	component->Create();

	component = new nc::SpriteComponent;
	player.AddComponent(component);
	component->Create();


	//Texture
	nc::Texture* background = engine.GetSystem<nc::ResourceManager>()->Get<nc::Texture>("background.png", engine.GetSystem<nc::Renderer>());

	
	SDL_Event event;
	bool quit = false;
	while (!quit) {

		SDL_PollEvent(&event);
		switch (event.type) {
			case SDL_QUIT:
				quit = true;
				break;

			default:
				break;
		}

		//INPUT
		engine.Update();
		player.Update();

		if (engine.GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_ESCAPE) == nc::InputSystem::eButtonState::PRESSED)
		{
			quit = true;
		}

		// player controller
		if (engine.GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_A) == nc::InputSystem::eButtonState::HELD)
		{
			player.m_transform.angle = player.m_transform.angle - 90.0f * engine.GetTimer().DeltaTime();
		}
		if (engine.GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_D) == nc::InputSystem::eButtonState::HELD)
		{
			player.m_transform.angle = player.m_transform.angle + 90.0f * engine.GetTimer().DeltaTime();
		}
		nc::Vector2 force{ 0,0 };
		if (engine.GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_W) == nc::InputSystem::eButtonState::HELD)
		{
			force = nc::Vector2(0, -1) * 1000.0f;
		}

		//physics
		force = nc::Vector2::Rotate(force, nc::DegreesToRadians(player.m_transform.angle));
		

		// BEGIN
		engine.GetSystem<nc::Renderer>()->BeginFrame();

		//Draw
		background->Draw({ 0,0 }, {1.0f,1.0f}, 0);
		player.Draw();
		

		// END
		engine.GetSystem<nc::Renderer>()->EndFrame();
		
	}

	engine.Shutdown();
	return 0; 
}