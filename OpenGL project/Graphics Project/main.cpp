#if defined (_WIN32)
#include <windows.h>
#endif
#if defined (__APPLE__) || defined (MACOSX)
#include <GL/glew.h>
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/glu.h>
#endif

#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <vector>


using namespace std;
int windowWidth = 640 , windowHeight = 480;
bool lbuttonDown = false;
bool rbuttonDown = false;
int mouse_x  = 0, mouse_y = 0;
//float camerapositionX = 12, camPosY = 8 , camPosZ = 12;
float camerapositionX = 10, camerapositionY = 8 , camerapositionZ = 30;

float camViewX = 0, camViewY = 0, camViewZ = 0;
const std::string renderingMode = "3D"; // "2D"
GLfloat materialShininess[] = {30.0f};

float transx=0,transy=0,rot=0,rot1=0;
bool WTopRight = false, WTopLeft = false, WBottomRight = false, WBottomLeft = false, Bike = false;
float BikeAng = 0.0f, wheelAng = 0.0f;
#define PI 3.14159265


void setupWindowAndProjection();
void resetModelViewMatrix();
bool init();

void Display();

void LeftButtonEvent();
void RightButtonEvent();
void Mouse(int button, int state, int x, int y);
void Motion(int x, int y);
void PassiveMotion(int x, int y);
void Keyboard(unsigned char key, int x, int y);
void KeyboardUp(unsigned char key, int x, int y);
void SpecialKey(int key, int x, int y);

void Reshape(int width, int height);
void Idle();

void drawAxis(int length);
void Window(float center_X ,float center_Y,  float center_Z, float height, float width);
void roof(float center_X ,float center_Y,  float center_Z, float TRLength , int angSigne, int type);


int main(int argc, char *argv[]){
	
	glutInit(&argc, argv);

	glutInitWindowPosition(200, 200);
	glutInitWindowSize(windowWidth, windowHeight);
	
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	//glutCreateWindow(std::string(renderingMode + " GLUT , OpenGL & GLEW Template").c_str());
	glutCreateWindow(std::string(" grapics project").c_str());
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutIdleFunc(Idle);
	glutPassiveMotionFunc(PassiveMotion);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKey);
	glutKeyboardUpFunc(KeyboardUp);

	glewInit();

    if (!GLEW_VERSION_2_0) {
        std::cout << "OpenGL 2.0 not available\n";
        return 1;
    }

	if (!init())
		return 2;

	glutMainLoop();

	return 0;
}

