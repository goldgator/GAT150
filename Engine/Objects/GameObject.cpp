#include "pch.h"
#include "GameObject.h"
#include "Components/Component.h"
#include "Components/RenderComponent.h"
#include "ObjectFactory.h"


namespace nc {
    GameObject::GameObject(const GameObject& other)
    {
        m_name = other.m_name;
        m_transform = other.m_transform;
        m_engine = other.m_engine;

        for (Component* component : other.m_components) {
            Component* clone = dynamic_cast<Component*>(component->Clone());
            clone->m_owner = this;
            AddComponent(clone);
        }
    }
    bool GameObject::Create(void* data)
    {
        m_engine = static_cast<Engine*>(data);

        return false;
    }

    void GameObject::Destroy()
    {
    }

    void GameObject::Read(const rapidjson::Value& value)
    {
        json::Get(value, "name", m_name);

        nc::json::Get(value, "position", m_transform.position);
        nc::json::Get(value, "scale", m_transform.scale);
        nc::json::Get(value, "angle", m_transform.angle);

        const rapidjson::Value& componentsValue = value["Components"];
        if (componentsValue.IsArray())
        {
            ReadComponents(componentsValue);
        }

    }

    void GameObject::Update()
    {
        for (auto component : m_components) {
            component->Update();
        }
    }

    void GameObject::Draw()
    {
        RenderComponent* component = GetComponent<RenderComponent>();
        if (component) {
            component->Draw();
        }
    }

    void GameObject::AddComponent(Component* component)
    {
        m_components.push_back(component);
    }

    void GameObject::RemoveComponent(Component* component)
    {
        auto iter = std::find(m_components.begin(), m_components.end(), component);
        if (iter != m_components.end()) {
            (*iter)->Destroy();
            delete (*iter);
        }
    }

    void GameObject::ReadComponents(const rapidjson::Value& value)
    {
        for (rapidjson::SizeType i = 0; i < value.Size(); i++)
        {
            const rapidjson::Value& componentValue = value[i];
            if (componentValue.IsObject())
            {
                std::string typeName;
                json::Get(componentValue, "type", typeName);

                Component* component = nc::ObjectFactory::Instance().Create<nc::Component>(typeName);
                    if (component)
                    {
                        component->Create(this);
                        component->Read(componentValue);
                        m_components.push_back(component);
                    }
            }
        }
    }


    void GameObject::RemoveAllComponents()
    {
        for (auto component : m_components) {
            component->Destroy();
            delete component;
        }
        m_components.clear();
    }

   
}
