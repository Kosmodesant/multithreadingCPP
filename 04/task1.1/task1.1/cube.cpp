#include <iostream>
#include "cube.h"

Cube::Cube(Point p1, Point p2, Point p3) {
	type = "Cube";
	Point p4 = fourthVertex(p1, p2, p3);
	points = { p1, p2, p3, p4 };
	sides = CubeSides(p1, p2, p3);
}

Point Cube::fourthVertex(Point p1, Point p2, Point p3) {
	Point p4{};
	if ((p2.x - p1.x) * (p3.x - p1.x) + (p2.y - p1.y) * (p3.y - p1.y) == 0) {
		p4.x = p1.x + (p2.x - p1.x) + (p3.x - p1.x);
		p4.y = p1.y + (p2.y - p1.y) + (p3.y - p1.y);
		p4.z = p1.z + (p2.z - p1.z) + (p3.z - p1.z);
	}
	else if ((p1.x - p2.x) * (p3.x - p2.x) + (p1.y - p2.y) * (p3.y - p2.y) == 0) {
		p4.x = p2.x + (p1.x - p2.x) + (p3.x - p2.x);
		p4.y = p2.y + (p1.y - p2.y) + (p3.y - p2.y);
		p4.z = p2.z + (p1.z - p2.z) + (p3.z - p2.z);
	}
	else if ((p1.x - p3.x) * (p2.x - p3.x) + (p1.y - p3.y) * (p2.y - p3.y) == 0) {
		p4.x = p3.x + (p1.x - p3.x) + (p2.x - p3.x);
		p4.y = p3.y + (p1.y - p3.y) + (p2.y - p3.y);
		p4.z = p3.z + (p1.z - p3.z) + (p2.z - p3.z);
	}
	else {
		std::cout << "These points cannot be the vertices of a Cube.\n";
	}
	return p4;
}

std::vector<double> Cube::CubeSides(Point p1, Point p2, Point p3) {
	double sideA{};
	double sideB{};
	double a = lengthOfSegment(p1, p2);
	double b = lengthOfSegment(p1, p3);
	double c = lengthOfSegment(p2, p3);
	if (a > b && a > c) {
		sideA = b;
		sideB = c;
	}
	else if (b > a && b > c) {
		sideA = a;
		sideB = c;
	}
	else if (c > a && c > b) {
		sideA = a;
		sideB = b;
	}
	return { sideA, sideB };
}

std::vector<double>& Cube::getSides() {
	return sides;
}

double Cube::getSquare() {
	return sides[0] * sides[1];
}

void Cube::printInfo() {
	std::cout << getType() << " points: " << std::endl;
	for (auto& point : this->points) {
		std::cout << "{" << point.x << ", " << point.y << "} ";
	}
	std::cout << std::endl << "side a = " << sides[0] << " side b = " << sides[1];
	std::cout << std::endl << getType() << " square = " << this->getSquare() << std::endl;
}