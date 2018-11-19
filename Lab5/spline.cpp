/*  =================== File Information =================
	Author: Justin Ritter
	File Name: spline.cpp
	Description:

	Purpose: Create a cubic spline 
	Usage:	

	Further Reading resources: 
	http://mathworld.wolfram.com/CubicSpline.html
	http://www.geos.ed.ac.uk/~yliu23/docs/lect_spline.pdf
	===================================================== */
#include <stdlib.h>
#include <GL/glui.h>
#include <iostream>
#include <cmath>
#include "spline.h"

/*	===============================================
Desc:	Default constructor for spline
Precondition: 	_resolution specifies how many points will be drawn between each control
				point for the spline.
Postcondition:
=============================================== */ 
spline::spline(int _resolution){
	// Set to Null
	head = NULL;
	tail = NULL;

	resolution = _resolution;
	points = 0;
	computed_x_y_z= NULL;
}

/*	===============================================
Desc:			Deallocate memory
Precondition:
Postcondition:
=============================================== */ 
spline::~spline(){
	// Delete all of our control points
	controlPoint* iter;
	iter = head;
	while(iter != NULL){
		head = head->next;
		delete iter;
		iter = head;
	}

	delete[] computed_x_y_z;
}

/*	===============================================
Desc:			Adds a point to the linked list of control points
Precondition:	If it is the first point, make sure it is the head nad tail.
				If there is no memory available, terminate the program.
Postcondition:	
=============================================== */ 
void spline::addPoint(float x, float y, float z){
	// Create a new point
	controlPoint* temp = new controlPoint();
	// Did the memory allocate?
	if(temp!=NULL){
		temp->setValues(x,y,z);
		temp->next = NULL;	// remember to set this to NULL since this is our last point in our list.
		std::cout << "Roller Coaster Route: (" << x << "," << y << "," << z << ")" << std::endl;
		points++;			// enumerate our point
	}
	else{
		std::cerr << "addPoint out of memory!" << std::endl;
		exit(1);
	}

	// If this is our first point, then it is our head and tail
	if(head==NULL && tail==NULL){
		head = temp;
		head->next = tail;
		tail = temp;
		tail->next = NULL;
	}else
	{
		tail->next = temp;
		tail = temp;
	}

	update(resolution);

}

/*	===============================================
Desc:	Reallocates memory for our resolution table.
		Note that as many possible resolution points are copied
		over to the new array.
Precondition:
Postcondition:
=============================================== */
void spline::update(int _resolution){

	resolution = _resolution;
	// resize our array
	if(computed_x_y_z==NULL){
		computed_x_y_z = new float[resolution*points*3+3];
	}
	else
	{ 	// resize! ewww, this is ugly though. We could speed up by doubling our size
		// everytime and keep track of the capacity of our array versus memory taken.
		delete[] computed_x_y_z;
		computed_x_y_z = new float[resolution*points*3+3];
	}
	std::cout << "resolution: " << resolution << " points: "<< points << " Array Table Size:"<< resolution*points*3+3 << std::endl;
}

/*	===============================================
		Desc:			This function draws a spline by making opengl calls of the form
							glPointSize(1.0);
							glBegin(GL_POINTS);
								glVertex(...)
							glEnd();

						Within this function we could compute a table of of values
						(i.e. computed_x_y_z) and then never have to call this function again,
						so long as the resolution is not updated.

		Precondition: 	resolution(in my implementation), specifies how many points to draw between
						each control point.

						output is used as a flag to output the points along the spline to the console.
						A value of 1 will output each interpolated point, while a value of 0 will output
						nothing to standard IO.
						You may remove this is parameter if you think it is unnecessary.
		Postcondition:
=============================================== */ 
void spline::draw_spline(int resolution, int output) {
	glPushMatrix();

	glPointSize(3.0);	
	glDisable(GL_LIGHTING);

	controlPoint* cur = head;
	int pos = 0;
	while (cur->next != NULL) {
		draw_resolution(cur, pos);
		cur = cur->next;
		pos++;
	}

	if (computed_x_y_z != NULL) {
		for (int i = 0; i < points; i++) {
			for (int res = 0; i < resolution; i++) {
				// Set the draw mode so that each vertex is drawn as a point.
				glBegin(GL_POINTS);
				// Our points will be drawn as red boxes
				glColor3f(1, 1, 1);
				// Finally draw a regular control point.
				glVertex3f(computed_x_y_z[i+res], computed_x_y_z[i+res + 1], computed_x_y_z[i + res + 2]);
				glEnd();

				glBegin(GL_LINES);
				glColor3f(0, 1, 0);
				glVertex3f(computed_x_y_z[i+res], computed_x_y_z[i+res + 1], computed_x_y_z[i+res + 2]);
				glVertex3f(computed_x_y_z[i+res + 3], computed_x_y_z[i+res + 4], computed_x_y_z[i+res + 5]);
				glEnd();
			}
		}
	}

	glEnable(GL_LIGHTING);
	glPopMatrix();
}

