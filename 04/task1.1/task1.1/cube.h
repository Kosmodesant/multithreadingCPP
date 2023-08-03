#pragma once
#include "line.h"

class Cube : public Line {
public:
	Cube() {};
	Cube(Point p1, Point p2, Point p3);
	std::vector<double>& getSides();

	Point fourthVertex(Point p1, Point p2, Point p3);
	std::vector<double> CubeSides(Point p1, Point p2, Point p3);
	double getSquare() override;
	void printInfo() override;

protected:
	std::vector<double> sides{};
};
