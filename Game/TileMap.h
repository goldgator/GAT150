#pragma once
#include "Core/Json.h"
#include <vector>

namespace nc {
	class TileMap {
	public:
		void Read(const rapidjson::Value& value);
		bool Create(class Scene* scene);

	protected:
		int m_numX{ 0 };
		int m_numY{ 0 };
		Vector2 m_size;
		Vector2 m_start;
		std::vector<std::string> m_tileNames;
		std::vector<int> m_tiles;

	};
}