// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "pch.h"
#include <SDL_image.h>
#include "Graphics/Texture.h"
#include "Engine.h"
#include "Objects/GameObject.h"
#include "Components/PhysicsComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/PlayerComponent.h"
#include "Core/Json.h"
#include "Core/Factory.h"

nc::Engine engine;
nc::GameObject player;
nc::Factory<nc::Object, std::string> objectFactory;

int main(int, char**)
{
	//profile
	//for (size_t i = 0; i < 100; i++) { std::sqrt(rand() % 100); }
	//std::cout << engine.GetTimer().ElapsedSeconds() << std::endl;

	objectFactory.Register("GameObject", nc::Object::Instantiate<nc::GameObject>);
	objectFactory.Register("PhysicsComponent", nc::Object::Instantiate<nc::PhysicsComponent>);

	nc::GameObject* player = objectFactory.Create<nc::GameObject>("GameObject");

	engine.Startup();
	
	rapidjson::Document document;
	player->Create(&engine);
	nc::json::Load("player.txt", document);
	player->Read(document);
	//player.m_transform.position = { 400, 300 };
	//player.m_transform.angle = 45;
	nc::Component* component = objectFactory.Create<nc::Component>("PhysicsComponent");
	player->AddComponent(component);
	component->Create();

	component = new nc::SpriteComponent;
	player->AddComponent(component);
	nc::json::Load("sprite.txt", document);
	component->Read(document);
	component->Create();

	component = new nc::PlayerComponent;
	player->AddComponent(component);
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
		player->Update();

		

		// BEGIN
		engine.GetSystem<nc::Renderer>()->BeginFrame();

		//Draw
		background->Draw({ 0,0 }, {1.0f,1.0f}, 0);
		player->Draw();
		

		// END
		engine.GetSystem<nc::Renderer>()->EndFrame();
		
	}

	engine.Shutdown();
	return 0; 
}