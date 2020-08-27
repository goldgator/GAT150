#pragma once
#include "SpriteComponent.h"


namespace nc {
	class SpriteAnimationComponent : public SpriteComponent {
		virtual bool Create(void* data = nullptr) override;
		virtual void Destroy() override;
		virtual SpriteAnimationComponent* Clone() const override { return new SpriteAnimationComponent{ *this }; }

		virtual void Update() override;

		void Read(const rapidjson::Value& value);

	protected:
		int m_frame{ 0 };
		float m_frameTimer{ 0 };
		float m_frameRate{ 0 };

		int m_numX{ 0 };
		int m_numY{ 0 };
		int m_numFrames{ 0 };
		int m_fps{ 0 };
	};
}