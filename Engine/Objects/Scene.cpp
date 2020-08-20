#include "pch.h"
#include "Scene.h"
#include "GameObject.h"
#include "Core/Json.h"
#include "ObjectFactory.h"

namespace nc {
    bool Scene::Create(void* data)
    {
        m_engine = static_cast<Engine*>(data);
        return true;
    }

    void Scene::Destroy()
    {
        RemoveAllGameObjects();
    }

    void Scene::Read(const rapidjson::Value& value)
    {
        const rapidjson::Value& objectsValue = value["GameObjects"];
        if (objectsValue.IsArray())
        {
            ReadGameObjects(objectsValue);
        }

    }

    void Scene::ReadGameObjects(const rapidjson::Value& value)
    {
        for (rapidjson::SizeType i = 0; i < value.Size(); i++)
        {
            const rapidjson::Value& objectValue = value[i];
            if (objectValue.IsObject())
            {
                std::string typeName;
                json::Get(objectValue, "type", typeName);
                nc::GameObject* gameObject = ObjectFactory::Instance().Create<nc::GameObject>(typeName);

                if (gameObject)
                {
                    gameObject->Create(m_engine);
                    gameObject->Read(objectValue);

                    AddGameObject(gameObject);
                }
            }
        }
    }

    void Scene::Update()
    {
        for (auto obj : m_gameObjects) {
            obj->Update();
        }
    }

    void Scene::Draw()
    {
        for (auto obj : m_gameObjects) {
            obj->Draw();
        }
    }

    GameObject* Scene::Find(const std::string& name)
    {
        for (auto gameObject : m_gameObjects)
		{
            if (gameObject->m_name == name)
			{
				return gameObject;
			}
		}

		return nullptr;

    }

    void Scene::AddGameObject(GameObject* gameObject)
    {
        m_gameObjects.push_back(gameObject);
    }

    void Scene::RemoveGameObject(GameObject* gameObject)
    {
        auto iter = std::find(m_gameObjects.begin(), m_gameObjects.end(), gameObject);
        if (iter != m_gameObjects.end())
        {
            if ((*iter) == gameObject) {
                // destroy (*iter)->
                (*iter)->Destroy();
                // delete 
                delete (*iter);
                // erase iter from m_gameObjects
                m_gameObjects.erase(iter);
            }
        }

    }

    void Scene::RemoveAllGameObjects()
    {
        for (GameObject* gameObject : m_gameObjects)
        {
            gameObject->Destroy();
            delete gameObject;
        }

        m_gameObjects.clear();
    }
}
