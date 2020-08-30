#include "pch.h"
#include "PlayerComponent.h"
#include "Components/PhysicsComponent.h"
#include "Components/RigidBodyComponent.h"
#include "Components/AudioComponent.h"
#include "Audio/Sound.h"


namespace nc {
    bool PlayerComponent::Create(void* data)
    {

		m_owner = static_cast<GameObject*>(data);
        return true;
    }

    void PlayerComponent::Destroy()
    {
    }

    void PlayerComponent::Update()
    {
		//RigidBodyComponent* bodyComp = m_owner->GetComponent<RigidBodyComponent>();
		//b2Body* body = bodyComp->GetBody();
		//Vector2 velocity = body->GetLinearVelocity();

		/*std::cout << velocity.x << ", " << velocity.y << std::endl;*/

		nc::Vector2 force{ 0,0 };

		auto contacts = m_owner->GetContactsWithTag("CircleBody");
		bool onGround = !contacts.empty();

		float angle = 90;
		GameObject* nearestPlanet = findNearestPlanet();
		if (nearestPlanet) {
			Vector2 distance = m_owner->m_transform.position - nearestPlanet->m_transform.position;
			//std::cout << distance.x << ", " << distance.y << std::endl;
			angle = distance.Angle();
			//std::cout << angle << std::endl;
			m_owner->m_transform.angle = angle + 90.0f;

			distance.Normalize();
			distance *= -180;
			force += distance;
		}

		// player controller
		if (m_owner->m_engine->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_A) == nc::InputSystem::eButtonState::HELD)
		{
			Vector2 push = Vector2::Rotate({ 160,0 }, nc::DegreesToRadians(angle - 90));

			//std::cout << push.x << ", " << push.y << std::endl;
			std::cout << push.Angle() << std::endl;

			force.x += push.x;
			force.y += push.y;
			//m_owner->m_transform.angle = m_owner->m_transform.angle - 90.0f * m_owner->m_engine->GetTimer().DeltaTime();
		}
		if (m_owner->m_engine->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_D) == nc::InputSystem::eButtonState::HELD)
		{
			Vector2 push = Vector2::Rotate({ 160,0 }, nc::DegreesToRadians(angle + 90));

			force.x += push.x;
			force.y += push.y;
			//m_owner->m_transform.angle = m_owner->m_transform.angle + 90.0f * m_owner->m_engine->GetTimer().DeltaTime();
		}

		if (m_owner->m_engine->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_SPACE) == nc::InputSystem::eButtonState::PRESSED && onGround)
		{
			Vector2 push = Vector2::Rotate({ 3500, 0 }, nc::DegreesToRadians(angle));

			std::cout << push.x << ", " << push.y << std::endl;

			force.x += push.x;
			force.y += push.y;

			AudioComponent* audioComponent = m_owner->GetComponent<AudioComponent>();
			if (audioComponent) {
				audioComponent->Play();
			}
		}


		RigidBodyComponent* component = m_owner->GetComponent<RigidBodyComponent>();
		if (component) {
			component->ApplyForce(force);
		}

		// check for coin contact
		auto coinContacts = m_owner->GetContactsWithTag("Coin");
		for (GameObject* contact : coinContacts) {
			contact->m_flags[GameObject::eFlags::DESTROY] = true;
			//Play coin sound
			Sound* sound = m_owner->m_engine->GetSystem<nc::ResourceManager>()->Get<nc::Sound>("coin.wav", m_owner->m_engine->GetSystem<nc::AudioSystem>());
			sound->Play();
		}
    }
	GameObject* PlayerComponent::findNearestPlanet()
	{
		GameObject* result{nullptr};
		float distance = 200000;
		for (GameObject* object : m_owner->m_scene->m_gameObjects) {
			if (object->m_tag == "CircleBody") {
				Vector2 difference = m_owner->m_transform.position - object->m_transform.position;
				//removes the space taken by the planet
				float radius = 96; /*radius is temporarily hardcoded*/
				float space = difference.Length() - (radius * object->m_transform.scale);
				if (space < distance) {
					distance = space;
					result = object;
				}
			}
		}

		/*if (result) {
			std::cout << result->m_transform.position.x << ", " << result->m_transform.position.y << std::endl;
		}*/

		return result;
	}
}
