#pragma once
#include <GL/glut.h>
#include<iostream>
#include <chrono>
#include "header.h"


extern int Top;
extern std::vector <std::vector<std::vector<int>>> Nigger;
extern std::vector <std::vector<std::vector<int>>> Border;
//extern int Nigger[50][WindowHeight][WindowHeight];
//extern int Border[50][WindowHeight][WindowHeight];

using namespace std;
int rx = 100, ry = 100;
int xCenter = 250, yCenter = 250;

void myinit(void)
{
	glClearColor(0.5, 0.5, 0.5, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 500, 0.0, 500);
}

void setPixel(int x, int y)
{
	//glBegin(GL_POINTS);
	glVertex2i(x, y);
	Nigger[Top][x][y] = 1;
	//cout << " NIGGER DONE ";
	//glEnd();
}
void Line(GLint x, GLint y, GLint w, GLint z)
{
	glBegin(GL_LINES);
	glVertex2i(x, y);
	glVertex2i(w, z);
	glEnd();
};
/*void LineDDA(double x, double y, double w, double z)
{
	double dx = (double)w - x; double dy = (double)z - y;
	if ((dy == 0) || (dx == 0))
	{
		if (dx == 0) dy = dy / abs(dy);
		else dx = dx / abs(dx);
	}
	else
		if (dy > dx) {
			dx = dx / abs(dy);	dy = dy / abs(dy);
		}
		else {
			dy = dy / abs(dx);	dx = dx / abs(dx);
		};
	glBegin(GL_POINTS);
	while (!((abs(x - w) < 0.1) && (abs(y - z) < 0.1))) {
		//cout << x << " " << y << "\n";
		glVertex2i(x, y);
		x = x + dx;
		y = y + dy;
	};
	glVertex2i(x, y);
	glEnd();
};*/
void LineBresenham(int x, int y, int w, int z)
{
	glBegin(GL_POINTS);
	int temp; //temp;
	if (x > w)
	{
		temp = x; x = w; w = temp;
		temp = y; y = z; z = temp;
	};

	int dx = w - x;
	int dy = z - y;
	if (abs(dx) >= abs(dy)) {
		if (dy < 0) dy = -dy;
		if (dx < 0) dx = -dx;
		int p = 2 * dy - dx;
		const int const1 = 2 * dy;
		const int const2 = 2 * (dy - dx);
		//cout << "x " << dx << " " << dy << " " << p << " " << const1 << " " << const2;
		dy = z - y;
		dx = w - x;
		int* xp; //x pointer;
		int* yp; //y pointer;
		setPixel(x, y);
		while (x < w)
		{
			if (p < 0)
			{
				p += const1;
			}
			else {
				p += const2;
				y += (dy > 0);
				y -= (dy < 0);
			};
			x++;
			setPixel(x, y);
		};
		while (y != z)
		{
			setPixel(x, y);
			y += dy / abs(dy);
		};
	}
	else
	{
		//cout << "ye";
		if (y > z)
		{
			temp = x; x = w; w = temp;
			temp = y; y = z; z = temp;
		};
		dx = w - x;
		dy = z - y;
		if (dx < 0) dx = -dx;
		//y = ax+b;
		//x = (y-b)/a
		int p = 2 * dx - dy;
		const int const1 = 2 * dx;
		const int const2 = 2 * (dx - dy);
		dx = w - x;

		int* xp; //x pointer;
		int* yp; //y pointer;
		setPixel(x, y);
		while (y < z)
		{
			if (p < 0)
			{
				p += const1;
			}
			else {
				p += const2;
				x += (dx > 0);
				x -= (dx < 0);
			};
			y++;
			setPixel(x, y);
			//cout << x << " " << y << " " << p << "\n";
		};
	};
	setPixel(x, y);
	glEnd();
}
/* //CIRCLE midpoint
F(x, y) = (x-A)^2 + (y-B)^2 - r^2 = x^2 + y^2 - 2Ax - 2By + (A^2 + B^2 - r^2)
F(x - 0.5, y) = (x -0.5 -A)^2 + (y -B)^2 - r^2 = x^2 + y^2 - 2Ax - 2By + (A^2 + B^2 - r^2) + (-x + 0.25 + A)
(x -0.5 -A)^2 = x^2 - 2(0.5+A)x + (0.5 + A)^2 = x^2 - x - 2Ax + 0.25 + A + A^2 = -x +0.25 + A
while (y tang va y<=x):
	veHinh (y, x);
	//if F <= 0: On/Inside circle, giu nguyen x
	GiuX = [F(x -0.5, y+1) - F(x -0.5, y) = (y+1-B)^2 - (y-B)^2 = (y+1)^2 - 2(y+1)B + B^2 - y^2 +2By - B^2 = y^2 + 2y + 1 - 2B - y^2 = 2(y-B) + 1]
	P = P +GiuX;
	y=y+1;
	F > 0 = outside, giam x
		giamX = [F(x-1.5, y+1) - F(x-0.5, y+1) = (x -1.5 -A)^2 - (x -0.5 -A)^2 = (x-1.5)^2 - (x-0.5)^2 -2A(x-1.5) +2A(x-0.5) +A^2 -A^2 = -2x +2A]
		P = P +giamX;
		x = x-1;
Tinh phet cut nhung roi nhan ra A voi B = 0 :).
*/
void CircleMidPoint(int X, int Y, int R)
{
	std::cout << "Circle midpoint\n";
	glBegin(GL_POINTS);
	int x = R;
	int y = 0;
	const int nigger = -(R * R);
	int P = nigger + (double)x * x + (double)y * y - x + 0.25;
	double gay = 0;
	while (y <= x)
	{
		setPixel(x + X, y + Y);		setPixel(-x + X, y + Y);		setPixel(x + X, -y + Y);		setPixel(-x + X, -y + Y);
		setPixel(y + X, x + Y);		setPixel(-y + X, x + Y);		setPixel(y + X, -x + Y);		setPixel(-y + X, -x + Y);
		y = y + 1;
		P = P + 2 * (y)+1;
		if (P > 0)
		{
			P = P - 2 * (x);
			x = x - 1;
		};
	};
	glEnd();
};
double EllipseFunction(double x, double y, double a, double b)
{
	return ((x / a) * (x / a) + (y / b) * (y / b) - 1);
};
void EllipseMidPoint(int X, int Y, int A, int B)
{
	glBegin(GL_POINTS);
	int x = A;
	int y = 0;
	int prevX = A, prevY = 0;
	double P = EllipseFunction(x - 0.5, y, A, B);
	while ((x >= 0) && (y <= B))
	{
		prevX = x; prevY = y;
		setPixel(x + X, y + Y);		setPixel(-x + X, y + Y);		setPixel(x + X, -y + Y);		setPixel(-x + X, -y + Y);
		y++;
		P = EllipseFunction(x - 0.5, y, A, B);
		while (P > 0)
		{
			x--;
			P = EllipseFunction(x - 0.5, y, A, B);
			if (x < 0) break;
		};
		if (abs(x - prevX) > 1) break;
	};
	x = prevX;
	y = prevY;
	P = EllipseFunction(x, y + 0.5, A, B);
	while ((x >= 0) && (y <= B))
	{
		prevX = x; prevY = y;
		setPixel(x + X, y + Y);		setPixel(-x + X, y + Y);		setPixel(x + X, -y + Y);		setPixel(-x + X, -y + Y);
		x--;
		P = EllipseFunction(x, y + 0.5, A, B);
		while (P < 0)
		{
			y++;
			P = EllipseFunction(x, y + 0.5, A, B);
			if (y > B) break;
		};
	};
	glEnd();
};
double ParabolaFunction(double X, double Y, double H, double K, double P)
{
	return ((X - H) * (X - H) - 4 * P * (Y - K));
};
void ParabolaMidPoint(int X, int Y, int P)
{
	int gay = 1;
	if (P < 0) { P = -1 * P; gay = -1; }
	if (P == 0) { setPixel(X, Y); return; };
	int x = 0;
	int y = 0;
	int prevX = 0, prevY = 0;
	double F;
	F = ParabolaFunction(x, y + 0.5, 0, 0, P);
	do
	{
		if ((x > 1000) || (y > 1000)) break;
		prevX = x; prevY = y;
		setPixel(x + X, gay * y + Y);		setPixel(-x + X, gay * y + Y);
		x++;
		F = ParabolaFunction(x, y + 0.5, 0, 0, P);
		while (F > 0)
		{
			y++;
			F = ParabolaFunction(x, y + 0.5, 0, 0, P);
		};
	} while ((abs(y - prevY) < 1.01) && (x < 1000) && (y < 1000));
	F = ParabolaFunction(x + 0.5, y, 0, 0, P);
	x = prevX;
	y = prevY;
	do
	{
		prevX = x; prevY = y;
		setPixel(x + X, gay * y + Y);		setPixel(-x + X, gay * y + Y);
		y++;
		F = ParabolaFunction(x + 0.5, y, 0, 0, P);
		while (F < 0)
		{
			x++;
			F = ParabolaFunction(x + 0.5, y, 0, 0, P);
		};
	} while ((abs(x - prevX) < 1.01) && (x < 1000) && (y < 1000));

};
double HyperbolaFunction(double X, double Y, double A, double B)
{
	return ((X / A) * (X / A) - (Y / B) * (Y / B) - 1);
};
void HyperbolaMidPoint(int X, int Y, double A, double B)
{
	if ((A <= 0.001) || (B <= 0.001)) return;
	int gay = 1;
	int x = A;
	int y = 0;
	int prevX = A, prevY = 0;
	double F;
	F = HyperbolaFunction(x + 0.5, y, A, B);
	//cout << F << "\n";
	do
	{
		prevX = x; prevY = y;
		setPixel(x + X, gay * y + Y);		setPixel(-x + X, gay * y + Y);
		setPixel(x + X, gay * -y + Y);		setPixel(-x + X, gay * -y + Y);
		y++;
		F = HyperbolaFunction(x + 0.5, y, A, B);
		//cout << F << "\n";
		while (F < 0)
		{
			x++;
			F = HyperbolaFunction(x + 0.5, y, A, B);
			//cout << F << "ye\n";
		};
	} while ((abs(x - prevX) < 1.01) && (x < 1000) && (y < 1000));
	x = prevX;
	y = prevY;
	F = HyperbolaFunction(x, y + 0.5, A, B);
	do
	{
		if ((x > 1000) || (y > 1000)) break;
		prevX = x; prevY = y;
		setPixel(x + X, gay * y + Y);		setPixel(-x + X, gay * y + Y);
		setPixel(x + X, gay * -y + Y);		setPixel(-x + X, gay * -y + Y);
		x++;
		F = HyperbolaFunction(x, y + 0.5, A, B);
		while (F > 0)
		{
			y++;
			F = HyperbolaFunction(x, y + 0.5, A, B);
		};
	} while ((abs(y - prevY) < 1.01) && (x < 1000) && (y < 1000));
};

