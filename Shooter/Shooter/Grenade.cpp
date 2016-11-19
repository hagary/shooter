//
//  Grenade.cpp
//  Shooter
//
//  Created by Hagar Yasser Omar on 11/19/16.
//  Copyright © 2016 Hagar Yasser Omar. All rights reserved.
//

#include "Grenade.hpp"

Grenade::Grenade(GLdouble r,GLfloat sc [3] , GLfloat tc [3],GLfloat cc [3], GLint sl, GLint st){
    sphereRadius    =   r;
    sphereColor[0]  =  sc[0]; sphereColor[1] = sc[1]; sphereColor[2]=sc[2];
    torusColor[0]  =  tc[0]; torusColor[1] = tc[1]; torusColor[2]=tc[2];
    cylinderColor[0]  =  cc[0]; cylinderColor[1] = cc[1]; cylinderColor[2]=cc[2];
    slices = sl;
    stacks = st;
}
void Grenade::drawSphere(){
    glColor3fv(sphereColor);
    glPushMatrix();
    glutSolidSphere(sphereRadius, slices, stacks);
    glPopMatrix();
}
void Grenade::drawTorus(){
    GLdouble inner  =   sphereRadius/20;
    GLdouble outer  =   sphereRadius + inner;
    
    glColor3fv(torusColor);
    glPushMatrix();
    glRotated(90, 1, 0, 0);
    glutSolidTorus(inner, outer, slices, stacks);
    glPopMatrix();
}
void Grenade::drawCylinder(){
    glColor3fv(cylinderColor);
    
    glPushMatrix();
    glTranslated(0, 6*sphereRadius/5, 0);
    glRotated(90, 1, 0, 0);
    drawHollowCylinder();
    drawEnclosingDisk();
    glPopMatrix();
}
void Grenade::drawHollowCylinder(){
    GLdouble radius =   sphereRadius/2.5;
    GLdouble height =   sphereRadius/2.5;
    
    glPushMatrix();
    GLUquadricObj * qobj;
    qobj = gluNewQuadric(); gluQuadricDrawStyle(qobj,GLU_FILL);
    gluCylinder(qobj, radius, radius, height, slices, stacks);
    glPopMatrix();
}
void Grenade::drawEnclosingDisk(){
    GLdouble radius =   sphereRadius/2.5;
    glPushMatrix();
    GLUquadricObj * qobj;
    qobj = gluNewQuadric();
    gluDisk(qobj, 0, radius, slices, stacks);
    glPopMatrix();
}
void Grenade::draw(){
    drawSphere();
    drawTorus();
    drawCylinder();
}