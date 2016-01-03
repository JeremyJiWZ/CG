// glutEx1.cpp : ∂®“Âøÿ÷∆Ã®”¶”√≥Ã–Úµƒ»Îø⁄µ„°£
//


#include <stdlib.h>
#include <GLUT/glut.h>
#include <stdio.h>
#include "bitmapProcess.h"

float fTranslate;
float fRotate;
float fScale     = 1.0f;	// set inital scale value to 1.0f

bool bPersp = false;
bool bAnim = false;
bool bWire = false;
bool selectMixTex = false;

int wHeight = 0;
int wWidth = 0;

Bitmap texture1 =Bitmap("/Users/jiwentadashi/Desktop/计算机图形/实验六/Crack.bmp");
Bitmap texture2 =Bitmap("/Users/jiwentadashi/Desktop/计算机图形/实验六/Monet.bmp");
Bitmap texture3 =Bitmap("/Users/jiwentadashi/Desktop/计算机图形/实验六/Spot.bmp");
BYTE* mixImage;//生成的图片
GLuint texNames[10];



//定义材质信息
float dest_mat_diffuse[] = {1,0,0,1};
float leg1_mat_diffuse[] = {0, 1, 0, 1.0f};
float leg2_mat_diffuse[] = {1, 1, 0, 1.0f};
float leg3_mat_diffuse[] = {0, 1, 1, 1.0f};
float leg4_mat_diffuse[] = {0, 0, 1, 1.0f};
float mat_diffuse[] = {0.65f, 0.65f, 0.65f, 1.0f};
float mat_specular[] = {0.8f, 0.8f, 0.8f, 1.0f};
float none_specular[] = {0,0,0,1};

//定义光源信息
float white[] = {0.3,0.3,0.3,1};
float blue[] = {0,0,1,1};
float red[] = {1,0,0,1};
float green[] = {0,1,0,1};
int light_choosen = 0;//0 for white, 1 for r,2 for g, 3 for b
float light_pos[] = {5,5,5,1};
float light_delta = 1;
float diffuse[] = {0.6,0.6,0.6};
float specular[] = {0.8,0.8,0.8,1};
//聚光灯
float flash_pos[] = {0,10,0,1};
float light_dir[] = {0,-1,0,1};
float angle =10;
const float delta_angle = 1;
const float delta_pos = 0.1;

void Draw_Leg();

void madeMixImage(){
    mixImage = new BYTE[12288];
    for (int i = 0; i < 64; i++)
    {
        for (int j = 0; j < 64; j++)
        {
            int c = ((((i & 0x8) == 0) ^ ((j & 0x8))) == 0) * 255;
            mixImage[i*64*3+j*3+0]=c;//r
            mixImage[i*64*3+j*3+1]=0;//g
            mixImage[i*64*3+j*3+2]=0;//b
        }
    }
}

