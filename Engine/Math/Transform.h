#pragma once
#include "Vector2.h"
#include <fstream>
#include "MathExt.h"
#include "Matrix33.h"

namespace nc {
	class Transform {
	public:
		Matrix33 matrix;

		Transform() : scale{ 0.0f }, angle{ 0.0f }, position{ Vector2(0.0f,0.0f) } {};
		Transform(float scale, float angle, Vector2 position) : scale{ scale }, angle{ angle }, position{ position } {};

		void Set(float scale, float angle, Vector2 position) { scale = scale; angle = angle; this->position = position; };

		friend std::istream& operator >> (std::istream& stream, Transform& t) { // stream >> v

			stream >> t.scale;
			stream >> t.angle;
			stream >> t.position;

			return stream;

		};

		void Update() {
			Matrix33 mxs;
			mxs.Scale(scale);
			Matrix33 mxr;
			mxr.Rotate(angle);
			Matrix33 mxt;
			mxt.Translate(position);

			matrix = mxs * mxr * mxt;
		}

		bool Load(const std::string& filename) {
			bool success = false;

			std::ifstream stream(filename);
			if (stream.is_open()) {
				success = true;

				//scale S
				//angle A
				//position {X,Y}
				//Example
				//3.0
				//0.0
				//{300.0,200.0}

				stream >> scale;
				stream >> angle;
				stream >> position;

				
			}

			return success;
		}

		float GetScale() {return scale;}
		void SetScale(float scale) { scale = scale; }

		float GetAngle() { return angle; }
		void SetAngle(float angle) {
			angle = fmod(angle, TWO_PI);
			angle = angle;
		}

		Vector2 GetPosition() { return position; }
		void SetPosition(Vector2 position) { this->position = position; }

		void RandomizePos() {
			position.x = random(0, 800);
			position.y = random(0,600);
		}

	public:
		float scale;
		float angle;
		Vector2 position;
		
	};

}