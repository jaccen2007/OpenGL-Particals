//
//  main.cpp
//  GraphicsFinal
//
//  Created by Steven Pantin on 4/21/16.
//  Copyright © 2016 Steven Pantin. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
//#include <GLUI/glui.h>
#include <GL/glui.h>
#include "Camera.h"
#include <iostream>
#include "Object.hpp"
#include "Partical.hpp"
#include "ParticalRound.hpp"
#include "Kinematics.hpp"
#include <vector>

const float CAMERA_MOVE_INC = 0.2;
const float CAMERA_ZOOM_FACTOR = 1.5;
const float CAMERA_ROTATE_FACTOR = 2;
//const int NUM_OF_PARTICALS = 300;
const int NUM_OF_PARTICALS = 50;

bool showGrid = true;
bool debugMode = true;
bool wireframe = false;

int	 camRotU = 0;
int	 camRotV = 0;
int	 camRotW = 0;
int  viewAngle = 45;
float eyeX = 0;
float eyeY = 0.5;
float eyeZ = 5;
float lookX = 0;
float lookY = 0;
float lookZ = -1;
float clipNear = 0.001;
float clipFar = 30;

int main_window;
Camera* camera = new Camera();
ParticalRound *particals[NUM_OF_PARTICALS];
std::vector<ParticalRound> additionalParticals;

void myGlutIdle(void);
void myGlutDisplay(void);
void onExit(void);
void draw_grid();
void myGlutReshape(int x, int y);
void myKeyboardFunc(unsigned char key, int x, int y);
void myKeyboardSpecFunc(int key, int x, int y);
void displayText( float x, float y, int r, int g, int b, const char *string );


void displayText( float x, float y, int r, int g, int b, const char *string ) {
    int j = strlen( string );
    
    glColor3f( r, g, b );
    glRasterPos2f( x, y );
    for( int i = 0; i < j; i++ ) {
        glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, string[i] );
    }
}

void myGlutIdle(void){
    if(glutGetWindow() != main_window) glutSetWindow(main_window);
    glutPostRedisplay();
}