void spline::draw_resolution(controlPoint* cur, int pos) {
	float splineX, splineY;
	computed_x_y_z[pos] = cur->x;
	computed_x_y_z[pos+1] = cur->y;
	computed_x_y_z[pos+2] = cur->z;

	for (int i = 0; i < resolution; i++) {
		float percent = i / resolution;
		splineX = calculate_Spline(percent, computed_x_y_z[i+pos], computed_x_y_z[i+pos]+percent, 5, 5);
		splineY = calculate_Spline(i / resolution, computed_x_y_z[i+pos+1], computed_x_y_z[i+pos+1]+percent, 5, 5);


		computed_x_y_z[i+pos] = splineX;
		computed_x_y_z[i+pos+1] = splineY;
		computed_x_y_z[i+pos+2] = cur->z;
	}
}

/*	===============================================
		Desc: 	Function for returning an interpolated point between sPos(starting position) and
				an gPos (goal/ending) position.
				The velocity at the starting point (Vs) and goal point(Vg) can be user specified.
		
				S = starting position of your interval
				G = ending(or "goal") position of your interval
				Vs = velocity your points grow from from your starting point
				Vg = velocity your point ends on from your goal position

		Precondition:
		Postcondition:
=============================================== */ 
float spline::calculate_Spline (float t, float S, float G, float Vs, float Vg) {
	return S + Vs*t + (-3*S + 3*G-2*Vs-Vg)*t*t + (2*S-2*G+Vs+Vg)*t*t*t;
}

/*	===============================================
Desc:	This function is responsible for drawing the original control points
		Use this as an example of how to iterate through the data structure.

		This function renders the control points and draws straight lines between them.
		You can use this function to compare with the draw_spline function.
Precondition:
Postcondition:
=============================================== */ 
void spline::render(){
	glPushMatrix();
	// Set our point sizes, these serve to highlight
	// the points that we added in our program.
	glPointSize(5.0);

	// Create an iterator to move through all of our control points
	controlPoint* iter;
	// Set the iterator to the head of our list.
	iter = head;

	// Disable lighting, so that lines and points show up.
	glDisable(GL_LIGHTING);
	// Iterate through each of the points until our iter reaches the end.
	while(iter != NULL){
		// Set the draw mode so that each vertex is drawn as a point.
		glBegin(GL_POINTS);
			// Our points will be drawn as red boxes
			glColor3f(1,0,0);
			// Color our start and stop positions different colors.
			if(iter==head){ glColor3f(0,0,1); }
			if(iter->next==NULL){ glColor3f(0,1,1); }
			// Finally draw a regular control point.
			glVertex3f(iter->x,iter->y,iter->z);
		glEnd();
		// Continue iterating through our list.
		iter = iter->next;
	}

	// Reset our iter to the head
	// The purpose of this loop is to
	// draw lines between each of the control points.
	iter = head;
	while(iter->next != NULL){
		glBegin(GL_LINES);
			glColor3f(0,1,0);
			glVertex3f(iter->x,iter->y,iter->z);
			glVertex3f(iter->next->x,iter->next->y,iter->next->z);
		glEnd();
		iter = iter->next;
	}

	// Renable lighting now that we are done drawing lines and points.
	glEnable(GL_LIGHTING);
	glPopMatrix();
}

/*	===============================================
Desc:	renderAsRollerCoaster is a hacked together function.
		For this you get to be creative with how you could render two or more splines
		together in order to create cool shapes. 
		Perhaps you could draw a tunnel to go through?
		Perhaps you create an overhead roller coaster?
		Perhaps you have other ideas?
Precondition:
Postcondition:
=============================================== */ 
void spline::renderAsRollerCoaster(int resolution, float width){
	 /*  


					(Optional) You Implement this Code  

	*/

}

