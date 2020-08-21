#pragma once
#include "Object.h"
#include "Math/Transform.h"
#include "Engine.h"
#include <vector>

namespace nc {
	class Component; //forward Declaration

	class GameObject : public Object {
	public:
		GameObject() = default;
		GameObject(const GameObject& other);

		// Inherited via Object
		virtual bool Create(void* data = nullptr) override;
		virtual void Destroy() override;
		virtual Object* Clone() override { return new GameObject{*this}; }

		void Read(const rapidjson::Value& value) override;

		void Update();
		void Draw();

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

		friend class Component;
		friend class PhysicsComponent;

	public:
		Transform m_transform;
		Engine* m_engine{nullptr};
		std::string m_name;

	protected:
		std::vector<Component*> m_components;
	};
}
