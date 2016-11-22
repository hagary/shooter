//
//  Target.hpp
//  Shooter
//
//  Created by Hagar Yasser Omar on 11/19/16.
//  Copyright © 2016 Hagar Yasser Omar. All rights reserved.
//

#ifndef Target_hpp
#define Target_hpp

#include <stdio.h>
#include <GLUT/glut.h>

class Target{
public:
    void draw();
    Target(GLfloat [3], GLfloat[3], GLfloat[3], GLint, GLint);
private:
    GLint slices;
    GLint stacks;
    GLfloat color1 [3];
    GLfloat color2 [3];
    GLfloat color3 [3];
};
#endif /* Target_hpp */
