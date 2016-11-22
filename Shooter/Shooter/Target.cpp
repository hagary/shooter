//
//  Target.cpp
//  Shooter
//
//  Created by Hagar Yasser Omar on 11/19/16.
//  Copyright © 2016 Hagar Yasser Omar. All rights reserved.
//

#include "Target.hpp"
Target::Target(GLfloat c1 [3], GLfloat c2 [3], GLfloat c3 [3], GLint sl, GLint st){
    color1[0]=c1[0]; color1[1]=c1[1]; color1[2]=c1[2];
    color2[0]=c2[0]; color2[1]=c2[1]; color2[2]=c2[2];
    color3[0]=c3[0]; color3[1]=c3[1]; color3[2]=c3[2];
    slices = sl;
    stacks = st;

}
void Target::draw(){
    glColor3fv(color1);
    glPushMatrix();
    GLUquadricObj * qobj;
    qobj = gluNewQuadric();
    gluDisk(qobj, 0, 0.2, slices, stacks);
    glPopMatrix();
}