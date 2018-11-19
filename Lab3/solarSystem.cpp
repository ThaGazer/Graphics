#include <stdlib.h>
#include <freeglut.h>
#include <GL/glui.h>
#include "solarSystem.h"

solarSystem::solarSystem(){

}

solarSystem::~solarSystem(){

}

// Render this with push and pop operations
// or alternatively implement helper functions
// for each of the planets with parameters.
void solarSystem::render(){
	
	// Some ideas for constants that can be used for
	// rotating the planets.
	static float rotation = 0.1;
	static float orbitSpeed = 0.1;
	static float moonOrbitX = 0.1;
	static float moonOrbitY = 0.1;
	static float moonOrbitSpeed = 1;

	glPushMatrix();

		// The Sun
		glPushMatrix();
			glRotatef(rotation,0,1,0);
			glColor3f(1.0f,0.4f,0.0f);
			glutSolidSphere(1.2,10,10);
		glPopMatrix();

		// The mercury
		glPushMatrix();
			glRotatef(rotation, 0, orbitSpeed, 0);
			glColor3f(1.0f, 0.4f, 0.0f);
			glTranslatef(2.0f, 0.0f, 0.0f);
			glutSolidSphere(.005, 10, 10);
		glPopMatrix();

		// The Venus
		glPushMatrix();
			glRotatef(rotation, 0, orbitSpeed, 0);
			glColor3f(1.0f, 1.0f, 0.0f);
			glTranslatef(3.0f, 0.0f, 0.0f);
			glutSolidSphere(.012, 10, 10);
		glPopMatrix();

		// The Earth
		glPushMatrix();
			glRotatef(rotation, 0, orbitSpeed, 0);
			glColor3f(0.0f, 1.0f, 1.0f);
			glTranslatef(4.0f, 0.0f, 0.0f);
			glutSolidSphere(.013, 10, 10);
		glPopMatrix();

		// The Moon
		glPushMatrix();
			glRotatef(rotation, 0, moonOrbitY, moonOrbitX);
			glColor3f(1.0f, 1.0f, 1.0f);
			glTranslatef(4.0f, 0.2f, 0.0f);
			glutSolidSphere(.0035, 10, 10);
		glPopMatrix();

		// The Mars
		glPushMatrix();
			glRotatef(rotation, 0, orbitSpeed, 0);
			glColor3f(1.0f, 0.0f, 0.0f);
			glTranslatef(5.0f, 0.0f, 0.0f);
			glutSolidSphere(.007, 10, 10);
		glPopMatrix();

		// The Jupiter
		glPushMatrix();
			glRotatef(rotation, 0, orbitSpeed, 0);
			glColor3f(1.0f, 1.0f, 0.0f);
			glTranslatef(7.0f, 0.0f, 0.0f);
			glutSolidSphere(.143, 10, 10);
		glPopMatrix();

		// The Saturn
		glPushMatrix();
			glRotatef(rotation, 0, orbitSpeed, 0);
			glColor3f(1.0f, 0.6f, 0.0f);
			glTranslatef(9.0f, 0.0f, 0.0f);
			glutSolidSphere(.125, 10, 10);
		glPopMatrix();

		// The Uranus
		glPushMatrix();
			glRotatef(rotation, 0, orbitSpeed, 0);
			glColor3f(0.0f, 0.0f, 0.5f);
			glTranslatef(10.0f, 0.0f, 0.0f);
			glutSolidSphere(.051, 10, 10);
		glPopMatrix();

		// The Netpune
		glPushMatrix();
			glRotatef(rotation, 0, orbitSpeed, 0);
			glColor3f(0.0f, 0.0f, 1.0f);
			glTranslatef(11.0f, 0.0f, 0.0f);
			glutSolidSphere(.050, 10, 10);
		glPopMatrix();

    glPopMatrix();
 
	rotation+= 0.1;
	orbitSpeed+=0.05;
	moonOrbitX+=moonOrbitSpeed;
	moonOrbitY+=moonOrbitSpeed;

}