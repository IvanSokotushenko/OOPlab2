#include "View.h"
using namespace std;

bool View::isAffiliation(Quadrangle *quadrangle)
{
	GetClientRect(this->hwnd, &(this->rt));
	POINT *points = quadrangle->getQuadrangle();
	return ((points[0].x < rt.left) || (points[0].y < rt.top) || (points[0].x > rt.right) || (points[0].y > rt.bottom) ||
		(points[1].x > rt.right) || (points[1].y < rt.top) || (points[1].x < rt.left) || (points[1].y > rt.bottom) ||
		(points[2].x > rt.right) || (points[2].y > rt.bottom) || (points[2].x < rt.left) || (points[2].y < rt.top) ||
		(points[3].x < rt.left) || (points[3].y > rt.bottom) || (points[3].x > rt.right) || (points[3].y < rt.top));
}

bool View::isRGB(color colorPenOrBrush)
{
	return ((colorPenOrBrush.R < 0 || colorPenOrBrush.R > 255) ||
		(colorPenOrBrush.G < 0 || colorPenOrBrush.G > 255) ||
		(colorPenOrBrush.B < 0 || colorPenOrBrush.B> 255));
}

bool View::isWidth(short *width)
{
	return (*width < 0 || *width > 9);
}

View::View()
{
	hwnd = GetConsoleWindow();
	hdc = GetDC(hwnd);
	colorPen = { 0, 0, 0 };
	colorBrush = { 255, 255, 255 };
	hPen = CreatePen(PS_SOLID, 5, RGB(this->colorPen.R, this->colorPen.G, this->colorPen.B));
	hBrush = CreateSolidBrush(RGB(this->colorBrush.R, this->colorBrush.G, this->colorBrush.B));
}

View::~View()
{
	SelectPen(hdc, hPen);
	SelectBrush(hdc, hBrush);
	DeletePen(hPen);
	DeleteBrush(hBrush);
	ReleaseDC(this->hwnd, this->hdc);
}

View::View(HWND hwnd, HDC hdc, short *width, color *colorPen, color *colorBrush)
{
	this->hwnd = hwnd;
	this->hdc = hdc;
	this->width = *width;
	if (isWidth(width))
		throw exception("Такую толщину линий задать нельзя!\nМаксимальная толщина - 9 пикселей.");
	this->colorPen = *colorPen;
	if (isRGB(*colorPen))
		throw exception("Такого цвета не существует!");
	this->colorBrush = *colorBrush;
	if (isRGB(*colorBrush))
		throw exception("Такого цвета не существует!");
	hPen = CreatePen(PS_SOLID, this->width, RGB(this->colorPen.R, this->colorPen.G, this->colorPen.B));
	hBrush = CreateSolidBrush(RGB(this->colorBrush.R, this->colorBrush.G, this->colorBrush.B));
}

void View::setCharacteristicsView(short *width, color *colorPen, color *colorBrush)
{
	this->width = *width;
	if (isWidth(width))
		throw exception("Такую толщину линий задать нельзя!\nМаксимальная толщина - 9 пикселей.");
	this->colorPen = *colorPen;
	if (isRGB(*colorPen))
		throw exception("Такого цвета не существует!");
	this->colorBrush = *colorBrush;
	if (isRGB(*colorBrush))
		throw exception("Такого цвета не существует!");
	hPen = CreatePen(PS_SOLID, this->width, RGB(this->colorPen.R, this->colorPen.G, this->colorPen.B));
	hBrush = CreateSolidBrush(RGB(this->colorBrush.R, this->colorBrush.G, this->colorBrush.B));
}

short *View::getWidth()
{
	return &this->width;
}

color *View::getColorPen()
{
	return &this->colorPen;
}

color *View::getColorBrush()
{
	return &this->colorBrush;
}

void View::viewUnpaintQudrangle(Quadrangle *quadrangle)
{
	if (isAffiliation(quadrangle))
		throw exception("Четырёхугольник выходит за границу экрана!");
	InvalidateRect(this->hwnd, 0, TRUE);
	UpdateWindow(this->hwnd);
	HPEN SelectPen(this->hdc, this->hPen);
	HBRUSH SelectBrush(this->hdc, GetStockBrush(NULL_BRUSH));
	POINT *points = quadrangle->getQuadrangle();
	Polygon(this->hdc, points, 4);
}

void View::viewPaintQudrangle(Quadrangle *quadrangle)
{
	if (isAffiliation(quadrangle))
		throw exception("Четырёхугольник выходит за границу экрана!");
	InvalidateRect(this->hwnd, 0, TRUE);
	UpdateWindow(this->hwnd);
	HPEN SelectPen(this->hdc, this->hPen);
	HBRUSH SelectBrush(this->hdc, this->hBrush);
	POINT *points = quadrangle->getQuadrangle();
	Polygon(this->hdc, points, 4);
}

void View::viewTwoNestedPaintQuadrangle(Quadrangle *externalQuadrangle, Quadrangle *internalQuadrangle)
{
	if (isAffiliation(externalQuadrangle))
		throw exception("Четырёхугольник выходит за границу экрана!");
	InvalidateRect(this->hwnd, 0, TRUE);
	UpdateWindow(this->hwnd);
	if (externalQuadrangle->isOnTheNested(internalQuadrangle))
		throw exception("Внутренний четырёхугольник выходит за границы внешнего!");
	HPEN SelectPen(this->hdc, this->hPen);
	HBRUSH SelectBrush(this->hdc, GetStockBrush(NULL_BRUSH));
	POINT *points1 = externalQuadrangle->getQuadrangle();
	POINT *points2 = internalQuadrangle->getQuadrangle();
	Polygon(this->hdc, points1, 4);
	Polygon(this->hdc, points2, 4);
	HBRUSH SelectBrush(this->hdc, this->hBrush);
	FloodFill(this->hdc, points1[0].x + 10, points1[0].y + 10, RGB(this->colorPen.R, this->colorPen.G, this->colorPen.B));
}

void View::enterCharacteristicsFromFiles(string fd)
{
	ifstream in(fd, ios::in);
	if (in.is_open())
	{
		in >> this->width;
		if (isWidth(&this->width))
			throw exception("Такую толщину линий задать нельзя!\nМаксимальная толщина - 9 пикселей.");
		in >> this->colorPen.R;
		in >> this->colorPen.G;
		in >> this->colorPen.B;
		this->colorPen = colorPen;
		if (isRGB(colorPen))
			throw exception("Такого цвета не существует!");
		in >> this->colorBrush.R;
		in >> this->colorBrush.G;
		in >> this->colorBrush.B;
		if (isRGB(colorBrush))
			throw exception("Такого цвета не существует!");
		this->hPen = CreatePen(PS_SOLID, 5, RGB(this->colorPen.R, this->colorPen.G, this->colorPen.B));
		this->hBrush = CreateSolidBrush(RGB(this->colorBrush.R, this->colorBrush.G, this->colorBrush.B));
		in.close();
	}
	else
		throw exception("В этом файле нет нужных данных");
}

void View::saveCharacteristicsToFile(string fd)
{
	ofstream out(fd, ios::out);
	out << this->width;
	out << " ";
	out << this->colorPen.R;
	out << " ";
	out << this->colorPen.G;
	out << " ";
	out << this->colorPen.B;
	out << " ";
	out << this->colorBrush.R;
	out << " ";
	out << this->colorBrush.G;
	out << " ";
	out << this->colorBrush.B;
	out.close();
}