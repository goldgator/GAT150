#pragma once

#include "Components/Component.h"
#include "Objects/Scene.h"

namespace nc {
	class PlayerComponent : public Component {
	public:
		// Inherited via Component
		virtual bool Create(void* data = nullptr) override;
		virtual void Destroy() override;
		virtual Object* Clone() const override { return new PlayerComponent{ *this }; }

		virtual void Update() override;

		GameObject* findNearestPlanet();

	protected:
		Scene* m_scene;

	};
}