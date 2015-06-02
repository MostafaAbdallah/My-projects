#if defined (_WIN32)
#include <windows.h>
#endif
#if defined (__APPLE__) || defined (MACOSX)
#include <GL/glew.h>
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#else
#include <AntTweakBar/AntTweakBar.h>
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

bool light0_move=false, light1_move=false, light2_move=false, light_in_pos=true;
int switch_light[4]={0};
int switch_loc[4];

float my_tw_windows_size_width=100,my_tw_windows_size_hight=100;
float Tw=0;



int tranx=0,trany=0,tranz=0;
int mouse_x  = 0, mouse_y = 0;
float camPosX = -10, camPosY = 10, camPosZ = 15;
float camViewX = 0, camViewY = 0, camViewZ = 0;
const std::string renderingMode = "3D"; // "2D"  
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
GLuint make_program(GLuint vertex_shader, GLuint fragment_shader); // to link between the fragment and vertex. 
GLuint make_shader(GLenum type, const char *filename);	// to read (fragment OR vertex) shader
void show_info_log(GLuint object,PFNGLGETSHADERIVPROC glGet__iv,PFNGLGETSHADERINFOLOGPROC glGet__InfoLog);
GLuint make_texture(const char *filename);   	// to read the texture
void* read_tga(const char *filename, int *width, int *height,int *bpp);
short le_short(unsigned char *bytes);
char* textFileRead(const char *fn , int &length);
void print(std::string s,int x , int y, int z);


/*struct{
	struct {
			bool light0_switch=false, light1_switch=false, light2_switch=false,light_all_switch=false;
	}uniforms;
	//bool light0_switch=false, light1_switch=false, light2_switch=false,light_all_switch=false;

}phongShader;*/

struct{
	GLuint vertex_shader, fragment_shader, program;
    GLuint textures[2];
    GLfloat fade_factor;
    							//texture ---> put in it the address of texture
    							// (fragment OR vertex)_shader ---> put in it the address of (fragment OR vertex)_shader
    							//program---> put in it ihe program lineking ?!!										
    struct {
        GLint fade_factor;
        GLint textures[2];
    } uniforms;
    
} shaderResources;

struct{
	GLuint vertex_shader, fragment_shader, program;
    GLuint textures[2];

    struct {

        GLint textures[1];
    } uniforms;
    
} alphaShader;

struct{
	GLuint vertex_shader, fragment_shader, program;
     GLuint textures[1];
   //  GLuint  light0_switch, light1_switch, light2_switch,light_all_switch;

    struct {

        GLint textures[1];
    } uniforms;

} phongShader;

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
	TwInit(TW_OPENGL_CORE,NULL);
	//TwWindowSize(my_tw_windows_size_width,my_tw_windows_size_hight);
	TwBar *myBar;
	myBar=TwNewBar("Lights :)");
	TwAddVarRW(myBar,"Lights :)",TW_TYPE_FLOAT,&Tw,NULL);



/*	if (switch_light[0]==1){
		switch_loc[0]=glGetUniformLocation(program,switch_light[0]);
	}


	if (switch_light[1]==1){
		switch_loc[1]=glGetUniformLocation(program,switch_light[1]);
	}


	if (switch_light[2]==1){
		switch_loc[2]=glGetUniformLocation(program,switch_light[2]);
	}


	if (switch_light[3]==1){
		switch_loc[3]=glGetUniformLocation(program.switch_light[3]);
	}*/




	glewInit();

    if (!GLEW_VERSION_2_0) {
        std::cout << "OpenGL 2.0 not available\n";
        return 1;
    }

	if (!init())
		return 2;

	//TwDraw();
	glutMainLoop();
	//TwDraw();

	return 0;
}

void print(std::string s,int x , int y , int z){

	glRasterPos3i(x,y,z);

	for ( auto i = 0u ; i < s.length(); ++i )
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,s[i]);

}

/*GLfloat lightPos_1[] = {5.0f , 2.0f , 10.0f , 0.0f};
GLfloat lightPos2[] = {-5.0f , 10.0f , 2.0f , 0.0f};
GLfloat lightPos3[] = {5.0f , 6.0f , -8.0f , 0.0f};*/


