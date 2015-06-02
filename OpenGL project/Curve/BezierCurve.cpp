#include "BezierCurve.hpp"
#include <fstream>
#include <iostream>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <GL/gl.h>
#include <GL/glut.h>

BezierBernsteinCurve::BezierBernsteinCurve() : controlPoints() , curvePoints() , selectedControlPoints(){

    // empty constructor
}

// accessibility

unsigned int BezierBernsteinCurve::controlPointsSize()const{

	return controlPoints.size();
}

unsigned int BezierBernsteinCurve::curvePointsSize()const{

    return curvePoints.size();
}

std::vector< glm::vec3 > BezierBernsteinCurve::curvePointsVector()const{

    return curvePoints;
}

glm::vec3 BezierBernsteinCurve::getCurveCenter()const{

    glm::vec3 center = glm::vec3(0,0,0);

    for ( auto conPt : controlPoints )
        center += conPt;

    center.x /= controlPoints.size();
    center.y /= controlPoints.size();
    center.z /= controlPoints.size();

    return center;
}

// interactivity

void BezierBernsteinCurve::addControlPoints(const std::vector< glm::vec3 >& cps){

	for ( auto i : cps )
		controlPoints.push_back(i);
}

void BezierBernsteinCurve::addControlPoints(const glm::vec3& cp){

	controlPoints.push_back(cp);
}

// rendering

void BezierBernsteinCurve::drawControlPoints(const bool& isNumbered , const float& pointSize , glm::vec4 pointColor)const{

    float currentSize,currentColor[4];

    glGetFloatv(GL_POINT_SIZE ,&currentSize);
    glGetFloatv(GL_CURRENT_COLOR,currentColor);

    normalizeRGBColor(pointColor);

    glPointSize(pointSize);
    glColor4f(pointColor.r,pointColor.g,pointColor.b,pointColor.a);

    glBegin(GL_POINTS);

        for ( auto i = 0u ; i < controlPoints.size(); ++i ){
            /*if ( i == selectedCp )
                glColor3ub(0,255,0);
            else
                glColor3ub(255,255,0);*/
            glVertex2f(controlPoints[i].x,controlPoints[i].y); 
        }

    glEnd();

    if (isNumbered){

        char buffer[3];

        for ( auto i = 0u ; i < controlPoints.size(); ++i ){

            glColor3f(1.0- pointColor.r,1.0- pointColor.g,1.0- pointColor.b);

            sprintf(buffer,"%u",i);

            drawString(std::string(buffer),controlPoints[i].x - 4,controlPoints[i].y - 2);
        }
    }

    glPointSize(currentSize);
    glColor4f(currentColor[0] , currentColor[1] , currentColor[2] , currentColor[3]);
}

void BezierBernsteinCurve::drawControlPolygon(const bool& isStippled , const float& lineWidth , glm::vec4 lineColor)const{

    float currentWidth,currentColor[4];

    glGetFloatv(GL_LINE_WIDTH ,&currentWidth);
    glGetFloatv(GL_CURRENT_COLOR,currentColor);

    normalizeRGBColor(lineColor);

    glLineWidth(lineWidth);
    glColor4f(lineColor.r,lineColor.g,lineColor.b,lineColor.a);

    if ( isStippled ){

        const unsigned short stipplePattern = 0xF0F0;

        glEnable(GL_LINE_STIPPLE);
        glLineStipple(1, stipplePattern);
    }

    glBegin(GL_LINE_STRIP);

        for ( auto conPt : controlPoints )
            glVertex2f(conPt.x,conPt.y); 

    glEnd();

    if ( isStippled )
        glDisable(GL_LINE_STIPPLE);

    glLineWidth(currentWidth);
    glColor4f(currentColor[0] , currentColor[1] , currentColor[2] , currentColor[3]);
}

void BezierBernsteinCurve::drawCurvePoints(const float& lineWidth , glm::vec4 lineColor)const{

    float currentWidth,currentColor[4];

    glGetFloatv(GL_LINE_WIDTH ,&currentWidth);
    glGetFloatv(GL_CURRENT_COLOR,currentColor);

    normalizeRGBColor(lineColor);

    glLineWidth(lineWidth);
    glColor4f(lineColor.r,lineColor.g,lineColor.b,lineColor.a);

    glBegin(GL_LINE_STRIP);

        for ( auto curPt : curvePoints )
            glVertex2f(curPt.x,curPt.y);

    glEnd();

    glPointSize(currentWidth);
    glColor4f(currentColor[0] , currentColor[1] , currentColor[2] , currentColor[3]);
}

