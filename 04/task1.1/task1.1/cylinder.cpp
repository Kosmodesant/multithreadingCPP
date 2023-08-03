#define _USE_MATH_DEFINES
#include <iostream>
#include "cylinder.h"

Cylinder::Cylinder(Point centre, double height, double radius) {
	type = "Cylinder";
	Point centre1 = { centre.x, centre.y, centre.z + height };
	points = { centre, centre1 };
	radius_ = height;
	height_ = radius;
}

double Cylinder::getSquare() {
	return (2 * M_PI * radius_ * height_ + 2 * Circle::getSquare());
}

double Cylinder::getVolume() {
	return (Circle::getSquare() * height_);
}

void Cylinder::printInfo() {
	std::cout << getType() << " centre: " << "{" << points[0].x << ", " << points[0].y << ", "
		<< points[0].z << "} " << "{" << points[1].x << ", " << points[1].y << ", "
		<< points[1].z << "} " << std::endl;
	std::cout << "radius = " << radius_ << " square = " << getSquare()
		<< " height = " << height_ << " volume = " << getVolume() << std::endl;
}
