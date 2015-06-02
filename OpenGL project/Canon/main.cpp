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

int windowWidth = 640 , windowHeight = 480;
bool ignoreRepeats = false;
bool lbuttonDown = false;
bool rbuttonDown = false;
int mouse_x  = 0, mouse_y = 0;
float camPosX = 12, camPosY = 8 , camPosZ = 12;     //camera position
float camViewX = 0, camViewY = 0, camViewZ = 0;     // camera views
float transx=0,transy=0,transz=0,base_x=0,base_y=0,base_z=0,rot=0,rot1=0;
const std::string renderingMode = "3D"; // "2D"
bool useLighting = true;

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

int main(int argc, char *argv[]){

	glutInit(&argc, argv);

	glutInitWindowPosition(200, 200);
	glutInitWindowSize(windowWidth, windowHeight);

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	glutCreateWindow(std::string(renderingMode + " GLUT & OpenGL Template").c_str());

	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutIdleFunc(Idle);
	glutPassiveMotionFunc(PassiveMotion);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKey);
	glutKeyboardUpFunc(KeyboardUp);

	if (!init())
		return 1;

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

void resetModelViewMatrix(){                // to control with camera

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if ( renderingMode == "3D" )
		gluLookAt(camPosX, camPosY, camPosZ,     camViewX, camViewY, camViewZ,     0, 1, 0);
}

