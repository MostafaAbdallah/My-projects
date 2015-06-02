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
#include "BezierCurve.hpp"
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <vector>

int windowWidth = 640 , windowHeight = 480;
bool ignoreRepeats = false;
bool lbuttonDown = false;
bool rbuttonDown = false;
int mouse_x  = 0, mouse_y = 0;
float camPosX = 7, camPosY = 8 , camPosZ = 19;
float camViewX = 5, camViewY = 0, camViewZ = -8;
const std::string renderingMode = "3D"; // "2D"
float rot = 0.0f;
GLfloat materialShininess[] = {30.0f};
bool useLighting = true,notloop=true;
int num_disk=3;
int num_tower=3;
static unsigned int k = 0;
BezierBernsteinCurve curve;

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

void solve(int numOfDisks , int fromTower , int toTower , int tempTower);


struct Shape{
	Shape(glm::vec3 pos , glm::vec3 col , float size);
	glm::vec3 shape_position;
	glm::vec3 color;
	float shape_size;	
};

Shape::Shape(glm::vec3 pos , glm::vec3 col , float size) : shape_position(pos) , color(col) , shape_size(size){

}

std::vector<Shape> disks;
std::vector<Shape> towers;
std::vector< std::pair< glm::vec3, int > >draw_moves;
std::vector<glm::vec3> disk_position_for_curve(num_disk);