GLfloat lightPos_1[4];
GLfloat lightPos2[4];
GLfloat lightPos3[4] ;


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
		

		glEnable(GL_NORMALIZE);
		
		glShadeModel(GL_SMOOTH);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		
		/*GLfloat lightAmbient_1[] = {0.0f , 0.0f , 0.0f , 0.0f};
		GLfloat lightDiffuse_1[] = {0.1f , 0.1f , 0.1f , 0.0f};
		GLfloat lightSpecular_1[] = {0.5f , 0.5f , 0.5f , 0.0f};*/

		GLfloat lightAmbient_1[] = {0.231f , 0.231f , 0.231f , 0.0f};
		//GLfloat lightDiffuse_1[] = {1.0f , 1.0f , 0.0f , 0.0f};
		GLfloat lightDiffuse_1[] = {0.277f , 0.277f , 0.277f , 0.0f};
		GLfloat lightSpecular_1[] = {1.0f , 0.0f , 0.0f , 0.0f};

		glLightfv(GL_LIGHT0, GL_POSITION , lightPos_1);
		glLightfv(GL_LIGHT0, GL_AMBIENT , lightAmbient_1);
		glLightfv(GL_LIGHT0, GL_DIFFUSE , lightDiffuse_1);
		glLightfv(GL_LIGHT0, GL_SPECULAR , lightSpecular_1);
		
		GLfloat lightAmbient2[] = {0.105f , 0.058f , 0.113f , 0.0f};
		GLfloat lightDiffuse2[] = {0.427f , 0.470f , 0.541f , 0.0f};
		GLfloat lightSpecular2[] = {0.0f , 0.5f , 0.0f , 0.0f};


		glLightfv(GL_LIGHT1, GL_POSITION , lightPos2);
		glLightfv(GL_LIGHT1, GL_AMBIENT , lightAmbient2);
		glLightfv(GL_LIGHT1, GL_DIFFUSE , lightDiffuse2);
		glLightfv(GL_LIGHT1, GL_SPECULAR , lightSpecular2);


		GLfloat lightAmbient3[] = {0.329f , 0.225f , 0.027f , 0.0f};
		GLfloat lightDiffuse3[] = {0.28f , 0.368f , 0.313f , 0.0f};
		GLfloat lightSpecular3[] = {0.0f , 0.0f , 0.5f , 0.0f};


		glLightfv(GL_LIGHT2, GL_POSITION , lightPos3);
		glLightfv(GL_LIGHT2, GL_AMBIENT ,  lightAmbient3);
		glLightfv(GL_LIGHT2, GL_DIFFUSE ,  lightDiffuse3);
		glLightfv(GL_LIGHT2, GL_SPECULAR , lightSpecular3);
	}

	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	//glBlendFunc(GL_ZERO, GL_ONE_MINUS_SRC_ALPHA);
	phongShader.textures[0] = make_texture("bricks.tga");
	/*shaderResources.textures[0] = make_texture("hello1.tga");
	
    shaderResources.textures[1] = make_texture("hello2.tga");
    alphaShader.textures[0] = make_texture("fence.tga");
    alphaShader.textures[1] = make_texture("pops.tga");
	
    if (alphaShader.textures[0] == 0)
        return false;

    if (shaderResources.textures[0] == 0 || shaderResources.textures[1] == 0)
        return false;*/

    /*shaderResources.vertex_shader = make_shader(GL_VERTEX_SHADER,"textureFade.vert");
    alphaShader.vertex_shader = make_shader(GL_VERTEX_SHADER,"alpha.vert");*/
    phongShader.vertex_shader = make_shader(GL_VERTEX_SHADER,"test.vert");

   /* if (shaderResources.vertex_shader == 0)
        return false;

    if (alphaShader.vertex_shader == 0)
        return false;*/

    if (phongShader.vertex_shader == 0)
        return false;

   /* shaderResources.fragment_shader = make_shader(GL_FRAGMENT_SHADER,"textureFade.frag");
    alphaShader.fragment_shader = make_shader(GL_FRAGMENT_SHADER,"alpha.frag");*/
    phongShader.fragment_shader = make_shader(GL_FRAGMENT_SHADER,"test.frag");
/*
    if (shaderResources.fragment_shader == 0)
        return false;

    if (alphaShader.fragment_shader == 0)
        return false;*/

    if (phongShader.fragment_shader == 0)
        return false;

/*    shaderResources.program = make_program(shaderResources.vertex_shader, shaderResources.fragment_shader);
    alphaShader.program = make_program(alphaShader.vertex_shader, alphaShader.fragment_shader);*/
    phongShader.program = make_program(phongShader.vertex_shader, phongShader.fragment_shader);
