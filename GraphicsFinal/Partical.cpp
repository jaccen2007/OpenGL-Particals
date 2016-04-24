//
//  Partical.cpp
//  GraphicsFinal
//
//  Created by Steven Pantin on 4/21/16.
//  Copyright © 2016 Steven Pantin. All rights reserved.
//

#include "Partical.hpp"

Partical::Partical(float x, float y, float z, float edgeLength, int tessEdge){
    origin = Point(x, y, z);
    color = Point(.3,.3,.3);
    this->edgeLength = edgeLength;
    this->tessEdge = tessEdge;
    
}

Partical::~Partical(){
    
}

void Partical::draw(){
    
    Point bl, br;
    float indexes[3][6] = {{2,2,0,0,0,0},{1,1,2,2,1,1},{0,0,1,1,2,2}};
    int norms[6][3] = {{1,0,0},{-1,0,0},{0,1,0},{0,-1,0},{0,0,1},{0,0,-1}};
    
    
    for(int i=0; i<6; i++){
        
        for (float x = 0; x < tessEdge; x++){
            glBegin(GL_TRIANGLE_STRIP);
            glNormal3f(norms[i][0], norms[i][1], norms[i][2]);
            for (float y = 0; y <= tessEdge; y++){
                bl = Point( (-1*(1/2.0) + (x / (float)tessEdge)),
                           (-1*(1/2.0) + (y / ((float)tessEdge))),
                           (1/2.0) );
                
                br = Point( (-1*(1/2.0) + ((x + 1) / (float)tessEdge)),
                           (-1*(1/2.0) + (y / ((float)tessEdge))),
                           (1/2.0) );
                
                
                bl[indexes[(i/2)][i]] *= (i%2)==0 ? 1:-1;
                br[indexes[(i/2)][i]] *= (i%2)==0 ? 1:-1;
                
                bl = Point(bl[indexes[0][i]]*edgeLength+ origin[0], bl[indexes[1][i]]*edgeLength+ origin[1], bl[indexes[2][i]]*edgeLength+ origin[2]);
                br = Point(br[indexes[0][i]]*edgeLength+ origin[0], br[indexes[1][i]]*edgeLength+ origin[1], br[indexes[2][i]]*edgeLength+ origin[2]);
                
                glColor3f(color[0], color[1], color[2]);
                //glColor3f(bl[0], bl[1], bl[2]);
                glVertex3f(bl[0], bl[1], bl[2]);
                glVertex3f(br[0], br[1], br[2]);
                
            }
            glEnd();
        }
    }
    
}


void Partical::setColor(Point p){
    this->color = p;
}

Point Partical::getColor(){
    return color;
}






