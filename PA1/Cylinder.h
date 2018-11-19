#ifndef CYLINDER_H
#define CYLINDER_H

#include "Shape.h"
#include "stdio.h"

class Cylinder : public Shape {
public:
	Cylinder() {};
	~Cylinder() {};

	void draw() {
		//starting value of theta
		float theta = 0.0;

		//delta change for theta
		float d_theta = (2 * PI) / m_segmentsX;

		//radius to draw around
		float radius = 0.5;

		glBegin(GL_TRIANGLES);
		for (int i = 0; i < m_segmentsX + 1; i++) {
			//increment to the next theta
			theta = d_theta * i;

			//calculations to stop repeating calculation
			float rCos = radius*cos(theta);
			float rSin = radius*sin(theta);
			float rdCos = radius*cos(theta + d_theta);
			float rdSin = radius*sin(theta + d_theta);

			//base
			//    p1
			//   /  \
			//  /    \
			// p2-----p3
			
			//bottom
			//p2
			glNormal3f(rCos, -radius, rSin);
			glVertex3f(rCos, -radius, rSin);
			
			//p1
			glNormal3f(0, -radius, 0);
			glVertex3f(0, -radius, 0);

			//p3
			glNormal3f(rdCos, -radius, rdSin);
			glVertex3f(rdCos, -radius, rdSin);

			//top
			//p2
			glNormal3f(rCos, radius, rSin);
			glVertex3f(rCos, radius, rSin);

			//p1
			glNormal3f(0, radius, 0);
			glVertex3f(0, radius, 0);

			//p3
			glNormal3f(rdCos, radius, rdSin);
			glVertex3f(rdCos, radius, rdSin);

			float height = -radius;
			float d_height = (radius*2/m_segmentsY);
			for (int j = 0; j < m_segmentsY; j++) {
				//tile
				// p5----p3-p4 
				// |       / |
				// |    /    |
				// | /       |
				// p1-p6----p2

				//right
				//p1
				glNormal3f(rCos, height, rSin);
				glVertex3f(rCos, height, rSin);

				//p2
				glNormal3f(rdCos, height, rdSin);
				glVertex3f(rdCos, height, rdSin);

				//p3
				glNormal3f(rCos, height+d_height, rSin);
				glVertex3f(rCos, height+d_height, rSin);

				//left
				//p4
				glNormal3f(rCos, height+d_height, rSin);
				glVertex3f(rCos, height+d_height, rSin);

				//p5
				glNormal3f(rdCos, height+d_height, rdSin);
				glVertex3f(rdCos, height+d_height, rdSin);

				//p6
				glNormal3f(rdCos, height, rdSin);
				glVertex3f(rdCos, height, rdSin);

				height += d_height;
			}
		}
		glEnd();
	};

	void drawNormal() {
		float theta = 0.0;
		float d_theta = (2 * PI) / m_segmentsX;
		float radius = 0.5;


		glBegin(GL_LINES);

		for (int i = 0; i < m_segmentsX + 1; i++) {
			theta = d_theta * i;
			float rCos = radius*cos(theta);
			float rSin = radius*sin(theta);
			float rdCos = radius*cos(theta + d_theta);
			float rdSin = radius*sin(theta + d_theta);

			//bottom
			//p2
			glVertex3f(rCos, -radius, rSin);
			glVertex3f(rCos*1.5, -radius*1.5, rSin*1.5);

			//p1
			glVertex3f(0, -radius, 0);
			glVertex3f(0, -radius*1.5, 0);


			//p3
			glVertex3f(rdCos, -radius, rdSin);
			glVertex3f(rdCos*1.5, -radius*1.5, rdSin*1.5);

			//top
			//p2
			glVertex3f(rCos, radius, rSin);
			glVertex3f(rCos*1.5, radius*1.5, rSin*1.5);


			//p1
			glVertex3f(0, radius, 0);
			glVertex3f(0, radius*1.5, 0);

			//p3
			glVertex3f(rdCos, radius, rdSin);
			glVertex3f(rdCos*1.5, radius*1.5, rdSin*1.5);

			float height = -radius;
			float d_height = (radius * 2 / m_segmentsY);
			for (int j = 0; j < m_segmentsY; j++) {
				//Tile
				//right
				//p1
				glVertex3f(rCos, height, rSin);
				glVertex3f(rCos*1.5, height*1.5, rSin*1.5);

				//p2
				glVertex3f(rdCos, height, rdSin);
				glVertex3f(rdCos*1.5, height*1.5, rdSin*1.5);

				//p3
				glVertex3f(rCos, height + d_height, rSin);
				glVertex3f(rCos*1.5, height + d_height*1.5, rSin*1.5);

				//left
				//p4
				glVertex3f(rCos, height + d_height, rSin);
				glVertex3f(rCos*1.5, height + d_height*1.5, rSin*1.5);

				//p5
				glVertex3f(rdCos, height + d_height, rdSin);
				glVertex3f(rdCos*1.5, height + d_height*1.5, rdSin*1.5);

				//p6
				glVertex3f(rdCos, height, rdSin);
				glVertex3f(rdCos*1.5, height*1.5, rdSin*1.5);

				height += d_height;
			}
		}
		glEnd();
	};
};
#endif
