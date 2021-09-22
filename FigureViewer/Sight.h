#ifndef SIGHT_H
#define SIGHT_H

#include "Figure.h"

class Sight : public Figure
{
public:
	Sight(int size=12, COLORREF Color= RGB(0, 0, 0), int offsetX=100, int offsetY=100) : Figure(size, offsetX, offsetY, Color)
	{
	}
	void Draw(HDC dc)

	{
	
		
		HPEN pen = (HPEN)SelectObject(dc, CreatePen(PS_SOLID, 1, Color));
		Rectangle(dc, offsetX - size, offsetY - size, offsetX + size, offsetY + size);
		
		/*
		Ellipse( dc, offsetX-size, offsetY-size, offsetX+size, offsetY+size);
		MoveToEx(dc, offsetX-size, offsetY,      NULL);
		LineTo(  dc, offsetX+size, offsetY);
		MoveToEx(dc, offsetX,      offsetY-size, NULL);
		LineTo(  dc, offsetX,      offsetY+size);*/
	}
	bool InnerPoint(int X, int Y){
		
		if ((X > offsetX - size) && (X < offsetX + size))
			if ((Y > offsetY - size) && (Y < offsetY + size))
				return true;
		return false;
	}
};

#endif SIGHT_H
