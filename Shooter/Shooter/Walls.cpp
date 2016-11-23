//
//  Walls.cpp
//  Shooter
//
//  Created by Hagar Yasser Omar on 11/22/16.
//  Copyright © 2016 Hagar Yasser Omar. All rights reserved.
//

#include "Walls.hpp"
Walls::Walls(){
    
}
void Walls::draw(){
    glBegin(GL_QUADS);
    /* Floor */
    glColor3f(0.7,0.7,0.7);
    glVertex3f(-1,-1,-1);
    glVertex3f(1,-1,-1);
    glVertex3f(1,-1,1);
    glVertex3f(-1,-1,1);
    
    /* Ceiling */
    glColor3f(0.7,0.7,0.7);
    glVertex3f(-1,1,-1);
    glVertex3f(1,1,-1);
    glVertex3f(1,1,1);
    glVertex3f(-1,1,1);
    
    /* Walls */
    
    //FRONT WALL
    glColor3f(0.6,0.6,0.6);
    glVertex3f(-1,-1,-1);
    glVertex3f(1,-1,-1);
    glVertex3f(1,1,-1);
    glVertex3f(-1,1,-1);
    //BACK WALL
    glVertex3f(-1,-1,1);
    glVertex3f(1,-1,1);
    glVertex3f(1,1,1);
    glVertex3f(-1,1,1);
    //SIDE WALLS
    glColor3f(0.5,0.5,0.5);
    glVertex3f(1,1,1);
    glVertex3f(1,-1,1);
    glVertex3f(1,-1,-1);
    glVertex3f(1,1,-1);
    
    glVertex3f(-1,1,1);
    glVertex3f(-1,-1,1);
    glVertex3f(-1,-1,-1);
    glVertex3f(-1,1,-1);
    glEnd();
}
//void Walls::drawWall() {
//    glPushMatrix();
//    glScaled(1.0, thickness, 1.0);
//    glutSolidCube(1);
//    glPopMatrix();
//}