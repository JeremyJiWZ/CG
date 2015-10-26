//
//  main.cpp
//  cg
//
//  Created by mr.ji on 15/10/15.
//  Copyright (c) 2015年 mr.ji. All rights reserved.
//

#include <iostream>
#include "GLUT/GLUT.h"
#include <math.h>
#define PI 3.14159

void star(int x, int y,int r)
{
    int x1,y1,x2,y2,x3,y3,x4,y4;
    float xoff,yoff,x1off;
    xoff = 0.5*r*cos(PI/6); //tail x's coordinate
    x1off = 0.8*r*cos(PI/6); //hand x's coordinate
    yoff = r+0.5*r/2; //tail y's coordinate
    x2=x-xoff;
    x3=x+xoff;
    y2=y3=y-yoff;
    x1=x-x1off;
    x4=x+x1off;
    y1=y4=y-0.5*r; //hand y's coordinate
    glColor3f(1.0f, 1.0f, 0);
    glBegin(GL_TRIANGLES);
        glVertex3i(x, y, 0);
        glVertex3i(x, y-r, 0);
        glVertex3i(x2, y2, 0);
    glEnd();
    
    glBegin(GL_TRIANGLES);
        glVertex3i(x,y,0);
        glVertex3i(x, y-r, 0);
        glVertex3i(x3, y3, 0);
    glEnd();
    
    glBegin(GL_TRIANGLES);
    glVertex3i(x1,y1,0);
    glVertex3i(x4,y4,0);
    glVertex3i(x,y-r,0);
    glEnd();
    
    
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 0, 0);
    glBegin(GL_QUADS);
        glVertex3i(0,0,0);
        glVertex3i(800, 0,0);
        glVertex3i(800, 600,0);
        glVertex3i(0, 600,0);
    glEnd();
    
    star(100, 550, 100); //main star
    
    
    glPushMatrix();
    glTranslatef(250, 570, 0);
    glRotatef(-30, 0, 0, 1);
    star(0, 0, 25); //small star1
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(280, 520, 0);
    glRotatef(30, 0, 0, 1);
    star(0, 0, 25); //small star2
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(275, 460, 0);
    star(0, 0, 25);
    glPopMatrix();  //small star3
    
    glPushMatrix();
    glTranslatef(230, 410, 0);
    glRotatef(-30, 0, 0, 1);
    star(0, 0, 25);
    glPopMatrix();
    
    glutSwapBuffers();
}

int main (int argc,  char *argv[])
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Simple GLUT App");
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 600);
    
    glutDisplayFunc(display);
    
    glutMainLoop();
    
    return 0;
}