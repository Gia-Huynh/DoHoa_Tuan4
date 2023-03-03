#include <GL/glut.h>
#include "header.h"

#pragma once
bool pressed = false;
int oldX = 0, oldY = 0;
extern int Top;
extern int Selected_Layer;
extern std::vector <std::vector<std::vector<int>>> Nigger;
extern std::vector <std::vector<std::vector<int>>> Border;
extern int* queueX;
extern int* queueY;
void resetPress()
{
	pressed = false;
	oldX = 0;
	oldY = 0;
};
int min(int a, int b)
{
	return (a > b) * b + (a <= b) * a;
};
void addLayer()
{
	Top++;
};
void fillLayer(int x, int y)
{
	//std::copy(&Nigger[Top][0][0], &Nigger[Top][0][0] + WindowHeight * WindowHeight, &Border[Top][0][0]);
	Border[Top] = Nigger[Top];
	int top = 0;
	queueX[0] = x;
	queueY[0] = y;
	RGBColor curColor;
	int curX; int curY;
	while (top >= 0) {
		curX = queueX[top];
		curY = queueY[top];
		top--;
		//std::cout << curX << " " << curY << "\n";
		if ((curX < 0) || (curY <= 0) || (curX >= WindowHeight) || (curY >= WindowHeight)) { continue; };
		if (Nigger[Top][curX][curY] == 0)
		{
			Nigger[Top][curX][curY] = 1;

			top++;
			queueX[top] = curX + 1;
			queueY[top] = curY;
			top++;
			queueX[top] = curX - 1;
			queueY[top] = curY;
			top++;
			queueX[top] = curX;
			queueY[top] = curY + 1;
			top++;
			queueX[top] = curX;
			queueY[top] = curY - 1;
		};
	};
	//printBorder(Top);
};
////// TEMPLATE
void templateFunc(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (pressed)
		{
			addLayer();
			glFlush();
			glutPostRedisplay();
			pressed = false;
		}
		else
		{
			pressed = true;
			oldX = x;
			oldY = y;
		}
	}
}
void dtFunc(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		/*std::cout << Top << "\n";
		for (int i = 0; i <= WindowHeight / 20; i++)
		{
			for (int j = 0; j <= WindowHeight / 20; j++)
			{
				std::cout << Border[Top][i * 20][j * 20] << " ";
			};
			std::cout << "\n";
		};*/
		//if (Nigger[Top][x][y] == 1) std::cout << "YES \n"; else std::cout << "NO \n";
		for (int i = Top; i >= 0; i--)
		{
			if (Nigger[i][x][y] == 1) {
				Selected_Layer = i;
				std::cout << i << "\n"; 
				return;
			};
		};
		Selected_Layer = 0;
	}
}

