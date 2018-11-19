#ifndef SPHERE_H
#define SPHERE_H

#include "Shape.h"

class Sphere : public Shape {
public:
	Sphere() {};
	~Sphere() {};

	void draw() {
		//starting points for phi and theta
		float theta = 0.0;
		float phi = 0.0;

		//the delta change for phi and theta
		float d_theta = (2 * PI) / m_segmentsX;
		float d_phi = PI / m_segmentsY;

		//the radius to draw around
		float radius = 0.5;

		glBegin(GL_TRIANGLES);
		for (int i = 0; i < m_segmentsX; i++) {
			//increment theta to next segment and reset phi for each segment
			theta = d_theta * i;
			phi = 0.0;

			for (int j = 0; j < m_segmentsY; j++) {
				//tile   
				// p5----p3-p6 
				// |       / |
				// |    /    |
				// | /       |
				// p1-p4----p2
				
				//top
				//p1
				glNormal3f(radius*sin(phi)*cos(theta), radius*cos(phi), radius*sin(phi)*sin(theta));
				glVertex3f(radius*sin(phi)*cos(theta), radius*cos(phi), radius*sin(phi)*sin(theta));

				//p2
				glNormal3f(radius*sin(phi)*cos(theta + d_theta), radius*cos(phi), radius*sin(phi)*sin(theta + d_theta));
				glVertex3f(radius*sin(phi)*cos(theta + d_theta), radius*cos(phi), radius*sin(phi)*sin(theta + d_theta));

				//p3
				glNormal3f(radius*sin(phi + d_phi)*cos(theta), radius*cos(phi + d_phi), radius*sin(phi + d_phi)*sin(theta));
				glVertex3f(radius*sin(phi + d_phi)*cos(theta), radius*cos(phi + d_phi), radius*sin(phi + d_phi)*sin(theta));

				//bottom
				//p4
				glNormal3f(radius*sin(phi + d_phi)*cos(theta), radius*cos(phi + d_phi), radius*sin(phi + d_phi)*sin(theta));
				glVertex3f(radius*sin(phi + d_phi)*cos(theta), radius*cos(phi + d_phi), radius*sin(phi + d_phi)*sin(theta));

				//p5
				glNormal3f(radius*sin(phi + d_phi)*cos(theta + d_theta), radius*cos(phi + d_phi), radius*sin(phi + d_phi)*sin(theta + d_theta));
				glVertex3f(radius*sin(phi + d_phi)*cos(theta + d_theta), radius*cos(phi + d_phi), radius*sin(phi + d_phi)*sin(theta + d_theta));

				//6
				glNormal3f(radius*sin(phi)*cos(theta + d_theta), radius*cos(phi), radius*sin(phi)*sin(theta + d_theta));
				glVertex3f(radius*sin(phi)*cos(theta + d_theta), radius*cos(phi), radius*sin(phi)*sin(theta + d_theta));

				phi += d_phi;
			}
		}
		glEnd();
	};

	void drawNormal() {
		float theta = 0.0;
		float phi = 0.0;
		float d_theta = (2 * PI) / m_segmentsX;
		float d_phi = PI / m_segmentsY;

		float radius = 0.5;

		glBegin(GL_LINES);
		for (int i = 0; i < m_segmentsX; i++) {
			theta = d_theta * i;
			phi = 0.0;

			for (int j = 0; j < m_segmentsY; j++) {
				//tile
				//top
				//p1
				glVertex3f(radius*sin(phi)*cos(theta), radius*cos(phi), radius*sin(phi)*sin(theta));
				glVertex3f(radius*sin(phi)*cos(theta)*1.5, radius*cos(phi)*1.5, radius*sin(phi)*sin(theta)*1.5);

				//p2
				glVertex3f(radius*sin(phi)*cos(theta + d_theta), radius*cos(phi), radius*sin(phi)*sin(theta + d_theta));
				glVertex3f(radius*sin(phi)*cos(theta + d_theta)*1.5, radius*cos(phi)*1.5, radius*sin(phi)*sin(theta + d_theta)*1.5);

				//p3
				glVertex3f(radius*sin(phi + d_phi)*cos(theta), radius*cos(phi + d_phi), radius*sin(phi + d_phi)*sin(theta));
				glVertex3f(radius*sin(phi + d_phi)*cos(theta)*1.5, radius*cos(phi + d_phi)*1.5, radius*sin(phi + d_phi)*sin(theta)*1.5);

				//bottom
				//p4
				glVertex3f(radius*sin(phi + d_phi)*cos(theta), radius*cos(phi + d_phi), radius*sin(phi + d_phi)*sin(theta));
				glVertex3f(radius*sin(phi + d_phi)*cos(theta)*1.5, radius*cos(phi + d_phi)*1.5, radius*sin(phi + d_phi)*sin(theta)*1.5);

				//p5
				glVertex3f(radius*sin(phi + d_phi)*cos(theta + d_theta), radius*cos(phi + d_phi), radius*sin(phi + d_phi)*sin(theta + d_theta));
				glVertex3f(radius*sin(phi + d_phi)*cos(theta + d_theta)*1.5, radius*cos(phi + d_phi)*1.5, radius*sin(phi + d_phi)*sin(theta + d_theta)*1.5);

				//p
				glVertex3f(radius*sin(phi)*cos(theta + d_theta), radius*cos(phi), radius*sin(phi)*sin(theta + d_theta));
				glVertex3f(radius*sin(phi)*cos(theta + d_theta)*1.5, radius*cos(phi)*1.5, radius*sin(phi)*sin(theta + d_theta)*1.5);

				phi += d_phi;
			}
		}
		glEnd();
	};
};

#endif
