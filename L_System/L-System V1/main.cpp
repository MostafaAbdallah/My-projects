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
#include <fstream>
#include <stack>

using namespace std;
int windowWidth = 640 , windowHeight = 480;
bool ignoreRepeats = false;
bool lbuttonDown = false;
bool rbuttonDown = false;
int mouse_x  = 0, mouse_y = 0;
float Mouse_x=0.0f,Mouse_Y=0.0f;
float camPosX = 12, camPosY = 8 , camPosZ = 12;
float camViewX = 0, camViewY = 0, camViewZ = 0;
const std::string renderingMode = "2D"; // "2D"
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

string str = "";
int main(int argc, char *argv[]){
	
     fstream fin;
     fin.open("the-Lsys.txt", fstream::in);
     if(!fin.fail()){
    	 while (!fin.eof()) {
     		getline(fin, str);

     	}
     }
     else
     	cout<<"Error"<<endl;
    

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

	//glClearColor(1.0f, 0.0f, 0.0f, 0.0f);

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


float x=0;
float y=0; 
float tempx=0.0f;
float tempy=0.0f;
float tempan=0.0f;
float xnew;
float ynew;
float anglenew= 90.0;
float changeAngle = 0.0f;
#define PI 3.14159265
bool nochange = false;
float angle=90.0f;
const float len=20;
stack<float>bracket;
void Display(){

	setupWindowAndProjection();
	//drawAxis(300);
	x=0.0f;
	y=-500.0f; 
	xnew = 0.0f;
	ynew = 0.0f;
	anglenew = 90.0f;
	angle=90.0f;
	changeAngle = 22.5f;

//===============================================================================================================
   
  //glClear(GL_COLOR_BUFFER_BIT);     
  glMatrixMode(GL_MODELVIEW);       
  glLoadIdentity();     
  glColor3f ( 1.0, 0.3, 0.5); 
  
  glBegin(GL_LINES) ;             
     
   		for (int i = 0; i < str.size(); ++i){
	     		nochange = false;
	         if(str[i]=='F'){
	         	angle = anglenew * PI/180.0;
		   	 	xnew=x+len * (cos((angle)));
		    	ynew=y+len * (sin((angle)));

	        }
	        if(str[i]=='-'){
	         anglenew=anglenew-changeAngle;
	         nochange = true;
	        }
	        if(str[i]=='+'){
	         anglenew=anglenew+changeAngle;
	         nochange = true;
	        }  
	        if(str[i]=='['){
	        	/*tempx = x;
	        	tempy = y;
	        	tempan = anglenew;*/
	        	bracket.push(x);
	        	bracket.push(y);
	        	bracket.push(anglenew);

	        	nochange = true;

	        }
	        if(str[i]==']'){
	        	/*x = tempx ;
	        	y = tempy ;
	        	anglenew = tempan ;*/
	        	anglenew = bracket.top();
	        	bracket.pop();
	        	y = bracket.top();
	        	bracket.pop();
	        	x = bracket.top();
	        	bracket.pop();
	        	nochange = true;
	        }
	       
	         
	         if(anglenew > 360)
	         	anglenew = anglenew - 360;
	         else if(anglenew < 0)
	        	anglenew = anglenew + 360;	
	        
		   if(nochange == false){
		   		glColor3f ( 1.0, 0.3, 0.5); 
		   		glVertex2f(x, y);  
	        	glVertex2f( xnew,ynew );  
		   		x=xnew;
		   		y=ynew;     
		   }	                                   
	        
      
	}

  glEnd();
  
//========================================================================================================================


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
		gluOrtho2D(-windowWidth,windowWidth,-windowHeight,windowHeight);
	else if ( renderingMode == "3D" )
		gluPerspective(45.0f,(GLfloat)windowWidth/(GLfloat)windowHeight, 0.5f ,150.0f);

	resetModelViewMatrix();
	
	glViewport(0,0,windowWidth,windowHeight);
}

void LeftButtonEvent(){
	
}

void RightButtonEvent(){

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

	mouse_x = x;
	mouse_y = (y - windowHeight/2) * -1;

	glutSetCursor(GLUT_CURSOR_SPRAY);

	if (lbuttonDown)
		std::cout << "Mouse dragged with left button at "<< "(" << mouse_x << "," << mouse_y << ")" << std::endl;

	else if (rbuttonDown)
		std::cout << "Mouse dragged with right button at "<< "(" << mouse_x << "," << mouse_y << ")" << std::endl;
}

void PassiveMotion(int x, int y){

	mouse_x = x;
	mouse_y = (y - windowHeight) * -1;

	//std::cout << "Mouse moved at "<< "(" << mouse_x << "," << mouse_y << ")" << std::endl;
}

void Keyboard(unsigned char key, int x, int y){

	switch(key){
		case 'a':
			
		break;
		case 'd':

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
	case '0' :
		
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
		
		break;

	case GLUT_KEY_F2 :
		std::cout << "Pressed F2" << " at position : (" << x << "," << y << ")" << std::endl;
		break;
	

	case GLUT_KEY_LEFT :
		
		break;

	case GLUT_KEY_RIGHT :
		
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