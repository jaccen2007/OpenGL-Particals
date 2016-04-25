//
//  Object.hpp
//  GraphicsFinal
//
//  Created by Steven Pantin on 4/21/16.
//  Copyright © 2016 Steven Pantin. All rights reserved.
//

#ifndef Object_hpp
#define Object_hpp

#include <stdio.h>
#include "Algebra.h"

class Object {
    
public:
    Object();
    virtual ~Object() {};
    
    virtual void draw(){};
    Point getOrigin();
    void setOrigin(const Point& p);
    void resetTime();
    double getTimeAlive();
    void updateTimeAlive(double timeToAdd);
    Vector getLuanchVector();
    void setLaunchVector(const Vector& v);
    double getLuanchVelocity();
    void setLaunchVelocity(double v);

    void setColor(Point p);
    Point getColor();
    void setRadius(float r);
    float getRadius();

    void setTeminalVelocity(double vt);
    double getTeminalVelocity();
protected:
    float radius;
    Point color;

    Point origin;
    double timeAlive;//zero at start
    Vector launchVector;
    double launchVelocity;
    double terminalVelocity;
};


#endif /* Object_hpp */