void dtMouseFunc(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (pressed)
		{
			addLayer();
			LineBresenham(oldX, oldY, x, y);
			glFlush();
			glutPostRedisplay();
			pressed = false;
		}
		else
		{
			pressed = true;
			oldX = x;
			oldY = y;
		}
	}
}
void TamGiacVuongCanFunc(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (pressed)
		{
			addLayer();
			if (x < oldX) { x = x + oldX; oldX = x - oldX; x = x - oldX; };
			if (y < oldY) { y = y + oldY; oldY = y - oldY; y = y - oldY; };
			if (x - oldX > y - oldY) x = oldX + y - oldY; else y = oldY + x - oldX;
			LineBresenham(oldX, oldY, x, oldY);
			LineBresenham(oldX, oldY, oldX, y);
			LineBresenham(x, oldY, oldX, y);
			fillLayer((x+oldX)/2, (y+oldY)/2 - abs(y-oldY)/3);
			glFlush();
			glutPostRedisplay();
			pressed = false;
		}
		else
		{
			pressed = true;
			oldX = x;
			oldY = y;
		}
	}
}
void TamGiacDeuFunc(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (pressed)
		{
			addLayer();
			if (x < oldX) { x = x + oldX; oldX = x - oldX; x = x - oldX; };
			if (y < oldY) { y = y + oldY; oldY = y - oldY; y = y - oldY; };
			if (x - oldX > y - oldY) x = oldX + y - oldY; else y = oldY + x - oldX;
			int gay = (x - oldX);
			LineBresenham(oldX+gay/2, oldY, oldX + gay / 2 + gay / 1.73205080757, y);
			LineBresenham(oldX + gay / 2 + gay / 1.73205080757, y, oldX + gay / 2 - gay / 1.73205080757,y);
			LineBresenham(oldX + gay / 2 - gay / 1.73205080757, y, oldX + gay / 2, oldY);
			fillLayer((x + oldX) / 2, (y + oldY) / 2);
			glFlush();
			glutPostRedisplay();
			pressed = false;
		}
		else
		{
			pressed = true;
			oldX = x;
			oldY = y;
		}
	}
}
void TuGiacFunc(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (pressed)
		{
			addLayer();
			LineBresenham(oldX, oldY, x, oldY);
			LineBresenham(oldX, oldY, oldX, y);
			LineBresenham(x, oldY, x, y);
			LineBresenham(oldX, y, x, y);
			fillLayer((x + oldX) / 2, (y + oldY) / 2);
			glFlush();
			glutPostRedisplay();
			pressed = false;
		}
		else
		{
			pressed = true;
			oldX = x;
			oldY = y;
		}
	}
}
void HinhVuongFunc(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (pressed)
		{
			addLayer();
			if (x < oldX) { x = x + oldX; oldX = x - oldX; x = x - oldX; };
			if (y < oldY) { y = y + oldY; oldY = y - oldY; y = y - oldY; };
			if (x - oldX > y - oldY) x = oldX + y - oldY; else y = oldY + x - oldX;
			LineBresenham(oldX, oldY, x, oldY);
			LineBresenham(oldX, oldY, oldX, y);
			LineBresenham(x, oldY, x, y);	
			LineBresenham(oldX, y, x, y);
			fillLayer((x + oldX) / 2, (y + oldY) / 2);
			glFlush();
			glutPostRedisplay();
			pressed = false;
		}
		else
		{
			pressed = true;
			oldX = x;
			oldY = y;
		}
	}
}
void HinhTronFunc(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (pressed)
		{
			addLayer();
			int ctX = (x - oldX) / 2 + oldX;
			int ctY = (y - oldY) / 2 + oldY;
			int R = min(x - oldX, y - oldY)/2;
			CircleMidPoint(ctX, ctY, R);
			fillLayer(ctX, ctY);
			glFlush();
			glutPostRedisplay();
			pressed = false;
		}
		else
		{
			pressed = true;
			oldX = x;
			oldY = y;
		}
	}
}

void ElipFunc(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (pressed)
		{
			addLayer();
			int ctX = (x - oldX) / 2 + oldX;
			int ctY = (y - oldY) / 2 + oldY;
			int R = min(x - oldX, y - oldY) / 2;
			EllipseMidPoint(ctX, ctY, abs(x-oldX)/2, abs(y - oldY) / 2);
			fillLayer(ctX, ctY);
			glFlush();
			glutPostRedisplay();
			pressed = false;
		}
		else
		{
			pressed = true;
			oldX = x;
			oldY = y;
		}
	}
}

void NguGiacFunc(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (pressed)
		{
			addLayer();
			if (x < oldX) { x = x + oldX; oldX = x - oldX; x = x - oldX; };
			if (y < oldY) { y = y + oldY; oldY = y - oldY; y = y - oldY; };
			if (x - oldX > y - oldY) x = oldX + y - oldY; else y = oldY + x - oldX;
			//1.37638192047 = Tan (108/2) = Tan (54);
			double gay = (double(y) - oldY)/2;
			LineBresenham((oldX + x)/2, oldY, x, oldY + (gay/ 1.37638192047));
			LineBresenham(x, oldY + (gay / 1.37638192047), oldX + (gay / 1.37638192047) + gay, y);
			LineBresenham(oldX + (gay / 1.37638192047) + gay, y, oldX - (gay / 1.37638192047) + gay, y);
			LineBresenham(oldX - (gay / 1.37638192047) + gay, y, oldX, oldY + (gay / 1.37638192047));
			LineBresenham(oldX, oldY + (gay / 1.37638192047), (oldX + x) / 2, oldY);
			fillLayer((x + oldX) / 2, (y + oldY) / 2);
			//GUD
			glFlush();
			glutPostRedisplay();
			pressed = false;
		}
		else
		{
			pressed = true;
			oldX = x;
			oldY = y;
		}
	}
}

void LucGiacFunc(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (pressed)
		{
			addLayer();
			if (x < oldX) { x = x + oldX; oldX = x - oldX; x = x - oldX; };
			if (y < oldY) { y = y + oldY; oldY = y - oldY; y = y - oldY; };
			if (x - oldX > y - oldY) x = oldX + y - oldY; else y = oldY + x - oldX;
			//1.37638192047 = Tan (108/2) = Tan (54);
			double gay = (double(y) - oldY) / 2;
			LineBresenham(oldX + gay * 0.57735026919, oldY, x - gay * 0.57735026919, oldY);
			LineBresenham(x - gay * 0.57735026919, oldY, x, oldY+gay);
			LineBresenham(x, oldY + gay, x - gay * 0.57735026919, y);
			LineBresenham(x - gay * 0.57735026919, y, oldX + gay * 0.57735026919,y);
			LineBresenham(oldX + gay * 0.57735026919, y, oldX, oldY + gay);
			LineBresenham(oldX, oldY + gay, oldX + gay * 0.57735026919, oldY);
			fillLayer((x + oldX) / 2, (y + oldY) / 2);
			glFlush();
			glutPostRedisplay();
			pressed = false;
		}
		else
		{
			pressed = true;
			oldX = x;
			oldY = y;
		}
	}
}

