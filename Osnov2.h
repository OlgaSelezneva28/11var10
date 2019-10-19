#pragma once
#include<iostream>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <cmath>
#include <stack>
#include "point.h"

using namespace std;


double osnov2y1(double x, double u1, double u2, double u3, double a1, double b1, double c1)//f1'
{
	double y1 = u1*(a1 - u1 - c1*u2 - b1*u3);
	return y1;
}

double osnov2y2(double x, double u1, double u2, double u3, double a2, double b2, double c2)//f2'
{
	double y2 = u2*(a2 - c2*u1 - u2 - b2*u3);
	return y2;
}

double osnov2y3(double x, double u1, double u2, double u3, double d1, double d2)//f3'
{
	double y3 = u3*(-1 + u1*d1 + d2*u2);
	return y3;
}

point metodRKS(int num, double h, double x, double u1, double u2, double u3, double a1, double b1, double c1, double a2, double b2, double c2, double d1, double d2)
{
	double v1 = u1;
	double v2 = u2;
	double v3 = u3;

	double k1 = 0, k2 = 0;
	//
	k1 = osnov2y1(x + (0.5 - 0.2886751)*h, u1 + (h*0.25)*k1 + (0.25 - 0.2886751)*h *k2, u2, u3,  a1, b1, c1);
	k2 = osnov2y1(x + (0.5 + 0.2886751)*h, u1 + (0.25 + 0.2886751)*h*k1 + k2*(h*0.25), u2, u3, a1, b1, c1);
	v1 = v1 + (h/2)*(k1 + k2);

		k1 = 0, k2 = 0;
	k1 = osnov2y2(x + (0.5 - 0.2886751)*h, u1, u2 + (h*0.25)*k1 + (0.25 - 0.2886751)*h *k2, u3, a2, b2, c2);
	k2 = osnov2y2(x + (0.5 + 0.2886751)*h, u1, u2 + (0.25 + 0.2886751)*h*k1 + k2*(h*0.25), u3, a2, b2, c2);
	v2 = v2 + (h/2)*(k1 + k2);

		k1 = 0, k2 = 0;
	k1 = osnov2y3(x + (0.5 - 0.2886751)*h, u1, u2, u3 + (h*0.25)*k1 + (0.25 - 0.2886751)*h *k2, d1,d2);
	k2 = osnov2y3(x + (0.5 + 0.2886751)*h, u1, u2, u3 + (0.25 + 0.2886751)*h*k1 + k2*(h*0.25), d1, d2);
	v3 = v3 + (h/2)*(k1 + k2);

	x += h;

	point st;
	st.num = num;
	st.x = x;
	st.y1 = v1;
	st.y2 = v2;
	st.y3 = v3;

	return st;
}

double max(double x, double y, double z)
{
	if ((x >= y) && (x >= z))
		return x;
	if ((y >= x) && (y >= z))
		return y;
	else 
		return z;
}


