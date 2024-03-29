//
//  constants.h
//  Shooter
//
//  Created by Hagar Yasser Omar on 11/19/16.
//  Copyright © 2016 Hagar Yasser Omar. All rights reserved.
//

#ifndef constants_h
#define constants_h

//GRENADE VALUES
const GLint grenadeSlices = 50;
const GLint grenadeStacks = 50;
 GLfloat gSphereColor[3]={0.2,0.2,0.2};
 GLfloat gTorusColor[3]={0,0,0.5};
 GLfloat gCylinderColor[3]={0,0,0.5};
const GLdouble gRadius = 0.5;

//BULLET VALUES
const GLint bSlices = 50;
const GLint bStacks = 50;
const GLdouble bRadius = 0.08;
const GLdouble bHeight = 0.6;
GLfloat bColor[3]={0.3,0.3,0.3};


//SHURIKEN VALUES
const GLint sSlices = 50;
const GLint sStacks = 50;
const GLdouble sRadius = 0.08;
const GLdouble sHeight = 0.08;
GLfloat sColor[3]={0,0,0.5};

//TARGET VALUES
const GLint tSlices = 50;
const GLint tStacks = 50;
GLfloat tColor1[3]={0.8,1.0,0.0}; //yellow
GLfloat tColor2[3]={0.6,0,0.0}; //red
GLfloat tColor3[3]={0,0,0.6}; //blue
GLdouble tPos[3]={0.0,0.0,-0.9};
GLdouble tScale = 0.5;


//WALL VALUES
GLdouble wThickness = 0.01;

#endif /* constants_h */