/*
    if (shaderResources.program == 0)
        return false;

    if (alphaShader.program == 0)
        return false; */

    if (phongShader.program == 0)
        return false;
/*
    shaderResources.uniforms.fade_factor = glGetUniformLocation(shaderResources.program, "fade_factor");
    shaderResources.uniforms.textures[0] = glGetUniformLocation(shaderResources.program, "textures[0]");
    shaderResources.uniforms.textures[1] = glGetUniformLocation(shaderResources.program, "textures[1]");

    alphaShader.uniforms.textures[0] = glGetUniformLocation(alphaShader.program, "textures[0]");*/
    phongShader.uniforms.textures[0] = glGetUniformLocation(phongShader.program, "tex");
    //phongShader.uniforms.textures[0] = glGetUniformLocation(phongShader.program, "tex");

    
	switch_loc[0]=glGetUniformLocation(phongShader.program,"switch_light[0]");
	switch_loc[1]=glGetUniformLocation(phongShader.program,"switch_light[1]");
	switch_loc[2]=glGetUniformLocation(phongShader.program,"switch_light[2]");
	switch_loc[3]=glGetUniformLocation(phongShader.program,"switch_light[3]");
	
	return true;
}
	float rot2=0;
float value = 0.0f;
void Display(){

	//glTranslatef(sin(rot/10),0,-sin(rot/10));



	if (light_in_pos==true){

	lightPos_1[0]=5.0f;		
	lightPos_1[1]=2.0f;	
	lightPos_1[2]=10.0f;
	lightPos_1[3]=0.0f;

	lightPos2[0]=-5.0f;	
	lightPos2[1]=10.0f;
	lightPos2[2]=2.0f;
	lightPos2[3]=0.0f;

	lightPos3[0]=6.0f;		
	lightPos3[1]=6.0f;	
	lightPos3[2]=-8.0f;
	lightPos3[3]=0.0f;

}

	lightPos_1[1] += sin(rot/20.0);
	lightPos2[1] -= sin(rot/20.0);
	lightPos3[1] += sin(rot/20.0);
	glLightfv(GL_LIGHT0, GL_POSITION , lightPos_1);
	glLightfv(GL_LIGHT1, GL_POSITION , lightPos2);
	glLightfv(GL_LIGHT2, GL_POSITION , lightPos3);



	glUseProgram(0);
	/* for (int i=0; i<4; ++i){
	 	 glUniform1f(switch_loc[i],switch_light[i]);
	 }*/



	setupWindowAndProjection();
	drawAxis(10);

	glColor3f(1,0,0);
	glTranslatef(lightPos_1[0],lightPos_1[1],lightPos_1[2]);
	glutSolidSphere(0.2,12,12);

	resetModelViewMatrix();
	
	print("LIGHT 0",lightPos_1[0],lightPos_1[1]+1,lightPos_1[2]);


	glColor3f(0,1,0);
	resetModelViewMatrix();
	glTranslatef(lightPos2[0],lightPos2[1],lightPos2[2]);
	glutSolidSphere(0.2,12,12);

	resetModelViewMatrix();
	print("LIGHT 1",lightPos2[0],lightPos2[1]+1,lightPos2[2]);

	glColor3f(0,0,1);
	glTranslatef(lightPos3[0],lightPos3[1],lightPos3[2]);
	glutSolidSphere(0.2,12,12);

	resetModelViewMatrix();
	print("LIGHT 2",lightPos3[0],lightPos3[1]+1,lightPos3[2]);
	

	resetModelViewMatrix();

	/*glColor3f(0,1,0);
	resetModelViewMatrix();
	glTranslatef(lightPos3[0],lightPos3[1],lightPos3[2]);
	glutSolidSphere(0.2,12,12);
	resetModelViewMatrix();
	print("LIGHT 2",lightPos3[0],lightPos3[1]+1,lightPos3[2]);*/

	//insert code below
	
	resetModelViewMatrix();
	glMaterialfv(GL_FRONT, GL_SHININESS, materialShininess);
	glUseProgram(phongShader.program);
	
	for (int i=0; i<4; ++i)
	 	glUniform1i(switch_loc[i],switch_light[i]);

	glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, phongShader.textures[0]);
    glUniform1i(phongShader.uniforms.textures[0], 0);
    // glUniform1i(phongShader.uniforms.light0_switch,1);
     //glUniform1i(phongShader.uniforms.light1_switchlight1_switch);
     //glUniform1i(phongShader.uniforms.light2_switch);
 	 //glUniform1i(phongShader.uniforms.lightall_switch);
    /*glTranslatef(4,0,-10);
    for (int i=0; i<5; i++){
    	for (int j=0;j<5;j++){
    			glColor3f(0,0,0);
	
				resetModelViewMatrix();
				 glTranslatef(4,0,-10);
				resetModelViewMatrix();
				glTranslatef(-3*i+tranx,trany,3*i*tranz);
				glTranslatef(3*j*tranx,trany,3*j+tranz);
				glColor3f(1,1,0);
				//resetModelViewMatrix();
				 glTranslatef(.5,0,-12.5);
				glutSolidTeapot(1);


    	}

    }*/

   /* glTranslatef(-8,0,-8);
    int gap = 4;
    int gridSize = 10;

    for (int i=0; i<gridSize; i++){

    	if ( i != 0){
    		glTranslatef(0,0,gap);
    		;
    		}


    	glPushMatrix();

    	for (int j=0;j<gridSize;j++){

			if ( j != 0||j%2!=0)
				glTranslatef(gap,sin(rot2),0);
			else
				glTranslatef(gap,cos(rot2),0);


			glutSolidTeapot(1);
    	}

    	glPopMatrix();
    } 
    if (rot2!=0.03)
    rot2 += 0.01;
	else
	rot2 -= 0.01;*/

	value += 0.05;

	

	for ( int k = 0; k < 6; ++k ){

		resetModelViewMatrix();
		glTranslatef(-10,0,-10);

		if ( k > 0)
			glTranslatef(0,0,6*k);

		for ( int i = 0 ; i < 6; ++i ){

			glTranslatef(4,sin(float(i)*value),0);

			glutSolidTeapot(1);
		}
	}

		//rot2 += 0.1;




