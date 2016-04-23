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
    Object() {};
    ~Object() {};
    
    virtual void draw(int x, int y, int z){};
protected:
    
    
};


#endif /* Object_hpp */
