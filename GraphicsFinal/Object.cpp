
#include "Object.hpp"

    Object::Object() {
        timeAlive=0;
        launchVector=Vector(1,1,1);
        launchVector.normalize();
        launchVelocity=5;//adjust as needed
    };
    
    void Object::setRadius(float r){
        if(r < 0) r = 0;
        this->radius = r;
    }

    float Object::getRadius(){
        return radius;
    }


    void Object::setColor(Point p){
        this->color = p;
    }

    Point Object::getColor(){
        return color;
    }

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
        if(time>0){
            timeAlive+=time;
        }
    }
    Vector Object::getLuanchVector(){
        return launchVector;
    }
    void Object::setLaunchVector(const Vector& v){
        launchVector=v;
        launchVector.normalize();
    }
    double Object::getLuanchVelocity(){
        return launchVelocity;
    }
    void Object::setLaunchVelocity(double v){
        if(timeAlive==0){
            launchVelocity=v;
        }
    }