/*	glColor3f(0,0,0);
	glRotatef(-rot,0,1,0);
	glTranslatef(0,cos(rot/10),0);
	glColor3f(1,1,0);
	glutSolidTeapot(2);*/

	//rot += 0.4;

	/*glUseProgram(shaderResources.program);

    glUniform1f(shaderResources.uniforms.fade_factor, shaderResources.fade_factor);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, shaderResources.textures[0]);
    glUniform1i(shaderResources.uniforms.textures[0], 0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, shaderResources.textures[1]);
    glUniform1i(shaderResources.uniforms.textures[1], 1);

	resetModelViewMatrix();

	glRotatef(rot,0,0,1);
	glTranslatef(0,0,5);
	glColor3f(0,1,0);
	glutSolidTeapot(1);

	glUseProgram(alphaShader.program);

	glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, alphaShader.textures[1]);
    glUniform1i(alphaShader.uniforms.textures[0], 0);

	resetModelViewMatrix();

	glRotatef(rot,0,0,1);
	glTranslatef(0,-5,0);

	glBegin(GL_QUADS);
		glTexCoord2f(0.0,0.0);
		glNormal3f(0,1,0);
		glVertex3i(0,0,5);

		glTexCoord2f(0.0,1.0);
		glNormal3f(0,1,0);
		glVertex3i(0,0,0);

		glTexCoord2f(1.0,1.0);
		glNormal3f(0,1,0);
		glVertex3i(5,0,0);

		glTexCoord2f(1.0,0.0);
		glNormal3f(0,1,0);
		glVertex3i(5,0,5);
		
	glEnd();

	resetModelViewMatrix();

	glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, alphaShader.textures[0]);
    glUniform1i(alphaShader.uniforms.textures[0], 1);
	glutSolidTeapot(4.0);

	 resetModelViewMatrix();
	
	glRotatef(rot,1,0,0);
	glTranslatef(5.5,0,0);
	//glScalef(3,3,0.2);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0,0.0);
		glNormal3f(0,1,0);
		glVertex3i(0,0,5);

		glTexCoord2f(0.0,1.0);
		glNormal3f(0,1,0);
		glVertex3i(0,0,0);

		glTexCoord2f(1.0,1.0);
		glNormal3f(0,1,0);
		glVertex3i(5,0,0);

		glTexCoord2f(1.0,0.0);
		glNormal3f(0,1,0);
		glVertex3i(5,0,5);
		
	glEnd();*/
		TwDraw();
		const char *m =TwGetLastError();
		if (m==NULL){std::cout<<"sleeeeeeeeeeeeeeeeeeeem ya m3lm"<<std::endl;}
			else
				printf("%s\n",m);

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
		++materialShininess[0];
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
		--materialShininess[0];
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
    if (key=='+')
    {
		++materialShininess[0];
    }
    if (key=='-')
    {
		--materialShininess[0];
    }

    if (key=='b')
    {
    	if (light0_move==true)
            ++lightPos_1[0];
        	
        	std::cout<<"i aaaaaaaam herrrrrre!!!   "<<  lightPos_1[0]<<std::endl;

    	if (light1_move==true)
            ++lightPos2[0];

    	if (light2_move==true)
           ++lightPos3[0];
        	//std::cout<<"i aaaaaaaam herrrrrre!!!";
    }

    if (key=='n')
    {
         
    	if (light0_move==true)
            ++lightPos_1[1];

    	if (light1_move==true)
            ++lightPos2[1];

    	if (light2_move==true)
            ++lightPos3[1];
    }

    if (key=='m')
    {
            
    	if (light0_move==true)
            ++lightPos_1[2];
        if (light1_move==true)
           ++lightPos2[2];
        if (light2_move==true)
            ++lightPos3[2];
    }


    if (key=='g')
    {
    	if (light0_move==true)
            lightPos_1[0]=lightPos_1[0]-1.0;

    	if (light1_move==true)
            lightPos2[0]=lightPos2[0]-1.0;

    	if (light2_move==true)
            lightPos3[0]=lightPos3[0]-1.0;
    }

       if (key=='h')
    {
         
    	if (light0_move==true)
            lightPos_1[1]=lightPos_1[1]-1.0;

    	if (light1_move==true)
            lightPos2[1]=lightPos2[1]-1.0;

    	if (light2_move==true)
            lightPos3[1]=lightPos3[1]-1.0;
    }

    if (key=='j')
    {
            
    	if (light0_move==true)
            lightPos_1[2]=lightPos_1[2]-1.0;
        if (light1_move==true)
            lightPos2[2]=lightPos2[2]-1.0;
        if (light2_move==true)
            lightPos3[2]=lightPos3[2]-1.0;
    }


}

