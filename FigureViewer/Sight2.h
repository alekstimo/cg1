#ifndef SIGHT2_H
#define SIGHT2_H

#include "Figure.h"

class Sight2 : public Figure
{
public:
	Sight2(int size = 12, COLORREF Color = RGB(0, 0, 0), int offsetX = 200, int offsetY = 200) : Figure(size, offsetX, offsetY,Color)
	{
	}
	void Draw(HDC dc)

	{

		/*COLORREF PenColor = RGB(0, 0, 0);
		HPEN pen = (HPEN)SelectObject(dc, CreatePen(PS_SOLID, 1, PenColor));
		Rectangle(dc, offsetX - size, offsetY - size, offsetX + size, offsetY + size);*/

		HPEN pen = (HPEN)SelectObject(dc, CreatePen(PS_SOLID, 1, Color));
		Ellipse( dc, offsetX-size, offsetY-size, offsetX+size, offsetY+size);
		MoveToEx(dc, offsetX-size, offsetY,      NULL);
		LineTo(  dc, offsetX+size, offsetY);
		MoveToEx(dc, offsetX,      offsetY-size, NULL);
		LineTo(  dc, offsetX,      offsetY+size);
	}
	bool InnerPoint(int X, int Y)
	{
		return (X - offsetX) * (X - offsetX) + (Y - offsetY) * (Y - offsetY) <= size * size;
	}
};

#endif SIGHT2_H