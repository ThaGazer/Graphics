#ifndef COHE_H
#define CONE_H

#include "Shape.h"

class Cone : public Shape {
public:
	Cone() {};
	~Cone() {};

	void draw() {
	};

	void drawNormal() {
	};

	double Intersect(Point eyePointP, Vector rayV, Matrix transformMatrix) {
		Matrix inverseTransform = invert(transformMatrix);
		Point eyePoint = inverseTransform * eyePointP;
		Vector ray = inverseTransform * rayV;

		double radiusSqr = RADIUS*RADIUS;
		double a = ray[0] * ray[0] + ray[2] * ray[2] - (radiusSqr*(ray[1] * ray[1]));
		double b = 2 * eyePoint[0] * ray[0] + 2 * eyePoint[2] * ray[2] + radiusSqr*ray[1] - RADIUS*eyePoint[1] * ray[1];
		double c = eyePoint[0] * eyePoint[0] + eyePoint[2] * eyePoint[2] + radiusSqr*eyePoint[1] - radiusSqr*eyePoint[1] * eyePoint[1] - radiusSqr*radiusSqr;
		double t = MIN_ISECT_DISTANCE;
		//Point isect;

		double det = b*b - 4 * a*c;
		if (det < 0) {
			t = -1;
		}
		else {
			double t1 = (-b - sqrt(det)) / (2 * a);
			double t2 = (-b + sqrt(det)) / (2 * a);

			double isectY2 = eyePoint[1] + t2 * ray[1];

			if (t1 > 0) {
				double isectY1 = eyePoint[1] + t1 * ray[1];
				if (!((isectY1 > -0.5) && (isectY1 < 0.5))) {
					t1 = -1;
				}
			}
			if (t2 > 0) {
				double isectY2 = eyePoint[1] + t2 * ray[1];
				if (!((isectY2 > -0.5) && (isectY2 < 0.5))) {
					t2 = -1;
				}
			}

			if ((t1 > 0) && (t2 > 0))
				t1 < t2 ? (t = t1) : (t = t2);
			else if (t1 < 0)
				t = t2;
			else if (t2 < 0)
				t = t1;
			else
				t = -1;
		}

		if (eyePoint[1] * ray[1] < 0) {
			double t1 = (-RADIUS - eyePoint[1]) / ray[1];
			Point tmpP = eyePoint + t1 * ray;
			if ((tmpP[0] * tmpP[0] + tmpP[2] * tmpP[2]) < radiusSqr) {
				if (((t1 > 0) && (t < 0)) || ((t1 > 0) && (t1 < t))) {
					t = t1;
				}
			}
		}

		//isect = eyePoint + t * ray;
		if (IN_RANGE(t, MIN_ISECT_DISTANCE))
			return -1;
		else
			return t;
	};

	Vector findIsectNormal(Point eyePoint, Vector ray, double dist) {
		Point tmpP = eyePoint + (dist * ray);
		Vector normalVector(tmpP[0], tmpP[1], tmpP[2]);

		if (IN_RANGE(normalVector[1], -0.5)) {
			normalVector[0] = 0; normalVector[1] = -1; normalVector[2] = 0;
		}
		else if ((normalVector[0] == 0) && (normalVector[2] == 0)) {
			normalVector[0] = 0; normalVector[1] = 1; normalVector[2] = 0;
		}
		else {
			normalVector[0] = 2 * normalVector[0];
			normalVector[1] = RADIUS * (RADIUS - normalVector[1]);
			normalVector[2] = 2 * normalVector[2];
		}

		return normalVector;
	};

private:
	double RADIUS = 0.5;
};

#endif
