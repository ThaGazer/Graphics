#ifndef COHE_H
#define CONE_H

#include "Shape.h"

class Cone : public Shape {
public:
	Cone() {};
	~Cone() {};

	void draw() {
		//initial value for theta
		float theta = 0.0;

		//delta change for theta
		float d_theta = (2 * PI) / m_segmentsX;

		//radius to draw around
		float radius = 0.5;


		glBegin(GL_TRIANGLES);
		for (int i = 0; i < m_segmentsX; i++) {
			theta = d_theta * i;
			radius = 0.5;

			//base
			//    p1
			//   /  \
			//  /    \
			// p2-----p3

			//p2
			glNormal3f(radius*cos(theta), -radius, radius*sin(theta));
			glVertex3f(radius*cos(theta), -radius, radius*sin(theta));

			//p1
			glNormal3f(0, -radius, 0);
			glVertex3f(0, -radius, 0);

			//p3
			glNormal3f(radius*cos(theta + d_theta), -radius, radius*sin(theta + d_theta));
			glVertex3f(radius*cos(theta + d_theta), -radius, radius*sin(theta + d_theta));


			float height = -radius;
			float d_height = radius*2 / m_segmentsY;
			float d_radius = radius / m_segmentsY;
			for (int j = 0; j < m_segmentsY-1; j++) {
				//box
				// p5----p3-p6 
				// |        /|
				// |     /   |
				// |  /      |
				// p1-p4----p2

				//bottom
				//p1
				glNormal3f(radius*cos(theta), height, radius*sin(theta));
				glVertex3f(radius*cos(theta), height, radius*sin(theta));

				//p2
				glNormal3f(radius*cos(theta + d_theta), height, radius*sin(theta + d_theta));
				glVertex3f(radius*cos(theta + d_theta), height, radius*sin(theta + d_theta));

				//p3
				glNormal3f((radius - d_radius)*cos(theta + d_theta), height + d_height, (radius - d_radius)*sin(theta + d_theta));
				glVertex3f((radius - d_radius)*cos(theta + d_theta), height + d_height, (radius - d_radius)*sin(theta + d_theta));

				//top
				//p4
				glNormal3f((radius - d_radius)*cos(theta + d_theta), height + d_height, (radius - d_radius)*sin(theta + d_theta));
				glVertex3f((radius - d_radius)*cos(theta + d_theta), height + d_height, (radius - d_radius)*sin(theta + d_theta));

				//p5
				glNormal3f((radius - d_radius)*cos(theta), height + d_height, (radius - d_radius)*sin(theta));
				glVertex3f((radius - d_radius)*cos(theta), height + d_height, (radius - d_radius)*sin(theta));

				//p6
				glNormal3f(radius*cos(theta), height, radius*sin(theta));
				glVertex3f(radius*cos(theta), height, radius*sin(theta));

				//increment height
				height += d_height;

				//decrease radius
				radius -= d_radius;
			}

			//top
			//    p1
			//   /  \
            //  /    \
			// p2-----p3

			//p1
			glNormal3f(radius*cos(theta), height, radius*sin(theta));
			glVertex3f(radius*cos(theta), height, radius*sin(theta));

			//p2
			glNormal3f(radius*cos(theta + d_theta), height, radius*sin(theta + d_theta));
			glVertex3f(radius*cos(theta + d_theta), height, radius*sin(theta + d_theta));

			//p3
			glNormal3f(0, height + d_height, 0);
			glVertex3f(0, height + d_height, 0);
		}
		glEnd();
	};

	void drawNormal() {
		//initial value for theta
		float theta = 0.0;

		//delta change for theta
		float d_theta = (2 * PI) / m_segmentsX;

		//radius to draw around
		float radius = 0.5;


		glBegin(GL_TRIANGLES);
		for (int i = 0; i < m_segmentsX; i++) {
			theta = d_theta * i;
			radius = 0.5;

			//base
			//    p1
			//   /  \
			//  /    \
			// p2-----p3

			//p2
			glVertex3f(radius*cos(theta), -radius, radius*sin(theta));
			glVertex3f(radius*cos(theta)*1.5, -radius*1.5, radius*sin(theta)*1.5);

			//p1
			glVertex3f(0, -radius, 0);
			glVertex3f(0, -radius*1.5, 0);

			//p3
			glVertex3f(radius*cos(theta + d_theta), -radius, radius*sin(theta + d_theta));
			glVertex3f(radius*cos(theta + d_theta)*1.5, -radius*1.5, radius*sin(theta + d_theta)*1.5);


			float height = -radius;
			float d_height = radius * 2 / m_segmentsY;
			float d_radius = radius / m_segmentsY;
			for (int j = 0; j < m_segmentsY - 1; j++) {
				//box
				// p5----p3-p6 
				// |        /|
				// |     /   |
				// |  /      |
				// p1-p4----p2

				//bottom
				//p1
				glVertex3f(radius*cos(theta), height, radius*sin(theta));
				glVertex3f(radius*cos(theta)*1.5, height*1.5, radius*sin(theta)*1.5);

				//p2
				glVertex3f(radius*cos(theta + d_theta), height, radius*sin(theta + d_theta));
				glVertex3f(radius*cos(theta + d_theta)*1.5, height*1.5, radius*sin(theta + d_theta)*1.5);

				//p3
				glVertex3f((radius - d_radius)*cos(theta + d_theta), height + d_height, (radius - d_radius)*sin(theta + d_theta));
				glVertex3f((radius - d_radius)*cos(theta + d_theta)*1.5, height + d_height*1.5, (radius - d_radius)*sin(theta + d_theta)*1.5);

				//top
				//p4
				glVertex3f((radius - d_radius)*cos(theta + d_theta), height + d_height, (radius - d_radius)*sin(theta + d_theta));
				glVertex3f((radius - d_radius)*cos(theta + d_theta)*1.5, height + d_height*1.5, (radius - d_radius)*sin(theta + d_theta)*1.5);

				//p5
				glVertex3f((radius - d_radius)*cos(theta), height + d_height, (radius - d_radius)*sin(theta));
				glVertex3f((radius - d_radius)*cos(theta)*1.5, height + d_height*1.5, (radius - d_radius)*sin(theta)*1.5);

				//p6
				glVertex3f(radius*cos(theta), height, radius*sin(theta));
				glVertex3f(radius*cos(theta)*1.5, height*1.5, radius*sin(theta)*1.5);

				//increment height
				height += d_height;

				//decrease radius
				radius -= d_radius;
			}

			//top
			//    p1
			//   /  \
			//  /    \
			// p2-----p3

            //p1
			glVertex3f(radius*cos(theta), height, radius*sin(theta));
			glVertex3f(radius*cos(theta)*1.5, height*1.5, radius*sin(theta)*1.5);

			//p2
			glVertex3f(radius*cos(theta + d_theta), height, radius*sin(theta + d_theta));
			glVertex3f(radius*cos(theta + d_theta)*1.5, height*1.5, radius*sin(theta + d_theta)*1.5);

			//p3
			glVertex3f(0, height + d_height, 0);
			glVertex3f(0, height + d_height*1.5, 0);
		}
		glEnd();
	};
};

#endif
