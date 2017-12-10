#pragma once
#pragma once
#include <windowsx.h>
#include "Quadrangle.h"
using namespace std;

struct color
{
	short R;
	short G;
	short B;
};

class View
{
	HWND hwnd;
	HDC hdc;
	RECT rt;
	HPEN hPen;
	HBRUSH hBrush;
	color colorPen, colorBrush;
	short width;

	bool isAffiliation(Quadrangle *quadrangle);
	bool isRGB(color colorPenOrBrush);
	bool isWidth(short *width);
	friend class Container;
public:
	View();
	~View();
	View(HWND, HDC, short *width, color *colorPen, color *colorBrush);
	void setCharacteristicsView(short *width, color *colorPen, color *colorBrush);
	short *getWidth();
	color *getColorPen();
	color *getColorBrush();
	void viewUnpaintQudrangle(Quadrangle *quadrangle);
	void viewPaintQudrangle(Quadrangle *quadrangle);
	void viewTwoNestedPaintQuadrangle(Quadrangle *externalQuadrangle, Quadrangle *internalQuadrangle);
	void enterCharacteristicsFromFiles(string fd);
	void saveCharacteristicsToFile(string fd);
};