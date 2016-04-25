//
//  Partical.hpp
//  GraphicsFinal
//
//  Created by Steven Pantin on 4/21/16.
//  Copyright © 2016 Steven Pantin. All rights reserved.
//

#ifndef Partical_hpp
#define Partical_hpp

#include <stdio.h>
#include "Object.hpp"
#include "Algebra.h"
#include "includeGL.hpp"

class Partical :public Object {
  
    constexpr static const float STANDARD_EDGE = 0.03;
    static const int MIN_TESS_EDGE = 1;
    
public:
    Partical(float x=0, float y=0, float z=0, float edgeLength=STANDARD_EDGE, int tessEdge=MIN_TESS_EDGE);
    ~Partical();
    
    void draw();
    
private:
    
    float edgeLength;
    int tessEdge;
    
};


#endif /* Partical_hpp */
