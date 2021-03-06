/*
 * Author: Justin Ritter
 * Date: 11/1/2018
 * Descriptions: Hey I'm threading! Decent speed-ups
 */

#define NUM_OPENGL_LIGHTS 8

#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <ctime>
#include <freeglut.h>
#include <GL/glui.h>
#include "Shape.h"
#include "Cube.h"
#include "Cylinder.h"
#include "Cone.h"
#include "Sphere.h"
#include "SceneParser.h"
#include "Camera.h"

using namespace std;

/** These are the live variables passed into GLUI ***/
int  isectOnly = 1;

int	 camRotU = 0;
int	 camRotV = 0;
int	 camRotW = 0;
int  viewAngle = 45;
float eyeX = 2;
float eyeY = 2;
float eyeZ = 2;
float lookX = -2;
float lookY = -2;
float lookZ = -2;

struct SceneObject {
	Shape* shape;
	Matrix trans;
	Matrix invTrans;
	SceneMaterial mat;
};

std::vector<SceneObject> sceneObjects;

/** These are GLUI control panel objects ***/
int  main_window;
string filenamePath = "data\\general\\robot.xml";
GLUI_EditText* filenameTextField = NULL;
GLubyte* pixels = NULL;
int pixelWidth = 0, pixelHeight = 0;
int screenWidth = 0, screenHeight = 0;

/** these are the global variables used for rendering **/
Cube* cube = new Cube();
Cylinder* cylinder = new Cylinder();
Cone* cone = new Cone();
Sphere* sphere = new Sphere();
SceneParser* parser = NULL;
Camera* camera = new Camera();

void setupCamera();
void updateCamera();

Shape* renderShape(int type) {
	switch (type) {
	case SHAPE_CUBE:
		return cube;
	case SHAPE_SPHERE:
		return sphere;
	case SHAPE_CYLINDER:
		return cylinder;
	case SHAPE_CONE:
		return cone;
	default:
		return cube;
	}
}

void flattenScene(SceneNode* root, Matrix composite) {
	std::vector<SceneTransformation*> transVec = root->transformations;
	for (int i = 0; i<transVec.size(); i++) {
		SceneTransformation* trans = transVec[i];
		switch (trans->type) {
		case TRANSFORMATION_TRANSLATE:
			composite = composite * trans_mat(trans->translate);
			break;
		case TRANSFORMATION_SCALE:
			composite = composite * scale_mat(trans->scale);
			break;
		case TRANSFORMATION_ROTATE:
			composite = composite * rot_mat(trans->rotate, trans->angle);
			break;
		case TRANSFORMATION_MATRIX:
			composite = composite * trans->matrix;
			break;
		}
	}

	SceneGlobalData globalData;
	parser->getGlobalData(globalData);
	std::vector<ScenePrimitive*> objectVec = root->primitives;
	for (int j = 0; j<objectVec.size(); j++) {
		SceneObject tempObj;
		tempObj.trans = composite;
		tempObj.invTrans = invert(composite);

		tempObj.mat = objectVec[j]->material;

		tempObj.shape = renderShape(objectVec[j]->type);
		sceneObjects.push_back(tempObj);
	}

	std::vector<SceneNode*> childrenVec = root->children;
	for (int k = 0; k<childrenVec.size(); k++) {
		flattenScene(childrenVec[k], composite);
	}
}

void setPixel(GLubyte* buf, int x, int y, int r, int g, int b) {
	buf[(y*pixelWidth + x) * 3 + 0] = (GLubyte)r;
	buf[(y*pixelWidth + x) * 3 + 1] = (GLubyte)g;
	buf[(y*pixelWidth + x) * 3 + 2] = (GLubyte)b;
}

Point calcColor(SceneObject object, Vector normal, Vector ray, Point point) {
	Point color;
	int i, j;

	SceneGlobalData gd;
	parser->getGlobalData(gd);

	for (int i = 0; i < parser->getNumLights(); i++) {
		SceneLightData ld;
		parser->getLightData(i, ld);

		Vector lDir = ld.pos - point;
		lDir.normalize();

		double dot_nl = dot(normal, lDir);
		double dot_vr = dot(ray, ((2 * normal*dot_nl) - lDir));
		if (dot_nl<0) dot_nl = 0;
		if (dot_vr<0) dot_vr = 0;

		double power = pow(dot_vr, object.mat.shininess);

		Point diffuse(object.mat.cDiffuse.r, object.mat.cDiffuse.g, object.mat.cDiffuse.b);

		double blend = object.mat.blend;
		double r_blend = 1 - blend;

		Point specular(object.mat.cSpecular.r, object.mat.cSpecular.g, object.mat.cSpecular.b);

		Point reflective(object.mat.cReflective.r, object.mat.cReflective.g, object.mat.cReflective.b);

		Point lightColor(ld.color.r, ld.color.g, ld.color.b);

		Point intensity(object.mat.cEmissive.r, object.mat.cEmissive.g, object.mat.cEmissive.b);
		for (j = 0; j < 3; j++) {
			color[j] = color[j] * intensity[j] + (diffuse[j] * dot_nl + specular[j] * lightColor[j] * power) + gd.ks*reflective[j];
			if (color[j]>1) {
				color[j] = 1.0;
			}
		}
	}

	Point ambient(object.mat.cAmbient.r, object.mat.cAmbient.g, object.mat.cAmbient.b);
	for (int i = 0; i < 3; i++) {
		//set color
		color[i] = gd.ka * ambient[i] + color[i];
		if (color[i] > 1) {
			color[i] = 1.0;
		}
	}

	//return final color
	return color;
}

