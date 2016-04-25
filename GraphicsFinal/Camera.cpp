
#include "Camera.h"

Camera::Camera() {
}

Camera::~Camera() {
}

void Camera::Orient(Point& eye, Point& focus, Vector& up) {

    this->eye = eye;
    look = focus - eye;
    this->up = up;
    
    look.normalize();
    w = look;
    w.negate();
    
    u = cross(up, w);
    v = cross(w, u);
    
    u.normalize();
    v.normalize();
}

void Camera::Orient(Point& eye, Vector& look, Vector& up) {
 
    this->eye = eye;
    this->look = look;
    this->up = up;
    
    this->look.normalize();
    w = Vector(this->look);
    w.negate();
    
    u = cross(up, w);
    v = cross(w, u);
    
    u.normalize();
    v.normalize();
}

Matrix Camera::GetOrthographicProjection(){
    
    double left = -1.0;
    double right = 1.0;
    double top = 1.0;
    double bottom = -1.0;
    
    double x = 2.0/(right-left);
    double y = 2.0/(top-bottom);
    double z = -2.0/(Far-Near);
    
    double sx = -((right+left)/(right-left));
    double sy = -((top+bottom)/(top-bottom));
    double sz = -((Far+Near)/(Far-Near));
    
    Matrix M(x, 0, 0, sx,
             0, y, 0, sy,
             0, 0, z, sz,
             0, 0, 0,  1);
    
    return M;
}

Matrix Camera::GetProjectionMatrix() {
    double c = -Near / Far;
    double a = -1.0/(c+1.0);
    double b = c/(c+1.0);
    
    Matrix M = Matrix(1, 0,  0, 0,
                      0, 1,  0, 0,
                      0, 0,  a, b,
                      0, 0, -1, 0);
    
    
    
    double sx = 1.0/(tan(DEG_TO_RAD(view*width/height/2))*Far);
    double sy = 1.0/(tan(DEG_TO_RAD(view/2))*Far);
    double sz = 1.0/Far;
    
    Matrix S = Matrix(sx,  0,  0,  0,
                       0, sy,  0,  0,
                       0,  0, sz,  0,
                       0,  0,  0,  1);
    return M * S;
}

void Camera::SetViewAngle (double viewAngle) {
    view = viewAngle;
}

void Camera::SetNearPlane (double nearPlane) {
    Near = nearPlane;
}

void Camera::SetFarPlane (double farPlane) {
    Far = farPlane;
}

void Camera::SetScreenSize (int screenWidth, int screenHeight) {
    width = screenWidth;
    height = screenHeight;
}

Matrix Camera::GetModelViewMatrix() {
    Matrix M(u[0], u[1], u[2], 0,
             v[0], v[1], v[2], 0,
             w[0], w[1], w[2], 0,
                0,    0,    0, 1);
    
    Matrix trans_eye = trans_mat(Vector(-eye[0],-eye[1],-eye[2]));
    
    return M*trans_eye;
}

void Camera::RotateV(double angle) {
    double theta = DEG_TO_RAD(angle);
    Matrix rotateVtheta = rot_mat(v, theta);
    
    u = rotateVtheta * u;
    w = rotateVtheta * w;
    look = rotateVtheta * look;
}

void Camera::RotateU(double angle) {
    double theta = DEG_TO_RAD(angle);
    Matrix rotateUtheta = rot_mat(u, theta);
    
    v = rotateUtheta * v;
    w = rotateUtheta * w;
    look = rotateUtheta * look;
}

void Camera::RotateW(double angle) {
    double theta = DEG_TO_RAD(angle);
    Matrix rotateWtheta = rot_mat(w, theta);
    
    v = rotateWtheta * v;
    u = rotateWtheta * u;

}

void Camera::Translate(const Vector &v) {
    eye = eye +v;
}

void Camera::Rotate(Point p, Vector axis, double degrees) {
    double theta = DEG_TO_RAD(degrees);
    Matrix rotationM = rot_mat(p, axis, theta);
    
    u = rotationM * u;
    v = rotationM * v;
    w = rotationM * w;
    
    look = rotationM * look;
}

Point Camera::GetEyePoint() {
    return eye;
}

Vector Camera::GetLookVector() {
    return look;
}

Vector Camera::GetUpVector() {
    return up;
}

double Camera::GetViewAngle() {
    return view;
}

double Camera::GetNearPlane() {
	return Near;
}

double Camera::GetFarPlane() {
	return Far;
}

int Camera::GetScreenWidth() {
	return width;
}

int Camera::GetScreenHeight() {
	return height;
}

double Camera::GetFilmPlanDepth() {
	return Far-Near;
}

double Camera::GetScreenWidthRatio() {
	return width/height;
}