void setLight(){
    if (light_choosen==0) {//white
        glEnable(GL_LIGHTING);
        glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
        glLightfv(GL_LIGHT0, GL_AMBIENT, white);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
        glEnable(GL_LIGHT0);
        glDisable(GL_LIGHT1);
        glDisable(GL_LIGHT2);
        glDisable(GL_LIGHT3);
        glDisable(GL_LIGHT4);
    }
    else if(light_choosen==1){//r
        glEnable(GL_LIGHTING);
        glLightfv(GL_LIGHT1, GL_POSITION, light_pos);
        glLightfv(GL_LIGHT1, GL_AMBIENT, red);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
        glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
        glEnable(GL_LIGHT1);
        glDisable(GL_LIGHT0);
        glDisable(GL_LIGHT2);
        glDisable(GL_LIGHT3);
        glDisable(GL_LIGHT4);
    }
    else if (light_choosen==2){//g
        glEnable(GL_LIGHTING);
        glLightfv(GL_LIGHT2, GL_POSITION, light_pos);
        glLightfv(GL_LIGHT2, GL_AMBIENT, green);
        glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse);
        glLightfv(GL_LIGHT2, GL_SPECULAR, specular);
        glEnable(GL_LIGHT2);
        glDisable(GL_LIGHT0);
        glDisable(GL_LIGHT1);
        glDisable(GL_LIGHT3);
        glDisable(GL_LIGHT4);
    }
    else if (light_choosen==3){//b
        glEnable(GL_LIGHTING);
        glLightfv(GL_LIGHT3, GL_POSITION, light_pos);
        glLightfv(GL_LIGHT3, GL_AMBIENT, blue);
        glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuse);
        glLightfv(GL_LIGHT3, GL_SPECULAR, specular);
        glEnable(GL_LIGHT3);
        glDisable(GL_LIGHT0);
        glDisable(GL_LIGHT1);
        glDisable(GL_LIGHT2);
        glDisable(GL_LIGHT4);
    }
    else if(light_choosen == 4){//聚光灯
        glEnable(GL_LIGHTING);
        glLightfv(GL_LIGHT4, GL_AMBIENT,white);             //设置环境光成分
        glLightfv(GL_LIGHT4, GL_SPECULAR,specular);                    //设置镜面光成分
        glLightfv(GL_LIGHT4, GL_DIFFUSE,diffuse);                     //设置漫射光成分
        
        glLightfv(GL_LIGHT4, GL_POSITION,flash_pos);
        glLightf(GL_LIGHT4,  GL_SPOT_CUTOFF,angle);             //裁减角度
        glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, light_dir);          //光源方向
        glLightf(GL_LIGHT4,GL_SPOT_EXPONENT,2.0);                    //聚集度
        glEnable(GL_LIGHT4);
        glDisable(GL_LIGHT0);
        glDisable(GL_LIGHT1);
        glDisable(GL_LIGHT2);
        glDisable(GL_LIGHT3);
    }
    
}
void solidCube(GLfloat size)
{
    glBegin(GL_QUADS);
    // Front Face
    glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 0.0f); glMultiTexCoord2f(GL_TEXTURE1, 0.0f, 0.0f); glVertex3f(-size, -size, size);
    glMultiTexCoord2f(GL_TEXTURE0, 1, 0.0f); glMultiTexCoord2f(GL_TEXTURE1, 1, 0.0f); glVertex3f(size, -size, size);
    glMultiTexCoord2f(GL_TEXTURE0, 1, 1); glMultiTexCoord2f(GL_TEXTURE1, 1, 1); glVertex3f(size, size, size);
    glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 1); glMultiTexCoord2f(GL_TEXTURE1, 0.0f, 1); glVertex3f(-size, size, size);
    // Back Face
    glTexCoord2f(1, 0.0f); glVertex3f(-size, -size, -size);
    glTexCoord2f(1, 1); glVertex3f(-size, size, -size);
    glTexCoord2f(0.0f, 1); glVertex3f(size, size, -size);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(size, -size, -size);
    // Top Face
    glTexCoord2f(0.0f, 1); glVertex3f(-size, size, -size);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, size, size);
    glTexCoord2f(1, 0.0f); glVertex3f(size, size, size);
    glTexCoord2f(1, 1); glVertex3f(size, size, -size);
    // Bottom Face
    glTexCoord2f(1, 1); glVertex3f(-size, -size, -size);
    glTexCoord2f(0.0f, 1); glVertex3f(size, -size, -size);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(size, -size, size);
    glTexCoord2f(1, 0.0f); glVertex3f(-size, -size, size);
    // Right face
    glTexCoord2f(1, 0.0f); glVertex3f(size, -size, -size);
    glTexCoord2f(1, 1); glVertex3f(size, size, -size);
    glTexCoord2f(0.0f, 1); glVertex3f(size, size, size);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(size, -size, size);
    // Left Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, -size, -size);
    glTexCoord2f(1, 0.0f); glVertex3f(-size, -size, size);
    glTexCoord2f(1, 1); glVertex3f(-size, size, size);
    glTexCoord2f(0.0f, 1); glVertex3f(-size, size, -size);
    glEnd();
}

