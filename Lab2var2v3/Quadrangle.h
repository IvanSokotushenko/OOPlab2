#pragma once
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct node
{
	int x, y;
};

class Quadrangle
{
	POINT *points;
	node leftTop, rightTop, rightBottom, leftBottom, change;
	string notTrivialSign;
	bool isBulge(node leftTop, node rightTop, node rightBottom, node leftBottom);
	bool isOnTheNested(Quadrangle *internalQuadrangle);
	friend class View;
	friend class Container;
public:
	Quadrangle();
	~Quadrangle();
	Quadrangle(node leftTop, node rightnTop, node rightBottom, node leftBottom);
	POINT *setQuadrangle(node leftTop, node rightTop, node rightBottom, node leftBottom);
	POINT *getQuadrangle();
	void enterCoordinatesFromFiles(string fd);
	void saveCoordinatesToFile(string fd);
	void changePosition(node *change);
};
