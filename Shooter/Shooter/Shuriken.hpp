//
//  Shuriken.hpp
//  Shooter
//
//  Created by Hagar Yasser Omar on 11/19/16.
//  Copyright © 2016 Hagar Yasser Omar. All rights reserved.
//

#ifndef Shuriken_hpp
#define Shuriken_hpp

#include <stdio.h>
#include "Trajectory.hpp"
#include <GLUT/glut.h>

class Shuriken : public Trajectory{
public:
    void draw();
    Shuriken(GLdouble,GLdouble, GLfloat [3], GLint, GLint);
private:
    GLfloat color[3];
    GLdouble coneRadius;
    GLdouble coneHeight;
    GLint slices;
    GLint stacks;
    void drawDiamond();
    void drawTorus();
    void drawFan();
};
#endif /* Shuriken_hpp */
