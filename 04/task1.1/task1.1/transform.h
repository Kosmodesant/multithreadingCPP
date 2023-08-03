#pragma once
#include"shape.h"

template <class T>
class Transform {
public:
	Transform() {};
	Transform(T& obj) {
		Object = obj;
	}

	T shift(int shiftX, int shiftY, int shiftZ) {
		for (auto& point : Object.getPoints()) {
			point.x += shiftX;
			point.y += shiftY;
			point.z += shiftZ;
		}
		return Object;
	}

	T scaleX(int scaleX) {
		for (auto& point : Object.getPoints()) {
			point.x *= scaleX;
		}
		return Object;
	}

	T scaleY(int scaleY) {
		for (auto& point : Object.getPoints()) {
			point.y *= scaleY;
		}
		return Object;
	}

	T scaleZ(int scaleZ) {
		for (auto& point : Object.getPoints()) {
			point.z *= scaleZ;
		}
		return Object;
	}

	T scale(int scale) {
		for (auto& point : Object.getPoints()) {
			point.x /= scale;
			point.y /= scale;
			point.z /= scale;
		}
		return Object;
	}

private:
	T Object{};
};