void Draw_Triangle() // This function draws a triangle with RGB colors
{
    //    glEnable(GL_COLOR_MATERIAL);
    //glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMateriali(GL_FRONT_AND_BACK,GL_SHININESS,100);
    
    glPushMatrix();
    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_TEXTURE_2D);//使用纹理
    if (selectMixTex) glBindTexture(GL_TEXTURE_2D, texNames[3]);//添加生成纹理
    else glBindTexture(GL_TEXTURE_2D, texNames[1]);//或者给茶壶添加纹理
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);//与光照混合
    glTranslatef(0, 0, 4+1);
    glRotatef(90, 1, 0, 0);
    glutSolidTeapot(1);
    glDisable(GL_TEXTURE_2D);//取消绑定纹理
    glPopMatrix();
    
    glPushMatrix();
    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_TEXTURE_2D);//使用纹理
    glBindTexture(GL_TEXTURE_2D, texNames[0]);//给桌面添加纹理
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);//与光照混合
    //第二号纹理
    glActiveTexture(GL_TEXTURE1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texNames[2]);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);
    glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_MODULATE);
    glTexEnvf(GL_TEXTURE_ENV, GL_SRC0_RGB, GL_TEXTURE);
    glTexEnvf(GL_TEXTURE_ENV, GL_OPERAND0_RGB, GL_SRC_COLOR);
    glTexEnvf(GL_TEXTURE_ENV, GL_SRC1_RGB, GL_PREVIOUS);
    glTexEnvf(GL_TEXTURE_ENV, GL_OPERAND1_RGB, GL_SRC_COLOR);
    glTranslatef(0, 0, 3.5);
    glScalef(5, 4, 1);
    solidCube(0.5);
    glDisable(GL_TEXTURE_2D);//取消绑定纹理
    glPopMatrix();
    
    glPushMatrix();
    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_TEXTURE_2D);//使用纹理
    glBindTexture(GL_TEXTURE_2D, texNames[0]);//给桌角1添加纹理
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);//与光照混合
    glTranslatef(1.5, 1, 1.5);
    Draw_Leg();
    glDisable(GL_TEXTURE_2D);//取消绑定纹理
    glPopMatrix();
    
    glPushMatrix();
    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_TEXTURE_2D);//使用纹理
    glBindTexture(GL_TEXTURE_2D, texNames[0]);//给桌角2添加纹理
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);//与光照混合
    glTranslatef(-1.5, 1, 1.5);
    Draw_Leg();
    glDisable(GL_TEXTURE_2D);//取消绑定纹理
    glPopMatrix();
    
    glPushMatrix();
    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_TEXTURE_2D);//使用纹理
    glBindTexture(GL_TEXTURE_2D, texNames[0]);//给桌角3添加纹理
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);//与光照混合
    glTranslatef(1.5, -1, 1.5);
    Draw_Leg();
    glDisable(GL_TEXTURE_2D);//取消绑定纹理
    glPopMatrix();
    
    glPushMatrix();
    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_TEXTURE_2D);//使用纹理
    glBindTexture(GL_TEXTURE_2D, texNames[0]);//给桌角4添加纹理
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);//与光照混合
    glTranslatef(-1.5, -1, 1.5);
    Draw_Leg();
    glDisable(GL_TEXTURE_2D);//取消绑定纹理
    glPopMatrix();
    
}

void Draw_Leg()
{
    glScalef(1, 1, 3);
    solidCube(0.5);
}

void updateView(int width, int height)
{
    glViewport(0,0,width,height);						// Reset The Current Viewport
    
    glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
    glLoadIdentity();									// Reset The Projection Matrix
    
    float whRatio = (GLfloat)width/(GLfloat)height;
    if (bPersp) {
        gluPerspective(45.0f, whRatio,0.1f,100.0f);
        //glFrustum(-3, 3, -3, 3, 3,100);
    } else {
        glOrtho(-3 ,3, -3, 3,-100,100);
    }
    
    glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
}

void reshape(int width, int height)
{
    if (height==0)										// Prevent A Divide By Zero By
    {
        height=1;										// Making Height Equal One
    }
    
    wHeight = height;
    wWidth = width;
    
    updateView(wHeight, wWidth);
}

void idle()
{
    glutPostRedisplay();
}

float eye[] = {0, 0, 8};
float center[] = {0, 0, 0};

