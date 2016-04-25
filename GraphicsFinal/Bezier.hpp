#ifndef BEZIER
#define BEZIER
#include "Algebra.h"
#include <vector>
#include <cassert>
class BezierCalc{
    public:
        BezierCalc(const Point& control0,const Point& control1,const Point& control2,const Point& control3);
        Point getColor(double t) const;
    private:
        std::vector<Point> ps;
};
#endif//BEZIER
