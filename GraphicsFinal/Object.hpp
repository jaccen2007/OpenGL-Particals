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
#include "Bezier.hpp"

class Object {
    
public:
    Object();
    virtual ~Object() {};
    
    virtual void draw(){};
    Point getOrigin();
    void setOrigin(const Point& p);
    Point getPosition();
    void setPosition(const Point& p);
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
    Point getLocation();

    void setTeminalVelocity(double vt);
    double getTeminalVelocity();

    void updateColor(double time);
    const BezierCalc* colorTransitionCalc;
protected:
    float radius;
    Point color;

    Point origin;
    Point position;
    double timeAlive;//zero at start
    Vector launchVector;
    double launchVelocity;
    double terminalVelocity;
};


#endif /* Object_hpp */
