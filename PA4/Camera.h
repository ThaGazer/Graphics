

#ifndef CAMERA_H
#define CAMERA_H

#include "Algebra.h"

#define DEFAULT_FOCUS_LENGTH 1
#define NEAR_PLANE 0.001
#define FAR_PLANE 30
#define VIEW_ANGLE 60.0

class Camera {
public:
	Camera();
	~Camera();
	void Reset();
	void Orient(Point& eye, Point& focus, Vector& up);
	void Orient(Point& eye, Vector& look, Vector& up);
	void SetViewAngle(double viewAngle);
	void SetNearPlane(double nearPlane);
	void SetFarPlane(double farPlane);
	void SetScreenSize(int screenWidth, int screenHeight);
	void SetLookDistance(double lookDistance);

	Matrix GetModelViewMatrix();
	//Matrix GetInvModelViewMatrix();
	Matrix GetProjectionMatrix();
	Matrix GetScaleMatrix();

	Matrix GetCamToWorld();
	void SetCamtoWorld();

	void RotateV(double angle);
	void RotateU(double angle);
	void RotateW(double angle);

	void Translate(const Vector &v);
	void Rotate(Point p, Vector axis, double degree);

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

private:
	Matrix m_modelView; //World to camera matrix
	Matrix m_invModelView; //camera to world matrix
	Matrix m_camtoWorld;
	//Matrix m_projection; //Projection matrix onto film plane.
	Vector m_n, m_u, m_v;  //n u v of the camera

	double m_viewAngle, m_filmPlanDepth;
	double m_nearPlane, m_farPlane;
	int m_screenWidth, m_screenHeight;
	double m_screenWidthRatio; // m_screenHeightRatio;
};
#endif

