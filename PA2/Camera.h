

#ifndef CAMERA_H
#define CAMERA_H

#include "Algebra.h"

class Camera {
private:
	int x = 0, y = 1, z = 2;
	int scrnW, scrnH;
	double vAngle, nPlane, fPlane;
	Point eye, focus;
	Vector look, up, u, v, w;
	Matrix wtc;
public:
	Camera();
	~Camera();
	void Orient(Point& eye, Point& focus, Vector& up);
	void Orient(Point& eye, Vector& look, Vector& up);
	void SetViewAngle (double viewAngle);
	void SetNearPlane (double nearPlane);
	void SetFarPlane (double farPlane);
	void SetScreenSize (int screenWidth, int screenHeight);

	Matrix GetProjectionMatrix();
	Matrix GetModelViewMatrix();

	void RotateV(double angle);
	void RotateU(double angle);
	void RotateW(double angle);
	void Rotate(Point p, Vector axis, double degree);
	void Translate(const Vector &v);

	Point GetEyePoint();
	Vector GetLookVector();
	Vector GetUpVector();
	double GetViewAngle();
	double GetNearPlane();
	double GetFarPlane();
	int GetScreenWidth();
	int GetScreenHeight();

	double GetFilmPlanDepth();
	double GetScreenWidthRatio();
};
#endif

