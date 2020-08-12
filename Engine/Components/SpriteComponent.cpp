#include "pch.h"
#include "SpriteComponent.h"
#include "Graphics/Texture.h"

namespace nc {
    bool SpriteComponent::Create(void* data)
    {
        m_texture = m_owner->m_engine->GetSystem<nc::ResourceManager>()->Get<nc::Texture>("cars.png", m_owner->m_engine->GetSystem<nc::Renderer>());

        return true;
    }

    void SpriteComponent::Destroy()
    {
    }

    void SpriteComponent::Update()
    {
    }

    void SpriteComponent::Draw()
    {
        //Render sprite
        m_texture->Draw({ 0,16,64,144 }, m_owner->m_transform.position, { 1.0f,1.0f }, m_owner->m_transform.angle);
    }
}
