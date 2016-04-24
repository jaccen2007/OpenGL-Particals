
#include "Object.hpp"

    Object::Object() {timeAlive=0;};
    
    Point Object::getOrigin(){
        return origin;
    }
    void Object::setOrigin(Point& p){
        origin=p;
    }
    void Object::resetTime(){
        timeAlive=0;
    }
    double Object::getTimeAlive(){
        return timeAlive;
    }
    void Object::updateTimeAlive(double time){
        if(time>timeAlive){
            timeAlive=time;
        }
    }
    Vector Object::getLuanchVector(){
        return launchVector;
    }
    void Object::setLaunchVector(const Vector& v){
        launchVector=v;
    }
    double Object::getLuanchVelocity(){
        return launchVelocity;
    }
    void Object::setLaunchVelocity(double v){
        if(timeAlive==0){
            launchVelocity=v;
        }
    }
