
#include "Object.hpp"

    Object::Object() {
        timeAlive=0;
        launchVector=Vector(1,1,1);
        launchVector.normalize();
        launchVelocity=5;//adjust as needed
        terminalVelocity=5;//
        origin=Point(0,0,0);
    };
    void Object::setTeminalVelocity(double vt){
        terminalVelocity=vt;
    }
    double Object::getTeminalVelocity(){
        return terminalVelocity;
    }
    
    void Object::setRadius(float r){
        if(r < 0) r = 0;
        this->radius = r;
    }

    float Object::getRadius(){
        return radius;
    }


    void Object::updateColor(double time){
        if(time>1){
            time=.999;
        }
        setColor(colorTransitionCalc->getColor(time));
    }
    void Object::setColor(Point p){
        this->color = p;
    }

    Point Object::getColor(){
        return color;
    }

    Point Object::getPosition(){
        return position;
    }
    Point Object::getLocation(){
        return position+origin;
    }
    void Object::setPosition(const Point& p){
        position=p;
    }
    Point Object::getOrigin(){
        return origin;
    }
    void Object::setOrigin(const Point& p){
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
