#include "Algebra.h"
#include "Object.hpp"
#define _e 2.71828
static const double VECTOR_TIME_DIFF= 0.0001;
class Physics{
public:
    Physics(const Vector& wind,const Vector& gravity=Vector(0,-9.8,0));
    Vector getMovementVector(Object* o);
    Point calculatePosition(Object* o);
    Vector getReflectedRay(Vector ray,Vector normal);
    void setWind(Vector newWind);//Dont normalize!!!!
    void setGravity(Vector newGravity);//Dont normalize!!!!
    static Vector getRandomVector(const Vector& seed,double degreeVariance);
private:
    Point calculatePosition(Object* o,double t);
    Vector wind;//DONT NORMALIZE THESE!!!!
    Vector gravity;//magnitude is what tells how fast to go
};
