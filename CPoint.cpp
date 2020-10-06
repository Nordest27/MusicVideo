
#include "CPoint.h"



CPoint::CPoint()
{
	p = vec3(0.0, 0.0, 0.0);
}

CPoint::~CPoint()
{
}

void CPoint::Scale(float q, const CPoint &center )
{
	vec3 dif = p - center.p;
	dif *= q;
	p = center.p + dif;
}


void CPoint::ScaleV(vec3 q, const CPoint &center)
{
	vec3 dif = p - center.p;
	dif.x *= q.x;
	dif.y *= q.y;
	dif.z *= q.z;
	p = center.p + dif;
}

CPoint& CPoint::operator=(const CPoint& other)
{
	p = other.p;
	return *this;
}

void CPoint::calcUnion()
{ 
	int i = 0; 
	while( uniPoints.size() > 0 && uniPoints[0].size() > 0 &&  i < 1200 )
		{
			int s, s1;
			s = rand() % uniPoints.size();
			s1 = rand() % uniPoints[0].size();
			if (uniPoints.size() > s && uniPoints[s].size() > s1 ){//&& distance(vec3(uniPoints[s][s1].x, uniPoints[s][s1].y, uniPoints[s][s1].z),p ) < 0. ) {
				renderPoints.push_back(uniPoints[s][s1].x);
				renderPoints.push_back(uniPoints[s][s1].y);
				renderPoints.push_back(uniPoints[s][s1].z);
				i += 1;
			}
		}
	/*cout << uniPoints.size()<< endl;
	if (uniPoints.size() <= 1)
	{

	}
	vec3 last1 = vec3(0, 0, 0);
	vec3 last2 = last1;
	for (int i = 0; i < int(uniPoints.size()) - 1; ++i)
		for (int j = 0; j < int(uniPoints[i].size()) - 1; ++j)
		{
			//if (uniPoints[i].size() <= 1) return;
			if (uniPoints[i + 1].size() > j + 1 )
			{

				renderPoints.push_back(uniPoints[i][j].x);
				renderPoints.push_back(uniPoints[i][j].y);
				renderPoints.push_back(uniPoints[i][j].z);
				renderPoints.push_back(uniPoints[i][j + 1].x);
				renderPoints.push_back(uniPoints[i][j + 1].y);
				renderPoints.push_back(uniPoints[i][j + 1].z);
				renderPoints.push_back(uniPoints[i + 1][j].x);
				renderPoints.push_back(uniPoints[i + 1][j].y);
				renderPoints.push_back(uniPoints[i + 1][j].z);

				renderPoints.push_back(uniPoints[i + 1][j].x);
				renderPoints.push_back(uniPoints[i + 1][j].y);
				renderPoints.push_back(uniPoints[i + 1][j].z);
				renderPoints.push_back(uniPoints[i + 1][j + 1].x);
				renderPoints.push_back(uniPoints[i + 1][j + 1].y);
				renderPoints.push_back(uniPoints[i + 1][j + 1].z);
				renderPoints.push_back(uniPoints[i][j + 1].x);
				renderPoints.push_back(uniPoints[i][j + 1].y);
				renderPoints.push_back(uniPoints[i][j + 1].z);
				last1 = uniPoints[i + 1][j];
				last2 = uniPoints[i + 1][j + 1];

			}
			else
			{
				renderPoints.push_back(uniPoints[i][j].x);
				renderPoints.push_back(uniPoints[i][j].y);
				renderPoints.push_back(uniPoints[i][j].z);
				renderPoints.push_back(uniPoints[i][j + 1].x);
				renderPoints.push_back(uniPoints[i][j + 1].y);
				renderPoints.push_back(uniPoints[i][j + 1].z);
				renderPoints.push_back(last1.x);
				renderPoints.push_back(last1.y);
				renderPoints.push_back(last1.z);

				renderPoints.push_back(last1.x);
				renderPoints.push_back(last1.y);
				renderPoints.push_back(last1.z);
				renderPoints.push_back(last2.x);
				renderPoints.push_back(last2.y);
				renderPoints.push_back(last2.z);
				renderPoints.push_back(uniPoints[i][j + 1].x);
				renderPoints.push_back(uniPoints[i][j + 1].y);
				renderPoints.push_back(uniPoints[i][j + 1].z);
			}
			//cout << last1.x << "," << last1.y << "," << last1.z << endl;
		}*/

}
	/*if (uniPoints.size() == 1)
	{

		return;
	}
	vec3 last1, last2;
	for (int i = 0; i < uniPoints.size()-1; ++i)
		for (int j = 0; j <  uniPoints[i].size()-1; ++j)
		{
			if (uniPoints[i + 1].size > j + 1)
			{
				renderPoints.push_back(uniPoints[i][j].x);
				renderPoints.push_back(uniPoints[i][j].y);
				renderPoints.push_back(uniPoints[i][j].z);
				renderPoints.push_back(uniPoints[i][j + 1].x);
				renderPoints.push_back(uniPoints[i][j + 1].y);
				renderPoints.push_back(uniPoints[i][j + 1].z);
				renderPoints.push_back(uniPoints[i + 1][j].x);
				renderPoints.push_back(uniPoints[i + 1][j].y);
				renderPoints.push_back(uniPoints[i + 1][j].z);

				renderPoints.push_back(uniPoints[i + 1][j].x);
				renderPoints.push_back(uniPoints[i + 1][j].y);
				renderPoints.push_back(uniPoints[i + 1][j].z);
				renderPoints.push_back(uniPoints[i + 1][j + 1].x);
				renderPoints.push_back(uniPoints[i + 1][j + 1].y);
				renderPoints.push_back(uniPoints[i + 1][j + 1].z);
				renderPoints.push_back(uniPoints[i][j + 1].x);
				renderPoints.push_back(uniPoints[i][j + 1].y);
				renderPoints.push_back(uniPoints[i][j + 1].z);
				last1 = uniPoints[i + 1][j];
				last2 = uniPoints[i + 1][j + 1];
			}
			else
			{
				renderPoints.push_back(uniPoints[i][j].x);
				renderPoints.push_back(uniPoints[i][j].y);
				renderPoints.push_back(uniPoints[i][j].z);
				renderPoints.push_back(uniPoints[i][j + 1].x);
				renderPoints.push_back(uniPoints[i][j + 1].y);
				renderPoints.push_back(uniPoints[i][j + 1].z);
				renderPoints.push_back(last1.x);
				renderPoints.push_back(last1.y);
				renderPoints.push_back(last1.z);

				renderPoints.push_back(last1.x);
				renderPoints.push_back(last1.y);
				renderPoints.push_back(last1.z);
				renderPoints.push_back(last2.x);
				renderPoints.push_back(last2.y);
				renderPoints.push_back(last2.z);
				renderPoints.push_back(uniPoints[i][j + 1].x);
				renderPoints.push_back(uniPoints[i][j + 1].y);
				renderPoints.push_back(uniPoints[i][j + 1].z);
			}
		}

	
}*/

