#ifndef CUBE_H
#define CUBE_H

#include "Shape.h"

class Cube : public Shape {
public:
	Cube() {};
	~Cube() {};

	void draw() {
		//radius to draw around
		float radius = 0.5;

		//initial height and width of cude
		float height = -radius;
		float width = -radius;

		//delta change of height and width
		float d_height = radius*2 / m_segmentsY;
		float d_width = radius*2 / m_segmentsX;

		glBegin(GL_TRIANGLES);
		for (int i = 0; i < m_segmentsX; i++) {
			//reset back to the bottom of the square
			height = -radius;
			for (int j = 0; j < m_segmentsY; j++) {
				//box
				// p5----p3-p6 
				// |        /|
				// |     /   |
				// |  /      |
				// p1-p4----p2

		//back
				//bottom
				//p1
				glNormal3f(width, height, -radius);
				glVertex3f(width, height, -radius);

				//p2
				glNormal3f(width + d_width, height, -radius);
				glVertex3f(width + d_width, height, -radius);

				//p3
				glNormal3f(width + d_width, height + d_height, -radius);
				glVertex3f(width + d_width, height + d_height, -radius);

				//top
				//p4
				glNormal3f(width + d_width, height + d_height, -radius);
				glVertex3f(width + d_width, height + d_height, -radius);

				//p5
				glNormal3f(width, height + d_height, -radius);
				glVertex3f(width, height + d_height, -radius);

				//p6
				glNormal3f(width, height, -radius);
				glVertex3f(width, height, -radius);

		//front
				//bottom
				//p1
				glNormal3f(width, height, radius);
				glVertex3f(width, height, radius);

				//p2
				glNormal3f(width + d_width, height, radius);
				glVertex3f(width + d_width, height, radius);

				//p3
				glNormal3f(width + d_width, height + d_height, radius);
				glVertex3f(width + d_width, height + d_height, radius);

				//top
				//p4
				glNormal3f(width + d_width, height + d_height, radius);
				glVertex3f(width + d_width, height + d_height, radius);

				//p5
				glNormal3f(width, height + d_height, radius);
				glVertex3f(width, height + d_height, radius);

				//p6
				glNormal3f(width, height, radius);
				glVertex3f(width, height, radius);

		//left
				//bottom
				//p1
				glNormal3f(-radius, height, width);
				glVertex3f(-radius, height, width);

				//p2
				glNormal3f(-radius, height, width + d_width);
				glVertex3f(-radius, height, width + d_width);

				//p3
				glNormal3f(-radius, height + d_height, width + d_width);
				glVertex3f(-radius, height + d_height, width + d_width);

				//top
				//p4
				glNormal3f(-radius, height + d_height, width + d_width);
				glVertex3f(-radius, height + d_height, width + d_width);

				//p5
				glNormal3f(-radius, height + d_height, width);
				glVertex3f(-radius, height + d_height, width);

				//p6
				glNormal3f(-radius, height, width);
				glVertex3f(-radius, height, width);

		//right
				//bottom
				//p1
				glNormal3f(radius, height, width);
				glVertex3f(radius, height, width);

				//p2
				glNormal3f(radius, height, width + d_width);
				glVertex3f(radius, height, width + d_width);

				//p3
				glNormal3f(radius, height + d_height, width + d_width);
				glVertex3f(radius, height + d_height, width + d_width);

				//top
				//p4
				glNormal3f(radius, height + d_height, width + d_width);
				glVertex3f(radius, height + d_height, width + d_width);

				//p5
				glNormal3f(radius, height + d_height, width);
				glVertex3f(radius, height + d_height, width);

				//p6
				glNormal3f(radius, height, width);
				glVertex3f(radius, height, width);

		//bottom
				//bottom
				//p1
				glNormal3f(width, -radius, height);
				glVertex3f(width, -radius, height);

				//p2
				glNormal3f(width + d_width, -radius, height);
				glVertex3f(width + d_width, -radius, height);

				//p3
				glNormal3f(width + d_width, -radius, height + d_height);
				glVertex3f(width + d_width, -radius, height + d_height);

				//top
				//p4
				glNormal3f(width + d_width, -radius, height + d_height);
				glVertex3f(width + d_width, -radius, height + d_height);

				//p5
				glNormal3f(width, -radius, height + d_height);
				glVertex3f(width, -radius, height + d_height);

				//p6
				glNormal3f(width, -radius, height);
				glVertex3f(width, -radius, height);

		//top
				//bottom
				//p1
				glNormal3f(width, radius, height);
				glVertex3f(width, radius, height);

				//p2
				glNormal3f(width + d_width, radius, height);
				glVertex3f(width + d_width, radius, height);

				//p3
				glNormal3f(width + d_width, radius, height + d_height);
				glVertex3f(width + d_width, radius, height + d_height);

				//top
				//p4
				glNormal3f(width + d_width, radius, height + d_height);
				glVertex3f(width + d_width, radius, height + d_height);

				//p5
				glNormal3f(width, radius, height + d_height);
				glVertex3f(width, radius, height + d_height);

				//p6
				glNormal3f(width, radius, height);
				glVertex3f(width, radius, height);

				//step height
				height += d_height;
			}
			//step width
			width += d_width;
		}
		glEnd();
	};