void key(unsigned char k, int x, int y)
{
    switch(k)
    {
        case 27:
        case 'q': {exit(0); break; }
        case 'p': {bPersp = !bPersp; break; }
            
        case ' ': {bAnim = !bAnim; break;}
        case 'o': {bWire = !bWire; break;}
        
            
        case 'a': {
            eye[0] -= 0.2f;
            center[0] -= 0.2f;
            break;
        }
        case 'd': {
            eye[0] += 0.2f;
            center[0] += 0.2f;
            break;
        }
        case 'w': {
            eye[1] -= 0.2f;
            center[1] -= 0.2f;
            break;
        }
        case 's': {
            eye[1] += 0.2f;
            center[1] += 0.2f;
            break;
        }
        case 'z': {
            eye[2] -= 0.2f;
            center[2] -= 0.2f;
            break;
        }
        case 'c': {
            eye[2] += 0.2f;
            center[2] += 0.2f;
            break;
        }
        case 'i'://y++
            light_pos[1]+=light_delta;
            break;
        case 'k'://y--
            light_pos[1]-=light_delta;
            break;
        case 'j'://x--
            light_pos[0]-=light_delta;
            break;
        case 'l'://x++
            light_pos[0]+=light_delta;
            break;
        case 'm'://z++
            light_pos[2]+=light_delta;
            break;
        case 'n':
            light_pos[2]-=light_delta;
            break;
        case '1':
            light_choosen=0;
            break;
        case '2':
            light_choosen=1;
            break;
        case '3':
            light_choosen=2;
            break;
        case '4':
            light_choosen=3;
            break;
        case '5':
            light_choosen=4;
            break;
        case '='://enlarge angle
            angle +=delta_angle;
            printf("%f\n",angle);
            break;
        case '-':
            angle -=delta_angle;
            printf("%f\n",angle);
            break;
        case '`':
            selectMixTex=!selectMixTex;
            break;
    }
    
    updateView(wHeight, wWidth);
}
void specialKey(int key,int x,int y){
    switch (key) {
        case GLUT_KEY_UP:
            flash_pos[2]-=delta_pos;
            break;
        case GLUT_KEY_DOWN:
            flash_pos[2]+=delta_pos;
            break;
        case GLUT_KEY_LEFT:
            flash_pos[0]-=delta_pos;
            break;
        case GLUT_KEY_RIGHT:
            flash_pos[0]+=delta_pos;
            break;
        default:
            break;
    }
}

void redraw()
{
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();									// Reset The Current Modelview Matrix
    
    gluLookAt(eye[0], eye[1], eye[2],
              center[0], center[1], center[2],
              0, 1, 0);				// ≥°æ∞£®0£¨0£¨0£©µƒ ”µ„÷––ƒ (0,5,50)£¨Y÷·œÚ…œ
    
    if (bWire) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    
    //    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    //    glLightfv(GL_LIGHT0, GL_AMBIENT, white);
    //    glEnable(GL_LIGHT0);
    
    setLight();
    
    //	glTranslatef(0.0f, 0.0f,-6.0f);			// Place the triangle at Center
    glRotatef(fRotate, 0, 1.0f, 0);			// Rotate around Y axis
    glRotatef(-90, 1, 0, 0);
    glScalef(0.2, 0.2, 0.2);
    Draw_Triangle();						// Draw triangle
    
    if (bAnim) fRotate    += 0.5f;
    glutSwapBuffers();
}
void bindTex(){
    
    
    glGenTextures(1, texNames);
    glBindTexture(GL_TEXTURE_2D, texNames[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 texture1.getWidth(), texture1.getHeight(),
                 0, GL_RGB, GL_UNSIGNED_BYTE, texture1.getImage());
    glGenTextures(1, &texNames[1]);
    
    glBindTexture(GL_TEXTURE_2D, texNames[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 texture2.getWidth(), texture2.getHeight(),
                 0, GL_RGB, GL_UNSIGNED_BYTE, texture2.getImage());
    
    glGenTextures(1, &texNames[2]);
    glBindTexture(GL_TEXTURE_2D, texNames[2]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 texture3.getWidth(), texture3.getHeight(),
                 0, GL_RGB, GL_UNSIGNED_BYTE, texture3.getImage());
    
    madeMixImage();
    glGenTextures(1, &texNames[3]);
    glBindTexture(GL_TEXTURE_2D, texNames[3]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 64, 64,
                 0, GL_RGB, GL_UNSIGNED_BYTE, mixImage);
}
void init(){
    texture1.ReadImage();
    texture2.ReadImage();
    texture3.ReadImage();
    bindTex();
    Bitmap test = Bitmap("/Users/jiwentadashi/Desktop/test1.bmp");
    test.setFH(RealImage, 64, 64);
    test.setIH(RealImage, 64, 64);
    test.setImage(mixImage);
    test.WriteFile();
}

int main (int argc,  char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(480,480);
    int windowHandle = glutCreateWindow("Simple GLUT App");
    
    init();
    
    glutDisplayFunc(redraw);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(key);
    glutSpecialFunc(specialKey);
    glutIdleFunc(idle);
    
    glutMainLoop();
    return 0;
}


