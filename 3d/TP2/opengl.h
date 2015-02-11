#ifndef OGL_H
#define OGLH

#include <stdio.h>      
#include <stdlib.h>     
#include <math.h>

#include "point.h"
#include "vector.h"

#include <iostream>
#include <GL/glut.h>

void DrawCurve(Point **pts, long nbPts) {
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < nbPts; ++i) {
		glVertex3f(pts[i]->getX(), pts[i]->getY(), pts[i]->getZ());
	}
	glEnd();
}

Point **HermiteCubicCurve(Point *p0, Point *p1, Vector *v0, Vector *v1, long nbU) {

	Point **pts = new Point*[nbU];

	for (int i = 0; i < nbU; ++i)
	{
		float u = 1 / (float) nbU * (float) i;

		double f1 = 2 * pow(u, 3) - 3 * pow(u, 2) + 1;
		double f2 = -2 * pow(u, 3) + 3 * pow(u, 2);
		double f3 = pow(u, 3) - 2 * pow(u, 2) + u;
		double f4 = pow(u, 3) - pow(u, 2);

		pts[i] = new Point(f1 * p0->getX() + f2 * p1->getX() + f3 * v0->getX() + f4 * v1->getX(),
			f1 * p0->getY() + f2 * p1->getY() + f3 * v0->getY() + f4 * v1->getY(),
			f1 * p0->getZ() + f2 * p1->getZ() + f3 * v0->getZ() + f4 * v1->getZ());
	}
	return pts;
}


long facto(long n) {
	if(n == 0) {
		return 1;
	}
	return n * facto(n - 1);
}

Point **BezierCurveByBernstein(Point **t, long nbPts, long nbU) {
	Point **pts = new Point*[nbU + 1];

	for (int j = 0; j < nbU; ++j)
	{
		float u = 1 / (float) nbU * (float) j;

		float x = 0, y = 0, z = 0;

		for (int i = 0; i < nbPts; ++i)
		{
			float b = (facto(nbPts - 1) / (facto(i) * facto(nbPts - i - 1))) * pow(u, i) * pow((1 - u), nbPts - i - 1);
			x += b * t[i]->getX();
			y += b * t[i]->getY();
			z += b * t[i]->getZ();
		}


		pts[j] = new Point(x, y, z);
	}

	pts[nbU] = new Point(t[nbPts - 1]->getX(), t[nbPts - 1]->getY(), t[nbPts - 1]->getZ());

	return pts;
}

Point **BezierCurveByCasteljau(Point **t, long nbPts, long nbU) {
	Point **pts = new Point*[nbU];

	for (int j = 0; j < nbU; ++j)
	{
		float u = 1 / (float) nbU * (float) j;

		float x = 0, y = 0, z = 0;

		for (int i = 0; i < nbPts; ++i)
		{
			float b = (facto(nbPts) / (facto(i) * facto(nbPts - i))) * pow(u, i) * pow((1 - u), nbPts - i);
			std::cout << b << std::endl;
			x += b * t[i]->getX();
			y += b * t[i]->getY();
			z += b * t[i]->getZ();
		}


		pts[j] = new Point(x, y, z);
	}

	return pts;
}


#endif