void KeyboardUp(unsigned char key, int x, int y){

	if (key == 'a')
		std::cout << "a key lifted" << " at position : (" << x << "," << y << ")" << std::endl;
}

void SpecialKey(int key, int x, int y){
		if (key==GLUT_KEY_F1){
			switch_light[0]=1;
			switch_light[1]=0;
			switch_light[2]=0;
			switch_light[3]=0;
			std::cout<<"hiiiiiiiiii"<<switch_light[0]<<std::endl;
		}
		if (key==GLUT_KEY_F2){
			switch_light[0]=0;
			switch_light[1]=1;
			switch_light[2]=0;
			switch_light[3]=0;
		}

		if (key==GLUT_KEY_F3){
			switch_light[0]=0;
			switch_light[1]=0;
			switch_light[2]=1;
			switch_light[3]=0;
		}

		if (key==GLUT_KEY_F4){
			switch_light[0]=0;
			switch_light[1]=0;
			switch_light[2]=0;
			switch_light[3]=1;
		}

		if (key==GLUT_KEY_F5){
			light0_move=true;
			light1_move=false;
			light2_move=false;
			light_in_pos=false;
			std::cout<<"i aaaaaaaam herrrrrre!!!";
		}

			if (key==GLUT_KEY_F6){
			light1_move=true;
			light0_move=false;
			light2_move=false;
			light_in_pos=false;

		}
			if (key==GLUT_KEY_F7){
			light2_move=true;
			light1_move=false;
			light0_move=false;
			light_in_pos=false;

		}
			if (key==GLUT_KEY_F8){
			light2_move=false;
			light1_move=false;
			light0_move=false;
			light_in_pos=true;

		}
}

void Reshape(int width, int height){

	windowWidth = width;
	windowHeight = height;

	std::cout << "Current Width & Height = (" << width << " , " << height << ")" << std::endl;
	TwWindowSize(width,height);
}

void Idle(){

	int milliseconds = glutGet(GLUT_ELAPSED_TIME);
    shaderResources.fade_factor = sin((float)milliseconds * 0.001f) * 0.5f + 0.5f;

	glutPostRedisplay();
}

GLuint make_texture(const char *filename){

    int width, height,bpp;
    GLvoid *pixels = read_tga(filename, &width, &height,&bpp);
    GLuint textureID;

    if (!pixels)
        return -1;

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,     GL_REPEAT );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,     GL_REPEAT );
    glTexImage2D(
        GL_TEXTURE_2D, 0,        
        ((32 == bpp) ? GL_RGBA8 : GL_RGB8),              
        width, height, 0,         
        ((32 == bpp) ? GL_BGRA : GL_BGR), GL_UNSIGNED_BYTE,   
        pixels                      
    );

    free(pixels);
    return textureID;
}

