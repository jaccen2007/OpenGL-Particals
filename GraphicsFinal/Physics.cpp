
#include "Physics.hpp"
    Physics::Physics(const Vector& wind,const Vector& gravity){
        this->wind=wind;
        this->gravity=gravity;
    }
    Vector Physics::getMovementVector(Object* o){//reflect off of bounce object's normal, then set objects launch vector to the reflection of this one
        double timeAlive=o->getTimeAlive();
        Point position=calculatePosition(o);
        Point point2=calculatePosition(o,timeAlive+.0001);
        Vector toReturn=point2-position;
        return toReturn;
    };
    Point Physics::calculatePosition(Object* o){
        return calculatePosition(o,o->getTimeAlive());
    }
    Vector Physics::getReflectedRay(Vector ray,Vector normal){
	    double dot_rn = dot(ray, normal);
        //GaDB 2
        Vector toReturn=((2 * dot_rn*normal)-ray);
        return toReturn;
    }
    Point Physics::calculatePosition(Object* o,double t){
        Point toReturn;
        double t2=t*t;
        for(int i=0;i<3;i++){
            //*
            toReturn[i]=o->getLuanchVector()[i]*o->getLuanchVelocity()*t+
                .5*gravity[i]*t2+
                .5*wind[i]*t2;
            /*/
            double eToTheTerminalGrav=pow(_e,(gravity[i]*t)/o->getTeminalVelocity());
            toReturn[i]=((((o->getTeminalVelocity()/gravity[i])*
            (o->getLuanchVector()[i]+o->getTeminalVelocity()))*
            (1-eToTheTerminalGrav))-
            ((o->getTeminalVelocity()*t)))+
                .5*wind[i]*t2;
            //*/
        }
        return toReturn;
    }
    void Physics::setWind(Vector newWind){
        this->wind=newWind;
    }
    void Physics::setGravity(Vector newGravity){
        this->gravity=newGravity;
    }
    Vector Physics::getRandomVector(const Vector& seed,double degreeVariance){
        double r=tan(DEG_TO_RAD(degreeVariance));
        double theta=DEG_TO_RAD(rand()%360);
        double phi=DEG_TO_RAD(rand()%360);
        return Vector(r*cos(theta)*sin(phi)+seed[0],r*sin(theta)*sin(phi)+seed[1],r*cos(theta)+seed[2]);
    }

