//
//  Bullet.cpp
//  Shooter
//
//  Created by Hagar Yasser Omar on 11/19/16.
//  Copyright © 2016 Hagar Yasser Omar. All rights reserved.
//

#include "Bullet.hpp"
Bullet::Bullet(GLdouble r, GLdouble h, GLfloat c [3], GLint sl, GLint st){
    radius = r;
    smallR = r / 1.5;
    sphereR = r / 2.25;
    height = h;
    smallH = h/4;
    coneH = h/6;
    smallConeH = h/6.5;
    color[0]=c[0]; color[1]=c[1]; color[2]=c[2];
    slices = sl;
    stacks = st;
    
}
void Bullet::draw(){
    glPushMatrix();
    glRotated(-90, 1, 0, 0);
    glColor3fv(color);
    drawBigCylinder();
    drawEnclosingDisk();
    drawBigTorus();
    drawSmallTorus();
    drawIntermediateCone();
    drawSmallCylinder();
    drawUpperCone();
    drawEnclosingSphere();
    glPopMatrix();
}
void Bullet::drawBigCylinder(){
    glPushMatrix();
    GLUquadricObj * qobj;
    qobj = gluNewQuadric(); gluQuadricDrawStyle(qobj,GLU_FILL);
    gluCylinder(qobj, radius, radius, height, slices, stacks);
    glPopMatrix();
}
void Bullet::drawEnclosingDisk(){
    glPushMatrix();
    GLUquadricObj * qobj;
    qobj = gluNewQuadric();
    gluDisk(qobj, 0, radius, slices, stacks);
    glPopMatrix();
}
void Bullet::drawBigTorus(){
    glPushMatrix();
    GLdouble innerR = radius/10;
    GLdouble outerR = radius + innerR;
    glutSolidTorus(innerR, outerR, slices, stacks);
    glPopMatrix();
}
void Bullet::drawSmallTorus(){
    glPushMatrix();
//    glTranslated(0, 0, -0.005);
    GLdouble innerR = radius/10;
    GLdouble outerR = radius/2 + innerR;
    glutSolidTorus(innerR, outerR, slices, stacks);
    glPopMatrix();
}
void Bullet::drawIntermediateCone(){
    glPushMatrix();
    glTranslated(0, 0, height);
    GLUquadricObj * qobj;
    qobj = gluNewQuadric(); gluQuadricDrawStyle(qobj,GLU_FILL);
    gluCylinder(qobj, radius, smallR, coneH, slices, stacks);
    glPopMatrix();
}
void Bullet::drawSmallCylinder(){
    glPushMatrix();
    glTranslated(0, 0, height + coneH);
    GLUquadricObj * qobj;
    qobj = gluNewQuadric(); gluQuadricDrawStyle(qobj,GLU_FILL);
    gluCylinder(qobj, smallR, smallR, smallH, slices, stacks);
    glPopMatrix();
}
void Bullet::drawUpperCone(){
    glPushMatrix();
    glTranslated(0, 0, height + coneH + smallH);
    GLUquadricObj * qobj;
    qobj = gluNewQuadric(); gluQuadricDrawStyle(qobj,GLU_FILL);
    gluCylinder(qobj, smallR, sphereR, smallConeH, slices, stacks);
    glPopMatrix();
}
void Bullet::drawEnclosingSphere(){
    glPushMatrix();
    glTranslated(0, 0, height + coneH + smallH + smallConeH);
    glutSolidSphere(sphereR, slices, stacks);
    glPopMatrix();
}