	void drawNormal() {
		float radius = 0.5;
		float height = -radius;
		float d_height = radius * 2 / m_segmentsY;
		float width = -radius;
		float d_width = radius * 2 / m_segmentsX;

		glBegin(GL_LINES);

		for (int i = 0; i < m_segmentsX; i++) {
			height = -radius;
			for (int j = 0; j < m_segmentsY; j++) {
				//box
				// p5----p3-p6 
				// |        /|
				// |     /   |
				// |  /      |
				// p1-p4----p2

				//back
				//bottom
				//p1
				glVertex3f(width, height, -radius);
				glVertex3f(width*1.5, height*1.5, -radius*1.5);

				//p2
				glVertex3f(width + d_width, height, -radius);
				glVertex3f(width + d_width*1.5, height*1.5, -radius*1.5);

				//p3
				glVertex3f(width + d_width, height + d_height, -radius);
				glVertex3f(width + d_width*1.5, height + d_height*1.5, -radius*1.5);

				//top
				//p4
				glVertex3f(width + d_width, height + d_height, -radius);
				glVertex3f(width + d_width*1.5, height + d_height*1.5, -radius*1.5);

				//p5
				glVertex3f(width, height + d_height, -radius);
				glVertex3f(width*1.5, height + d_height*1.5, -radius*1.5);

				//p6
				glVertex3f(width, height, -radius);
				glVertex3f(width*1.5, height*1.5, -radius*1.5);

				//front
				//bottom
				//p1
				glVertex3f(width, height, radius);
				glVertex3f(width*1.5, height*1.5, radius*1.5);

				//p2
				glVertex3f(width + d_width, height, radius);
				glVertex3f(width + d_width*1.5, height*1.5, radius*1.5);

				//p3
				glVertex3f(width + d_width, height + d_height, radius);
				glVertex3f(width + d_width*1.5, height + d_height*1.5, radius*1.5);

				//top
				//p4
				glVertex3f(width + d_width, height + d_height, radius);
				glVertex3f(width + d_width*1.5, height + d_height*1.5, radius*1.5);

				//p5
				glVertex3f(width, height + d_height, radius);
				glVertex3f(width*1.5, height + d_height*1.5, radius*1.5);

				//p6
				glVertex3f(width, height, radius);
				glVertex3f(width*1.5, height*1.5, radius*1.5);

				//left
				//bottom
				//p1
				glVertex3f(-radius, height, width);
				glVertex3f(-radius*1.5, height*1.5, width*1.5);

				//p2
				glVertex3f(-radius, height, width + d_width);
				glVertex3f(-radius*1.5, height*1.5, width + d_width*1.5);

				//p3
				glVertex3f(-radius, height + d_height, width + d_width);
				glVertex3f(-radius*1.5, height + d_height*1.5, width + d_width*1.5);

				//top
				//p4
				glVertex3f(-radius, height + d_height, width + d_width);
				glVertex3f(-radius*1.5, height + d_height*1.5, width + d_width*1.5);

				//p5
				glVertex3f(-radius, height + d_height, width);
				glVertex3f(-radius*1.5, height + d_height*1.5, width*1.5);

				//p6
				glVertex3f(-radius, height, width);
				glVertex3f(-radius*1.5, height*1.5, width*1.5);

				//right
				//bottom
				//p1
				glVertex3f(radius, height, width);
				glVertex3f(radius*1.5, height*1.5, width*1.5);

				//p2
				glVertex3f(radius, height, width + d_width);
				glVertex3f(radius*1.5, height*1.5, width + d_width*1.5);

				//p3
				glVertex3f(radius, height + d_height, width + d_width);
				glVertex3f(radius*1.5, height + d_height*1.5, width + d_width*1.5);

				//top
				//p4
				glVertex3f(radius, height + d_height, width + d_width);
				glVertex3f(radius*1.5, height + d_height*1.5, width + d_width*1.5);

				//p5
				glVertex3f(radius, height + d_height, width);
				glVertex3f(radius*1.5, height + d_height*1.5, width*1.5);

				//p6
				glVertex3f(radius, height, width);
				glVertex3f(radius*1.5, height*1.5, width*1.5);

				//bottom
				//bottom
				//p1
				glVertex3f(width, -radius, height);
				glVertex3f(width*1.5, -radius*1.5, height*1.5);

				//p2
				glVertex3f(width + d_width, -radius, height);
				glVertex3f(width + d_width*1.5, -radius*1.5, height*1.5);

				//p3
				glVertex3f(width + d_width, -radius, height + d_height);
				glVertex3f(width + d_width*1.5, -radius*1.5, height + d_height*1.5);

				//top
				//p4
				glVertex3f(width + d_width, -radius, height + d_height);
				glVertex3f(width + d_width*1.5, -radius*1.5, height + d_height*1.5);

				//p5
				glVertex3f(width, -radius, height + d_height);
				glVertex3f(width*1.5, -radius*1.5, height + d_height*1.5);

				//p6
				glVertex3f(width, -radius, height);
				glVertex3f(width*1.5, -radius*1.5, height*1.5);

				//top
				//bottom
				//p1
				glVertex3f(width, radius, height);
				glVertex3f(width*1.5, radius*1.5, height*1.5);

				//p2
				glVertex3f(width + d_width, radius, height);
				glVertex3f(width + d_width*1.5, radius*1.5, height*1.5);

				//p3
				glVertex3f(width + d_width, radius, height + d_height);
				glVertex3f(width + d_width*1.5, radius*1.5, height + d_height*1.5);

				//top
				//p4
				glVertex3f(width + d_width, radius, height + d_height);
				glVertex3f(width + d_width*1.5, radius*1.5, height + d_height*1.5);

				//p5
				glVertex3f(width, radius, height + d_height);
				glVertex3f(width*1.5, radius*1.5, height + d_height*1.5);

				//p6
				glVertex3f(width, radius, height);
				glVertex3f(width*1.5, radius*1.5, height*1.5);

				height += d_height;
			}
			width += d_width;
		}
		glEnd();
	};
};

#endif
