#include <stdio.h>
#include <string.h>
#include <graphics.h>
#include <math.h>
#include <windows.h>
#include <time.h>
#include "draw.h"

#define PI 3.1415926535
void DrawCircle(double r)
{
	double x, y;
	x = GetCurrentX();
	y = GetCurrentY();
	MovePen(x + r, y);
    DrawArc(r, r, 0, 360);
}

void DrawRectangle(double w, double h, double alpha)
{
	double x, y;
	x = GetCurrentX();
	y = GetCurrentY();
	MovePen(x, y);
	DrawLine(w * cos(alpha), w * sin(alpha));
	DrawLine(h * cos(alpha + 0.5 * PI), h * sin(alpha + 0.5 * PI));
	DrawLine(w * cos(alpha + PI), w * sin(alpha +  PI));
	DrawLine(h * cos(alpha + 1.5 * PI), h * sin(alpha + 1.5 * PI));
}

void Line(double x1, double x2, double y1, double y2)
{
	MovePen(x1, y1);
	DrawLine(x2 - x1, y2 - y1);
}

void DrawArrow(double size, double alpha)
{
	double x, y;
	x = GetCurrentX();
	y = GetCurrentY();
	MovePen(x, y);
	DrawLine(size * 0.01 * 1 * cos(alpha), size * 0.01 * 1 * sin(alpha));
	x = GetCurrentX();
	y = GetCurrentY();
	MovePen(x, y);
	DrawLine(size * 0.01 * 0.3 * cos(alpha + 0.75 * PI), size * 0.01 * 0.3 * sin(alpha + 0.75 * PI));
	MovePen(x, y);
	DrawLine(size * 0.01 * 0.3 * cos(alpha - 0.75 * PI), size * 0.01 * 0.3 * sin(alpha - 0.75 * PI));
}
void AlphaLine(double size, double alpha)
{
	double x, y;
	x = GetCurrentX();
	y = GetCurrentY();
	MovePen(x, y);
	DrawLine(size * 1 * cos(alpha), size * 1 * sin(alpha));
	
}
void DrawHealth(double size, double x, double y)
{
	MovePen(x + size, y); 
	DrawArc(size, size, 0, 180);
	DrawArc(size, size, 0, 180);
	DrawArc(size * 4, size * 3, 180, 60); 
	DrawArc(size * 4, size * 3, -60, 60); 	
}
void DrawStrength(double size, double x, double y)
{
	MovePen(x + 1.5 * size, y);
	DrawLine(2 * size, 0);
	DrawLine(0, -1.4 * size);
	DrawLine(-2.6 * size, 0);
	DrawLine(0, -1.8 * size);
	DrawLine(-1.8 * size, 0);
	DrawLine(0, 1.8 * size);
	DrawLine(-2.6 * size, 0);
	DrawLine(0, 1.4 * size);
	DrawLine(2 * size, 0);
	DrawLine(0, 4 * size);
	AlphaLine(1.5 * size / cos(PI / 4), PI / 4);
	AlphaLine(1.5 * size / cos(PI / 4), -PI / 4);
	DrawLine(0, -4 * size);
}
void DrawPoison(double size, double x, double y)
{
	MovePen(x, y);
	AlphaLine(1 * size / cos(PI / 4), PI / 4);
	MovePen(x, y);
	AlphaLine(1 * size / cos(PI / 4), PI / 4 * 3);
	MovePen(x, y);
	AlphaLine(1 * size / cos(PI / 4), PI / 4 * 5);
	MovePen(x, y);
	AlphaLine(1 * size / cos(PI / 4), PI / 4 * 7);
	MovePen(x + 2 * size * cos(PI / 12 * 4.8), y + 2 * size * sin(PI / 12 * 4.8));
	DrawArc(2 * size, 2 * size, 72, -324);
	DrawLine(0, 2 * size);
	DrawLine(4 * size * cos(PI / 12 * 4.8), 0);
	DrawLine(0, -2 * size);
	MovePen(x, y + 5 * size);
	DrawCircle(0.5 * size);
	MovePen(x + 1 * size, y + 6 * size);
	DrawCircle(0.3 * size);
}
void DrawWeak(double size, double x, double y)
{
	MovePen(x + 1.5 * size, y);
	DrawLine(2 * size, 0);
	DrawLine(0, -1.4 * size);
	DrawLine(-2.6 * size, 0);
	DrawLine(0, -1.8 * size);
	DrawLine(-1.8 * size, 0);
	DrawLine(0, 1.8 * size);
	DrawLine(-2.6 * size, 0);
	DrawLine(0, 1.4 * size);
	DrawLine(2 * size, 0);
	DrawLine(0, 3 * size);
	AlphaLine(0.75 * size / cos(PI / 4), -PI / 4);
	AlphaLine(0.75 * size / cos(PI / 4), PI / 4);
	AlphaLine(0.75 * size / cos(PI / 4), -PI / 4);
	AlphaLine(0.75 * size / cos(PI / 4), PI / 4);
	DrawLine(0, -3 * size);
}
void DrawDiamond(double size)
{
	double x, y;
	x = GetCurrentX();
	y = GetCurrentY();
	MovePen(x, y + size / 2);
	AlphaLine(size, - PI / 6);
	AlphaLine(size, - PI / 6 * 5);
	AlphaLine(size, PI / 6 * 5);
	AlphaLine(size, PI / 6);
}
void DrawBlock(double size, double x, double y)
{
	MovePen(x + size, y); 
	DrawLine(-size, 0);
	DrawLine(0, 1.5 * size);
	AlphaLine(size, - PI / 4);
	AlphaLine(size, PI / 4);
	AlphaLine(size, - PI / 4);
	AlphaLine(size, PI / 4);
	DrawLine(0, - 1.5 * size);
	DrawLine(-2 * size, 0);
}
void DrawVulnerable(double size, double x, double y)
{
	MovePen(x, y); 
	DrawLine(0, 1 * size);
	MovePen(x + size, y); 
	DrawLine(-2 * size, 0);
    MovePen(x, y); 
    DrawLine(0, -2.5 * size);
}
void DrawFrail(double size, double x, double y)
{
	MovePen(x, y); 
	DrawLine(0, 2.5 * size);
	MovePen(x + size, y); 
	DrawLine(-2 * size, 0);
    MovePen(x, y); 
    DrawLine(0, -1 * size);
}
