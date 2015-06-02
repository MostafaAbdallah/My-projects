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

int windowWidth = 640 , windowHeight = 480;
bool ignoreRepeats = false;
bool lbuttonDown = false;
bool rbuttonDown = false;
int mouse_x  = 0, mouse_y = 0;
float camPosX = 12, camPosY = 8 , camPosZ = 12;
float camViewX = 0, camViewY = 0, camViewZ = 0;
const std::string renderingMode = "3D"; // "2D"
float rot = 0.0f;
GLfloat materialShininess[] = {30.0f};
bool useLighting = true;

float x_1=0.0f, y_1=2.05f,z_1=0.0f;
float x_2=0.0f, y_2=1.55f,z_2=0.0f;
float x_3=0.0f, y_3=1.0f,z_3=0.0f;
float time_change=0.0f;

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
void tower();
void Disk();

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

	glPointSize(3.0);
	glLineWidth(2.0);

	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

	if ( renderingMode == "3D" && useLighting ){        //for lighhing

		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_NORMALIZE);

		glShadeModel(GL_FLAT);
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

void Display(){

	setupWindowAndProjection();
	drawAxis(10);
	tower();
	Disk();

	if(time_change<2.35f){
		if(time_change<0.6f)
			y_1=y_1+0.1f;
		else if (time_change<1.6f)
		 	x_1=x_1+0.1f;
		
		else if(time_change<2.35f){
			y_1=y_1-0.1f;
		}

		
	}

	else if(time_change<4.1f){
		if(time_change<2.9f)
			y_2=y_2+0.1f;
		else if (time_change<3.45f)
		 	x_2=x_2+0.1f;
		
		else if(time_change<4.1f){
			y_2=y_2-0.1f;
			
		}
		
	}

	else if(time_change<5.9f){
		if(time_change<4.8f)
			y_1=y_1+0.1f;
		else if (time_change<5.25f)
		 	x_1=x_1-0.1f;
		
		else if(time_change<5.9f){
			y_1=y_1-0.1f;
			
		}
		
	}

	else if(time_change<8.15f){
		if(time_change<6.5f)
			y_3=y_3+0.1f;
		else if (time_change<7.5f)
		 	x_3=x_3+0.1f;
		
		else if(time_change<8.15f){
			y_3=y_3-0.1f;
			
		}
		
	}

	else if(time_change<9.95f){
		if(time_change<8.75f)
			y_1=y_1+0.1f;
		else if (time_change<9.3f)
		 	x_1=x_1-0.1f;
		
		else if(time_change<9.95f){
			y_1=y_1-0.1f;
			
		}
		
	}
	else if(time_change<11.65f){
		if(time_change<10.6f)
			y_2=y_2+0.1f;
		else if (time_change<11.05f)
		 	x_2=x_2+0.1f;
		
		else if(time_change<11.65f){
			y_2=y_2-0.1f;
			
		}
		
	}

	else if(time_change<=13.85f){
		if(time_change<12.3f)
			y_1=y_1+0.1f;
		else if (time_change<13.3f)
		 	x_1=x_1+0.1f;
		
		else if(time_change<=13.85f){
			y_1=y_1-0.1f;
			
		}
		
	}
	time_change=time_change+.01;
	std::cout<<time_change<<std::endl;
	if(time_change>13.87f){
		std::cout<<"HERE";
		 x_1=0.0f;  y_1=2.05f; z_1=0.0f;
		 x_2=0.0f;  y_2=1.55f; z_2=0.0f;
		 x_3=0.0f;  y_3=1.0f; z_3=0.0f;
		 time_change=0.0f;		
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
		gluOrtho2D(0.0,windowWidth,0.0,windowHeight);
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
		else
			lbuttonDown = false;
	}
}

void Motion(int x, int y){

	mouse_x = x;
	mouse_y = (y - windowHeight) * -1;

	glutSetCursor(GLUT_CURSOR_SPRAY);

	if (lbuttonDown)
		std::cout << "Mouse dragged with left button at "<< "(" << mouse_x << "," << mouse_y << ")" << std::endl;

	else if (rbuttonDown)
		std::cout << "Mouse dragged with right button at "<< "(" << mouse_x << "," << mouse_y << ")" << std::endl;
}

