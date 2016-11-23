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
#define AIM 1
#define REPLAY 2

/* ------GAME OBJECTS-------*/
Target *t;
Walls *w;
Bullet *b;
double bulletX = 0;
double bulletY = -0.05;
double bulletZ = 0.19;
double bulletDirAngle = 0;
Grenade *g;
Shuriken *s;

int width = 1024;
int height = 720;

int prevMouseX=0;
int prevMouseY=0;

/* CAMERA VALUES */
double xCamDir = 0.0;
double yCamDir = 0.0;
double zCamDir = -0.5;

double xCamPos = 0.0;
double yCamPos = 0.0;
double zCamPos = 0.2;
/*END*/

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
    glLoadIdentity();
    gluLookAt(xCamPos , yCamPos, zCamPos, xCamDir, yCamDir, zCamDir, 0.0, 1, 0);
    
}

void initGame(){
    w = new Walls();
    t = new Target(tPos,tScale,tColor1,tColor2,tColor3,tSlices,tStacks);
    s = new Shuriken(sRadius, sHeight, sColor, sSlices, sStacks);
    b = new Bullet(bRadius, bHeight, bColor, bSlices, bStacks);
    g = new Grenade(gRadius, gSphereColor,gTorusColor,gCylinderColor, grenadeSlices,grenadeStacks);
    game_mode   = AIM;
    trajectory  = BULLET;
}
void Display() {
    setupLights();
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
            glTranslated(bulletX, bulletY, bulletZ);
            glRotated(bulletDirAngle, 0, 1, 0);
            glRotated(-90, 1, 0, 0);
            glScaled(0.1, 0.1, 0.1);
            b->draw();
            glPopMatrix();
            glColor3f(1, 0, 0);
            glPointSize(9.0);
            glBegin(GL_LINES);
            glVertex3f(bulletX, bulletY, bulletZ);
            glVertex3f(xCamDir, bulletY, -1);
            glEnd();
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
    if(game_mode == SHOOT && trajectory == BULLET){
        double changeX = xCamDir - bulletX;
        double changeZ = -1 - bulletZ;
        double magnitude = sqrt(changeX*changeX + changeZ*changeZ);
        if(magnitude!=0){
            double advanceX = changeX /magnitude;
            double advanceZ = changeZ/magnitude;
            bulletX+=0.01*advanceX;
            bulletZ+=0.01*advanceZ;
        }
    }
    glutPostRedisplay();
    
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
    
    /* SHOOT MODE*/
    if(game_mode==AIM && k==' ')
        game_mode = SHOOT;
    
    glutPostRedisplay();//redisplay to update the screen with the changes
}

void passM(int mouseX,int mouseY)
{
    
    /* CAMERA CONTROL */
    if(game_mode == AIM){
        //Adjust to scene coordinates
        double winW =glutGet(GLUT_WINDOW_WIDTH);
        mouseX = mouseX - winW/2;
        
        //Change x-comp of center of gluLookAT
        xCamDir += 0.001*(mouseX - prevMouseX);
        if(xCamDir<-0.3)
            xCamDir = -0.3;
        if(xCamDir>0.3)
            xCamDir = 0.3;
        prevMouseX = mouseX;
        
        //Rotate Trajectory
        double changeX = xCamDir - bulletX;
        double changeZ = -1 - bulletZ;
        double angle = atan2(fabs(changeX),fabs(changeZ));
        bulletDirAngle = (angle*180/M_PI);
        if(changeX>0)
            bulletDirAngle*=-1;
        
    }
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
        glutIdleFunc(anim);
    
    glEnable(GL_DEPTH_TEST);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    
    glShadeModel(GL_SMOOTH);
    
    glutMainLoop();
    return 0;
}

