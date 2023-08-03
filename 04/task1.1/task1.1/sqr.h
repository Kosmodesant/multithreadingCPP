#pragma once
#include "cube.h"

class Sqr : public Cube {
public:
	Sqr() {};
	Sqr(Point p1, Point p2, Point p3, Point h);

	double getSquare() override;
	double getVolume() override;
	void printInfo() override;
};
