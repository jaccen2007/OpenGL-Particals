//
//  main.cpp
//  GraphicsFinal
//
//  Created by Steven Pantin on 4/21/16.
//  Copyright © 2016 Steven Pantin. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#ifdef __APPLE__
    #include <GLUI/glui.h>
#else
    #include <GL/glui.h>
#endif

#include "Camera.h"
#include <iostream>
#include "Object.hpp"
#include "Partical.hpp"
#include "ParticalRound.hpp"
#include "Physics.hpp"
#include "Bezier.hpp"
#include "Shape.h"
#include "Cone.h"
#include "Cube.h"
#include "Sphere.h"
#include "Cylinder.h"
#include <vector>
#include <cstdlib>
#include <ctime>

const float CAMERA_MOVE_INC = 0.2;
const float CAMERA_ZOOM_FACTOR = 1.5;
const float CAMERA_ROTATE_FACTOR = 2;
const int NUM_OF_PARTICALS = 200;
//const int NUM_OF_PARTICALS = 1;
std::vector<Vector> vectors;

ParticalRound *particals[NUM_OF_PARTICALS];
std::vector<ParticalRound> additionalParticals;

const std::vector<std::vector<BezierCalc*> > ColorTransitions{
    std::vector<BezierCalc*>{//yellow
         new BezierCalc(Point(1,1,1),Point(1,.8,0),Point(1,.2,0),Point(.5,0,0))
        ,new BezierCalc(Point(1,1,0),Point(1,.3,0),Point(.8,.2,0),Point(.5,0,0))
        ,new BezierCalc(Point(1,1,.2),Point(.8,.4,0),Point(.5,0,.5),Point(.5,0,0))
    }
    ,std::vector<BezierCalc*>{//blue
         new BezierCalc(Point(0,0,1),Point(1,.8,0),Point(1,.2,0),Point(.5,0,0))
        ,new BezierCalc(Point(.5,.5,1),Point(1,.3,0),Point(.8,.2,0),Point(.5,0,0))
        ,new BezierCalc(Point(.3,.4,.8),Point(.8,.4,0),Point(.5,0,.5),Point(.5,0,0))
    }
};
const std::vector<Shape*> shapes{
new Cube()
,new Cylinder()
,new Cone()
,new Sphere()
};

Shape* shape=shapes[0];


Camera* camera = new Camera();

Matrix shapeTransform(
1,0,0,2,
0,.5,0,1,
0,0,1,0,
0,0,0,1);

Matrix shapeTransformInv(
1,0,0,-2,
0,2,0,-1,
0,0,1,0,
0,0,0,1);

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
std::ostream& operator<<(std::ostream& os,Point& p){
    os<<"{"<<p[0]<<","<<p[1]<<","<<p[2]<<"}";
    return os;
}

Physics physics(Vector(7,2,0));

int main_window;
std::vector<ParticalRound*> particalsVec;

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
Point randColor(){
    int randVal=rand()%7;//all combinations of three 0's or 1's
    //except 111, white doesn't show well
    char midMask=3;//010
                       //get each bit, 0 or 1
    Point toReturn(randVal>>2,(randVal&midMask)>>1,(randVal&1));
    return toReturn;
}

