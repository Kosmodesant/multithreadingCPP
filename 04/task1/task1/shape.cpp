#define _USE_MATH_DEFINES
#include "shape.h"
#include <cmath>

Shape::Shape(int _type, int _x1, int _y1, int _z1, int _x2, int _y2, int _z2,
    int _x3, int _y3, int _z3,
    int _x4, int _y4, int _z4,
    int _x5, int _y5, int _z5,
    int _x6, int _y6, int _z6,
    int _x7, int _y7, int _z7,
    int _x8, int _y8, int _z8)
    : type(_type)
{
    x[0] = _x1; y[0] = _y1; z[0] = _z1;
    x[1] = _x2; y[1] = _y2; z[1] = _z2;
    x[2] = _x3; y[2] = _y3; z[2] = _z3;
    x[3] = _x4; y[3] = _y4; z[3] = _z4;
    x[4] = _x5; y[4] = _y5; z[4] = _z5;
    x[5] = _x6; y[5] = _y6; z[5] = _z6;
    x[6] = _x7; y[6] = _y7; z[6] = _z7;
    x[7] = _x8; y[7] = _y8; z[7] = _z8;

    calculateSquareAndVolume();
}

Shape::Shape(int type, int _x1, int _y1, double R, double H)
    : type(type), radius(R), height(H)
{
    x[0] = _x1; y[0] = _y1;

    calculateSquareAndVolume();
}

void Shape::calculateSquareAndVolume()
{
    switch (type)
    {
    case LINE:
        square = 0;
        volume = 0;
        break;
    case SQUARE:
    {
        int a = abs(x[0] - x[1]);
        int b = abs(y[0] - y[1]);
        square = a * b;
        volume = 0;
    }
    break;
    case CUBE:
    {
        int a = abs(x[0] - x[1]);
        int b = abs(y[0] - y[1]);
        int c = abs(z[0] - z[1]);
        square = 2 * a * b + 2 * a * c + 2 * b * c;
        volume = a * b * c;
    }
    break;
    case CIRCLE:
        square = M_PI * radius * radius;
        volume = 0;
        break;
    case CYLINDER:
        square = M_PI * radius * radius + 2 * M_PI * radius * height;
        volume = M_PI * radius * radius * height;
        break;
    default:
        square = 0;
        volume = 0;
        break;
    }
}
