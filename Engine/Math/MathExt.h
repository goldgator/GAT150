#pragma once


namespace nc {
	const float PI = 3.1415f;
	const float TWO_PI = PI * 2;
	//const float RAND_MAX = 10;

	
	inline int random(int min, int max) {
		int diff = max - min;
		return ((rand() % diff) + min);
	}

	template<typename T>
	inline T clamp(T value, T min, T max) {
		if (value > max) value = max;
		if (value < min) value = min;

		return value;
	}

	template<>
	inline nc::Vector2 clamp<nc::Vector2>(nc::Vector2 v, nc::Vector2 min, nc::Vector2 max)
	{
		v.x = clamp(v.x, min.x, max.x);
		v.y = clamp(v.y, min.y, max.y);

		return v;

	}

	inline float DegreesToRadians(float degree) {
		return (degree / 180) * PI;
	}

}