//
//  main.cpp
//  lab2
//
//  Created by mr.ji on 15/10/29.
//  Copyright (c) 2015年 mr.ji. All rights reserved.
//
//主要工作是调节perspective的角度值，桌子放置的X\Y位置
#include "GLUT/GLUT.h"

float fTranslate;
float fRotate;
float scaleRatio=1.0f;//缩放率

void Draw_Desk() //This function draws a desk with RGB colors
{
    glColor3f(1, 1, 1);
    glPushMatrix();
    
    glTranslatef(0, 0, 0.0f);
    glScalef(5, 4, 1);
    glutWireCube(1);//the desk surface
    
    glPopMatrix();
    glPushMatrix();
    
    glTranslatef(-1.5, 1, 2.0f);
    glScalef(1, 1, 3);
    glutWireCube(1);//the desk leg
    
    glPopMatrix();
    glPushMatrix();
    
    glTranslatef(-1.5, -1, 2.0f);
    glScalef(1, 1, 3);
    glutWireCube(1);//the second desk leg
    
    glPopMatrix();
    glPushMatrix();
    
    glTranslatef(1.5, 1, 2.0f);
    glScalef(1, 1, 3);
    glutWireCube(1);//the third leg
    
    glPopMatrix();
    glPushMatrix();
    
    glTranslatef(1.5, -1, 2.0f);
    glScalef(1, 1, 3);
    glutWireCube(1);//the forth leg
    
    glPopMatrix();
    
    
}

void reshape(int width, int height)
{
    if (height==0)										// Prevent A Divide By Zero By
    {
        height=1;										// Making Height Equal One
    }
    
    glViewport(0,0,width,height);						// Reset The Current Viewport
    
    glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
    glLoadIdentity();									// Reset The Projection Matrix
    
    // Calculate The Aspect Ratio Of The Window
    gluPerspective(80.0f,(GLfloat)width/(GLfloat)height,1.0f,100.0f);
    
    glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
    glLoadIdentity();									// Reset The Modelview Matrix
}

void idle()
{
    glutPostRedisplay();
}

void redraw()
{
    // If want display in wireframe mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();									// Reset The Current Modelview Matrix
    
    glPushMatrix();
    glTranslatef(-10.0f, 0.0f,-15.0f);		// Place the desk Left
    glTranslatef(0.0f, fTranslate, 0.0f);	// Translate in Y direction
    Draw_Desk();						// draw the desk
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0f, 0.0f,-15.0f);			// Place the desk at Center
    glRotatef(fRotate, 0, 1.0f, 0);			// Rotate around Y axis
    Draw_Desk();            //draw the desk
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(10.0f, 0.0f, -15.0f);      //place the desk right
    glScalef(scaleRatio, scaleRatio, scaleRatio); //set scale ratio
    Draw_Desk();            //draw the right desk
    glPopMatrix();
    
    fTranslate += 0.02f;
    fRotate    += 0.5f;
    scaleRatio -=0.005f;
    
    if(fTranslate > 2.0f) fTranslate = 0.0f;
    if(scaleRatio < 0.5f) scaleRatio = 1.0f;
    glutSwapBuffers();
}

int main (int argc,  char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(640,480);
    glutCreateWindow("Exercise2");
    
    glutDisplayFunc(redraw);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);					
    
    glutMainLoop();
    
    return 0;
    
}
