//
//  Target.cpp
//  Shooter
//
//  Created by Hagar Yasser Omar on 11/19/16.
//  Copyright © 2016 Hagar Yasser Omar. All rights reserved.
//

#include "Target.hpp"
Target::Target(GLdouble pos [3], GLdouble s,GLfloat c1 [3], GLfloat c2 [3], GLfloat c3 [3], GLint sl, GLint st){
    color1[0]=c1[0]; color1[1]=c1[1]; color1[2]=c1[2];
    color2[0]=c2[0]; color2[1]=c2[1]; color2[2]=c2[2];
    color3[0]=c3[0]; color3[1]=c3[1]; color3[2]=c3[2];
    slices = sl;
    stacks = st;
    posX = pos[0]; posY=pos[1]; posZ=pos[2];
    scale = s;
    

}
void Target::draw(){
    glPushMatrix();
    glScaled(scale, scale, scale);
    glTranslated(posX, posY, posZ);
    
    //1. Inner Yellow Disk
    glColor3fv(color1);
    GLUquadricObj * qobjY;
    qobjY = gluNewQuadric();
    gluDisk(qobjY, 0, 0.1, slices, stacks);
    //2. Middle Red Disk
    glColor3fv(color2);
    GLUquadricObj * qobjR;
    qobjR = gluNewQuadric();
    gluDisk(qobjR, 0.1, 0.2, slices, stacks);
    //3. Outer Blue Disk
    glColor3fv(color3);
    GLUquadricObj * qobjB;
    qobjB = gluNewQuadric();
    gluDisk(qobjB, 0.2, 0.3, slices, stacks);
    glPopMatrix();


}