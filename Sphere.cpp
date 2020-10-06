#include "Sphere.h"
#include <set>
#include <map>


Sphere::Sphere()
{
	points = vector<CPoint>();
	rad = 0.5;
	res = 10;
	center = CPoint();
}

Sphere::~Sphere()
{
}

void Sphere::ini(float rad1, int res1, vec3 center1)
{
	rad = rad1;
	res = res1;
	center.p = center1;
}

void Sphere::PointsSphere()
{
	points = vector<CPoint>();
	CPoint aux;
	for (int i = 0; i < res; ++i)
	{
		float angl1 = (180 * float(rand() % 1000) / 1000) / (2 * 3.1416);
		float angl2 = (180 * float(rand() % 1000) / 1000) / (2 * 3.1416);
		aux.p.x = center.p.x + rad * cos(angl1)*sin(angl2);
		aux.p.y = center.p.y + rad * sin(angl1)*sin(angl2);
		aux.p.z = center.p.z + rad * cos(angl2);
		points.push_back(aux);
	}
}

void Sphere::constrLines(float dist, float gruix, float squig)
{
	set<pair<int, int>> connected;
	for (int i = 0; i < points.size(); i += 1)
		for (int j = 0; j < 3; ++j)
		{
			int min = 0;
			float mindist = 5 * rad;
			for (int u = i; u < points.size(); ++u)
			{
				auto it = connected.find(pair<int, int>(i, u));
				if(it != connected.end()) j++;
				else if (u != i)
				{
					float daux = distance(points[i].p, points[u].p);
					if (mindist > daux)
					{
						mindist = daux;
						min = u;
					}
				}
			}
			if (j < 3 && mindist < rad*1.5)
			{
				Line l(points[i].p, points[min].p);
				int segs = 10 * distance(points[i].p, points[min].p);
				l.constr(gruix, gruix, 3 + rand()%(1+segs), gruix, squig);
				points[i].uniPoints.push_back(l.vini);
				points[min].uniPoints.push_back(l.vfi);
				for (int i = 0; i < l.points.size(); ++i)
					renderPoints.push_back(l.points[i]);
				for (int i = 0; i < l.normal.size(); ++i)
					normalPoints.push_back(l.normal[i]);
				connected.insert(pair<int, int>(i, min));
				connected.insert(pair<int, int>(min, i));
			}
		}
	for (int i = 0; i < points.size(); ++i)
	{
		points[i].calcUnion();
		for (int j = 0; j < points[i].renderPoints.size(); ++j)
			renderPoints.push_back(points[i].renderPoints[j]);
		for (int j = 0; j < points[i].renderPoints.size(); j+= 3)
		{
			vec3 norm = vec3(points[i].renderPoints[j]-points[i].p.x, points[i].renderPoints[j + 1] - points[i].p.y, points[i].renderPoints[j + 2] - points[i].p.z);
			normalPoints.push_back(norm.x);
			normalPoints.push_back(norm.y);
			normalPoints.push_back(norm.z);
		}
	}
}

void Sphere::Scale(float q)
{
	rad *= q;
	for (int i = 0; i < points.size(); ++i)
		points[i].Scale(q, center);
}

void Sphere::ScaleV(vec3 q)
{
	for (int i = 0; i < points.size(); ++i)
		points[i].ScaleV(q, center);
}