void PassiveMotion(int x, int y){

	mouse_x = x;
	mouse_y = (y - windowHeight) * -1;

	std::cout << "Mouse moved at "<< "(" << mouse_x << "," << mouse_y << ")" << std::endl;
}
void Keyboard(unsigned char key, int x, int y){

		if (key=='8')
	    {
	            camPosX--;
	    }
	    if (key=='2')
	    {
	            camPosX++;
	    }
	    if (key=='4')
	    {
	            camPosZ--;
	    }
	     if (key=='6')
	    {
	            camPosZ++;
	    }
	    if (key=='0')
	    {
	            camPosY++;
	    }
	    if (key=='.')
	    {
	            camPosY--;
	    }

	    if (key=='9')
	    {
	            camViewX--;
	    }
	    if (key=='7')
	    {
	            camViewX++;
	    }
	    if (key=='3')
	    {
	            camViewZ--;
	    }
	     if (key=='1')
	    {
	            camViewZ++;
	    }
	    if (key=='*')
	    {
	            camViewY++;
	    }
	    if (key=='/')
	    {
	            camViewY--;
	   }


		std::cout << "Pressed key : " << (char)key << " at position : ("<< x << "," << y << ")" << std::endl;


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

void tower(){
		resetModelViewMatrix();
		glColor3f(0.5f,0.5f,0.5f);
		GLUquadricObj *q1;
	    q1 = gluNewQuadric();
	    glRotatef(270,1,0,0);
	    gluCylinder(q1,0.5f,0.5f,6.0f,80,10);

		resetModelViewMatrix();
		glColor3f(0.5f,0.5f,0.5f);
		glTranslatef(5.5,0,0);
	    GLUquadricObj *q2;
	    q2 = gluNewQuadric();
	    glRotatef(270,1,0,0);
	    gluCylinder(q2,0.5f,0.5f,6.0f,80,10);

		resetModelViewMatrix();
		glColor3f(0.5f,0.5f,0.5f);
		glTranslatef(10.10,0,0);
	    GLUquadricObj *q3;
	    q3 = gluNewQuadric();
	    glRotatef(270,1,0,0);
	    gluCylinder(q3,0.5f,0.5f,6.0f,80,10);

}

void Disk(){
	resetModelViewMatrix();
 	glColor3f(0.0f,0.5f,0.0f);
    GLUquadricObj* qobj1 = gluNewQuadric();
      glTranslatef(x_1, y_1, z_1);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    gluDisk(qobj1, 0.0, 1.3, 32, 1);
    gluCylinder(qobj1, 1.3f, 1.3, 0.5, 32, 1);
      glTranslatef(-x_1, -y_1, z_1);
      glTranslatef(x_1, y_1, z_1);
    gluDisk(qobj1, 0.0, 1.3, 32, 1);
      glTranslatef(-x_1, -y_1, z_1);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    gluDeleteQuadric(qobj1);

    	resetModelViewMatrix();
 	glColor3f(0.5f,0.5f,0.0f);
    GLUquadricObj* qobj2 = gluNewQuadric();
      glTranslatef(x_2, y_2, z_2);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    gluDisk(qobj2, 0.0, 1.6, 32, 1);
    gluCylinder(qobj2, 1.6f, 1.6, 0.5, 32, 1);
      glTranslatef(-x_2, -y_2, z_2);
      glTranslatef(x_2, y_2, z_2);
    gluDisk(qobj2, 0.0, 1.6, 32, 1);
      glTranslatef(-x_2, -y_2, z_2);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    gluDeleteQuadric(qobj2);

    	resetModelViewMatrix();
 	glColor3f(0.5f,0.0f,0.0f);
    GLUquadricObj* qobj3 = gluNewQuadric();
      glTranslatef(x_3, y_3, z_3);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    gluDisk(qobj3, 0.0, 2.0, 32, 1);
    gluCylinder(qobj3, 2.0f, 2.0, 0.5, 32, 1);
      glTranslatef(-x_3, -y_3, z_3);
      glTranslatef(x_3, y_3, z_3);
    gluDisk(qobj3, 0.0, 2.0, 32, 1);
      glTranslatef(-x_3, -y_3, z_3);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    gluDeleteQuadric(qobj3);

}