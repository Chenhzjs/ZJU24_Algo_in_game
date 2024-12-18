#ifndef _DRAW_H_
#define _DRAW_H_

void DrawCircle(double r);
void DrawRectangle(double w, double h, double alpha);
void Line(double x1, double x2, double y1, double y2);
void AlphaLine(double size, double alpha);
void DrawArrow(double size, double alpha);
void DrawHealth(double size, double x, double y);
void DrawStrength(double size, double x, double y);
void DrawPoison(double size, double x, double y);
void DrawWeak(double size, double x, double y);
void DrawDiamond(double size); 
void DrawBlock(double size, double x, double y);
void DrawVulnerable(double size, double x, double y);
void DrawFrail(double size, double x, double y);
#endif
