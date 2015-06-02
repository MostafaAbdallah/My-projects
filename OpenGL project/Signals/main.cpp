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
#include <glm/glm.hpp>

#endif
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <fstream>
#include <utility>



int windowWidth = 640 , windowHeight = 480;
bool ignoreRepeats = false;
bool lbuttonDown = false;
bool rbuttonDown = false;
int mouse_x  = 0, mouse_y = 0;
float camPosX = 12, camPosY = 8 , camPosZ = 12;
float camViewX = 0, camViewY = 0, camViewZ = 0;
const std::string renderingMode = "2D"; // "2D"
float rot = 0.0f;
GLfloat materialShininess[] = {30.0f};

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
void KeyboardUp(unsigned char key, int x, int y);
void SpecialKey(int key, int x, int y);
void Reshape(int width, int height);
void Idle();
void print(std::string s,int x , int y);
std::vector<glm::vec3> transformation(std::vector<glm::vec3> v);

int main(int argc, char *argv[]){

	glutInit(&argc, argv);

	glutInitWindowPosition(200, 200);
	glutInitWindowSize(windowWidth, windowHeight);
	
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	glutCreateWindow(std::string(renderingMode + " GLUT , OpenGL & GLEW Template").c_str());

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

	glPointSize(5.0);
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
		
		glShadeModel(GL_SMOOTH);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		GLfloat lightPos[] = {2.0f , 10.0f , 2.0f , 0.0f};
		GLfloat lightAmbient[] = {0.0f , 0.0f , 0.0f , 0.0f};
		GLfloat lightDiffuse[] = {1.0f , 1.0f , 1.0f , 0.0f};
		GLfloat lightSpecular[] = {1.0f , 0.5f , 0.0f , 0.0f};

		glLightfv(GL_LIGHT0, GL_POSITION , lightPos);
		glLightfv(GL_LIGHT0, GL_AMBIENT , lightAmbient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE , lightDiffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR , lightSpecular);
	}


	return true;
}

std::vector<glm::vec3> points;
bool start=false, draw=false;
char buffer[3];
float shift=200, scalar=-1.5; 
void Display(){

	setupWindowAndProjection();
	drawAxis(windowWidth);
		glPointSize(8.0);
		glLineWidth(1.5);
	glBegin(GL_POINTS);
		for (int i = -10; i < 10; ++i){
			glColor3f(0.5f,0.5f,1.0f);
			glVertex3i(i*100, 0,0);

		}
	glEnd();
	glBegin(GL_POINTS);
		for (int i = -10; i < 10; ++i){
			glColor3f(0.5f,0.5f,0.5f);
			glVertex3i(0,i*100,0);

		}
	glEnd();
	glColor3f(1.0f,0.5f,0.3f);
	if(draw){
		glBegin(GL_LINE_STRIP);
			for (auto i = 0u; i < points.size(); ++i){
				glVertex3i(points[i].x, points[i].y,0);
			
			}
		glEnd();
	}
	glColor3f(1.0f,1.0f,0.3f);
	glBegin(GL_POINTS);
		for (auto i = 0u; i < points.size(); ++i){
			glVertex3i(points[i].x, points[i].y,0);

		}
	glEnd();
	if(start){
		points=transformation(points);
		start=!start;
	}


	glutSwapBuffers();
	
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

	if ( renderingMode == "2D" )
		//gluOrtho2D(0.0,windowWidth,0.0,windowHeight);
			gluOrtho2D(-windowWidth  ,windowWidth,-windowHeight,windowHeight);

	else if ( renderingMode == "3D" )
		gluPerspective(45.0f,(GLfloat)windowWidth/(GLfloat)windowHeight, 0.5f ,150.0f);

	resetModelViewMatrix();
	
	glViewport(0,0,windowWidth,windowHeight);
	//glViewport(-windowWidth,windowWidth,-windowHeight,windowHeight);
}

void LeftButtonEvent(){
	points.push_back(glm::vec3(mouse_x, mouse_y ,0));
	/*std::cout<<points[1].x<<"------"<<points[1].y<<std::endl;
	system("pause");*/
}

