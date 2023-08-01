
#include "transform.h"

Transform::Transform(const Shape& sh)
    : shape(sh)
{}

Shape Transform::shift(int m, int n, int k)
{
    int numPoints = (shape.getType() == Shape::CIRCLE || shape.getType() == Shape::CYLINDER) ? 1 : 8;

    for (int i = 0; i < numPoints; ++i)
    {
        shape.x[i] += m;
        shape.y[i] += n;
        shape.z[i] += k;
    }

    shape.calculateSquareAndVolume();
    return shape;
}

Shape Transform::scaleX(int a)
{
    int numPoints = (shape.getType() == Shape::CIRCLE || shape.getType() == Shape::CYLINDER) ? 1 : 8;

    for (int i = 0; i < numPoints; ++i)
    {
        shape.x[i] *= a;
    }

    shape.calculateSquareAndVolume();
    return shape;
}

Shape Transform::scaleY(int d)
{
    int numPoints = (shape.getType() == Shape::CIRCLE || shape.getType() == Shape::CYLINDER) ? 1 : 8;

    for (int i = 0; i < numPoints; ++i)
    {
        shape.y[i] *= d;
    }

    shape.calculateSquareAndVolume();
    return shape;
}

Shape Transform::scaleZ(int e)
{
    int numPoints = (shape.getType() == Shape::CIRCLE || shape.getType() == Shape::CYLINDER) ? 1 : 8;

    for (int i = 0; i < numPoints; ++i)
    {
        shape.z[i] *= e;
    }

    shape.calculateSquareAndVolume();
    return shape;
}

Shape Transform::scale(int s)
{
    int numPoints = (shape.getType() == Shape::CIRCLE || shape.getType() == Shape::CYLINDER) ? 1 : 8;

    for (int i = 0; i < numPoints; ++i)
    {
        shape.x[i] /= s;
        shape.y[i] /= s;
        shape.z[i] /= s;
    }

    shape.calculateSquareAndVolume();
    return shape;
}