void BezierBernsteinCurve::drawConstructionPolygon(const bool& isStippled , const float& lineWidth , glm::vec4 lineColor , const int& speed)const{

    float currentWidth,currentColor[4];

    glGetFloatv(GL_LINE_WIDTH ,&currentWidth);
    glGetFloatv(GL_CURRENT_COLOR,currentColor);

    normalizeRGBColor(lineColor);

    glLineWidth(lineWidth);
    glColor4f(lineColor.r,lineColor.g,lineColor.b,lineColor.a);

    if ( isStippled ){

        const unsigned short stipplePattern = 0xF0F0;

        glEnable(GL_LINE_STIPPLE);
        glLineStipple(1, stipplePattern);
    }

    static float t = 0.0f;
    static int sign = 1;
    glm::vec3 p1, p2;
    for ( int i = 1; i < controlPoints.size(); ++i ){

        glm::vec3 p = lerp(controlPoints[i-1],controlPoints[i],t);
        if(i!=controlPoints.size()-1){
            p1 = lerp(controlPoints[i],controlPoints[i+1],t);
            std::cout<<p1.x<<"   "<<p1.y<<std::endl;
            p2 = lerp(p,p1,t);

        }

        glPointSize(10);

        glBegin(GL_POINTS);
            glVertex2f(p.x,p.y); 
        glEnd();
        if(i!=controlPoints.size()-1){
            std::cout<<p1.x<<"   "<<p1.y<<std::endl;
            glBegin(GL_LINES);
                glVertex2f(p.x,p.y);
                glVertex2f(p1.x,p1.y);
            glEnd();
             glBegin(GL_POINTS);
                glVertex2f(p2.x,p2.y); 
            glEnd();
        }

    }

    if ( t >= 1.0f )
        sign = -1;
    else if ( t <= 0.0f )
        sign = 1;

    t += 0.1f / speed * sign;
    

    if ( isStippled )
        glDisable(GL_LINE_STIPPLE);

    glLineWidth(currentWidth);
    glColor4f(currentColor[0] , currentColor[1] , currentColor[2] , currentColor[3]);
}

// helper functions

void BezierBernsteinCurve::drawString(const std::string& str,const int& x , const int& y)const{

    glRasterPos2i(x,y);

    for ( auto ch : str )
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,ch);
}

void BezierBernsteinCurve::normalizeRGBColor(glm::vec4& color)const{

    if (color.r > 1.0f || color.g > 1.0f || color.b > 1.0f){

        color.r /= 256;
        color.g /= 256;
        color.b /= 256;
        color.a /= 256;
    }
}

int BezierBernsteinCurve::specialFactorial(int n , const int& r)const{

    int result = 1;

    for ( int i = 0; i < r; ++i ){

        result *= n;
        --n;
    }

    return result;
}

int BezierBernsteinCurve::factorial(int n)const{

    int result = 1;

    while (n){
        result *= n;
        --n;
    }

    return result;
}

int BezierBernsteinCurve::binomialCoefficient(const int& n , int r)const{

    if (n - r < r)
        r = n - r;

    return specialFactorial(n,r) / factorial(r);
}

float BezierBernsteinCurve::bernsteinPolynomial(const int& n,const int& i,const float& t)const{

    return binomialCoefficient(n , i) * std::pow(t , i) * std::pow(1.0f - t , n - i);
}

glm::vec3 BezierBernsteinCurve::lerp(const glm::vec3& A ,const glm::vec3& B , const float& t)const{

    return A + ( (B-A) * t );
}

// generation
void BezierBernsteinCurve::generateCurve(const float& deltaT){

	float t = 0.0f;

    // size - 1 not size
    // because in the math two points
    // are considered p0 and p1
    int n = controlPoints.size()-1;
    
	curvePoints.clear();

	while ( t <= 1.0 ){

		glm::vec3 p;

	    // <= not <
	    for ( int i = 0; i <= n; ++i )
	        p += controlPoints[i] * bernsteinPolynomial(n,i,t);

        curvePoints.push_back(p);
        t += deltaT;
    }
}

// transformations
void BezierBernsteinCurve::translate(const glm::vec3& tv){

    glm::mat4 transMat = glm::translate(tv);

    for ( auto i = 0u; i < controlPoints.size(); ++i )
        controlPoints[i] = glm::vec3(transMat * glm::vec4(controlPoints[i],1.0));
}

void BezierBernsteinCurve::rotate(const float& angle , const glm::vec3& axis, const glm::vec3& origin){

    glm::mat4 transMat = glm::translate(origin);

    glm::quat rotQuat = glm::angleAxis(glm::degrees(angle),axis);

    glm::mat4 invTransMat = glm::translate(-origin);

    for ( auto i = 0u; i < controlPoints.size(); ++i )
        controlPoints[i] = glm::vec3( transMat * (rotQuat * (invTransMat * glm::vec4(controlPoints[i],1.0))) );
}

void BezierBernsteinCurve::scale(const glm::vec3& sv){

    glm::mat4 scaleMat = glm::scale(sv);

    for ( auto i = 0u; i < controlPoints.size(); ++i )
        controlPoints[i] = glm::vec3(scaleMat * glm::vec4(controlPoints[i],1.0));
}

// persistence
void BezierBernsteinCurve::saveCurveToFile(const std::string& fileName)const{

    std::ofstream fout;

    fout.open(fileName);

    if ( fout.good() ){

        fout << "CVF" << std::endl << std::endl;

        fout << "CP " << controlPoints.size() << std::endl;

        for ( auto i = 0u; i < controlPoints.size(); ++i ){

            fout << controlPoints[i].x << " " << controlPoints[i].y << " " << controlPoints[i].z << std::endl;
        }

        fout << std::endl;
    }

}

void BezierBernsteinCurve::loadCurveFromFile(const std::string& fileName){

    std::ifstream fin;

    fin.open(fileName);

    if ( fin.good() ){

        std::string signature,cmd;
        float x,y,z;
        int cpSize = -1;

        fin >> signature;

        if ( signature != "CVF" ){

            std::cerr << "Invalid File Format From File: " << fileName << std::endl;
            throw "Invalid Format";
        }

        controlPoints.clear();

        fin >> cmd >> cpSize;
        
        for ( auto i = 0; i < cpSize; ++i ){

            fin >> x >> y >> z;

            controlPoints.push_back(glm::vec3(x,y,z));
        }

    }
    else{

        std::cerr << "Could Not Find File: " << fileName << std::endl;
        throw "File Not Found";
    }

}