void setupWindowAndProjection(){            //make project work as 3D or 2D

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

void drawAxis(int length){              //  to draw the Axis X, Y, Z

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

//float rot = 0.0f;

void Display(){

	setupWindowAndProjection();
	drawAxis(15);

    glTranslatef(transx,transy,transz);
    glScalef(7,1,6);
    glColor3b(100,200,0);
    glutSolidCube(.5);



	resetModelViewMatrix();
    glTranslatef(transx,transy+.7,transz-1);
    glScalef(1,3,1);
    glColor3b(0,120,150);
    glutSolidCube(.6);

    resetModelViewMatrix();
    glTranslatef(transx,transy+.7,transz+1);
    glScalef(1,3,1);
    glColor3b(100,100,0);
    glutSolidCube(.6);

    resetModelViewMatrix();
   // glPushMatrix();

	//resetModelViewMatrix();
     glTranslatef(transx,transy,transz);
    glRotatef(rot,0,1,0);
     glTranslatef(-transx,-transy,-transz);
     //glPopMatrix();

    glTranslatef(transx,transy,transz);
    GLUquadricObj* qobj = gluNewQuadric();
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    gluDisk(qobj, 0.0, 0.0, 32, 1);
    gluCylinder(qobj, 1.0f, 1.0, 1.0, 32, 1);
    glTranslatef(0.0f, 0.0f, 1.0f);
   // gluDisk(qobj, 0.0, 1.0, 32, 1);
    glTranslatef(0.0f, 0.0f, -2.0f);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    gluDeleteQuadric(qobj);

    resetModelViewMatrix();
    glTranslatef(transx-.8,transy,transz+1.7);
    glColor3b(00,00,00);
    GLUquadricObj* wheel1 ;
     wheel1 = gluNewQuadric();
    gluDisk(wheel1, 0.0, .5, 32, 1);
    gluDeleteQuadric(wheel1);

    resetModelViewMatrix();
    glTranslatef(transx+.8,transy,transz+1.7);
    glColor3b(00,00,00);
    GLUquadricObj* wheel2 ;
     wheel2 = gluNewQuadric();
    gluDisk(wheel2, 0.0, .5, 32, 1);
    gluDeleteQuadric(wheel2);



    resetModelViewMatrix();
    glTranslatef(transx+.8,transy,transz-1.7);
    glColor3b(00,00,00);
    GLUquadricObj* wheel3 ;
     wheel3 = gluNewQuadric();
    gluDisk(wheel3, 0.0, .5, 32, 1);
    gluDeleteQuadric(wheel3);


     resetModelViewMatrix();
    glTranslatef(transx-.8,transy,transz-1.7);
    glColor3b(00,00,00);
    GLUquadricObj* wheel4 ;
     wheel4 = gluNewQuadric();
    gluDisk(wheel4, 0.0, .5, 32, 1);
    gluDeleteQuadric(wheel4);

     resetModelViewMatrix();
     glColor3b(00,100,00);
     glTranslatef(transx-.8,transy,transz-2);
  /*  GLUquadricObj *q1;
    q1 = gluNewQuadric();
    glRotatef(360,0,1,0);
    gluCylinder(q1,0.0f,0.2f,0.9f,32,32);*/

      resetModelViewMatrix();
     glColor3b(00,100,00);
     glTranslatef(transx+.8,transy,transz-2);
    GLUquadricObj *q2;
    q2 = gluNewQuadric();
    glRotatef(360,0,1,0);
    gluCylinder(q2,0.0f,0.2f,0.9f,32,32);

      resetModelViewMatrix();
     glColor3b(00,100,00);
     glTranslatef(transx+.8,transy,transz+2);
    GLUquadricObj *q3;
    q3 = gluNewQuadric();
    glRotatef(180,0,1,0);
    gluCylinder(q3,0.0f,0.2f,0.9f,32,32);


      resetModelViewMatrix();
     glColor3b(00,100,00);
     glTranslatef(transx-.8,transy,transz+2);
    GLUquadricObj *q4;
    q4 = gluNewQuadric();
    glRotatef(180,0,1,0);
    gluCylinder(q4,0.0f,0.2f,0.9f,32,32);



    resetModelViewMatrix();
    glTranslatef(transx,transy,transz);
    glRotatef(rot,0,1,0);
     glTranslatef(-transx,-transy,-transz);

     glTranslatef(transx,transy,transz);
    glRotatef(rot1,0,0,1);
     glTranslatef(-transx,-transy,-transz);

    GLUquadricObj *quadratic;
quadratic = gluNewQuadric();
 glTranslatef(transx,transy+1.1,transz);
glRotatef(90,0,1,0);

gluCylinder(quadratic,0.6f,0.3f,4.8f,32,32);

resetModelViewMatrix();
glTranslatef(transx,transy,transz);
    glRotatef(rot,0,1,0);
     glTranslatef(-transx,-transy,-transz);

        glTranslatef(transx,transy,transz);
    glRotatef(rot1,0,0,1);
     glTranslatef(-transx,-transy,-transz);


glColor3b(100,100,0);
glTranslatef(transx,transy+1.1,transz);
glRotatef(90,0,1,0);
GLUquadricObj *q;
q = gluNewQuadric();
glRotatef(180,0,1,0);
gluCylinder(q,.6f,0.0f,1.2f,32,32);







	glutSwapBuffers();
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



    if (key=='a')
        {
            transx++;
        }
    if (key=='d')
        {
            transx--;
        }

         if (key=='-')
        {
            camPosZ--;
        }
    if (key=='+')
        {
           camPosZ++;
        }

        if (key=='w')
        {
            rot++;
        }
    if (key=='s')
        {
            rot--;
        }

         if (key=='z')
        {
            rot1++;
        }
    if (key=='x')
        {
            rot1--;
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
	     camPosY ++;
		std::cout << "Pressed Up" << " at position : (" << x << "," << y << ")" << std::endl;
		break;

		case GLUT_KEY_DOWN :
	     camPosY --;
		std::cout << "Pressed Up" << " at position : (" << x << "," << y << ")" << std::endl;
		break;


		case GLUT_KEY_RIGHT :
	     camPosX ++;
		std::cout << "Pressed Up" << " at position : (" << x << "," << y << ")" << std::endl;
		break;

		case GLUT_KEY_LEFT :
	     camPosX --;
		std::cout << "Pressed Up" << " at position : (" << x << "," << y << ")" << std::endl;
		break;
//		if ()


	/*case GLUT_KEY_INSERT :
		{
			int modifiers = glutGetModifiers();

			if (modifiers == (GLUT_ACTIVE_CTRL | GLUT_ACTIVE_ALT)){

				std::cout << "Pressed Insert " <<"with only Ctrl and Alt" << std::endl;
			}
			else if (modifiers & GLUT_ACTIVE_CTRL && modifiers & GLUT_ACTIVE_ALT){

				std::cout << "Pressed Insert " <<"with Ctrl and Alt" << std::endl;
			}

			break;
		}*/

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
