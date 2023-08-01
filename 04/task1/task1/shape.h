#pragma once
#include <string>

class Shape
{
public:
    static const int LINE = 0;
    static const int SQUARE = 1;
    static const int CUBE = 2;
    static const int CIRCLE = 3;
    static const int CYLINDER = 4;

    Shape() = default;
    Shape(int type, int _x1, int _y1, int _z1, int _x2, int _y2, int _z2,
        int _x3 = 0, int _y3 = 0, int _z3 = 0,
        int _x4 = 0, int _y4 = 0, int _z4 = 0,
        int _x5 = 0, int _y5 = 0, int _z5 = 0,
        int _x6 = 0, int _y6 = 0, int _z6 = 0,
        int _x7 = 0, int _y7 = 0, int _z7 = 0,
        int _x8 = 0, int _y8 = 0, int _z8 = 0);
    Shape(int type, int _x1, int _y1, double R, double H);

    int getType() const { return type; }
    double getSquare() const { return square; }
    double getVolume() const { return volume; }

private:
    int type;
    int x[8] = { 0 };
    int y[8] = { 0 };
    int z[8] = { 0 };
    double radius = 0.0;
    double height = 0.0;
    double square = 0.0;
    double volume = 0.0;

    void calculateSquareAndVolume();
};
