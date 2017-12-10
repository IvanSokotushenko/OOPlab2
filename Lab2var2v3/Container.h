#pragma once
#include "Quadrangle.h"
#include "View.h"
#include <fstream>
using namespace std;

struct link
{
	Quadrangle *quadrangle;
	link *next, *prev;
};

class Container
{
	int count;
	link *head, *tail;
public:
	Container();
	~Container();
	void addFigure(Quadrangle &quadrangle);
	void removeFigure(int number);
	void searchFigureOnNumber(int number);
	void searchFigureOnSign(string sign);
	void printInfo();
	void printInfoBack();
	void saveInFile(string fd);
};