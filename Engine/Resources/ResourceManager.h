#pragma once
#include "Core/System.h"
#include "Resource.h"
#include <string>

namespace nc {
	class ResourceManager : public System {
	public:

		// Inherited via System
		virtual bool Startup() override;

		virtual void Shutdown() override;

		virtual void Update() override;

		template<typename T>
		T* Get(const std::string& name, void* data = nullptr);

		void RemoveAll();

	protected:
		std::map<std::string, Resource*> m_resources;
	};

	template<typename T>
	inline T* ResourceManager::Get(const std::string& name, void* data)
	{
		T* resource = dynamic_cast<T*>(m_resources[name]);

		if (resource == nullptr) {
			resource = new T;
			resource->Create(name, data);

			m_resources[name] = resource;
		}

		return resource;
	}
}