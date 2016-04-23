//
//  ParticalRound.cpp
//  GraphicsFinal
//
//  Created by Steven Pantin on 4/21/16.
//  Copyright © 2016 Steven Pantin. All rights reserved.
//

#include "ParticalRound.hpp"
#include "Object.hpp"
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>

ParticalRound::ParticalRound(float x, float y, float z, float radius, int tessEdge){
    origin = Point(x, y, z);
    color = Point(.3,.3,.3);
    this->radius = radius;
    this->tessEdge = tessEdge;
    
}

ParticalRound::~ParticalRound(){
    
}

void ParticalRound::draw(){
    
    Point tl, bl;
    for (float y = 0; y < tessEdge; y++) {
        
        float yBottom = cos(PI / tessEdge * y) * radius;
        float yTop = cos(PI / tessEdge * (y+1)) * radius;
        
        float r = sqrt((radius*radius) - (yBottom*yBottom));
        float rNext = sqrt((radius*radius) - (yTop*yTop));
        
        glBegin(GL_TRIANGLE_STRIP);
        for (int i = 0; i <= tessEdge; i++) {
            
            tl = Point( (r * cos((2 * ((double)(i + 1))*PI) / tessEdge)),
                       (yBottom),
                       (r * sin((2 * ((double)(i + 1))*PI) / tessEdge)) );
            
            bl = Point( (rNext * cos((2 * ((double)(i + 1))*PI) / tessEdge)),
                       (yTop),
                       (rNext * sin((2 * ((double)(i + 1))*PI) / tessEdge)) );
            
            glColor3f(color[0], color[1], color[2]);
            //glColor3f(tl[0], tl[1], tl[2]);
            glNormal3f(tl[0], tl[1], tl[2]);
            glVertex3f(tl[0]+origin[0], tl[1]+origin[1], tl[2]+origin[2]);
            glNormal3f(bl[0], bl[1], bl[2]);
            glVertex3f(bl[0]+origin[0], bl[1]+origin[1], bl[2]+origin[2]);
            
        }
        glEnd();
    }
    
}

void ParticalRound::setRadius(float r){
    if(r < 0) r = 0;
    this->radius = r;
}

float ParticalRound::getRadius(){
    return radius;
}

void ParticalRound::setOrigin(Point p){
    this->origin = p;
}

Point ParticalRound::getOrigin(){
    return origin;
}

void ParticalRound::setColor(Point p){
    this->color = p;
}

Point ParticalRound::getColor(){
    return color;
}