bool init(){

	glClearColor(0.1f, 0.2f, 0.3f, 0.0f);

	glPointSize(3.0);
	glLineWidth(2.0);


	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

	if ( renderingMode == "3D" ){
		
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_NORMALIZE);

		glShadeModel(GL_FLAT);
		glShadeModel(GL_SMOOTH);

		//GLfloat lightPos[] = {2.0f , 1.0f , 2.0f , 0.0f};

		GLfloat lightPos[] = {camerapositionX +15, camerapositionY+15 , camerapositionZ +5, 0.0f};

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



void Display(){

	setupWindowAndProjection();
	//drawAxis(300);

	resetModelViewMatrix();
	glColor3f(0.0f, 0.3f, 0.0f);
	//GROUND
	glBegin(GL_POLYGON);
		glVertex3f(-50.0f,0.0f,-50.0f);
		glVertex3f(-50.0f,0.0f,50.0f);
		glVertex3f(50.0f,0.0f,50.0f);
		glVertex3f(50.0f,0.0f,-50.0f);		
	glEnd();
	
	
	glPushMatrix();
		glColor3f(0.5f,0.5f,0.2f);
		glScalef(2.5f, 2.0f , 1.5f);
		glTranslatef(0.0f,4.0f,0.0f);
		glutSolidCube(8);
	glPopMatrix();

	//Top left window background
 	glPushMatrix();
		glColor3f(0.0f, 0.0f, 0.8f);
		Window(-6.5f,12.5f,6.1f,3,4.5);

		if(WTopLeft){
			glTranslatef((-6.5f-2), (12.5f-4.5),6.1f);
			glRotatef(rot, 0.0f, 1.0f, 0.0f);
			glTranslatef(-(-6.5f-2), -(12.5f-4.5),-6.1f);
		}
		glColor3f(0.3f, 0.5f, 0.8f);
		Window(-6.5f,12.5f,6.2f,3,4.5);
	glPopMatrix();


	//Top right window background
	glPushMatrix();
		glColor3f(0.8f, 0.0f, 0.0f);
		Window(6.5f,12.5f,6.1f,3,4.5);
		if(WTopRight){
			glTranslatef((6.5f-2), (12.5f-4.5),6.1f);
			glRotatef(rot, 0.0f, 1.0f, 0.0f);
			glTranslatef(-(6.5f-2), -(12.5f-4.5),-6.1f);
		}
		glColor3f(0.3f, 0.0f, 0.8f);
		Window(6.5f,12.5f,6.2f,3,4.5);
	glPopMatrix();	

	//bottom left window background
	glPushMatrix();
		glColor3f(0.4f, 0.3f, 0.5f);
		Window(-6.5f,7.5f,6.1f,3,4.5);

		if(WBottomLeft){
			glTranslatef((-6.5f-2), (7.5f-4.5),6.1f);
			glRotatef(rot, 0.0f, 1.0f, 0.0f);
			glTranslatef(-(-6.5f-2), -(7.5f-4.5),-6.1f);
		}
		glColor3f(0.4f, 0.7f, 0.2f);
		Window(-6.5f,7.5f,6.2f,3,4.5);
	glPopMatrix();

	//bottom right window background
	glPushMatrix();
		glColor3f(0.8f, 0.0f, 0.0f);
		Window(6.5f,7.5f,6.1f,3,4.5);

		if(WBottomRight){
			glTranslatef((6.5f-2), (7.5f-4.5),6.1f);
			glRotatef(rot, 0.0f, 1.0f, 0.0f);
			glTranslatef(-(6.5f-2), -(7.5f-4.5),-6.1f);
		}
		glColor3f(0.0f, 0.7f, 0.2f);
		Window(6.5f,7.5f,6.2f,3,4.5);

	glPopMatrix();

	//Door background
	glPushMatrix();
		glColor3f(0.8f, 0.0f, 0.0f);
		Window(0.0f,4.0f,6.1f,5.5,4.0);
		
			glTranslatef((0.0f-2), (4.0f-4.0),6.1f);
			glRotatef(rot1, 0.0f, 1.0f, 0.0f);
			glTranslatef(-(0.0f-2), -(4.0f-4.0),-6.1f);
		
		glColor3f(0.4f, 0.3f, 0.2f);
		Window(0.0f,4.0f,6.2f,5.5,4.0);
	glPopMatrix();
	//Stairs
	glPushMatrix();
		glColor3f(0.6f, 0.4f, 0.4f);
		glScalef(2.5f, 0.2f , 2.0f);
		glTranslatef(0.0f,1.0f,4.0f);
		glutSolidCube(2);
	glPopMatrix();
	//Stairs
	//resetModelViewMatrix();
	glPushMatrix();
		glColor3f(0.6f, 0.4f, 0.4f);
		glScalef(2.5f, 0.5f , 1.5f);
		glTranslatef(0.0f,1.5f,4.0f);
		glutSolidCube(2);
	glPopMatrix();

	//roof
	glPushMatrix();
		glColor3f(0.2f, 0.5f, 0.2f);
		roof(0.0f, 21.8f, 6.2f, 20, 1, 0);
		roof(0.0f, 21.8f, -6.2f, 20, -1, 0);
		glRotatef(90, 0, 1, 0);
		roof(0.0f, 21.8f, 6.2f, 20, 3, 0);
		roof(0.0f, 21.8f, -6.2f, 20, -3, 0);
		//roof(16.0f, 21.8f, -6.2f, 20, -1, 1);
	glPopMatrix();

	//Bike
	glPushMatrix();
		glTranslatef(transx, 0.0f, 0.0f);
		
		glRotatef(BikeAng, 0, 1, 0);
		

		glColor3f(1.0f, 0.0f,0.0f);
		glTranslatef(0.8,.85,18.0f);
		glRotatef(180, 1,0,0);
	    
	  


	    GLUquadricObj* wheel1 ;
	     wheel1 = gluNewQuadric();
	     glPushMatrix();
	     glTranslatef(0.0,0.0,0.9);
	     gluDisk(wheel1, 0.0, 0.9, 32, 1);
	     gluCylinder(wheel1,0.9f,0.9f,0.1f,32,32);
	     glPopMatrix();
	     glTranslatef(0.0,0.0,0.9);
	    gluDisk(wheel1, 0.0, 0.9, 32, 1);
	    gluDeleteQuadric(wheel1);
	 glPopMatrix(); 
	 
	 glPushMatrix();
	 	glTranslatef(transx, 0.0f, 0.0f);
	 	glRotatef(BikeAng, 0, 1, 0);
		glColor3f(1.0f, 0.0f,0.0f);
		glTranslatef(3.8,.85,18.0f);
		glRotatef(180, 1,0,0);

		glTranslatef(0.1f,0.5f, 0.95f);
		glRotatef(wheelAng, 0,1,0);
	    glTranslatef(-0.1f,-0.5f,-0.95f);


	    GLUquadricObj* wheel2 ;
	     wheel2 = gluNewQuadric();
	     glPushMatrix();
	     glTranslatef(0.0,0.0,0.9);
	     gluDisk(wheel2, 0.0, 0.9, 32, 1);
	     gluCylinder(wheel2,0.9f,0.9f,0.1f,32,32);
	     glPopMatrix();
	     glTranslatef(0.0,0.0,0.9);
	    gluDisk(wheel2, 0.0, 0.9, 32, 1);
	    gluDeleteQuadric(wheel2);
	 glPopMatrix();
	 
	 glPushMatrix();
	 	glTranslatef(transx, 0.0f, 0.0f);
		 glRotatef(BikeAng, 0, 1, 0);
		 glColor3f(0.3f, 0.5f,0.2f);
		 glTranslatef(2.2,0.85f,17.05f);
		 glScalef(1.5f, 0.05f , 0.05f);
		 glutSolidCube(2);
	 glPopMatrix();

	 if(Bike)
	 	BikeAng++;

	glutSwapBuffers();
}

void resetModelViewMatrix(){

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if ( renderingMode == "3D" )
		gluLookAt(camerapositionX, camerapositionY, camerapositionZ,     camViewX, camViewY, camViewZ,     0, 1, 0);
}

void setupWindowAndProjection(){

	if ( renderingMode == "2D" )
		glClear(GL_COLOR_BUFFER_BIT);
	else if ( renderingMode == "3D" )
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if ( renderingMode == "2D" )
		gluOrtho2D(-windowWidth,windowWidth,-windowHeight,windowHeight);
	else if ( renderingMode == "3D" )
		gluPerspective(45.0f,(GLfloat)windowWidth/(GLfloat)windowHeight, 0.5f ,150.0f);

	resetModelViewMatrix();
	
	glViewport(0,0,windowWidth,windowHeight);
}

void LeftButtonEvent(){
	Bike = true;
}

void RightButtonEvent(){
	Bike = false;
}

void Mouse(int button, int state, int x, int y){

	mouse_x = x - windowWidth/2;
	mouse_y = (y - windowHeight/2) * -1;

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
		else
			lbuttonDown = false;
	}
}

