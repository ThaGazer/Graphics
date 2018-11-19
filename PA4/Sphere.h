#ifndef SPHERE_H
#define SPHERE_H

#include "Shape.h"

class Sphere : public Shape {
public:
	Sphere() {};
	~Sphere() {};

	void draw() {
	};

	void drawNormal() {
	};

	double Intersect(Point eyePointP, Vector rayV, Matrix transformMatrix) {
		Matrix inverseTransform = invert(transformMatrix);
		Point eyePoint = inverseTransform * eyePointP;
		Vector ray = inverseTransform * rayV;

		double t = MIN_ISECT_DISTANCE;
		double a = ray[0] * ray[0] + ray[1] * ray[1] + ray[2] * ray[2];
		double b = 2 * (ray[0] * eyePoint[0] + ray[1] * eyePoint[1] + ray[2] * eyePoint[2]);
		double c = eyePoint[0] * eyePoint[0] + eyePoint[1] * eyePoint[1] + eyePoint[2] * eyePoint[2] - RADIUS * RADIUS;

		double det = b*b - 4 * a*c;
		if (det < 0) {
			return -1;
		}

		double t1 = (-b - sqrt(det)) / (2 * a);
		double t2 = (-b + sqrt(det)) / (2 * a);

		if ((t1 > 0) && (t2 > 0))
			t1 < t2 ? (t = t1) : (t = t2);
		else if (t1 < 0)
			t = t2;
		else if (t2 < 0)
			t = t1;
		else
			return -1;

		return t;
	};

	Vector findIsectNormal(Point eyePoint, Vector ray, double dist) {
		Point tmpP = eyePoint + dist * ray;
		Vector normalVector(tmpP[0], tmpP[1], tmpP[2]);
		return normalVector;
	};

private:
	double RADIUS = 0.5;
};

#endif
