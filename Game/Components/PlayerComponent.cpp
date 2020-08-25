#include "pch.h"
#include "PlayerComponent.h"
#include "Components/PhysicsComponent.h"
#include "Components/RigidBodyComponent.h"


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

		// player controller
		if (m_owner->m_engine->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_A) == nc::InputSystem::eButtonState::HELD)
		{
			force.x = -200000;
			//m_owner->m_transform.angle = m_owner->m_transform.angle - 90.0f * m_owner->m_engine->GetTimer().DeltaTime();
		}
		if (m_owner->m_engine->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_D) == nc::InputSystem::eButtonState::HELD)
		{
			force.x = 200000;
			//m_owner->m_transform.angle = m_owner->m_transform.angle + 90.0f * m_owner->m_engine->GetTimer().DeltaTime();
		}

		if (m_owner->m_engine->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_SPACE) == nc::InputSystem::eButtonState::PRESSED)
		{
			force.y = -2000000;
			//m_owner->m_transform.angle = m_owner->m_transform.angle + 90.0f * m_owner->m_engine->GetTimer().DeltaTime();
		}

		//if (m_owner->m_engine->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_W) == nc::InputSystem::eButtonState::HELD)
		//{
		//	force = nc::Vector2(0, -1) * 1000.0f;
		//}
		////physics
		//force = nc::Vector2::Rotate(force, nc::DegreesToRadians(m_owner->m_transform.angle));

		RigidBodyComponent* component = m_owner->GetComponent<RigidBodyComponent>();
		if (component) {
			component->ApplyForce(force);
		}
    }
}
