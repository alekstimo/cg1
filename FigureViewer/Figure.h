#ifndef FIGURE_H
#define FIGURE_H

class Figure
{
protected:
	int size;
	int offsetX, offsetY;
	COLORREF Color;
	int sizeChange = 5;
private:
	bool isDragging;
	int previousX, previousY;
public:
	Figure(int size, int offsetX, int offsetY, COLORREF Color) : size(size), offsetX(offsetX), offsetY(offsetY), Color(Color), isDragging(false), previousX(0), previousY(0)
	{
	}
	void Clear(HDC dc, HWND hWnd)
	{
		
		RECT rect;
		GetClientRect(hWnd, &rect);
		FillRect(dc, &rect, (HBRUSH)(COLOR_WINDOW + 1));

		/*COLORREF PenColor = RGB(255, 255, 255);
		HPEN pen = (HPEN)SelectObject(dc, CreatePen(PS_SOLID, 1, PenColor));
		Rectangle(dc, previousX- size, previousY - size, previousX + size, previousY + size);*/
	}
	virtual void Draw(HDC dc) = 0;
	virtual bool InnerPoint(int X, int Y) = 0;
	void MoveTo(int X, int Y)
	{
		
		offsetX = X;
		offsetY = Y;
	}
	void Move(int X, int Y)
	{
		previousX = offsetX;
		offsetX = previousX +  X;
		previousY = offsetY;
		offsetY = previousY + Y;
	}
	void StartDragging(int X, int Y)
	{
		if (InnerPoint(X, Y)) {
			previousX = offsetX;
			previousY = offsetY;

			offsetX = X;
			offsetY = Y;
			isDragging = true;
		}
	}
	void Drag(int X, int Y)
	{
		MoveTo(X, Y);
	}
	void ChangeSize(int SIZE)
	{
		if (SIZE > 0)
			size += sizeChange;
		else if (size > 10) {
				size -= sizeChange;
		}
		/*if(SIZE>0)
		 size += SIZE/10;
		else if(abs(SIZE/10)<size)
		 size += SIZE / 10;*/
	}
	void StopDragging()
	{
		isDragging = false;
	}
	bool IsDragging()
	{
		return isDragging;
	}
	bool MkCtrl(WPARAM wParam) {
		if (wParam == MK_CONTROL)
			return 1;
		return 0;
	}
	bool inWindow(int wSize, int X, int Y) {
		if ((offsetX+X+size < wSize) && (offsetY+Y+size < wSize))
			if ((offsetY+Y-size > 0) && (offsetX+X-size > 0))
				return true;
		return false;
	}
	bool inWindowNewSize(int wSize) {
	if((offsetX+size+sizeChange<wSize)&&(offsetY+size+sizeChange<wSize))
		if((offsetX-size-sizeChange>0)&& (offsetY - size - sizeChange > 0))
			return true;
	return false;
	}
	int getX() {
		return offsetX;
	}
	int getY() {
		return offsetY;
	}
};

#endif FIGURE_H