void initVector(int i){
    //if(i==0) shape=shapes[rand()%shapes.size()];
    /*
    physics.setGravity(Vector(0,0,0));
    physics.setWind(Vector(0,0,0));
    particalsVec[i]->setLaunchVelocity(0);
    particalsVec[i]->setRadius(1);

    /*/
    //physics.setWind(Vector(7,0,-4));
    physics.setWind(Vector(0,0,0));
    particalsVec[i]->setColor(randColor());
        particalsVec[i]->setLaunchVector(Physics::getRandomVector(Vector(1,1,0),30));
        //particalsVec[i]->setLaunchVector(Physics::getRandomVector(Vector(1,.8,0),5));
    //particalsVec[i]->setLaunchVelocity(10);
    particalsVec[i]->setLaunchVelocity(((rand()%1000)/200.0)+3);
    //*/
    particalsVec[i]->colorTransitionCalc=ColorTransitions[0][rand()%ColorTransitions[0].size()];
}
bool collision(Point from,Vector direction,double& distance){
    bool toReturn=false;
    distance=shape->Intersect(from,direction,shapeTransform);
    if(distance>0&&distance<0.02){
        toReturn=true;
    }
    return toReturn;
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
    
    glColor3f(0,0,0);
    glutSolidCube(20);
    
    
    static int MAX_FRAMES=500;
    static float speed = 1.15;
    static float shrink = 0.00005;
    static float frameTimeStep= 0.003;//replace with chronos lib if lab comps support c++11
    frameCount++;
    if(frameCount%MAX_FRAMES==0){
        for(int i=0;i<NUM_OF_PARTICALS;i++){
            if(particalsVec[i]){
                delete particalsVec[i];
            }
            particalsVec[i]=new ParticalRound();
            initVector(i);
        }
        speed = 1.15;
        frameCount = 1;

    }

    for(int i=0;i<NUM_OF_PARTICALS;i++){
        if(particalsVec[i]->getRadius()>0&&particalsVec[i]->getLocation()[1]>0){
           particalsVec[i]->draw();
        }
        particalsVec[i]->updateTimeAlive(frameTimeStep);
        Point p=physics.calculatePosition(particalsVec[i]);
        particalsVec[i]->setPosition(p);
        double collisionDist;
        Vector movementVector=physics.getMovementVector(particalsVec[i]);
        Point fromPoint=particalsVec[i]->getPosition();
        //glLineWidth(3);
        //glPointSize(3);
        //glColor3f(1,0,0);
        //glBegin(GL_LINES);
        //glVertex3dv(fromPoint.unpack());
        movementVector.normalize();
        //Point toPoint=fromPoint+movementVector;
        //glVertex3dv((toPoint).unpack());
        //glEnd();
        if(collision(fromPoint,movementVector,collisionDist)){
            Vector normal=shape->findIsectNormal(shapeTransformInv*fromPoint,shapeTransformInv*movementVector,collisionDist);
            //Point intersect=fromPoint+movementVector*collisionDist;
            //glColor3f(1,1,1);
            //glTranslatef(intersect[0],intersect[1],intersect[2]);
            //glutSolidSphere(.01,5,5);
            //glTranslatef(-intersect[0],-intersect[1],-intersect[2]);
        //glColor3f(1,0,1);
        //glBegin(GL_LINES);
        //glVertex3dv(intersect.unpack());
        //glVertex3dv((intersect+normal).unpack());
        //glEnd();
            movementVector.normalize();
            Vector newLaunchVect=-physics.getReflectedRay(movementVector,normal);
        //glColor3f(0,1,0);
        //glBegin(GL_LINES);
        //glVertex3dv(intersect.unpack());
        //Point reflectedTo=intersect+newLaunchVect;
        //glVertex3dv((reflectedTo).unpack());
        //glEnd();
            newLaunchVect.normalize();
            particalsVec[i]->setLaunchVector(newLaunchVect);
            particalsVec[i]->setOrigin(particalsVec[i]->getLocation());
            double timeToCollision=particalsVec[i]->getTimeAlive();
            particalsVec[i]->resetTime();
            particalsVec[i]->setLaunchVelocity(particalsVec[i]->getLuanchVelocity()/(timeToCollision*10));

    //glColor3f(1,1,0);
    //glPushMatrix();
    //glMultMatrixd(shapeTransform.unpack());
    //shape->setSegments(20,20);
    //shape->draw();
    //glPopMatrix();
    //glutSwapBuffers();
    //glutPostRedisplay();
        }
        if(frameCount>100){
            particalsVec[i]->setRadius(particalsVec[i]->getRadius()-shrink);
        }
        particalsVec[i]->updateColor(double(frameCount)/double(MAX_FRAMES/2));
        //GDB 0 if wireframe == true
    }
    glColor3f(1,1,0);
    glPushMatrix();
    glMultMatrixd(shapeTransform.unpack());
    shape->setSegments(20,20);
    shape->draw();
    glPopMatrix();
    glutSwapBuffers();
    glutPostRedisplay();
    
    
    ///////////FIREWORKS//////////
    static float speed0 = 1.15;
    static float shrink0 = 0.00015;
    
    if(frameCount < 10){
        speed0 -= 0.0025;
    }
    if(frameCount < 30){
        speed0 -= 0.002;
    }
    if(frameCount > 40){
        speed0 -= 0.01;
    }
    
    
    if(speed0 < 1.001) speed0 = 1.001;
    
    
    for(int i=0; i<NUM_OF_PARTICALS; i++){
        Point o = particals[i]->getOrigin()*speed0;
        if(frameCount > 60){
            o[1] -= 0.005;
        }else{
            ParticalRound pp(o[0], o[1], o[2]);
            pp.setColor(particals[i]->getColor());
            additionalParticals.push_back(pp);
        }
        particals[i]->setOrigin(o);
        particals[i]->setRadius(particals[i]->getRadius()-shrink0);
        
        Point c = particals[i]->getColor();
        c[0] -= 0.09;
        c[1] -= 0.09;
        c[2] -= 0.09;
        
        particals[i]->setColor(c);
        particals[i]->draw();
    }
    
    for(int i=0; i<additionalParticals.size(); i++){
        additionalParticals[i].setRadius(additionalParticals[i].getRadius()-(shrink0*10));
        if(additionalParticals[i].getRadius() > 0){
            additionalParticals[i].draw();
        }
        
    }
    //////////////////////////

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
        if(particalsVec[i]){
            delete particalsVec[i];
        }
    }
    for(unsigned int i=0;i<ColorTransitions.size();i++){
        for(unsigned int j=0;j<ColorTransitions[i].size();j++){
            if(ColorTransitions[i][j]){
                delete ColorTransitions[i][j];
            }
        }
    }
    if(camera){
        delete camera;
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
    glColor3f( .2, .2, .2 );
    for(float i = 0 ; i < grid_size; i+=.2){
        glBegin(GL_LINES);
        glVertex3f( 0.0, 0.0, i );  glVertex3f( grid_size, 0.0, i );
        glVertex3f( i, 0.0, 0.0 );  glVertex3f( i, 0.0, grid_size );
        glEnd();
    }
    
    glBegin(GL_LINES);
    glVertex3f( 0.0, 0.0, grid_size );  glVertex3f( grid_size, 0.0, grid_size );
    glVertex3f( grid_size, 0.0, 0.0 );  glVertex3f( grid_size, 0.0, grid_size );
    glEnd();
    glPopMatrix();
    glEnable( GL_LIGHTING );
    
}

int main(int argc, char* argv[]){
    for(int i=0;i<100;i++){
        vectors.push_back(Physics::getRandomVector(Vector(1,1,1),30));
    }
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
    
    ///////SEED FIREWORKS///////
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
    /////////////////////////////
    
    srand (time(NULL));
    for(int i=0; i<NUM_OF_PARTICALS; i++){
        particalsVec.push_back(new ParticalRound());
        initVector(i);
    }
    
    
    glutMainLoop();
    
    return EXIT_SUCCESS;
    
}
