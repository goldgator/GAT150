#pragma once
#include <SDL.h>
#include <string>
#include "Math/Vector2.h"

namespace nc {
	class Texture {
		public:
			bool Create(const std::string& name, SDL_Renderer* renderer);
			void Destroy();

			void Draw(const Vector2& position, const Vector2& scale, float angle);
			Vector2 GetSize();

	protected:
		SDL_Texture* m_texture{ nullptr };
		SDL_Renderer* m_renderer{ nullptr };
	};
}