void Motion(int x, int y){

	mouse_x = x - windowWidth/2;
	mouse_y = (y - windowHeight/2) * -1;

	glutSetCursor(GLUT_CURSOR_SPRAY);

	if (lbuttonDown)
		std::cout << "Mouse dragged with left button at "<< "(" << mouse_x << "," << mouse_y << ")" << std::endl;

	else if (rbuttonDown)
		std::cout << "Mouse dragged with right button at "<< "(" << mouse_x << "," << mouse_y << ")" << std::endl;
}

void PassiveMotion(int x, int y){

	mouse_x = x - windowWidth/2;
	mouse_y = (y - windowHeight/2) * -1;
	//std::cout << "Mouse moved at "<< "(" << mouse_x << "," << mouse_y << ")" << std::endl;
}

void Keyboard(unsigned char key, int x, int y){

	switch(key){
		case 'w':
			transy++;
		break;
		case 's':
			transy--;

		break;
		case 'f':
			transx++;
		break;
		case 'b':
			transx--;
		break;
		case 'r':
			if(wheelAng < 45)
				wheelAng++;
		break;
		case 'l':
			if(wheelAng > -45)
				wheelAng--;
		break;

		case '0':
			camerapositionZ++;
		break;
		case '.':
			camerapositionZ--;
		break;
		case 'C':
			if(rot<0)
				rot++;
			
		break;
		case 'O':
			if(rot > -90)
				rot--;
		break;

		case 'c':
			if(rot1<0)
				rot1++;
			
		break;
		case 'o':
			if(rot1 > -90)
				rot1--;
		break;



		case '+':
		++materialShininess[0];
		break;

		case '-':
		--materialShininess[0];
		break;
	// Backspace
	case 8 :
		std::cout << "Pressed Backspace" << std::endl;
		break;

	// Escape
	case 27 :
		std::cout << "Pressed Escape" << std::endl;
		break;

	// Delete
	case 127 :
		std::cout << "Pressed key : " << (char)key << " at position : ("<< x << "," << y << ")" << std::endl;
		break;

	/*default : 
		std::cout << "Pressed key : " << (char)key << " at position : ("<< x << "," << y << ")" << std::endl;
		break;*/
	}

	int mod = glutGetModifiers();

	switch(mod){

	case GLUT_ACTIVE_CTRL :
		break;
	case GLUT_ACTIVE_SHIFT :
		
		break;
	case GLUT_ACTIVE_ALT :
		std::cout << "Alt Held" << std::endl; 
		break;
	}
}

