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
bool draw= false,draw_shift_points = false;
std::vector< glm::vec3 > controlPoints;
std::vector< glm::vec3 > shiftlPoints;
std::vector< glm::vec3 > curvePoints;
bool updated = false;
int selectedCp = -1;
bool edit = false;
char buffer[3];

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


int binomialCoefficient(const int& n , int r);
int specialFactorial(int n , const int& r);
int factorial(int n);
float bernsteinPolynomial(const int& n,const int& i,const float& t);
glm::vec3 bezierCurve(const std::vector< glm::vec3 >& cp,const float& t);

int specialFactorial(int n , const int& r){

    int result = 1;

    for ( int i = 0; i < r; ++i ){

        result *= n;
        --n;
    }

    return result;
}

int factorial(int n){

    int result = 1;

    while (n){
        result *= n;
        --n;
    }

    return result;
}

int binomialCoefficient(const int& n , int r){

    if (n - r < r)
        r = n - r;

    return specialFactorial(n,r) / factorial(r);
}

float bernsteinPolynomial(const int& n,const int& i,const float& t){

    return binomialCoefficient(n , i) * std::pow(t , i) * std::pow(1.0f - t , n - i);
}

glm::vec3 bezierCurve(const std::vector< glm::vec3 >& cp,const float& t){

    glm::vec3 p;

    // size - 1 not size
    // because in the math two points
    // are considered p0 and p1
    int n = cp.size()-1;

    // <= not <
    for ( int i = 0; i <= n; ++i )
        p += cp[i] * bernsteinPolynomial(n,i,t);

    return p;
}

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

	glClearColor(0.1f, 0.1f, 0.1f, 0.0f);

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

	if ( updated ){
		t = 0.0f;
		curvePoints.clear();

		while ( t <= 1.0 ){
	        curvePoints.push_back(bezierCurve(controlPoints,t));
	        t += 0.01;
	    }

	    updated = false;
	}

    glPointSize(3);
    glColor3ub(255,0,0);
    glBegin(GL_LINE_STRIP);

        for ( auto i = 0u ; i < curvePoints.size(); ++i )
            glVertex2f(curvePoints[i].x,curvePoints[i].y);

    glEnd();

   
    glPointSize(10);
    glColor3ub(255,255,0);
    glBegin(GL_POINTS);

        for ( auto i = 0u ; i < controlPoints.size(); ++i ){
        	if ( i == selectedCp )
        		glColor3ub(0,255,0);
        	else
        		glColor3ub(255,255,0);
            glVertex2f(controlPoints[i].x,controlPoints[i].y); 
        }

    glEnd();

    for ( auto i = 0u ; i < controlPoints.size(); ++i ){

    	glColor3f(0,1,1);
    	sprintf(buffer,"%i",i);

    	print(std::string(buffer),controlPoints[i].x,controlPoints[i].y);
    }

    glBegin(GL_POINTS);
    	glColor3f(1.0f,0.0f,1.0f);
    	for (int i=0; i<shiftlPoints.size(); ++i)
    		 glVertex2f(shiftlPoints[i].x,shiftlPoints[i].y); 

    glEnd();

    //--------------------------------------------------------------------
		glPointSize(1);
    	glBegin(GL_POINTS);
    	glColor3f(0.0f,0.0f,1);
    	glVertex2f(curvePoints[0].x,curvePoints[0].y);
    	for (int i=0;i<curvePoints.size();++i){


    			
    		//glVertex2f(curvePoints[i].x,curvePoints[i].y);
    	}
    	glEnd();


	glutSwapBuffers();
}

void print(std::string s,int x , int y){

	glRasterPos2i(x,y);

	for ( auto i = 0u ; i < s.length(); ++i )
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,s[i]);

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

	for ( auto i = 0u ; i < controlPoints.size(); ++i ){
        
		if ( isClickOnVertex(mouse_x , mouse_y , controlPoints[i].x , controlPoints[i].y) ) {
			edit = true;
			selectedCp = i;
			break;
		}
		else{
			edit = false;
			selectedCp = -1;
		}    	
    }  

}

void RightButtonEvent(){
	updated = true;
	if (draw_shift_points==true)
		shiftlPoints.push_back(glm::vec3(mouse_x,mouse_y,0.0));	
	else

		controlPoints.push_back(glm::vec3(mouse_x,mouse_y,0.0));
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
		controlPoints[selectedCp] = glm::vec3(mouse_x,mouse_y,0.0);
	}

	if (rbuttonDown)
		std::cout << "Mouse dragged with right button at "<< "(" << mouse_x << "," << mouse_y << ")" << std::endl;
}

void PassiveMotion(int x, int y){

	mouse_x = x;
	mouse_y = (y - windowHeight) * -1;

	std::cout << "Mouse moved at "<< "(" << mouse_x << "," << mouse_y << ")" << std::endl;
}

void SpecialKey(int key, int x, int y){

	switch(key){

	case GLUT_KEY_F1:
        exit(0);
		break;

	case GLUT_KEY_F2:
        
        std::cout << "control " << controlPoints.size() << std::endl;
        std::cout << "curve " << curvePoints.size() << std::endl;
        draw = true;
		break;

	case GLUT_KEY_F3:
        curvePoints.clear();
        controlPoints.clear();
        t = 0.0;
        draw = false;
		break;
		case GLUT_KEY_F4:
		draw_shift_points=true;
		break;

		case GLUT_KEY_F5:
		draw_shift_points=false;
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
