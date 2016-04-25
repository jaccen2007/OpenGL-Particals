//
//  ParticalRound.hpp
//  GraphicsFinal
//
//  Created by Steven Pantin on 4/21/16.
//  Copyright © 2016 Steven Pantin. All rights reserved.
//

#ifndef ParticalRound_hpp
#define ParticalRound_hpp

#include <stdio.h>
#include "Object.hpp"
#include "Algebra.h"
#include "includeGL.hpp"

class ParticalRound :public Object {
    
    constexpr static const float STANDARD_RADIUS = 0.03;
    static const int MIN_TESS_EDGE = 5;
    
public:
    ParticalRound(float x=0, float y=0, float z=0, float radius=STANDARD_RADIUS, int tessEdge=MIN_TESS_EDGE);
    ~ParticalRound();
    
    void draw();
    
    
private:
    int tessEdge;
    
};


#endif /* ParticalRound_hpp */