void generateRays(int i) {
	for (int j = 0; j < pixelHeight; j++) {
		double epsilon = .05;

		//generate ray from i,j
		double px = -1.0 + 2.0 * i / (double)screenWidth;
		double py = -1.0 + 2.0 * j / (double)screenHeight;

		Point screenPoint(px, py, -1);
		Vector genRay = (camera->GetCamToWorld() * screenPoint) - camera->GetEyePoint();
		genRay.normalize();

		double minDist = MIN_ISECT_DISTANCE;
		int minObj = -1;

		//find closest object
		for (int k = 0; k < sceneObjects.size(); k++) {
			double isectDist = sceneObjects[k].shape->
				Intersect(camera->GetEyePoint(), genRay, sceneObjects[k].trans) - epsilon;

			if ((isectDist < minDist) && (isectDist > 0) && !(IN_RANGE(isectDist, 0))) {
				minDist = isectDist;
				minObj = k;
			}
		}

		if (minObj != -1) {
			Point pointObjSpace = sceneObjects[minObj].invTrans * camera->GetEyePoint();
			Vector rayObjSpace = sceneObjects[minObj].invTrans * genRay;
			Vector normal = sceneObjects[minObj].shape->findIsectNormal(pointObjSpace, rayObjSpace, minDist);
			normal = (transpose(sceneObjects[minObj].invTrans) * normal);
			normal.normalize();

			Point isectWP = camera->GetEyePoint() + minDist*genRay;
			Point color = calcColor(sceneObjects[minObj], normal, genRay, isectWP);
			color = color * 255;
			setPixel(pixels, i, j, color[0], color[1], color[2]);
		}
	}
}

void callback_start(int id) {
	cout << "start button clicked!" << endl;

	if (parser == NULL) {
		cout << "no scene loaded yet" << endl;
		return;
	}

	pixelWidth = screenWidth;
	pixelHeight = screenHeight;

	updateCamera();

	if (pixels != NULL) {
		delete pixels;
	}
	pixels = new GLubyte[pixelWidth  * pixelHeight * 3];
	memset(pixels, 0, pixelWidth  * pixelHeight * 3);

	cout << "(w, h): " << pixelWidth << ", " << pixelHeight << endl;

	std::vector<std::thread> threads;

	//spawn a thread for each row on the screen
	if (isectOnly != 1) {
		time_t start = time(NULL);
		for (int i = 0; i < pixelWidth; i++) {
			threads.push_back(thread(generateRays, i));
		}

		//wait for threads to complete
		for (int i = 0; i < threads.size(); i++) {
			threads[i].join();
		}
		time_t stop = time(NULL);


		cout << (stop - start) << endl;
	}

	cout << "DONE" << endl;
	glutPostRedisplay();
}



void callback_load(int id) {
	char curDirName [2048];
	if (filenameTextField == NULL) {
		return;
	}
	printf ("%s\n", filenameTextField->get_text());

	if (parser != NULL) {
		delete parser;
	}
	parser = new SceneParser (filenamePath);
	cout << "success? " << parser->parse() << endl;

	setupCamera();
	sceneObjects.clear();
	flattenScene(parser->getRootNode(), Matrix());
}


/***************************************** myGlutIdle() ***********/

void myGlutIdle(void)
{
	/* According to the GLUT specification, the current window is
	undefined during an idle callback.  So we need to explicitly change
	it if necessary */
	if (glutGetWindow() != main_window)
		glutSetWindow(main_window);

	glutPostRedisplay();
}


/**************************************** myGlutReshape() *************/

void myGlutReshape(int x, int y)
{
	float xy_aspect;

	xy_aspect = (float)x / (float)y;
	glViewport(0, 0, x, y);
	camera->SetScreenSize(x, y);

	screenWidth = x;
	screenHeight = y;

	glutPostRedisplay();
}