/*void display()
{
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(2.0);
	int n, a, b, c, d;
	std::chrono::steady_clock::time_point begin;
	std::chrono::steady_clock::time_point end;
		
	std::cout << "Nhap input (n + 3 so hoac 4 so): ";
	cin >> n;

	begin = std::chrono::steady_clock::now();
	switch (n)
	{
	case 0:
		cin >> a >> b >> c >> d;
		LineDDA(a, b, c, d);
		break;
	case 1:
		cin >> a >> b >> c >> d;
		LineBresenham(a, b, c, d);
		break;
	case 2:
		cin >> a >> b >> c;
		CircleMidPoint(a, b, c);
		break;
	case 3:
		cin >> a >> b >> c >> d;
		EllipseMidPoint(a, b, c, d);
		break;
	case 4:
		cin >> a >> b >> c;
		ParabolaMidPoint(a, b, c);
		break;
	case 5:
		cin >> a >> b >> c >> d;
		HyperbolaMidPoint(a, b, c, d);
		break;
	case 99:
		cin >> a >> b >> c >> d;
		Line(a, b, c, d);
		break;
	case 98:
		//cin >> a >> b >> c >> d;
		//x1 = 1
		//y1 = 0
		cout <<"Goc  | Sai so \n";
		int a, b, c, d;
		c = 250;
		d = 250;
		cout << fixed;
		a = 500;
		for (b = 500; b > 0; b -= 10)
		{
			cout << (atan2(1 * (b - d) - 0 * (a - c), 1 * (a - c) + 0 * (b - d)) * 57.2957795131 - 0) << " " << LineDDATest(a, b, c, d) << "\n";
		}
		b = 0;
		for (a = 500; a > 0; a -= 10)
		{
			cout << (atan2(1 * (b - d) - 0 * (a - c), 1 * (a - c) + 0 * (b - d)) * 57.2957795131 - 0) << " " << LineDDATest(a, b, c, d) << "\n";
		}
		a = 0;
		for (b = 0; b < 500; b += 10)
		{
			cout << (atan2(1 * (b - d) - 0 * (a - c), 1 * (a - c) + 0 * (b - d)) * 57.2957795131 - 0) << " " << LineDDATest(a, b, c, d) << "\n";
		}
		b = 500;
		for (a = 0; a < 500; a += 10)
		{
			cout << (atan2(1 * (b - d) - 0 * (a - c), 1 * (a - c) + 0 * (b - d)) * 57.2957795131 - 0) << " " << LineDDATest(a, b, c, d) << "\n";
		}

		break;
	case 97:
		c = 250;
		d = 250;
		cout << fixed;
		a = 500;
		cout << "Goc  | Sai so \n";
		for (b = 500; b > 0; b -= 10)
		{
			cout << (atan2(1 * (b - d) - 0 * (a - c), 1 * (a - c) + 0 * (b - d)) * 57.2957795131 - 0) << " " << LineBresenhamTest(a, b, c, d) << "\n";
		}
		b = 0;
		for (a = 500; a > 0; a -= 10)
		{
			cout << (atan2(1 * (b - d) - 0 * (a - c), 1 * (a - c) + 0 * (b - d)) * 57.2957795131 - 0) << " " << LineBresenhamTest(a, b, c, d) << "\n";
		}
		a = 0;
		for (b = 0; b < 500; b += 10)
		{
			cout << (atan2(1 * (b - d) - 0 * (a - c), 1 * (a - c) + 0 * (b - d)) * 57.2957795131 - 0) << " " << LineBresenhamTest(a, b, c, d) << "\n";
		}
		b = 500;
		for (a = 0; a < 500; a += 10)
		{
			cout << (atan2(1 * (b - d) - 0 * (a - c), 1 * (a - c) + 0 * (b - d)) * 57.2957795131 - 0) << " " << LineBresenhamTest(a, b, c, d) << "\n";
		}
		break;
	case 96:
		cout << "Cleared screen";
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glColor3f(1.0, 0.0, 0.0);
		glPointSize(2.0);
		break;
	default:
		std::cout << "Bad Input, chuong trinh tu huy\n";
		glutDestroyWindow(glutGetWindow());
		return;
	}
		end = std::chrono::steady_clock::now();
		std::cout << "Thoi gian chay: " << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << " ms";
		cout << "\n\n";
		glFlush();
		glutPostRedisplay();
	//};
};
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("20120070");
	myinit();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}*/
