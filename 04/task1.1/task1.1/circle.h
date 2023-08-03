#pragma once
#include "shape.h"

class Circle : public Shape {
public:
	Circle() {};
	Circle(Point centre, double radius);
	std::vector<Point>& getPoints();
	double getSquare() override;
	void printInfo() override;

protected:
	std::vector<Point> points{};
	double radius_{};
};