void RezOsn2()
{
	point *mas, * obh;
	mas = new point[1000];
	obh = new point[1000];
	double *e;
	e = new double[1000];
	e[0] = 0;
	double *h;
	h = new double[1000];

	double a1, b1, c1, a2, b2, c2, d1, d2, x0, u01, u02, u03, h0, E, xn;
	//xn - граница отрезка интегрирования
	int n = 0;
	x0 = 0.0;
	//
	cout << "u1' = u1(a1 - u1 - c1u2 - b1u3) "<< endl;
	cout << "u2' = u2(a2 - c2u1 - u2 - b2u3) "<< endl;
	cout << "u3' = u3(-1 + d1u1 + d2u2) "<< endl;
	cout << endl;
	//
	cout << "enter a1, b1, c1, a2, b2, c2, d1, d2 :  "<< endl;
	cin >> a1 >> b1 >> c1 >> a2 >> b2 >> c2 >> d1 >> d2;
	cout << endl;
	if ((a1 <0) || (a2 < 0) || (b1 < 0) || (b2 < 0) || (c1 < 0) || (c2 <0) || (d1 < 0) || (d2 < 0))
		{
			cout << "Incorrectly"<< endl;
			throw -1;
		}
	//
	cout << " u01:  "<< endl;
	cin >> u01;
	cout << endl;
	//
	cout << " u02 :  "<< endl;
	cin >> u02;
	cout << endl;
	//
	cout << "u03:  "<< endl;
	cin >> u03;
	cout << endl;
	//
	cout << "h0:  "<< endl;
	cin >> h0;
	cout << endl;
	//
	cout << "xn:  "<< endl;
	cout <<"xn - pravai granitca"<<endl;
	cin >> xn;
	cout << endl;
	//
	cout << "Enter E: "<<endl;
	cin >> E;
	cout << endl;
	//
	cout << "number of steps: " << endl;
	cin >> n;


	 point t;
	 t.num = 0;
	 t.x = x0;
	 t.y1 = u01;
	 t.y2 = u02;
	 t.y3 = u03;
	 mas[0] = t;
	 obh[0] = t;
	 h[0] = h0;

	 int p1,p2;
	 p1 = p2 = 0;
	 point3d e12;
	 e12.x1 = 0;
	 e12.x2 = 0;
	 e12.x3 = 0;

	 int i = 1;
	 while (i < n)
	 {
		point t1, t12, t2;
		
		//(x(n+1),v(n+1))
				x0 = mas[i-1].x;
				u01 = mas[i-1].y1;
				u02 = mas[i-1].y2;
				u03 = mas[i-1].y3;

				t1 = metodRKS(i, h0, x0, u01, u02,u03, a1, b1, c1, a2, b2, c2, d1, d2);
				obh[i] = t1;
			
		//(x(n+1/2),y(n+1/2))

				t12 = metodRKS(i, h0 * (0.5), x0, u01, u02,u03, a1, b1, c1, a2, b2, c2, d1, d2);
				
			
		//(x(n),Y(n))	

				t2 = metodRKS(i, h0*(0.5), t12.x, t12.y1, t12.y2,t12.y3, a1, b1, c1, a2, b2, c2, d1, d2);
			
				double en1 = t2.y1 - t1.y1;
				double en2 = t2.y2 - t1.y2;
				double en3 = t2.y3 - t1.y3;
				e12.x1 = en1;
				e12.x2 = en2;
				e12.x3 = en3;
				
				double S = max(en1,en2,en3);

				if (S < 0)
				S = (-1)*S;
				int p = 4;
				e[i] = S;

				if (S < E/(pow(2, p + 1)))
				{
					h0 = 2*h0;
					mas[i] = t2;
					p2 ++;
					h[i] = h0;
					
					if (mas[i].x > xn)
						break;
					i++;
				}
				if (S > E)
				{
					h0 = h0*(0.5);
					p1 ++;
					h[i] = h0;
				}
				if ((S > E/(pow(2, p + 1))) || (S < E))
				{
					mas[i] = t2;
					h0 = h0;
					h[i] = h0;
					if (mas[i].x > xn)
						break;
					i++;
				}

	 }
	 
	 cout << endl;
	 cout << "n  "  <<"     "<< "x  "  <<"     "<< "v1  " <<"              "<< "v2  " <<"               "<< "v3  " <<"               "<< "OLP  " <<"      "<<"h  " << endl;
	 cout << endl;
	 for (int i = 0; (i < n) && (mas[i].x < xn); i++)
	 {
		 cout << i <<"     " << mas[i].x <<"     "<<"(" << obh[i].y1 <<" ; "<<obh[i].y2 << " ; "<< obh[i].y3<<")"<<"           "<< "(" <<mas[i].y1 <<" ; "<<mas[i].y2 << " ; "<< mas[i].y3<<")"<<"         "<< e[i]<< "      "<<h[i] << endl;
		 cout << endl;
		 cout << endl;
	 }
	 cout << "p1 =    "<< p1 << "       "<< "p2 =    " << p2 << endl;
	 cout << endl;
}