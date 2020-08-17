#include "pch.h"
#include "SpriteComponent.h"
#include "Graphics/Texture.h"

namespace nc {
    bool SpriteComponent::Create(void* data)
    {
        m_texture = m_owner->m_engine->GetSystem<nc::ResourceManager>()->Get<nc::Texture>(m_textureName, m_owner->m_engine->GetSystem<nc::Renderer>());

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
        //{ 0,16,64,144 }
        m_texture->Draw(m_rect, m_owner->m_transform.position, Vector2{ 1.0f,1.0f } * m_owner->m_transform.scale, m_owner->m_transform.angle);
    }
    void SpriteComponent::Read(const rapidjson::Value& value)
    {
        nc::json::Get(value, "texture", m_textureName);
        nc::json::Get(value, "rect", m_rect);
    }
}