void show_info_log(
    GLuint object,
    PFNGLGETSHADERIVPROC glGet__iv,
    PFNGLGETSHADERINFOLOGPROC glGet__InfoLog
)
{
    GLint log_length;
    char *log;

    glGet__iv(object, GL_INFO_LOG_LENGTH, &log_length);
    log = (char *)malloc(log_length);
    glGet__InfoLog(object, log_length, NULL, log);
    fprintf(stderr, "%s", log);
    free(log);
}

GLuint make_shader(GLenum type, const char *filename)
{
    GLint length;
    GLchar *source = textFileRead(filename, length);
    GLuint shader;
    GLint shader_ok;

    if (!source)
        return 0;

    shader = glCreateShader(type);
    glShaderSource(shader, 1, (const GLchar**)&source, &length);
    free(source);
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_ok);
    if (!shader_ok) {
        fprintf(stderr, "Failed to compile %s:\n", filename);
        show_info_log(shader, glGetShaderiv, glGetShaderInfoLog);
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

GLuint make_program(GLuint vertex_shader, GLuint fragment_shader)
{
    GLint program_ok;

    GLuint program = glCreateProgram();

    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &program_ok);
    if (!program_ok) {
        fprintf(stderr, "Failed to link shader program:\n");
        show_info_log(program, glGetProgramiv, glGetProgramInfoLog);
        glDeleteProgram(program);
        return 0;
    }
    return program;
}

short le_short(unsigned char *bytes){

    return bytes[0] | ((char)bytes[1] << 8);
}

void* read_tga(const char *filename, int *width, int *height,int *bpp){

    struct tga_header {
       char  id_length;
       char  color_map_type;
       char  data_type_code;
       unsigned char  color_map_origin[2];
       unsigned char  color_map_length[2];
       char  color_map_depth;
       unsigned char  x_origin[2];
       unsigned char  y_origin[2];
       unsigned char  width[2];
       unsigned char  height[2];
       char  bits_per_pixel;
       char  image_descriptor;
    } header;

    int i, color_map_size;
    unsigned int pixels_size;
    FILE *f;
    size_t read;
    GLvoid *pixels;

    f = fopen(filename, "rb");

    if (!f) {
        fprintf(stderr, "Unable to open %s for reading\n", filename);
        return NULL;
    }

    read = fread(&header, 1, sizeof(header), f);

    if (read != sizeof(header)) {
        fprintf(stderr, "%s has incomplete tga header\n", filename);
        fclose(f);
        return NULL;
    }
    if (2 != header.data_type_code) {
        fprintf(stderr, "%s is not an uncompressed RGB tga file\n", filename);
        fclose(f);
        return NULL;
    }

    for (i = 0; i < header.id_length; ++i)
        if (getc(f) == EOF) {
            fprintf(stderr, "%s has incomplete id string\n", filename);
            fclose(f);
            return NULL;
        }


    *bpp = header.bits_per_pixel;

    color_map_size = le_short(header.color_map_length) * (header.color_map_depth/8);
    for (i = 0; i < color_map_size; ++i)
        if (getc(f) == EOF) {
            fprintf(stderr, "%s has incomplete color map\n", filename);
            fclose(f);
            return NULL;
        }

    *width = le_short(header.width); 
    *height = le_short(header.height);
    pixels_size = *width * *height * (header.bits_per_pixel/8);
    pixels = malloc(pixels_size);

    read = fread(pixels, 1, pixels_size, f);
    fclose(f);

    if (read != pixels_size) {
        fprintf(stderr, "%s has incomplete image\n", filename);
        free(pixels);
        return NULL;
    }
    
    return pixels;
}

char* textFileRead(const char *fn , int &length){

    FILE *fp;
    char *content = NULL;

    int count=0;

    if (fn != NULL) {
        fp = fopen(fn,"rt");

        if (fp != NULL) {
      
            fseek(fp, 0, SEEK_END);
            count = ftell(fp);
            length = count;
            rewind(fp);

            if (count > 0) {
                content = (char *)malloc(sizeof(char) * (count+1));
                count = fread(content,sizeof(char),count,fp);
                content[count] = '\0';
            }

            fclose(fp);
        }
    }

    return content;
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
