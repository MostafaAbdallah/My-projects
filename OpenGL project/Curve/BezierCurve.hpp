#ifndef BEZIER_CURVE_HPP
#define BEZIER_CURVE_HPP

#include <vector>
#include <string>
#include <glm/glm.hpp>
/*
	* means LATER
	- means TODO
	+ means DONE
	> means IMPLEMENTED

	Users:
		- Curve Designer
			+ Real-time drawing
				> control points drawing with indices on each control point
				> control polygon drawing with stippled lines
				> curve points drawing	
				* tangents & normals drawing
				* fernet frame drawing
			- Interactive Curve editing capabilities
				> control points specification
				- control points selection
				> control points transformation
				- knots , multiplicity , degree & weight control
			* Projective invariance for NURBS

		- Curve User
			> access of curve points
			> access of sizes of control points & curve points
			> access of curve center
			* fernet frame
			
		- Student
			+ Real-time drawing
				> control points drawing with indices on each control point
				> control polygon drawing with stippled lines
				> curve points drawing
				* tangents & normals drawing
				* fernet frame drawing
			* drawing the blending functions ( addition of control points as vectors )
			+ Drawing & Animating the construction polygon
			+ Controlling animation speed
			* Render control point support
			* velocity , acceleration , continuity , normals & tangets

		- General
			> Curve persistence 
			> Curve generation

	Design Problems:
		+ Who loops over values of t ?
		+ Pre-Build entire curve or build curve points on the run ?
		+ Who draws the curve ?
		- When Loading a curve , should we generate ? or he should generate ?
		- if control points are not drawn , then can we control the polygon in real time ? NO
		- convert all helper functions to friend functions outside the class
*/


class BezierBernsteinCurve{

public:
	
	BezierBernsteinCurve();

	void rebuildCurve();

	// generation
	void generateCurve(const float& deltaT);

	// interactivity
	void addControlPoints(const glm::vec3& cp);
	void addControlPoints(const std::vector< glm::vec3 >& cps);
	void selectControlPoints(const unsigned int& toBeSelected);
	void selectControlPoints(const std::vector< unsigned int >& toBeSelected);
	void deselectControlPoints(const unsigned int& toBeDeselected);
	void deselectControlPoints(const std::vector< unsigned int >& toBeDeselected);
	void selectAll();
	void deselectAll();
	
	// transformations
	void translate(const glm::vec3& tv);
	void rotate(const float& angle , const glm::vec3& axis , const glm::vec3& origin = glm::vec3(0,0,0));
	void scale(const glm::vec3& sv);

	// rendering
	void drawControlPoints(const bool& isNumbered , const float& pointSize , glm::vec4 pointColor)const;
	void drawControlPolygon(const bool& isStippled , const float& lineWidth , glm::vec4 lineColor)const;
	void drawCurvePoints(const float& lineWidth , glm::vec4 lineColor)const;
	void drawConstructionPolygon(const bool& isStippled , const float& lineWidth , glm::vec4 lineColor , const int& speed = 10)const;

	// accessibility 
	unsigned int controlPointsSize()const;
	unsigned int curvePointsSize()const;
	std::vector< glm::vec3 > curvePointsVector()const;
	glm::vec3 getCurveCenter()const;

	// persistence
	void saveCurveToFile(const std::string& fileName)const;
	void loadCurveFromFile(const std::string& fileName);

private:

	// helper functions
	int binomialCoefficient(const int& n , int r)const;
	int specialFactorial(int n , const int& r)const;
	int factorial(int n)const;
	float bernsteinPolynomial(const int& n,const int& i,const float& t)const;
	void drawString(const std::string& str,const int& x , const int& y)const;
	void normalizeRGBColor(glm::vec4& color)const;
	glm::vec3 lerp(const glm::vec3& A ,const glm::vec3& B , const float& t)const;
	
	// member variables
	std::vector< glm::vec3 > controlPoints;
	std::vector< glm::vec3 > curvePoints;
	std::vector< unsigned int > selectedControlPoints;
};

#endif