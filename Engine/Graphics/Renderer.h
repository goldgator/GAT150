#pragma once
#include "Core/System.h"
#include "Texture.h"
#include <SDL.h>

namespace nc {
	class Renderer : public System {
	public:

		// Inherited via System
		virtual bool Startup() override;
		virtual void Shutdown() override;
		virtual void Update() override;

		bool Create(const std::string&, int width, int height);
		void BeginFrame();
		void EndFrame();

		friend class Texture;

	protected:
		SDL_Window* m_window{ nullptr };
		SDL_Renderer* m_renderer { nullptr };
	};
}