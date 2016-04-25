
#include "Physics.hpp"
    Physics::Physics(const Vector& wind,const Vector& gravity){
        this->wind=wind;
        this->gravity=gravity;
    }
    Vector Physics::getMovementVector(Object* o){//reflect off of bounce object's normal, then set objects launch vector to the reflection of this one
        return calculateOrigin(o)-calculateOrigin(o,(o->getTimeAlive()-VECTOR_TIME_DIFF));
    };
    Point Physics::calculateOrigin(Object* o){
        return calculateOrigin(o,o->getTimeAlive());
    }
    Vector Physics::getReflectedRay(Vector ray,Vector normal){
	    double dot_rn = dot(ray, normal);
        return (ray-(2 * dot_rn*normal));
    }
    Point Physics::calculateOrigin(Object* o,double t){
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
        double theta=atan(seed[1]/seed[0]);
        double phi=acos(seed[2]);
        double thetaAdd=rand()%int(DEG_TO_RAD(degreeVariance)*1000)/1000.0;
        phi+=sqrt(degreeVariance*degreeVariance-thetaAdd*thetaAdd);
        theta+=thetaAdd;
        return Vector(cos(theta)*sin(phi),sin(theta)*sin(phi),cos(theta));
    }

