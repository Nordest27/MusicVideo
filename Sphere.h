
#include "Line.h"

class Sphere
{
public:
	CPoint center;
	vector<CPoint> points;
	vector<Line> lines;
	vector<GLfloat> renderPoints, normalPoints;
	float rad;
	int res;

	Sphere();
	~Sphere();

	void PointsSphere();
	void ini(float rad1, int res1, vec3 center1);
	void Scale(float q);
	void ScaleV(vec3 q);
	void constrLines(float dist, float gruix, float squig);
};