void myGlutDisplay(void){
    static long frameCount = 1;
    
    if(wireframe){
        glDisable(GL_POLYGON_OFFSET_FILL);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }else{
        glEnable(GL_POLYGON_OFFSET_FILL);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    
    glClearColor(.9f, .9f, .9f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    camera->SetViewAngle(viewAngle);
    camera->SetNearPlane(clipNear);
    camera->SetFarPlane(clipFar);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    Matrix projection = camera->GetProjectionMatrix();
    glMultMatrixd(projection.unpack());
    
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    Point eyeP(eyeX, eyeY, eyeZ);
    Vector lookV(lookX, lookY, lookZ);
    Vector upV(0, 1, 0);
    camera->Orient(eyeP, lookV, upV);
    camera->RotateV(camRotV);
    camera->RotateU(camRotU);
    camera->RotateW(camRotW);
    Matrix modelView = camera->GetModelViewMatrix();
    glMultMatrixd(modelView.unpack());
    
    
    camera->RotateV(-camRotV);
    camera->RotateU(-camRotU);
    camera->RotateW(-camRotW);
    
    
    static float speed = 1.15;
    static float shrink = 0.00015;
    
    if(frameCount < 10){
        speed -= 0.0025;
    }
    if(frameCount < 30){
        speed -= 0.002;
    }
    if(frameCount > 40){
        speed -= 0.01;
    }
    
    
    if(speed < 1.001) speed = 1.001;
    
    for(int i=0; i<NUM_OF_PARTICALS; i++){
        Point o = particals[i]->getOrigin()*speed;
        if(frameCount > 60){
            o[1] -= 0.005;
        }else{
            ParticalRound pp(o[0], o[1], o[2]);
            pp.setColor(particals[i]->getColor());
            additionalParticals.push_back(pp);
        }
        particals[i]->setOrigin(o);
        particals[i]->setRadius(particals[i]->getRadius()-shrink);
        
        Point c = particals[i]->getColor();
        c[0] -= 0.09;
        c[1] -= 0.09;
        c[2] -= 0.09;
        
        particals[i]->setColor(c);
        particals[i]->draw();
    }
    
    for(int i=0; i<additionalParticals.size(); i++){
        additionalParticals[i].setRadius(additionalParticals[i].getRadius()-(shrink*10));
        if(additionalParticals[i].getRadius() > 0){
            additionalParticals[i].draw();
        }

    }
    
    
    if(debugMode){
        //TODO: fix text display
        //displayText( 50,50, 255,0,0, "debug" );
        draw_grid();
        //drawing the axes
        glDisable(GL_LIGHTING);
        glLineWidth(4);
        glBegin(GL_LINES);
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(0, 0, 0); glVertex3f(1.0, 0, 0);
        glColor3f(0.0, 1.0, 0.0);
        glVertex3f(0, 0, 0); glVertex3f(0.0, 1.0, 0);
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(0, 0, 0); glVertex3f(0, 0, 1.0);
        glEnd();
        glLineWidth(1);
        glEnable(GL_LIGHTING);
    }
    
    frameCount++;
    if(frameCount%200 ==0){
        speed = 1.15;
        frameCount = 1;
        Point cc(Point( ((double)rand()/(RAND_MAX))*10.0, ( (double)rand()/(RAND_MAX) )*10.0, ((double) rand() / (RAND_MAX))*10.0));
        
        int tries = 0;
        for(int i=0; i<NUM_OF_PARTICALS; i++){
            Point oo((((double) rand() / (RAND_MAX)) -0.5)/10.0, ((((double) rand() / (RAND_MAX)) -0.5)/10.0), ((((double) rand() / (RAND_MAX)) -0.5)/10.0));
            
            if((oo[0]*oo[0] + oo[1]*oo[1] + oo[2]*oo[2]) < particals[0]->getRadius()*particals[0]->getRadius()){
                particals[i] = new ParticalRound(oo[0], oo[1], oo[2]);
                particals[i]->setColor(cc);
            }else{
                if(tries++ < 70){
                    i--;
                }else{
                    particals[i] = new ParticalRound(oo[0], oo[1], oo[2]);
                    particals[i]->setColor(cc);
                    tries = 0;
                }
            }
            
        }
        additionalParticals.erase(additionalParticals.begin(), additionalParticals.end());
    }
    
    //std::cout << additionalParticals.size() << std::endl;
    
    glutSwapBuffers();
    glutPostRedisplay();
}

void myKeyboardSpecFunc(int key, int x, int y){
    
    switch(key){
        case GLUT_KEY_UP: camRotU+=CAMERA_ROTATE_FACTOR;
            break;
        case GLUT_KEY_DOWN: camRotU-=CAMERA_ROTATE_FACTOR;
            break;
        case GLUT_KEY_LEFT: camRotV+=CAMERA_ROTATE_FACTOR;
            break;
        case GLUT_KEY_RIGHT: camRotV-=CAMERA_ROTATE_FACTOR;
            break;
    }
    
    
    glutPostRedisplay();
}

void myKeyboardFunc(unsigned char key, int x, int y){
    //std::cout << "key: " << key << "\nx: " << x << "\ny: " << y << std::endl;
    
    
    /*
     w - shift camera up
     s - shift camera down
     d - shift camera right
     a - shift camera left
     r - shift camera forward
     f - shift camera back
     + - zoom in
     - - zoom out
     */
    switch(key){
        case '0': debugMode = (debugMode)? false:true;
            break;
            
        case 'w': eyeY += CAMERA_MOVE_INC;
            break;
            
        case 's': eyeY -= CAMERA_MOVE_INC;
            break;
            
        case 'a': eyeX -= CAMERA_MOVE_INC;
            break;
            
        case 'd': eyeX += CAMERA_MOVE_INC;
            break;
            
        case 'r': eyeZ -= CAMERA_MOVE_INC;
            break;
            
        case 'f': eyeZ += CAMERA_MOVE_INC;
            break;
            
        case '+': eyeX /= CAMERA_ZOOM_FACTOR;
                  eyeY /= CAMERA_ZOOM_FACTOR;
                  eyeZ /= CAMERA_ZOOM_FACTOR;
            break;
            
        case '-': eyeX *= CAMERA_ZOOM_FACTOR;
                  eyeY *= CAMERA_ZOOM_FACTOR;
                  eyeZ *= CAMERA_ZOOM_FACTOR;
            break;
            
        case ' ': camRotV=0;
                  camRotU=0;
            break;
            
        case 'q': wireframe = (wireframe)? false:true;
            break;
    }
    
    glutPostRedisplay();
}

void onExit(void){
    for(int i=0;i<NUM_OF_PARTICALS;i++){
        delete particals[i];
    }
    
}

void myGlutReshape(int x, int y){
    float xy_aspect;
    
    xy_aspect = (float)x / (float)y;
    glViewport(0, 0, x, y);
    
    camera->SetScreenSize(x, y);
    
    glutPostRedisplay();
}

void draw_grid(){
    int grid_size = 20;
    glDisable(GL_LIGHTING);
    glPushMatrix();
    glTranslatef(-grid_size/2,0,-grid_size/2);
    for(float i = 0 ; i < grid_size; i+=.2){
        glBegin(GL_LINES);
        glColor3f( 1.0, 1.0, 1.0 );
        glVertex3f( 0.0, 0.0, i );  glVertex3f( grid_size, 0.0, i );
        glVertex3f( i, 0.0, 0.0 );  glVertex3f( i, 0.0, grid_size );
        glEnd();
    }
    
    glBegin(GL_LINES);
    glColor3f( 1.0, 1.0, 1.0 );
    glVertex3f( 0.0, 0.0, grid_size );  glVertex3f( grid_size, 0.0, grid_size );
    glVertex3f( grid_size, 0.0, 0.0 );  glVertex3f( grid_size, 0.0, grid_size );
    glEnd();
    glPopMatrix();
    glEnable( GL_LIGHTING );
    
}

int main(int argc, char* argv[]){
    atexit(onExit);
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 600);
    
    main_window = glutCreateWindow("Graphics Final");
    glutDisplayFunc(myGlutDisplay);
    glutReshapeFunc(myGlutReshape);
    glutKeyboardFunc(myKeyboardFunc);
    glutSpecialFunc(myKeyboardSpecFunc);

    
    glClearColor (0.48, 0.48, 0.48, 0.0);
    glShadeModel (GL_SMOOTH);
    
    GLfloat light_pos0[] = {0.0f, 0.0f, 1.0f, 0.0f};
    GLfloat diffuse[] = {0.5f, 0.5f, 0.5f, 0.0f};
    GLfloat ambient[] = {0.05f, 0.05f, 0.05f, 0.0f};
    
    glLightfv (GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv (GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv (GL_LIGHT0, GL_POSITION, light_pos0);
    
    glColorMaterial (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable (GL_COLOR_MATERIAL);
    
    glEnable(GL_LIGHTING);
    glEnable (GL_LIGHT0);
    glEnable (GL_DEPTH_TEST);

    glPolygonOffset(1, 1);
    
    
    srand (time(NULL));
    particals[0] =  new ParticalRound();
    for(int i=0; i<NUM_OF_PARTICALS; i++){
        
        Point oo((((double) rand() / (RAND_MAX)) -0.5)/10.0, ((((double) rand() / (RAND_MAX)) -0.5)/10.0), ((((double) rand() / (RAND_MAX)) -0.5)/10.0));
        
        if((oo[0]*oo[0] + oo[1]*oo[1] + oo[2]*oo[2]) < particals[0]->getRadius()*particals[0]->getRadius()){
            particals[i] = new ParticalRound(oo[0], oo[1], oo[2]);
            particals[i]->setColor(Point(10,0,0));
        }else{
            i--;
        }
        
        
        
    }
    
    
    glutMainLoop();
    
    return EXIT_SUCCESS;
    
}
