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
#define HIT_WALL 3
#define HIT_TARGET 4

double trajX;
double trajY;
double trajZ;

/* ------GAME OBJECTS-------*/
Target *t;
Walls *w;
Bullet *b;
double bulletX = 0;
double bulletY = -0.05;
double bulletZ = 0.19;
double bulletDirAngle = 0;
double bulletRotAngle = 0;
Grenade *g;
double grenadeX = 0;
double grenadeY = -0.05;
double grenadeZ = 0.16;
double grenadeDirAngle;
double grenadeRotAngle = 0;
double gBezier = 0.0;
Shuriken *s;
double shurikenX = 0;
double shurikenY = -0.05;
double shurikenZ = 0.16;
double shurikenDirAngle;
double shurikenRotAngle = 0;
double sBezier = 0.0;

int width = 1024;
int height = 720;

int prevMouseX=0;
int prevMouseY=0;

/* CAMERA VALUES */
double xCamDir = 0.0;
double yCamDir = 0.0;
double zCamDir = -0.5;

float xCamPos = 0.0;
float yCamPos = 0.0;
float zCamPos = 0.2;
/*END*/

void setupLights(){
    GLfloat ambient[] = { 0.7f, 0.7f, 0.7, 1.0f };
    GLfloat diffuse[] = { 0.6f, 0.6f, 0.6, 1.0f };
    GLfloat specular[] = { 1.0f, 1.0f, 1.0, 1.0f };
    GLfloat shininess[] = { 50 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
    
    GLfloat lightIntensity[] = { 0.7f, 0.7f, 1, 1.0f };
    GLfloat lightPosition[] = { 0, 0.9, -0.9, 0.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, lightIntensity);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
}
void setupCamera(){
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
void resetPositions(){
     bulletX = 0;
     bulletY = -0.05;
     bulletZ = 0.19;
    
     grenadeX = 0;
     grenadeY = -0.05;
     grenadeZ = 0.16;
    
     shurikenX = 0;
     shurikenY = -0.05;
     shurikenZ = 0.16;
}
void translateBullet(){
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
void rotateBullet(){
    double changeX = xCamDir - bulletX;
    double changeZ = -1 - bulletZ;
    double angle = atan2(fabs(changeX),fabs(changeZ));
    bulletDirAngle = (angle*180/M_PI);
    if(changeX>0)
        bulletDirAngle*=-1;
}
void rotateGrenade(){
    double changeX = xCamDir - 0;
    double changeZ = -1 - 0.16;
    double angle = atan2(fabs(changeX),fabs(changeZ));
    grenadeDirAngle = (angle*180/M_PI);
    if(changeX>0)
        grenadeDirAngle*=-1;
}
void rotateShuriken(){
    double changeX = xCamDir - 0;
    double changeZ = -1 - 0.16;
    double angle = atan2(fabs(changeX),fabs(changeZ));
    shurikenDirAngle = (angle*180/M_PI);
    if(changeX>0)
        shurikenDirAngle*=-1;
}
double* bezier(double t, float* p0,float* p1,float* p2,float* p3){
    double res[2];
    res[0]=pow((1-t),3)*p0[0]+3*t*pow((1-t),2)*p1[0]+3*pow(t,2)*(1-t)*p2[0]+pow(t,3)*p3[0];
    res[1]=pow((1-t),3)*p0[1]+3*t*pow((1-t),2)*p1[1]+3*pow(t,2)*(1-t)*p2[1]+pow(t,3)*p3[1];
    return res;
}
void translateGrenade(){
    float p0 [2] = {0.16,-0.05};
    float p1 [2] = {0,0.2};
    float p2 [2] = {-0.4,0.2};
    float p3 [2] = {-0.6, -0.9};
    double* p =bezier(gBezier,p0,p1,p2,p3);
    gBezier+=0.001;
    grenadeY = p[1];
    grenadeZ = p[0];
}
void translateShuriken(){
    float p0 [2] = {0,0.16};
    float p1 [2] = {-0.1,-0.1};
    float p2 [2] = {-0.4,-0.75};
    float p3 [2] = {0, -0.9};
    double* p =bezier(gBezier,p0,p1,p2,p3);
    gBezier+=0.001;
    shurikenX = p[0];
    shurikenZ = p[1];
}
void setReplayMode(int v){
    //change cam position
    resetPositions();
    game_mode = REPLAY;
}
void anim(){
    switch(trajectory){
        case BULLET:{
            trajX = bulletX;
            trajY = bulletY;
            trajZ = bulletZ;
            break;
        }
        case GRENADE:{
            trajX = grenadeX;
            trajY = grenadeY;
            trajZ = grenadeZ;
            break;
        }
        case SHURIKEN:{
            trajX = shurikenX;
            trajY = shurikenY;
            trajZ = shurikenZ;
            break;
        }
    }
    if(game_mode == SHOOT){
        switch(trajectory){
            case BULLET:
            {
                translateBullet();
                bulletRotAngle++;
                break;
            }
            case GRENADE:
            {
                translateGrenade();
                grenadeRotAngle++;
                break;
            }
            case SHURIKEN:
            {
                translateShuriken();
                shurikenRotAngle+=2;
                break;
            }
        }

    }
    if(trajX < -0.99 || trajX > 0.99 || trajY <-0.99 || trajY >0.99 || trajZ <-0.99){
        if(game_mode == SHOOT)
            glutTimerFunc(1000,setReplayMode, 0);
        game_mode = HIT_WALL;
    }
    //TODO HIT_TARGET
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
void key(unsigned char k, int x,int y){
    /* TARGET CONTROL */
    /* Z-AXIS */
    if(k=='k')
        t->posZ-=0.01;
    if(k=='l')
        t->posZ+=0.01;
    
    /*TRAJECTORY CHOICE*/
    if(k=='b'){
        trajectory = BULLET;
    }
    if(k=='g'){
        trajectory = GRENADE;
    }
    if(k=='s'){
        trajectory = SHURIKEN;
    }
    
    /* SHOOT MODE*/
    if(game_mode==AIM && k==' ')
        game_mode = SHOOT;
    
    glutPostRedisplay();//redisplay to update the screen with the changes
}
void passM(int mouseX,int mouseY){
    
    if(game_mode == AIM){
        /* CAMERA CONTROL */
        //Adjust to scene coordinates
        double winW =glutGet(GLUT_WINDOW_WIDTH);
        mouseX = mouseX - winW/2;
        
        //Change x-comp of center of gluLookAT
        xCamDir += 0.01*(mouseX - prevMouseX);
        if(xCamDir<-0.3)
            xCamDir = -0.3;
        if(xCamDir>0.3)
            xCamDir = 0.3;
        prevMouseX = mouseX;
        /*END*/
        
        /*Rotate Bullet*/
        rotateBullet();
        
    }
    glutPostRedisplay();
    
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
    setupCamera();
    setupLights();

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
            if(game_mode == SHOOT)
                glRotated(bulletRotAngle, 0, 0, -1);
            glRotated(-90, 1, 0, 0);
            glScaled(0.1, 0.1, 0.1);
            b->draw();
            glPopMatrix();
            //Aiming Direction
            glColor3f(1, 0, 0);
            glPointSize(9.0);
            glBegin(GL_LINES);
            glVertex3f(bulletX, bulletY, bulletZ);
            glVertex3f(xCamDir, bulletY, -1);
            glEnd();
            break;
        }
        case GRENADE:
        {   rotateGrenade();
            glPushMatrix();
            glRotated(grenadeDirAngle, 0, 1, 0);
            glTranslated(grenadeX, grenadeY, grenadeZ);
            glScaled(0.03, 0.03, 0.03);
            if(game_mode == SHOOT){
                glRotated(grenadeRotAngle, 1, 0, -1);
            }
            g->draw();
            glPopMatrix();
            break;
        }
        case SHURIKEN:
        {   rotateShuriken();
            glPushMatrix();
            glRotated(shurikenDirAngle, 0, 1, 0);
            glTranslated(shurikenX, shurikenY, shurikenZ);
            if(game_mode == SHOOT){
                glRotated(shurikenRotAngle, 0, 1, 0);
            }
            glRotated(-90, 1, 0, 0);
            glScaled(0.08, 0.08, 0.08);
            s->draw();
            glPopMatrix();
            break;
        }
    }
    glFlush();
    
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