/***************************************** setupCamera() *****************/
void setupCamera()
{
	SceneCameraData cameraData;
	parser->getCameraData(cameraData);

	camera->Reset();
	camera->SetViewAngle(cameraData.heightAngle);
	if (cameraData.isDir == true) {
		camera->Orient(cameraData.pos, cameraData.look, cameraData.up);
	}
	else {
		camera->Orient(cameraData.pos, cameraData.lookAt, cameraData.up);
	}

	viewAngle = camera->GetViewAngle();
	Point eyeP = camera->GetEyePoint();
	Vector lookV = camera->GetLookVector();
	eyeX = eyeP[0];
	eyeY = eyeP[1];
	eyeZ = eyeP[2];
	lookX = lookV[0];
	lookY = lookV[1];
	lookZ = lookV[2];
	camRotU = 0;
	camRotV = 0;
	camRotW = 0;
	GLUI_Master.sync_live_all();
}

void updateCamera()
{
	camera->Reset();

	Point guiEye(eyeX, eyeY, eyeZ);
	Point guiLook(lookX, lookY, lookZ);
	camera->SetViewAngle(viewAngle);
	camera->Orient(guiEye, guiLook, camera->GetUpVector());
	camera->RotateU(camRotU);
	camera->RotateV(camRotV);
	camera->RotateW(camRotW);
	camera->SetCamtoWorld();
}

/***************************************** myGlutDisplay() *****************/

void myGlutDisplay(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	if (parser == NULL) {
		return;
	}

	if (pixels == NULL) {
		return;
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glDrawPixels(pixelWidth, pixelHeight, GL_RGB, GL_UNSIGNED_BYTE, pixels);
	glutSwapBuffers();
}

void onExit()
{
	delete cube;
	delete cylinder;
	delete cone;
	delete sphere;
	delete camera;
	if (parser != NULL) {
		delete parser;
	}
	if (pixels != NULL) {
		delete pixels;
	}
}

/**************************************** main() ********************/

int main(int argc, char* argv[])
{
	atexit(onExit);

	/****************************************/
	/*   Initialize GLUT and create window  */
	/****************************************/

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(500, 500);

	main_window = glutCreateWindow("CSI 4341: Assignment 4");
	glutDisplayFunc(myGlutDisplay);
	glutReshapeFunc(myGlutReshape);

	/****************************************/
	/*         Here's the GLUI code         */
	/****************************************/

	GLUI* glui = GLUI_Master.create_glui("GLUI");

	filenameTextField = new GLUI_EditText( glui, "Filename:", filenamePath);
	filenameTextField->set_w(300);
	glui->add_button("Load", 0, callback_load);
	glui->add_button("Start!", 0, callback_start);
	glui->add_checkbox("Isect Only", &isectOnly);
	
	GLUI_Panel *camera_panel = glui->add_panel("Camera");
	(new GLUI_Spinner(camera_panel, "RotateV:", &camRotV))
		->set_int_limits(-179, 179);
	(new GLUI_Spinner(camera_panel, "RotateU:", &camRotU))
		->set_int_limits(-179, 179);
	(new GLUI_Spinner(camera_panel, "RotateW:", &camRotW))
		->set_int_limits(-179, 179);
	(new GLUI_Spinner(camera_panel, "Angle:", &viewAngle))
		->set_int_limits(1, 179);

	glui->add_column_to_panel(camera_panel, true);

	GLUI_Spinner* eyex_widget = glui->add_spinner_to_panel(camera_panel, "EyeX:", GLUI_SPINNER_FLOAT, &eyeX);
	eyex_widget->set_float_limits(-10, 10);
	GLUI_Spinner* eyey_widget = glui->add_spinner_to_panel(camera_panel, "EyeY:", GLUI_SPINNER_FLOAT, &eyeY);
	eyey_widget->set_float_limits(-10, 10);
	GLUI_Spinner* eyez_widget = glui->add_spinner_to_panel(camera_panel, "EyeZ:", GLUI_SPINNER_FLOAT, &eyeZ);
	eyez_widget->set_float_limits(-10, 10);

	GLUI_Spinner* lookx_widget = glui->add_spinner_to_panel(camera_panel, "LookX:", GLUI_SPINNER_FLOAT, &lookX);
	lookx_widget->set_float_limits(-10, 10);
	GLUI_Spinner* looky_widget = glui->add_spinner_to_panel(camera_panel, "LookY:", GLUI_SPINNER_FLOAT, &lookY);
	looky_widget->set_float_limits(-10, 10);
	GLUI_Spinner* lookz_widget = glui->add_spinner_to_panel(camera_panel, "LookZ:", GLUI_SPINNER_FLOAT, &lookZ);
	lookz_widget->set_float_limits(-10, 10);

	glui->add_button("Quit", 0, (GLUI_Update_CB)exit);

	glui->set_main_gfx_window(main_window);

	/* We register the idle callback with GLUI, *not* with GLUT */
	GLUI_Master.set_glutIdleFunc(myGlutIdle);

	glutMainLoop();

	return EXIT_SUCCESS;
}



