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
    void setOrigin(Point& p);
    void resetTime();
    double getTimeAlive();
    void updateTimeAlive(double time);
    Vector getLuanchVector();
    void setLaunchVector(const Vector& v);
    double getLuanchVelocity();
    void setLaunchVelocity(double v);
protected:
    Point origin;
    double timeAlive;//zero at start
    Vector launchVector;
    double launchVelocity;
};


#endif /* Object_hpp */
