#pragma once
#include "circle.h"

class Cylinder : public Circle {
public:
	Cylinder() {};
	Cylinder(Point centre, double height, double radius);

	double getSquare() override;

	double getVolume() override;

	void printInfo() override;

protected:
	double height_{};
};
