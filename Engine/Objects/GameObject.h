#pragma once
#include "Object.h"
#include "Math/Transform.h"
#include "Engine.h"
#include "Scene.h"

#include <bitset>
#include <vector>

namespace nc {
	class Component; //forward Declaration

	class GameObject : public Object {
	public:
		enum eFlags { //<0,1,0,0>
			ACTIVE,
			VISIBLE,
			DESTROY,
			TRANSIENT
		};
	public:
		GameObject() = default;
		GameObject(const GameObject& other);

		// Inherited via Object
		virtual bool Create(void* data = nullptr) override;
		virtual void Destroy() override;
		virtual Object* Clone() const override { return new GameObject{*this}; }

		void Read(const rapidjson::Value& value) override;

		void Update();
		void Draw();

		void BeginContact(GameObject* other);
		void EndContact(GameObject* other);
		std::vector<GameObject*> GetContactsWithTag(const std::string& tag);

		void ReadComponents(const rapidjson::Value& value);


		template<typename T>
		T* GetComponent() {
			T* result{ nullptr };
			for (auto component : m_components) {
				result = dynamic_cast<T*>(component);
				if (result) break;
			}

			return result;
		}

		void AddComponent(Component* component);
		void RemoveComponent(Component* component);
		void RemoveAllComponents();

		void SetScene(Scene* scene) { m_scene = scene; };

		friend class Component;
		friend class PhysicsComponent;
		friend class PlayerComponent;

	public:
		std::string m_name;
		std::string m_tag;
		float m_lifetime{0};
		
		std::bitset<32> m_flags; // (int) <0...31> (0,1,0,1,0,1,1,1,0...)

		Transform m_transform;
		Engine* m_engine{nullptr};

	protected:
		std::vector<Component*> m_components;
		std::list<GameObject*> m_contacts;
		Scene* m_scene;
	};
}