void MuiTenFunc(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (pressed)
		{
			addLayer();
			int gae = ((x - oldX) * 2) / 5;
			int gaeY = ((y - oldY) * 2) / 5;

			LineBresenham(oldX, oldY + gaeY, oldX, y - gaeY);

			LineBresenham(oldX, oldY+gaeY, oldX+gae*2, oldY+gaeY);
			LineBresenham(oldX + gae * 2, oldY + gaeY, oldX + gae * 2, oldY);

			LineBresenham(oldX, y - gaeY, oldX + gae * 2, y - gaeY);
			LineBresenham(oldX + gae * 2, y - gaeY, oldX + gae * 2, y);

			LineBresenham(oldX + gae * 2, y, x, oldY + (y - oldY)/2);
			LineBresenham(oldX + gae * 2, oldY, x, oldY+(y - oldY) / 2);
			fillLayer((x + oldX) / 2, (y + oldY) / 2);
			glFlush();
			glutPostRedisplay();
			pressed = false;
		}
		else
		{
			pressed = true;
			oldX = x;
			oldY = y;
		}
	}
}
void NgoiSaoFunc(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (pressed)
		{
			addLayer();
			if (x < oldX) { x = x + oldX; oldX = x - oldX; x = x - oldX; };
			if (y < oldY) { y = y + oldY; oldY = y - oldY; y = y - oldY; };
			if (x - oldX > y - oldY) x = oldX + y - oldY; else y = oldY + x - oldX;
			//1.37638192047 = Tan (108/2) = Tan (54);
			double gay = (double(y) - oldY) / 2;
			double gae = (double(x) - oldX) / 2;
			LineBresenham((oldX + x) / 2, oldY, (oldX + x) / 2 + gae/4, oldY + (gay / 1.37638192047));
			LineBresenham((oldX + x) / 2 + gae / 4, oldY + (gay / 1.37638192047),x, oldY + (gay / 1.37638192047));
			LineBresenham(x, oldY + (gay / 1.37638192047),(oldX + x) / 2 + gae / 4, oldY + gay + gay / 3);
			LineBresenham((oldX + x) / 2 + gae / 4, oldY + gay + gay / 3, oldX + (gay / 1.37638192047) + gay, y);
			LineBresenham(oldX + (gay / 1.37638192047) + gay, y, oldX + gae, oldY + gay + gay / 3);
			LineBresenham(oldX + gae, oldY + gay + gay / 3, oldX - (gay / 1.37638192047) + gay, y);
			//LineBresenham(x, oldY + (gay / 1.37638192047), oldX + (gay / 1.37638192047) + gay, y);
			//LineBresenham(oldX - (gay / 1.37638192047) + gay, y, oldX, oldY + (gay / 1.37638192047));
			LineBresenham(oldX, oldY + (gay / 1.37638192047), (oldX + x) / 2, oldY);
			fillLayer((x + oldX) / 2, (y + oldY) / 2);
			//GUD
			glFlush();
			glutPostRedisplay();
			pressed = false;
		}
		else
		{
			pressed = true;
			oldX = x;
			oldY = y;
		}
	}
}

