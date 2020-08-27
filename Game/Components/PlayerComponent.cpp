#include "pch.h"
#include "PlayerComponent.h"
#include "Components/PhysicsComponent.h"
#include "Components/RigidBodyComponent.h"
#include "Components/AudioComponent.h"


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
		nc::Vector2 force{ 0,0 };
		auto contacts = m_owner->GetContactsWithTag("Floor");
		bool onGround = !contacts.empty();

		// player controller
		if (m_owner->m_engine->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_A) == nc::InputSystem::eButtonState::HELD)
		{
			force.x = -80;
			//m_owner->m_transform.angle = m_owner->m_transform.angle - 90.0f * m_owner->m_engine->GetTimer().DeltaTime();
		}
		if (m_owner->m_engine->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_D) == nc::InputSystem::eButtonState::HELD)
		{
			force.x = 80;
			//m_owner->m_transform.angle = m_owner->m_transform.angle + 90.0f * m_owner->m_engine->GetTimer().DeltaTime();
		}

		if (m_owner->m_engine->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_SPACE) == nc::InputSystem::eButtonState::PRESSED && onGround)
		{
			force.y = -2000;
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
		}
    }
}
