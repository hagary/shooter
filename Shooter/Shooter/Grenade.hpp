//
//  Grenade.hpp
//  Shooter
//
//  Created by Hagar Yasser Omar on 11/19/16.
//  Copyright © 2016 Hagar Yasser Omar. All rights reserved.
//

#ifndef Grenade_hpp
#define Grenade_hpp

#include <stdio.h>
#include "Trajectory.hpp"
#include "GLUT/glut.h"
class Grenade : public Trajectory{
public:
    void draw();
    Grenade(GLdouble, GLfloat[3],GLfloat[3],GLfloat[3], GLint, GLint);
private:
    GLint stacks;
    GLint slices;
    GLdouble sphereRadius;
    GLfloat sphereColor [3];
    GLfloat torusColor [3];
    GLfloat cylinderColor [3];
    void drawSphere();
    void drawTorus();
    void drawCylinder();
    void drawHollowCylinder();
    void drawEnclosingDisk();
};
#endif /* Grenade_hpp */