void CongFunc(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (pressed)
		{
			addLayer();
			int gae = ((x - oldX) * 2 )/ 5;
			int gaeY = ((y - oldY) * 2) / 5;
			LineBresenham(oldX + gae, oldY, x - gae, oldY);
			LineBresenham(oldX + gae, oldY, oldX + gae, oldY + gaeY);
			LineBresenham(x - gae, oldY, x - gae, oldY + gaeY);

			LineBresenham(oldX + gae, y, x - gae, y);
			LineBresenham(oldX + gae, y, oldX + gae, y-gaeY);
			LineBresenham(x - gae, y, x - gae, y - gaeY);


			LineBresenham(oldX, oldY + gaeY, oldX, y - gaeY);
			LineBresenham(oldX, oldY + gaeY, oldX + gae, oldY + gaeY);
			LineBresenham(oldX, y - gaeY, oldX + gae, y - gaeY);


			LineBresenham(x, oldY + gaeY, x,  y - gaeY);
			LineBresenham(x, oldY + gaeY, x-gae, oldY + gaeY);
			LineBresenham(x, y - gaeY, x-gae, y - gaeY);
			/*
			LineBresenham(oldX, oldY, x, oldY);
			LineBresenham(oldX, oldY, oldX, y);
			LineBresenham(x, oldY, x, y);
			LineBresenham(oldX, y, x, y);*/
			fillLayer((x + oldX) / 2, (y + oldY) / 2);
			glFlush();
			glutPostRedisplay();
			pressed = false;
		}
		else
		{
			pressed = true;
			oldX = x;
			oldY = y;
		}
	}
}
void TruFunc(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (pressed)
		{
			addLayer();
			if (x < oldX) { x = x + oldX; oldX = x - oldX; x = x - oldX; };
			if (y < oldY) { y = y + oldY; oldY = y - oldY; y = y - oldY; };
			if (x - oldX > y - oldY) x = oldX + y - oldY; else y = oldY + x - oldX;
			int gaeY = (y - oldY) * 2 / 5;
			LineBresenham(oldX, oldY + gaeY, x, oldY + gaeY);
			LineBresenham(oldX, oldY + gaeY, oldX, y - gaeY);
			LineBresenham(x, oldY + gaeY, x, y - gaeY);
			LineBresenham(oldX, y - gaeY, x, y - gaeY);
			fillLayer((x + oldX) / 2, (y + oldY) / 2);
			glFlush();
			glutPostRedisplay();
			pressed = false;
		}
		else
		{
			pressed = true;
			oldX = x;
			oldY = y;
		}
	}
}
void NhanFunc(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (pressed)
		{
			addLayer();
			LineBresenham(oldX, oldY, x, oldY);
			LineBresenham(oldX, oldY, oldX, y);
			LineBresenham(x, oldY, x, y);
			LineBresenham(oldX, y, x, y);
			fillLayer((x + oldX) / 2, (y + oldY) / 2);
			glFlush();
			glutPostRedisplay();
			pressed = false;
		}
		else
		{
			pressed = true;
			oldX = x;
			oldY = y;
		}
	}
}
void ChiaFunc(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (pressed)
		{
			addLayer();
			if (x < oldX) { x = x + oldX; oldX = x - oldX; x = x - oldX; };
			if (y < oldY) { y = y + oldY; oldY = y - oldY; y = y - oldY; };
			if (x - oldX > y - oldY) x = oldX + y - oldY; else y = oldY + x - oldX;
			int gaeY = (y - oldY) * 2 / 5;
			LineBresenham(oldX, oldY + gaeY, x, oldY + gaeY);
			LineBresenham(oldX, oldY + gaeY, oldX, y - gaeY);
			LineBresenham(x, oldY + gaeY, x, y - gaeY);
			LineBresenham(oldX, y - gaeY, x, y - gaeY);
			fillLayer((x + oldX) / 2, (y + oldY) / 2);



			int ctX = (x - oldX) / 2 + oldX;
			int ctY = (y - oldY) / 2 + oldY;
			int R = (y - oldY) / 5;
			CircleMidPoint(ctX, oldY + R, R/2);
			CircleMidPoint(ctX, y - R, R/2);
			fillLayer(ctX, oldY + R);
			fillLayer(ctX, y - R);
			glFlush();
			glutPostRedisplay();
			pressed = false;
		}
		else
		{
			pressed = true;
			oldX = x;
			oldY = y;
		}
	}
}

void ToMauRed(int button, int state, int x, int y)
{
	if (pressed)
	{
	}
	else
	{
		RGBColor black;
		RGBColor red;
		red.r = 0xff;
		red.g = 0;
		red.b = 0;
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
			boundaryFill(x, y, red, black);
			std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
			std::cout << "Thoi gian ve: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "\n";
		};
	};
}
void ToMauGreen(int button, int state, int x, int y)
{
	if (pressed)
	{
	}
	else
	{
		RGBColor black;
		RGBColor red;
		red.r = 0;
		red.g = 255;
		red.b = 0;
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
			boundaryFill(x, y, red, black);
			std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
			std::cout << "Thoi gian ve: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "\n";
		};
	};
}
void ToMauYellow(int button, int state, int x, int y)
{
	if (pressed)
	{
	}
	else
	{
		RGBColor black;
		RGBColor red;
		red.r = 255;
		red.g = 255;
		red.b = 0;
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
			boundaryFillBFS(x, y, red, black);
			std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
			std::cout << "Thoi gian ve, thuat toan cu: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "\n";
		};
	};
}