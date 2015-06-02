#if defined (_WIN32)
#include <windows.h>
#endif
#if defined (__APPLE__) || defined (MACOSX)
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/glu.h>
#endif

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <utility>
#include <glm/glm.hpp>
#include <fstream>
#include "BezierCurve.hpp"

int windowWidth = 640 , windowHeight = 480;
bool ignoreRepeats = false;
bool lbuttonDown = false;
bool rbuttonDown = false;
bool centerOrigin = false;
int mouse_x  = 0, mouse_y = 0;

float camPosX = 12, camPosY = 8 , camPosZ = 12;
float camViewX = 0, camViewY = 0, camViewZ = 0;
const std::string renderingMode = "2D"; // "3D"
bool useLighting = false;

float t = 0.0f;
int sign = 1;
bool updated = false;
int selectedCp = -1;
bool edit = false;
char buffer[3];
BezierBernsteinCurve bc;

void print(std::string s,int x , int y);
void setupWindowAndProjection();
void drawAxis(int length);
void resetModelViewMatrix();
bool init();
void Display();
void LeftButtonEvent();
void RightButtonEvent();
void Mouse(int button, int state, int x, int y);
void Motion(int x, int y);
void PassiveMotion(int x, int y);
void Keyboard(unsigned char key, int x, int y);
void SpecialKey(int key, int x, int y);
void Reshape(int width, int height);
void Idle();

int main(int argc, char *argv[]){

	glutInit(&argc, argv);

	glutInitWindowPosition(200, 200);
	glutInitWindowSize(windowWidth, windowHeight);

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	glutCreateWindow(std::string(renderingMode + " Smoothness Of Motions On Curves").c_str());

	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutIdleFunc(Idle);
	glutPassiveMotionFunc(PassiveMotion);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKey);

	if (!init())
		return 1;

	glutMainLoop();

	return 0;
}

bool init(){

	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

	glPointSize(3.0);
	//glLineWidth(2.0);

	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

	if ( renderingMode == "3D" && useLighting ){

		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_NORMALIZE);

		//glShadeModel(GL_FLAT);
		glShadeModel(GL_SMOOTH);

		GLfloat lightPos[] = {2.0f , 1.0f , 2.0f , 0.0f};
		GLfloat lightAmbient[] = {0.0f , 0.0f , 0.0f , 0.0f};
		GLfloat lightDiffuse[] = {1.0f , 1.0f , 1.0f , 0.0f};
		GLfloat lightSpecular[] = {1.0f , 1.0f , 1.0f , 0.0f};

		glLightfv(GL_LIGHT0, GL_POSITION , lightPos);
		glLightfv(GL_LIGHT0, GL_AMBIENT , lightAmbient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE , lightDiffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR , lightSpecular);

		glEnable(GL_COLOR_MATERIAL);

		GLfloat materialShininess[] = {30.0f};
		GLfloat materialAmbient[] = {0.02f , 0.17f , 0.02f , 0.0f};
		GLfloat materialDiffuse[] = {0.08f , 0.61f , 0.08f , 0.0f};
		GLfloat materialSpecular[] = {0.63f , 0.73f , 0.3f , 0.0f};

		glMaterialfv(GL_FRONT, GL_AMBIENT , materialAmbient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE , materialDiffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR , materialSpecular);
		glMaterialfv(GL_FRONT, GL_SHININESS, materialShininess);
	}

	if ( renderingMode == "3D" ){

		glEnable(GL_DEPTH_TEST);
	}

	return true;
}

void resetModelViewMatrix(){

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if ( renderingMode == "3D" )
		gluLookAt(camPosX, camPosY, camPosZ,     camViewX, camViewY, camViewZ,     0, 1, 0);
}

void setupWindowAndProjection(){

	if ( renderingMode == "2D" )
		glClear(GL_COLOR_BUFFER_BIT);
	else if ( renderingMode == "3D" )
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if ( renderingMode == "2D" && centerOrigin )
		gluOrtho2D(-windowWidth,windowWidth,-windowHeight,windowHeight);
	else if (renderingMode == "2D")
		gluOrtho2D(0,windowWidth,0,windowHeight);
	else if ( renderingMode == "3D" )
		gluPerspective(45.0f,(GLfloat)windowWidth/(GLfloat)windowHeight, 0.5f ,150.0f);

	resetModelViewMatrix();

	glViewport(0,0,windowWidth,windowHeight);
}

void drawAxis(int length){

	bool enableAgain = true;

	if ( glIsEnabled(GL_LIGHTING) )
		glDisable(GL_LIGHTING);
	else
		enableAgain = false;

	glLineWidth(2);
	glBegin(GL_LINES);
		glColor3f(1,0,0);
		glVertex3i(0,0,0);
		glVertex3i(0,length,0);

		glColor3f(0,1,0);
		glVertex3i(0,0,0);
		glVertex3i(length,0,0);

		glColor3f(0,0,1);
		glVertex3i(0,0,0);
		glVertex3i(0,0,length);
	glEnd();

	if ( enableAgain )
		glEnable(GL_LIGHTING);
}

