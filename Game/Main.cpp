// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "pch.h"
#include <SDL_image.h>
#include "Graphics/Texture.h"
#include "Engine.h"
#include "Objects/GameObject.h"
#include "Components/PlayerComponent.h"
#include "Core/Json.h"
#include "Objects/ObjectFactory.h"
#include "Objects/Scene.h"


nc::Engine engine;
nc::GameObject player;
nc::Scene scene;

//nc::ObjectFactory objectFactory;

int main(int, char**)
{
	//profile
	//for (size_t i = 0; i < 100; i++) { std::sqrt(rand() % 100); }
	//std::cout << engine.GetTimer().ElapsedSeconds() << std::endl;

	scene.Create(&engine);

	nc::ObjectFactory::Instance().Initialize();
	nc::ObjectFactory::Instance().Register("PlayerComponent", nc::Object::Instantiate<nc::PlayerComponent>);

	/*nc::GameObject* player = nc::ObjectFactory::Instance().Create<nc::GameObject>("GameObject");*/

	engine.Startup();
	
	rapidjson::Document document;
	nc::json::Load("Scene.txt", document);
	scene.Read(document);
	
	/*nc::Component* component = nc::ObjectFactory::Instance().Create<nc::Component>("PhysicsComponent");
	component->Create(player);
	player->AddComponent(component);

	component = nc::ObjectFactory::Instance().Create<nc::Component>("SpriteComponent");
	component->Create(player);
	nc::json::Load("sprite.txt", document);
	component->Read(document);
	player->AddComponent(component);

	component = nc::ObjectFactory::Instance().Create<nc::Component>("PlayerComponent");
	component->Create(player);
	player->AddComponent(component);*/


	//Texture
	//nc::Texture* background = engine.GetSystem<nc::ResourceManager>()->Get<nc::Texture>("background.png", engine.GetSystem<nc::Renderer>());

	
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
		scene.Update();
		

		// BEGIN
		engine.GetSystem<nc::Renderer>()->BeginFrame();

		//Draw
		//background->Draw({ 0,0 }, {1.0f,1.0f}, 0);
		scene.Draw();
		

		// END
		engine.GetSystem<nc::Renderer>()->EndFrame();
		
	}

	engine.Shutdown();
	scene.Destroy();
	return 0; 
}