void KeyboardUp(unsigned char key, int x, int y){

		x=0; y=0;
}


void SpecialKey(int key, int x, int y){

	switch(key){

	case GLUT_KEY_F1 :
			WTopLeft = true;
			WTopRight = WBottomLeft = WBottomRight = false;
			rot = 0;
		break;

	case GLUT_KEY_F2 :
			WTopRight = true;
			WTopLeft = WBottomLeft = WBottomRight = false;
			rot = 0;
		break;
	case GLUT_KEY_F3 :
			WBottomLeft = true;
			WTopRight = WTopLeft = WBottomRight = false;
			rot = 0;
	break;
	case GLUT_KEY_F4 :
			WBottomRight = true;
			WTopRight = WBottomLeft = WTopLeft = false;
			rot = 0;
	break;
	case GLUT_KEY_F5 :
			
			WTopRight = WBottomLeft = WBottomRight = WTopLeft = false;
	break;	

	case GLUT_KEY_UP :
	     camerapositionY ++;
		
		break;

		case GLUT_KEY_DOWN :
	     camerapositionY --;
		
		break;


		case GLUT_KEY_RIGHT :
	     camerapositionX ++;
		
		break;

		case GLUT_KEY_LEFT :
	     camerapositionX --;
		
		break;

	case GLUT_KEY_INSERT :
		{
			int modifiers = glutGetModifiers();

			if (modifiers == (GLUT_ACTIVE_CTRL | GLUT_ACTIVE_ALT)){

				std::cout << "Pressed Insert " <<"with only Ctrl and Alt" << std::endl;
			}
			else if (modifiers & GLUT_ACTIVE_CTRL && modifiers & GLUT_ACTIVE_ALT){

				std::cout << "Pressed Insert " <<"with Ctrl and Alt" << std::endl;
			}

			break;
		}



	}
}

void Reshape(int width, int height){

	windowWidth = width;
	windowHeight = height;

	std::cout << "Current Width & Height = (" << width << " , " << height << ")" << std::endl;
}

void Idle(){

	glutPostRedisplay();
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
void Window(float center_X ,float center_Y,  float center_Z, float height, float width){
	glBegin(GL_QUADS);
		glVertex3f(center_X-width/2,center_Y-height/2, center_Z);
		glVertex3f(center_X+width/2,center_Y-height/2, center_Z);
		glVertex3f(center_X+width/2,center_Y+height/2, center_Z);
		glVertex3f(center_X-width/2,center_Y+height/2, center_Z);
	glEnd();	
}
void roof(float center_X ,float center_Y,  float center_Z, float TRLength , int angSigne, int type){
	float ANG = (30 * PI) / 180.0f;
	float R = (TRLength/2.0f) / (cos(ANG));

	glBegin(GL_TRIANGLES);
		glVertex3f(center_X-R,  center_Y - R/2,  center_Z - R/1.8 * angSigne * type);
		glVertex3f(center_X,    center_Y + R /2, center_Z - R/1.8 * angSigne);
		glVertex3f(center_X+R,  center_Y - R /2,  center_Z - R/1.8 * angSigne * type);
	glEnd();
}
