
// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/norm.hpp>
using namespace glm;

#include <vector>
#include <cmath>
#include <iostream>
#include <common/shader.hpp>
using namespace std;
class CPoint
{
public:
	vector<vector<vec3>> uniPoints;
	vector<GLfloat> renderPoints;
	vec3 p;

	CPoint();
	~CPoint();

	void Scale(float q, const CPoint &center);
	void ScaleV(vec3 q, const CPoint &center);
	void calcUnion();
	CPoint& operator=(const CPoint& other);
};