void RightButtonEvent(){

}

void Mouse(int button, int state, int x, int y){

	mouse_x = (x-windowWidth/2)*2;
	mouse_y = (y-windowHeight/2)*2*-1;

	glutSetCursor(GLUT_CURSOR_LEFT_ARROW);

	if (button == GLUT_RIGHT_BUTTON){

		if (state == GLUT_DOWN){
			std::cout << "Right button pressed"<< std::endl;
			rbuttonDown = true;
			RightButtonEvent();
		}
		else{
			std::cout << "Right"<< "at (" << x << "," <<y<< ")" << std::endl;

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

	mouse_x = (x-windowWidth/2)*2;
	mouse_y = (y-windowHeight/2)*2*-1;

	glutSetCursor(GLUT_CURSOR_SPRAY);

	if (lbuttonDown){
		std::cout << "Mouse dragged with left button at "<< "(" << mouse_x << "," << mouse_y << ")" << std::endl;
		std::cout << "Mouse  "<< "(" << x << "," << y << ")" << std::endl;
	}
	else if (rbuttonDown)
		std::cout << "Mouse dragged with right button at "<< "(" << mouse_x << "," << mouse_y << ")" << std::endl;
}

void PassiveMotion(int x, int y){
	mouse_x = (x-windowWidth/2)*2;
	mouse_y = (y-windowHeight/2)*2*-1;

	std::cout << "Mouse moved at "<< "(" << mouse_x << "," << mouse_y << ")" << std::endl;
}

void Keyboard(unsigned char key, int x, int y){

	switch(key){
		case ' ':
		start=true;
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

	// Enter
	case 13 :
		draw=true;
		std::cout << "Pressed Enter" << std::endl;
		break;

	// Escape
	case 27 :
		std::cout << "Pressed Escape" << std::endl;
		break;

	// Delete
	case 127 :
		std::cout << "Pressed Delete" << std::endl;
		break;

	default : 
		std::cout << "Pressed key : " << (char)key << " at position : ("<< x << "," << y << ")" << std::endl;
		break;
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

	if (key == 'a')
		std::cout << "a key lifted" << " at position : (" << x << "," << y << ")" << std::endl;
}

void SpecialKey(int key, int x, int y){

	switch(key){

	case GLUT_KEY_F2 :
		std::cout << "Pressed F2" << " at position : (" << x << "," << y << ")" << std::endl;
		break;

	case GLUT_KEY_UP :
		std::cout << "Pressed Up" << " at position : (" << x << "," << y << ")" << std::endl;
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

	case GLUT_KEY_F1 :
		ignoreRepeats = !ignoreRepeats;
		glutIgnoreKeyRepeat(ignoreRepeats);
		
		if (ignoreRepeats)
			std::cout << "Repeates disabled" << std::endl;
		else
			std::cout << "Repeats enabled" << std::endl;

		break;

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

	glLineWidth(3);
	glBegin(GL_LINES);
		glColor3f(1,0,0);
		glVertex3i(0,0,0);
		glVertex3i(0,length,0);

		glColor3f(1,0,0);
		glVertex3i(0,0,0);
		glVertex3i(0,-length,0);

		glColor3f(0,1,0);
		glVertex3i(0,0,0);
		glVertex3i(length,0,0);


		glColor3f(0,1,0);
		glVertex3i(0,0,0);
		glVertex3i(-length,0,0);

		glColor3f(0,0,1);
		glVertex3i(0,0,0);
		glVertex3i(0,0,length);
	glEnd();

	if ( enableAgain )
		glEnable(GL_LIGHTING);
}
void print(std::string s,int x , int y){

	glRasterPos2i(x,y);

	for ( auto i = 0u ; i < s.length(); ++i )
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,s[i]);

}
std::vector<glm::vec3> transformation(std::vector<glm::vec3> v){
	std::vector<glm::vec3> new_point;
	int x=0;
	for (auto i = 0u; i < v.size(); ++i){
		x=(v[i].x-shift)/scalar;
		new_point.push_back(glm::vec3(x,points[i].y,0));
	}
	return new_point;
}