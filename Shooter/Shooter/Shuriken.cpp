//
//  Shuriken.cpp
//  Shooter
//
//  Created by Hagar Yasser Omar on 11/19/16.
//  Copyright © 2016 Hagar Yasser Omar. All rights reserved.
//

#include "Shuriken.hpp"

Shuriken::Shuriken(GLdouble cR, GLdouble cH, GLfloat c [3], GLint sl, GLint st){
    coneRadius = cR;
    coneHeight = cH;
    color[0]=c[0]; color[1]=c[1]; color[2]=c[2];
    slices = sl;
    stacks = st;
}
void Shuriken::draw(){
    drawDiamond();
    drawTorus();
    drawFan();
    //duplicate fans
    glPushMatrix();
    glRotated(-90, 0, 0, 1);
    drawFan();
    glPopMatrix();
    glPushMatrix();
    glRotated(180, 0, 0, 1);
    drawFan();
    glPopMatrix();
    glPushMatrix();
    glRotated(90, 0, 0, 1);
    drawFan();
    glPopMatrix();
}
void Shuriken::drawDiamond(){
    glColor3fv(color);
    glPushMatrix();
    glScaled(1/11.0, 1/11.0, 1/11.0);
    glutSolidOctahedron();
    glPopMatrix();
    
}
void Shuriken::drawTorus(){
    glColor3f(0.5,0.5,0.5);
    GLdouble inner = coneRadius/5;
    glPushMatrix();
    glutSolidTorus(inner, coneRadius+0.005, slices, stacks);
    glPopMatrix();
}
void Shuriken::drawFan(){
    glColor3fv(color);
    glPushMatrix();
    glTranslated(0,coneRadius, 0);
    
    //draw base polygon
    glBegin(GL_POLYGON);
    glVertex3f(0, 0, 0);
    glVertex3f(0.12, 0.1, 0);
    glVertex3f(0, 0.4, 0);
    glVertex3f(-0.12, 0.1, 0);
    glVertex3f(0, 0, 0);
    glEnd();

    //draw 3 protruding polygons
    glBegin(GL_POLYGON);
    glVertex3f(0, 0, 0);
    glVertex3f(0.12, 0.1, 0);
    glVertex3f(0, 0.25, 0.05);
    glVertex3f(-0.12, 0.1, 0);
    glEnd();
    
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_POLYGON);
    glVertex3f(0.12, 0.1, 0);
    glVertex3f(0, 0.25, 0.05);
    glVertex3f(0, 0.4, 0);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3f(0, 0.25, 0.05);
    glVertex3f(-0.12, 0.1, 0);
    glVertex3f(0, 0.4, 0);
    glEnd();
    
    glPopMatrix();
    
}