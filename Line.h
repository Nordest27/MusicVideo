
#include "CPoint.h";


class Line
{
private:
	void renderCylinder(CPoint &p1, CPoint &p2, float r1, float r2, vec3 antdesp, vec3 desp, bool bfirst, bool blast);
public:
	CPoint ini, fi;
	vector<vec3> vini, vfi; 
	vector<GLfloat> points;
	vector<GLfloat> normal;

	Line();
	Line(vec3 i, vec3 f);
	~Line();

	void iniVal(CPoint &cini, CPoint &cfi);
	void constr(float r1, float r2, int div, float gruix, float squig);
};

