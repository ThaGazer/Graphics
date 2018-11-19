#include "Camera.h"

Camera::Camera() {
}

Camera::~Camera() {
}

void Camera::Orient(Point& eye, Point& focus, Vector& up) {
	this->Orient(eye, (focus - eye), up);
}


void Camera::Orient(Point& eye, Vector& look, Vector& up) {
	this->eye = eye;
	this->look = normalize(look);
//	normalize(this->look);
	this->up = normalize(up);
	normalize(up);
	this->w = -this->look;
	normalize(w);
	this->u = cross(look, normalize(up));
	normalize(u);
	this->v = cross(w, u);
	normalize(v);

	wtc = Matrix(this->u[x], this->u[y], this->u[z], 0,
		this->v[x], this->v[y], this->v[z], 0,
		this->w[x], this->w[y], this->w[z], 0,
		0, 0, 0, 1) *
		Matrix(inv_trans_mat(Vector(this->eye[x], this->eye[y], this->eye[z])));
}

Matrix Camera::GetProjectionMatrix() {
	double angle = (this->GetViewAngle()*PI*RAD) / (2*PI);
	double hei = tan(angle)*this->GetFarPlane();
	double wid = hei * this->GetScreenWidthRatio();
	double hinge = -this->GetNearPlane() / this->GetFarPlane();

	return Matrix(1,0,0,0,
				  0,1,0,0,
				  0,0,(-1/(hinge+1)),(hinge/(hinge+1)),
				  0,0,-1,0) * 
		   Matrix((1.0/hei),0,0,0,
			      0,(1.0/wid),0,0,
			      0,0,(1.0/this->GetFarPlane()),0,
			      0,0,0,1);
}


void Camera::SetViewAngle (double viewAngle) {
	this->vAngle = viewAngle;
}

void Camera::SetNearPlane (double nearPlane) {
	this->nPlane = nearPlane;
}

void Camera::SetFarPlane (double farPlane) {
	this->fPlane = farPlane;
}

void Camera::SetScreenSize (int screenWidth, int screenHeight) {
	this->scrnW = screenWidth;
	this->scrnH = screenHeight;
}

Matrix Camera::GetModelViewMatrix() {
	return wtc;
}

void Camera::RotateV(double angle) {
	Rotate(this->GetEyePoint(), this->GetUpVector(), angle);
}

void Camera::RotateU(double angle) {
	Rotate(this->GetEyePoint(),normalize(cross(this->GetLookVector(), this->GetUpVector())), angle);
}

void Camera::RotateW(double angle) {
	Rotate(this->GetEyePoint(), this->GetLookVector(), angle);
}

void Camera::Translate(const Vector &v) {
	//does anyone even use this
}


void Camera::Rotate(Point p, Vector axis, double degrees) {
	wtc = wtc * inv_rot_mat(p, axis, (degrees * RAD));
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
	return vAngle;
}

double Camera::GetNearPlane() {
	return nPlane;
}

double Camera::GetFarPlane() {
	return fPlane;
}

int Camera::GetScreenWidth() {
	return scrnW;
}

int Camera::GetScreenHeight() {
	return scrnH;
}

double Camera::GetFilmPlanDepth() {
	return GetFarPlane()-GetNearPlane();
}

double Camera::GetScreenWidthRatio() {
	return GetScreenWidth()/GetScreenHeight();
}
