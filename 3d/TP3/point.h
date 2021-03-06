#ifndef POINT_H
#define POINT_H

#include "coord.h"
#include "vector.h"

class Point : public Coord
{
public:
    Point();
    Point(double x, double y, double z);

    Point *projectOnLine(Point *b, Point *c);
    Point *projectOnLine(Vector *u, Point *b);
    Point *projectOnPlan(Point *a, Vector *n);

};

#endif // POINT_H
