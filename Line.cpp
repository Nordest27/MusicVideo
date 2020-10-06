
#include "Line.h"


Line::Line()
{
	ini = fi = CPoint();
	points = vector<GLfloat>();
}

Line::Line(vec3 i, vec3 f)
{
	ini.p = i;
	fi.p  = f;
}

Line::~Line()
{
}

void Line::renderCylinder(CPoint &p1, CPoint &p2, float r1, float r2, vec3 antdesp, vec3 desp, bool bfirst, bool blast)
{
	int inisize = points.size();
	vec3 v = p2.p - p1.p;
	vec3 zero = vec3(0, 0, 0);
	if (v.z == 0)
		v.z = .0001;

	vec3 cm = cross(v, vec3(0, 0, 1));
	vec3 ccm = cross(v, cm);
	float dm = dot(zero, p2.p);
	int res =11;
	float suma = 2 * (3.14 / res) * abs(3.14 / 2);
	int i = 0;
	vec3 ant, first;
	while(suma <= 2*3.14)
	{
		float calc = 0;
		if ( suma > 3.14 ) calc = 2* (3.14 / res) * abs(3*3.14 / 2 - suma);
		else calc = 2* (3.14 / res) * abs(3.14 / 2 - suma);
		suma += calc;
		if (calc < 3.14 / res / 20) suma += 2*3.14 /(res*res);
		vec3 vf = cm * cos(suma) + dm * v * (1 - cos(suma)) + ccm * sin(suma);
		vf = normalize(vf);
		vf *= r1;
		vec3 vf2, ant2;
		if (i == 0) {
			first = vf;
			ant = vf; 
		}
		ant2 = ant + v;
		ant2 += (r1 - r2)*((v - ant2) / r1);
		vf2 = vf + v;
		vf2 += (r1 - r2) *((v - vf2) / r1);

		normal.push_back(vf.x);
		normal.push_back(vf.y);
		normal.push_back(vf.z);

		normal.push_back(vf.x);
		normal.push_back(vf.y);
		normal.push_back(vf.z);

		normal.push_back(ant.x);
		normal.push_back(ant.y);
		normal.push_back(ant.z);

		normal.push_back(ant.x);
		normal.push_back(ant.y);
		normal.push_back(ant.z);

		normal.push_back(ant.x);
		normal.push_back(ant.y);
		normal.push_back(ant.z);

		normal.push_back(vf.x);
		normal.push_back(vf.y);
		normal.push_back(vf.z);

		vf += antdesp;
		ant += antdesp;
		vf2 += desp;
		ant2 += desp;

		points.push_back(vf.x );
		points.push_back(vf.y );
		points.push_back(vf.z );

		points.push_back(vf2.x);
		points.push_back(vf2.y);
		points.push_back(vf2.z);

		points.push_back(ant2.x);
		points.push_back(ant2.y);
		points.push_back(ant2.z);

		points.push_back(ant.x);
		points.push_back(ant.y);
		points.push_back(ant.z);

		points.push_back(ant2.x);
		points.push_back(ant2.y);
		points.push_back(ant2.z);

		points.push_back(vf.x);
		points.push_back(vf.y);
		points.push_back(vf.z);


		if (bfirst) {
			//cout << "here" << endl;
			vini.push_back(vf + p1.p + antdesp);
		}
		if (blast) {
			//cout << "final" << endl;
			vfi.push_back(vf2 + p1.p + desp);
		}

		ant = vf;
		ant -= antdesp;
		i++;
	}

	vec3 first2, ant2;
	ant2 = ant + v;
	ant2 += (r1-r2)*((v-ant2)/r1);
	first2 = first + v;
	first2 += (r1-r2) * ((v-first2)/r1);

	normal.push_back(first.x);
	normal.push_back(first.y);
	normal.push_back(first.z);

	normal.push_back(first.x);
	normal.push_back(first.y);
	normal.push_back(first.z);

	normal.push_back(ant.x);
	normal.push_back(ant.y);
	normal.push_back(ant.z);

	normal.push_back(ant.x);
	normal.push_back(ant.y);
	normal.push_back(ant.z);

	normal.push_back(first.x);
	normal.push_back(first.y);
	normal.push_back(first.z);

	normal.push_back(ant.x);
	normal.push_back(ant.y);
	normal.push_back(ant.z);

	normal.push_back(ant.x);
	normal.push_back(ant.y);
	normal.push_back(ant.z);

	normal.push_back(first.x);
	normal.push_back(first.y);
	normal.push_back(first.z);

	normal.push_back(first.x);
	normal.push_back(first.y);
	normal.push_back(first.z);

	first += antdesp;
	first2 += desp;
	ant2 += desp;
	ant += antdesp;

	points.push_back(first.x);
	points.push_back(first.y);
	points.push_back(first.z);

	points.push_back(first2.x);
	points.push_back(first2.y);
	points.push_back(first2.z);

	points.push_back(ant2.x);
	points.push_back(ant2.y);
	points.push_back(ant2.z);

	points.push_back(ant.x);
	points.push_back(ant.y);
	points.push_back(ant.z);

	points.push_back(first.x);
	points.push_back(first.y);
	points.push_back(first.z);

	points.push_back(ant2.x);
	points.push_back(ant2.y);
	points.push_back(ant2.z);

	points.push_back(ant.x);
	points.push_back(ant.y);
	points.push_back(ant.z);

	points.push_back(first2.x);
	points.push_back(first2.y);
	points.push_back(first2.z);

	points.push_back(first2.x);
	points.push_back(first2.y);
	points.push_back(first2.z);

	for (int i = inisize; i < points.size() ; i += 3)
	{
		points[i] += p1.p.x;
		points[i+1] += p1.p.y;
		points[i+2] += p1.p.z;
	}
	/*for (int i = inisize; i < points.size(); i += 9)
	{
		vec3 v1, v2, norm;
		v1 = vec3(points[i+3], points[i + 4], points[i + 5]);
		v2 = vec3(points[i], points[i + 1], points[i + 2]);
		norm = normalize(cross(v1, v2));
		normal.push_back(norm.x);
		normal.push_back(norm.y);
		normal.push_back(norm.z);
		normal.push_back(norm.x);
		normal.push_back(norm.y);
		normal.push_back(norm.z);
		normal.push_back(norm.x);
		normal.push_back(norm.y);
		normal.push_back(norm.z);
	}*/
}

