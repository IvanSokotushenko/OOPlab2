#include "Quadrangle.h"
#include "View.h"
#include "Container.h"
using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");
	try {
		HWND hwnd = GetConsoleWindow();
		HDC hdc = GetDC(hwnd);

		Quadrangle first({ 300, 100 }, { 400, 100 }, { 500, 300 }, { 300, 220 });
		Quadrangle second({ 350, 150 }, { 380, 150 }, { 400, 220 }, { 350, 200 });
		Quadrangle third({ 310, 100 }, { 410, 100 }, { 510, 300 }, { 310, 220 });
		Quadrangle fourth({ 320, 100 }, { 420, 100 }, { 520, 300 }, { 320, 220 });
		Quadrangle fifth({ 300, 100 }, { 400, 100 }, { 500, 300 }, { 300, 220 });
		Quadrangle sixth({ 360, 150 }, { 390, 150 }, { 410, 220 }, { 360, 200 });
		Container container;

		container.addFigure(first);
		container.addFigure(second);
		container.addFigure(third);
		container.addFigure(fourth);
		container.addFigure(fifth);
		container.addFigure(sixth);

		container.printInfo();
		container.saveInFile("Container_save.txt");

		container.removeFigure(4);
		container.printInfo();
		container.printInfoBack();

		container.searchFigureOnNumber(2);
		container.searchFigureOnSign("big  ");
		container.searchFigureOnSign("small");

		/*
		HWND hwnd = GetConsoleWindow();
		HDC hdc = GetDC(hwnd);

		color colorPen = { 0, 0, 0 };
		color colorBrush = { 255, 0, 0 };
		short width = 5;

		// Создаём три четырёхугольника
		Quadrangle first({ 300, 100 }, { 400, 100 }, { 500, 300 }, { 300, 220 });
		Quadrangle second({ 350, 150 }, { 380, 150 }, { 400, 220 }, { 350, 200 });
		Quadrangle third({ 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 });
		third.enterCoordinatesFromFiles("Quadrangle_CoordinatesFromFile.txt");
		// Вызываем конструктор с параметрами
		View quadrangle1(hwnd, hdc, &width, &colorPen, &colorBrush);
		// Выводим изображения
		quadrangle1.viewUnpaintQudrangle(&first);
		getchar();
		quadrangle1.viewPaintQudrangle(&second);
		getchar();
		quadrangle1.viewTwoNestedPaintQuadrangle(&first, &second);
		getchar();
		// Выводим изображение двух вложенных четырёхугольников с новыми параметрами, полученными из файла
		quadrangle1.enterCharacteristicsFromFiles("Quadrangle_CharacteristicsFromFiles.txt");
		quadrangle1.viewTwoNestedPaintQuadrangle(&first, &second);
		getchar();
		// Демонстрация работы функции сдвига фигуры
		quadrangle1.viewPaintQudrangle(&third);
		getchar();
		node change = { -100, 0 };
		third.changePosition(&change);
		quadrangle1.viewPaintQudrangle(&third);
		getchar();
		third.saveCoordinatesToFile("Quadrangle_CoordinatesInFile.txt");
		quadrangle1.saveCharacteristicsToFile("Quadrangle_CharacteristicsInFiles.txt");
		*/
	}
	catch (exception exeption)
	{
		cout << exeption.what() << endl;
	}
	return 0;
}