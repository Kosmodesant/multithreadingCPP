#define _USE_MATH_DEFINES
#include <iostream>
#include "circle.h"

Circle::Circle(Point centre, double radius) {
	type = "Circle";
	points = { centre };
	radius_ = radius;
}

std::vector<Point>& Circle::getPoints() {
	return points;
}

double Circle::getSquare() {
	return M_PI * pow(radius_, 2);
}

void Circle::printInfo() {
	std::cout << getType() << " centre: " << "{" << points[0].x << ", " << points[0].y << "} " << std::endl;
	std::cout << "radius = " << radius_ << " square = " << getSquare() << std::endl;
}
