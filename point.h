#pragma once
#include<iostream>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <cmath>
#include <stack>

using namespace std;


struct point
{
	int num;
	double x, y1, y2, y3;
};

ostream& operator<< (ostream &os, const point &p)
{
	cout << endl;

	os << p.num <<"  "<<  "x" <<p.num << "1:  "<< p.x << "          " << "v" <<p.num <<"1:   " << p.y1 << "          " << "v" <<p.num <<"2:   " << p.y2 << "          " << "v" <<p.num <<"3:   " << p.y3 <<endl;

	return os;
}

struct point3d
{
	double x1,x2, x3;
};

