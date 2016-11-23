//
//  main.cpp
//  Shooter
//
//  Created by Hagar Yasser Omar on 11/16/16.
//  Copyright © 2016 Hagar Yasser Omar. All rights reserved.
//

#include <GLUT/glut.h>
#include <stdio.h>
#include <math.h>

#include "Grenade.hpp"
#include "Bullet.hpp"
#include "Shuriken.hpp"
#include "Target.hpp"
#include "Walls.hpp"
#include "constants.h"


/* ------TRAJECTORY CHOICE-------*/
int trajectory;
#define BULLET 0
#define GRENADE 1
#define SHURIKEN 2

/* ------GAME MODE-------*/
int game_mode;
#define SHOOT 0
#define TARGET 1
#define REPLAY 2

/* ------GAME OBJECTS-------*/
Target *t;
Walls *w;
Bullet *b;
Grenade *g;
Shuriken *s;

int width = 1024;
int height = 720;

int prevMouseX=0;
int prevMouseY=0;

double xCamDir= 0.0;

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
    
    gluPerspective(120, width / height, 0.001, 100);
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    gluLookAt(0 , 0, 0.2, xCamDir, 0.0, -0.5, 0.0, 1, 0);
    
}

void initGame(){
    w = new Walls();
    t = new Target(tPos,tScale,tColor1,tColor2,tColor3,tSlices,tStacks);
    s = new Shuriken(sRadius, sHeight, sColor, sSlices, sStacks);
    b = new Bullet(bRadius, bHeight, bColor, bSlices, bStacks);
    g = new Grenade(gRadius, gSphereColor,gTorusColor,gCylinderColor, grenadeSlices,grenadeStacks);
    game_mode   = TARGET;
    trajectory  = SHURIKEN;
}
void Display() {
    //    setupLights();
    setupCamera();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //Walls
    w->draw();
    //Target
    t->draw();
    switch (trajectory) {
        case BULLET:
        {
            glPushMatrix();
            glScaled(0.1, 0.1, 0.1);
            b->draw();
            glPopMatrix();
            break;
        }
        case GRENADE:
        {
            glPushMatrix();
            glScaled(0.06, 0.08, 0.08);
            g->draw();
            glPopMatrix();
            break;
        }
        case SHURIKEN:
        {
            glPushMatrix();
            glScaled(0.1, 0.1, 0.1);
            s->draw();
            glPopMatrix();
            break;
        }
    }
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
    
    /*TRAJECTORY CHOICE*/
    if(k=='b')
        trajectory = BULLET;
    if(k=='g')
        trajectory = GRENADE;
    if(k=='s')
        trajectory = SHURIKEN;
    
    glutPostRedisplay();//redisplay to update the screen with the changes
}

void passM(int mouseX,int mouseY)
{
    
    /* CAMERA CONTROL */
    //Adjust to scene coordinates
    double winW =glutGet(GLUT_WINDOW_WIDTH);
    mouseX = mouseX - winW/2;
    //Change x-comp of center of gluLookAT
    xCamDir += 0.001*(mouseX - prevMouseX);
    if(xCamDir<-0.1)
        xCamDir = -0.1;
    if(xCamDir>0.1)
        xCamDir = 0.1;
    
    prevMouseX = mouseX;
    glutPostRedisplay();
    
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
    glutPassiveMotionFunc(passM);
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

