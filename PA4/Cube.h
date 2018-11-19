#ifndef CUBE_H
#define CUBE_H

#include "Shape.h"


class Cube : public Shape {
public:
	Cube() {};
	~Cube() {};

	void draw() {
	};

	void drawNormal() {
	};

	double Intersect(Point eyePointP, Vector rayV, Matrix transformMatrix) {
		Matrix inverseTransform = invert(transformMatrix);
		Point eyePoint = inverseTransform * eyePointP;
		Vector ray = inverseTransform * rayV;

		double t = MIN_ISECT_DISTANCE;
		Point tmpP;//isect;

		for (int i = 0; i < 3; i++) {

			int a, b;
			if (i == 0) {
				a = 1;
				b = 2;
			}
			else if (i == 1) {
				a = 0;
				b = 2;
			}
			else if (i == 2) {
				a = 1;
				b = 0;
			}

			if (eyePoint[i] * ray[i] < 0) {
				double t1 = (-SIDELENGTH - eyePoint[i]) / ray[i];
				tmpP = eyePoint + t1 * ray;
				if ((tmpP[a] >= -SIDELENGTH) && (tmpP[a] <= SIDELENGTH) && (tmpP[b] >= -SIDELENGTH) && (tmpP[b] <= SIDELENGTH)) {
					if ((t1 > 0) && (t1 < t)) {
						t = t1;
					}
				}

				double t2 = (SIDELENGTH - eyePoint[i]) / ray[i];
				tmpP = eyePoint + t2 * ray;
				if ((tmpP[a] >= -SIDELENGTH) && (tmpP[a] <= SIDELENGTH) && (tmpP[b] >= -SIDELENGTH) && (tmpP[b] <= SIDELENGTH)) {
					if ((t2 > 0) && (t2 < t)) {
						t = t2;
					}
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

		if (IN_RANGE(normalVector[0], 0.5)) {
			normalVector[0] = 1; normalVector[1] = 0; normalVector[2] = 0;
		}
		else if (IN_RANGE(normalVector[0], -0.5)) {
			normalVector[0] = -1; normalVector[1] = 0; normalVector[2] = 0;
		}
		else if (IN_RANGE(normalVector[1], 0.5)) {
			normalVector[0] = 0; normalVector[1] = 1; normalVector[2] = 0;
		}
		else if (IN_RANGE(normalVector[1], -0.5)) {
			normalVector[0] = 0; normalVector[1] = -1; normalVector[2] = 0;
		}
		else if (IN_RANGE(normalVector[2], 0.5)) {
			normalVector[0] = 0; normalVector[1] = 0; normalVector[2] = 1;
		}
		else if (IN_RANGE(normalVector[2], -0.5)) {
			normalVector[0] = 0; normalVector[1] = 0; normalVector[2] = -1;
		}
		else {
			//printf ("something is wrong here in cube normalVector\n");
			//printf ("%lf, %lf, %lf\n", x_cord, y_cord, z_cord);
			//printf ("t: %lf\n", t);
		}

		return normalVector;
	};

private:
	double SIDELENGTH = 0.5;
};

#endif