void Line::iniVal(CPoint &cini, CPoint &cfi)
{
	ini = cini;
	fi = cfi;
}

void Line::constr(float r1, float r2, int div, float gruix, float squig)
{
	//div = 7;
	vec3 v = fi.p - ini.p;
	float dist = length(v);
	float antRad = r1;
	vec3 ant = ini.p + (v / float(div));
	ini.p = ant;
	vec3 desp = normalize(vec3(rand() % 360, rand() % 360, rand() % 360));
	desp *= squig*15*dist/div;
	vec3 antdesp = vec3(0, 0, 0);
	for (float i = dist / div; i < dist-dist/div; i += dist / div)
	{
		float rad = float((rand() % 50)/30)*gruix+gruix/2;
		rad += (antRad - rad)*0.85;
		bool last, first;
		first = last = false;
		if (i + 2 * dist / div >= dist) {
			rad = r2;
			last = true;
			desp = vec3(0, 0, 0);
		}
		if (i == dist / div) first = true;
		CPoint cini, cfi;
		cini.p = ant;
		cfi.p = ant +(v/ float(div));
		//cini.p += antdesp;
		//cfi.p += desp;
		renderCylinder(cini, cfi, antRad, rad, antdesp, desp, first, last);
		//cfi.p -= desp;
		antRad = rad;
		ant = cfi.p;
		antdesp = desp;
		desp = normalize(vec3(rand() % 360-180, rand() % 360-180, rand() % 360-180));
		desp *= squig;
	}
}