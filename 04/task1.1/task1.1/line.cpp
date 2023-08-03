#include <iostream>
#include "line.h"

Line::Line(Point p1, Point p2) {
	type = "Line";
	points = { p1, p2 };
}

std::vector<Point>& Line::getPoints() {
	return points;
}

double Line::lengthOfSegment(Point p1, Point p2) {
	int a = abs(p1.x - p2.x);
	int b = abs(p1.y - p2.y);
	int c = abs(p1.z - p2.z);
	return sqrt(pow(a, 2) + pow(b, 2) + pow(c, 2));
}

void Line::printInfo() {
	std::cout << getType() << " points: " << std::endl;
	for (auto& point : this->points) {
		std::cout << "{" << point.x << ", " << point.y << "} ";
	}
	std::cout << std::endl;
}