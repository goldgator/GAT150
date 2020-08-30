#pragma once
#include "box2d/box2d.h"
#include <cmath>
#include <iostream>
#include <algorithm>
#include <string>


using std::string;

namespace nc {
	class Vector2 {
	public:
		float x, y;

		Vector2() : x{ 0 }, y{ 0 } {};
		Vector2(float x, float y) : x{ x }, y{ y } {};
		Vector2(int x, int y) : x{ static_cast<float>(x) }, y{ static_cast<float>(y) } {}
		Vector2(const b2Vec2& v) : x{ v.x }, y{ v.y } {}

		float& operator [] (size_t index) { return (&x)[index]; };
		const float& operator [] (size_t index) const { return (&x)[index]; };

		inline void Set(float x, float y) { this->x = x; this->y = y; };

		friend std::ostream& operator << (std::ostream& stream, Vector2& v) {
			stream << v.x << " " << v.y;
			return stream;
		}

		Vector2 operator + (const Vector2& v) const { return Vector2(x + v.x, y + v.y); };
		Vector2 operator - (const Vector2& v) const { return Vector2(x - v.x, y - v.y); };
		Vector2 operator * (const Vector2& v) const { return Vector2(x * v.x, y * v.y); };
		Vector2 operator / (const Vector2& v) const { return Vector2(x / v.x, y / v.y); };

		Vector2 operator + (float s) const { return Vector2(x + s, y + s); };
		Vector2 operator - (float s) const { return Vector2(x - s, y - s); };
		Vector2 operator * (float s) const { return Vector2(x * s, y * s); };
		Vector2 operator / (float s) const { return Vector2(x / s, y / s); };

		Vector2& operator += (const Vector2& v) { x += v.x; y += v.y; return *this; };
		Vector2& operator -= (const Vector2& v) { x -= v.x; y -= v.y; return *this; };
		Vector2& operator *= (const Vector2& v) { x *= v.x; y *= v.y; return *this; };
		Vector2& operator /= (const Vector2& v) { x /= v.x; y /= v.y; return *this; };

		Vector2& operator += (float s) { x += s; y += s; return *this; };
		Vector2& operator -= (float s) { x -= s; y -= s; return *this; };
		Vector2& operator *= (float s) { x *= s; y *= s; return *this; };
		Vector2& operator /= (float s) { x /= s; y /= s; return *this; };

		Vector2 operator - () const { return Vector2{ -x, -y }; };

		//Conversion from Vector2 to b2Vec2
		operator b2Vec2() const { return b2Vec2{ x,y }; };

		friend std::istream& operator >> (std::istream& stream, Vector2& v) { // stream >> v
			string line;
			stream >> line;
			if (line.empty()) return stream;

			//Format {X,Y}
			string strip = line.substr(line.find("{") + 1, line.find("}")-1);
			std::replace(strip.begin(),strip.end() ,',', ' ');
			size_t sz;
			float vx = stof(strip, &sz);
			float vy = stof(strip.substr(sz));

			v.x = vx;
			v.y = vy;

			return stream;

		}; 

		inline float Length() const {
			return sqrt((x * x) + (y * y));
		}

		inline float LengthSqr() const {
			return (x * x) + (y * y);
		}
		static float Distance(const Vector2& v1, const Vector2& v2) {
			Vector2 v = v1 - v2;
			return v.Length();
		}

		inline Vector2 Normalized() {
			float length = Length();
			Vector2 n = (length == 0.0f) ? Vector2{ 0.0f, 0.0f } : *this / length;

			return n;
		}

		inline float Angle() {
			float length = Length();
			Vector2 n = (length == 0.0f) ? Vector2{ 0.0f, 0.0f } : *this / length;
			float degrees = (atan2(n.y, n.x) * 180) / 3.1415f;

			return degrees;
		}

		inline void Normalize() {
			float length = Length();
			if (length == 0.0f) {
				x = y = 0.0f;
				*this = Vector2{ 0.0f, 0.0f };
			}
			else {
				*this /= length;
			}
		}

		inline static Vector2 Rotate(const Vector2& v, float radians) {
			float x = v.x * cos(radians) - v.y * sin(radians);
			float y = v.x * sin(radians) + v.y * cos(radians);

			return { x,y };
		}
	};
}