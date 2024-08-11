#pragma once
#include <string>

#include "Cell.h"

class Field
{
	Cell** cells;
	bool** revealed;

	int width, height, mines;

	const int cellSize = 50;
	const int spacing = 3;

	const int startX = 50;
	const int startY = 50;

	void GenetateField();
	void RevealCell(int x, int y);

	Coord GetCellCoordByPoint(CPoint& point);
public: 
	Field();
	Field(int width, int height, int mines);
	Field(const Field& other);

	void Draw(CPaintDC& dc);

	bool Set(CPoint& point, bool& end);
	bool SetMarker(CPoint& point);

	bool Win();

	Field& operator=(const Field& other);
};