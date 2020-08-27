#pragma once
#include "Core/System.h"
#include <fmod.hpp>

namespace nc
{
	class AudioSystem : public System
	{
	public:
		// Inherited via System
		virtual bool Startup() override;
		virtual void Shutdown() override;
		virtual void Update() override;
		

		friend class Sound;

	protected:
		FMOD::System* m_system{ nullptr };

	};
}