void Display(){

	setupWindowAndProjection();
	drawAxis(400);
	//insert code below

	bc.drawControlPolygon(true,1,glm::vec4(1,0,1,0));

	if ( updated ){
	
	    bc.generateCurve(0.005);
	    updated = false;
	}

	bc.drawCurvePoints(2,glm::vec4(0,1,0,0));

	bc.drawControlPoints(true,10,glm::vec4(1,1,0,0));

	bc.drawConstructionPolygon(false , 3.5 , glm::vec4(1,0.5,0.3,0) ,10);

	glutSwapBuffers();
}

void Keyboard(unsigned char key, int x, int y){

	switch(key){

	case 'a' :
	
		break;

	case 'z' :
		break;

	// Enter
	case 13 :
		centerOrigin = !centerOrigin;
		break;

	// Delete
	case 27 :
		exit(0);
		break;

	default :
		std::cout << "Pressed key : " << (char)key << " at position : ("<< x << "," << y << ")" << std::endl;
		break;
	}

	/*int mod = glutGetModifiers();

	switch(mod){

	case GLUT_ACTIVE_CTRL :

		break;
	case GLUT_ACTIVE_SHIFT :

		break;
	case GLUT_ACTIVE_ALT :
		std::cout << "Alt Held" << std::endl;
		break;
	}*/
}

bool isClickOnVertex(int x , int y , float vx , float vy){

	glm::vec2 v(vx - x , vy - y);

	if (glm::length(v) < 8)
		return true;
	else
		return false;
}

void LeftButtonEvent(){

	/*for ( auto i = 0u ; i < controlPoints.size(); ++i ){
        
		if ( isClickOnVertex(mouse_x , mouse_y , controlPoints[i].x , controlPoints[i].y) ) {
			edit = true;
			selectedCp = i;
			break;
		}
		else{
			edit = false;
			selectedCp = -1;
		}    	
    }  */

}

void RightButtonEvent(){
	updated = true;
	bc.addControlPoints(glm::vec3(mouse_x,mouse_y,0.0));
}

void Mouse(int button, int state, int x, int y){

	mouse_x = x;
	mouse_y = (y - windowHeight) * -1;

	glutSetCursor(GLUT_CURSOR_LEFT_ARROW);

	if (button == GLUT_RIGHT_BUTTON){

		if (state == GLUT_DOWN){
			std::cout << "Right button pressed"<< std::endl;
			rbuttonDown = true;
			RightButtonEvent();
		}
		else{
			std::cout << "Right button lifted "<< "at (" << mouse_x << "," << mouse_y<< ")" << std::endl;
			rbuttonDown = false;
		}
	}
	else if (button == GLUT_LEFT_BUTTON){

		if (state == GLUT_DOWN){
			lbuttonDown = true;
			LeftButtonEvent();
		}
		else{
			lbuttonDown = false;
			updated = false;
			selectedCp = -1;
			edit = false;
		}
	}
}

void Motion(int x, int y){

	mouse_x = x;
	mouse_y = (y - windowHeight) * -1;	

	glutSetCursor(GLUT_CURSOR_SPRAY);

	if (lbuttonDown && edit){
		updated = true;
		//controlPoints[selectedCp] = glm::vec3(mouse_x,mouse_y,0.0);
	}

	if (rbuttonDown)
		std::cout << "Mouse dragged with right button at "<< "(" << mouse_x << "," << mouse_y << ")" << std::endl;
}

void PassiveMotion(int x, int y){

	mouse_x = x;
	mouse_y = (y - windowHeight) * -1;
}

int fileCounter = 0;

void SpecialKey(int key, int x, int y){

	switch(key){

	case GLUT_KEY_F1:
        exit(0);
		break;

	case GLUT_KEY_F2:
		bc.saveCurveToFile("test" + std::to_string(fileCounter) + ".curvefile");
		++fileCounter;
		break;

	case GLUT_KEY_F3:
       	bc.loadCurveFromFile("test3.curvefile");
       	updated = true;
		break;

	case GLUT_KEY_F4:
        bc.translate(glm::vec3(1,0,0));
       	updated = true;
		break;

	case GLUT_KEY_F5:
        bc.scale(glm::vec3(0.5,1.5,0));
       	updated = true;
		break;

	case GLUT_KEY_F6:
        bc.rotate(1,glm::vec3(0,0,1),bc.getCurveCenter());
       	updated = true;
		break;


	case GLUT_KEY_UP :
		std::cout << "Pressed Up" << " at position : (" << x << "," << y << ")" << std::endl;
		break;
	}
}

void Reshape(int width, int height){

	windowWidth = width;
	windowHeight = height;
}

void Idle(){

	glutPostRedisplay();
}