void draw_Disk(Shape d);
void creat_disk(int num_Disk);
void creat_tower(int num_tower);
void draw_tower(Shape t);
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
//fromTower is the tower which the disks start
//toTower is the tower where the disk will be in the end of program 
//tempTower is the tower that use to help us to move the disks
void solve(int numOfDisks , int fromTower , int toTower , int tempTower){

	if ( numOfDisks == num_disk ){

		// move disk 1 from fromTower to toTower 
		printf("move disk %d from tower %d to tower %d\n",numOfDisks,fromTower , toTower );
		// reset curve
		curve.resetCurve();
		// add control points
		//curve.addControlPoints(disks[numOfDisks-1].shape_position);
		curve.addControlPoints(disk_position_for_curve[numOfDisks-1]);
		curve.addControlPoints(towers[fromTower-1].shape_position+glm::vec3(0.0f,15.0f, 0.0f));
		curve.addControlPoints(towers[toTower-1].shape_position+glm::vec3(0.0f,15.0f, 0.0f));
		curve.addControlPoints(towers[toTower-1].shape_position + glm::vec3(0,numOfDisks,0));
		// generate curve
		curve.generateCurve(0.01f);
		// move disk along curve
		for ( auto i = 0u; i < curve.curvePointsVector().size(); ++i){
			disk_position_for_curve[numOfDisks-1]= curve.curvePointsVector()[i];
			//disks[numOfDisks-1].shape_position = curve.curvePointsVector()[i];
			draw_moves.push_back(std::make_pair(curve.curvePointsVector()[i], (numOfDisks-1)));
		}
		return;
	}

	solve(numOfDisks+1 , fromTower , tempTower , toTower);

	// move disk number "numOfDisks" from fromTower to toTower
	printf("move disk %d from tower %d to tower %d\n",numOfDisks,fromTower , toTower );
	// reset curve
	curve.resetCurve();
	// add control points
	//curve.addControlPoints(disks[numOfDisks-1].shape_position);
	curve.addControlPoints(disk_position_for_curve[numOfDisks-1]);
	curve.addControlPoints(towers[fromTower-1].shape_position+glm::vec3(0.0f,15.0f, 0.0f));
	curve.addControlPoints(towers[toTower-1].shape_position+glm::vec3(0.0f,15.0f, 0.0f));
	curve.addControlPoints(towers[toTower-1].shape_position + glm::vec3(0,numOfDisks,0));
	// generate curve
	curve.generateCurve(0.01f);
	// move disk along curve
	for ( auto i = 0u; i < curve.curvePointsVector().size(); ++i){
		disk_position_for_curve[numOfDisks-1]= curve.curvePointsVector()[i];
		//disks[numOfDisks-1].shape_position = curve.curvePointsVector()[i];
		draw_moves.push_back(std::make_pair(curve.curvePointsVector()[i], (numOfDisks-1)));
	}

	solve(numOfDisks+1 , tempTower , toTower , fromTower);	
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

	if ( renderingMode == "3D" && useLighting && notloop){        //for lighhing

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
	disks.clear();
	towers.clear();
	draw_moves.clear();
	disk_position_for_curve.clear();
	curve.resetCurve();
	creat_disk(num_disk);
	creat_tower(num_tower);
	/*curve.addControlPoints(disks[disks.size()-1].shape_position);
	curve.addControlPoints(towers[0].shape_position+glm::vec3(0.0f,15.0f, 0.0f));
	curve.addControlPoints(towers[1].shape_position+glm::vec3(0.0f,15.0f, 0.0f));
	curve.addControlPoints(towers[1].shape_position);
	curve.generateCurve(0.01f);*/

	solve(1, 1, 3 , 2);
	return true;
}

void Display(){

	setupWindowAndProjection();
	drawAxis(10);
	//static unsigned int k = 0;
	int currnt_index;
		if ( k < draw_moves.size() ){
			currnt_index=draw_moves[k].second;
			disks[currnt_index].shape_position = draw_moves[k].first;
			k++;
			//k =(k+1)%draw_moves.size();
		}
	//for ( auto i = 0u; i < curve.curvePointsVector().size(); ++i)
		

		//if ( k < curve.curvePointsVector().size() ){
		//	disks[disks.size()-1].shape_position = curve.curvePointsVector()[k];
		//	k ++;
			//k %= curve.curvePointsVector().size();
		//}
		//k %= curve.curvePointsVector().size();

/*	curve.drawControlPolygon(false,1,glm::vec4(1,0,1,0));

	curve.drawCurvePoints(2,glm::vec4(0,1,0,0));

	curve.drawControlPoints(true,10,glm::vec4(1,1,0,0));

	curve.drawConstructionPolygon(true , 1 , glm::vec4(0,151,70,0) ,50);*/


	for (auto i = 0u; i < disks.size(); ++i)
		draw_Disk(disks[i]);

	for (auto i = 0u; i < towers.size(); ++i)
		draw_tower(towers[i]);

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

	if (key=='8'){
        camPosX--;
    }
    if (key=='2'){
        camPosX++;
    }
    if (key=='4'){
        camPosZ--;
    }
     if (key=='6'){
        camPosZ++;
    }
    if (key=='0'){
        camPosY++;
    }
    if (key=='.'){
        camPosY--;
    }
    if (key=='9'){
        camViewX--;
    }
    if (key=='7'){
        camViewX++;
    }
    if (key=='3'){
        camViewZ--;
    }
     if (key=='1'){
        camViewZ++;
    }
    if (key=='*'){
        camViewY++;
    }
    if (key=='/'){
        camViewY--;
    }
    if (key==' '){
    	num_disk++;
    	notloop=false;
    	resetModelViewMatrix();
    	setupWindowAndProjection();
        init();
        k=0;

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

void draw_tower(Shape t){
	resetModelViewMatrix();
	glColor3f(t.color.x, t.color.y, t.color.z);
	GLUquadricObj *q1;
    q1 = gluNewQuadric();
    	glTranslatef(t.shape_position.x,t.shape_position.y, t.shape_position.z);
    	glRotatef(270,1,0,0);
    gluCylinder(q1,0.5f,0.5f,6.0f,80,10);
		
}

void draw_Disk(Shape d){
	resetModelViewMatrix();
 	glColor3f(d.color.x, d.color.y, d.color.z);
    GLUquadricObj* qobj = gluNewQuadric();
    	glTranslatef(d.shape_position.x, d.shape_position.y, d.shape_position.z);
    	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    gluDisk(qobj, 0.0, d.shape_size, 32, 1);
    gluCylinder(qobj, d.shape_size, d.shape_size, 0.5, 32, 1);
      glTranslatef(-d.shape_position.x, -d.shape_position.y, -d.shape_position.z);
      glTranslatef(d.shape_position.x, d.shape_position.y, d.shape_position.z);
    gluDisk(qobj, 0.0, d.shape_size, 32, 1);
      	glTranslatef(-d.shape_position.x, -d.shape_position.y, -d.shape_position.z);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    gluDeleteQuadric(qobj);
}

void creat_disk(int num_Disk){
	float disk_size = 2.5f;

	for (int i = 1; i <= num_Disk; ++i){
		disk_position_for_curve[i-1]=glm::vec3(5.0f, 5.0f*i*0.2, 0.0f);
		disks.push_back(Shape(glm::vec3(5.0f, 5.0f*i*0.2, 0.0f),glm::vec3(1.0f, i * 0.1f, i * 0.3f), disk_size));
		disk_size -= 0.3;
	}

}

void creat_tower(int num_tower){
	for (int i = 1; i <= num_tower; ++i){
		towers.push_back(Shape(glm::vec3(i*5.0f, 0.0f, 0.0f),glm::vec3(1.0f, i * 0.1f, i * 0.3f), 2.0f));
		//disk_size -= 0.3;
	}	
}