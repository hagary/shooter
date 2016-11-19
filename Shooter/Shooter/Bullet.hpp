//
//  Bullet.hpp
//  Shooter
//
//  Created by Hagar Yasser Omar on 11/19/16.
//  Copyright © 2016 Hagar Yasser Omar. All rights reserved.
//

#ifndef Bullet_hpp
#define Bullet_hpp

#include <stdio.h>
#include <GLUT/glut.h>
#include "Trajectory.hpp"

class Bullet : public Trajectory{
public:
    void draw();
    Bullet(GLdouble,GLdouble,GLfloat[3],GLint,GLint);
private:
    GLdouble radius;
    GLdouble height;
    GLdouble smallH;
    GLdouble coneH;
    GLdouble smallR;
    GLdouble sphereR;
    GLdouble smallConeH;
    GLfloat color [3];
    GLint slices;
    GLint stacks;
    void drawBigCylinder();
    void drawSmallCylinder();
    void drawIntermediateCone();
    void drawUpperCone();
    void drawEnclosingDisk();
    void drawEnclosingSphere();
    void drawBigTorus();
    void drawSmallTorus();
};

#endif /* Bullet_hpp */
