//
//  main.cpp
//  Shooter
//
//  Created by Hagar Yasser Omar on 11/16/16.
//  Copyright © 2016 Hagar Yasser Omar. All rights reserved.
//

#include <GLUT/glut.h>
#include <stdio.h>

#include "Grenade.hpp"
#include "Bullet.hpp"
#include "Shuriken.hpp"
#include "Target.hpp"
#include "Walls.hpp"
#include "constants.h"


int width = 1024;
int height = 720;

Target *t;


void setupLights() {
    GLfloat ambient[] = { 0.7f, 0.7f, 0.7, 1.0f };
    GLfloat diffuse[] = { 0.6f, 0.6f, 0.6, 1.0f };
    GLfloat specular[] = { 1.0f, 1.0f, 1.0, 1.0f };
    GLfloat shininess[] = { 50 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
    
    GLfloat lightIntensity[] = { 0.7f, 0.7f, 1, 1.0f };
    GLfloat lightPosition[] = { -7.0f, 6.0f, 3.0f, 0.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, lightIntensity);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
}

void setupCamera() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
//    float aspect = (float)width / (float)height;
//    glOrtho(-aspect, aspect, -1, 1, -1, 1);
//    glOrtho(-0.5, 0.5, -0.5, 0.5, -1, 1);
//    glFrustum(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat near, GLfloat far);
    gluPerspective(120, width / height, 0.001, 10);
    
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0 , 0, 0.2,0.0, 0.0, -0.5, 0.0, 1, 0);
}

void initGame(){
    t = new Target(tPos,tScale,tColor1,tColor2,tColor3,tSlices,tStacks);
}
void Display() {
//    setupLights();
    setupCamera();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //grenade
//    Grenade *g = new Grenade(gRadius, gSphereColor,gTorusColor,gCylinderColor, grenadeSlices,grenadeStacks);
//    glPushMatrix();
//    glRotated(angle, 1, 1, 1);
//    g->draw();
//    glPopMatrix();
    
    //bullet
//    Bullet *b = new Bullet(bRadius, bHeight, bColor, bSlices, bStacks);
//        glPushMatrix();
//        glTranslated(0, -0.05, 0.16);
//        glScaled(0.03, 0.03, 0.03);
//        b->draw();
//        glPopMatrix();
    
    
    //shuriken
//    Shuriken *s = new Shuriken(sRadius, sHeight, sColor, sSlices, sStacks);
//            glPushMatrix();
//            glRotated(angle, 1, 1, 1);
//            s->draw();
//            glPopMatrix();
    
    //Target
        glPushMatrix();
        t->draw();
        glPopMatrix();
    
    //Walls
    Walls *w = new Walls();
        w->draw();
    glFlush();

}
void anim(){


}
void spe(int k, int x,int y){
    /* TARGET CONTROL */
    
    /* X-AXIS */
    if(k==GLUT_KEY_RIGHT){
        t->posX += 0.01;
    }
    if(k==GLUT_KEY_LEFT)
        t->posX -= 0.01;
    /* Y-AXIS */
    if(k==GLUT_KEY_UP)
        t->posY += 0.01;
    if(k==GLUT_KEY_DOWN)
        t->posY -= 0.01;

    glutPostRedisplay();
}
void key(unsigned char k, int x,int y)
{
    /* TARGET CONTROL */
    /* Z-AXIS */
    if(k=='k')
        t->posZ-=0.01;
    if(k=='l')
        t->posZ+=0.01;
        
    glutPostRedisplay();//redisplay to update the screen with the changes
}

int main(int argc, char** argv) {
    //Initialize needed objects
    initGame();
    
    glutInit(&argc, argv);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(50, 50);

    glutCreateWindow("Shooter");
//    glutFullScreen();
    glutDisplayFunc(Display);
    glutKeyboardFunc(key);
    glutSpecialFunc(spe);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
//    glutIdleFunc(anim);

    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_LIGHTING);
//    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    
    glShadeModel(GL_SMOOTH);
    
    glutMainLoop();
    return 0;
}

