#include "Quadrangle.h" 
using namespace std;

bool Quadrangle::isBulge(node leftTop, node rightTop, node rightBottom, node leftBottom)
{
	return (((rightTop.x - leftTop.x)*(rightBottom.y - leftTop.y) - (rightTop.y - leftTop.y)*(rightBottom.x - leftTop.x))*
		((rightTop.x - leftTop.x)*(leftBottom.y - leftTop.y) - (rightTop.y - leftTop.y)*(leftBottom.x - leftTop.x))<0 ||
		((leftBottom.x - rightBottom.x)*(rightTop.y - rightBottom.y) - (leftBottom.y - rightBottom.y)*(rightTop.x - rightBottom.x))*
		((leftBottom.x - rightBottom.x)*(leftTop.y - rightBottom.y) - (leftBottom.y - rightBottom.y)*(leftTop.x - rightBottom.x))<0);
}

bool Quadrangle::isOnTheNested(Quadrangle *internalQuadrangle)
{
	POINT *points1 = this->getQuadrangle();
	POINT *points2 = internalQuadrangle->getQuadrangle();
	return ((points2[0].x < points1[0].x) || (points2[0].y < points1[0].y) ||
		(points2[1].x > points1[1].x) || (points2[1].y < points1[1].y) ||
		(points2[2].x > points1[2].x) || (points2[2].y > points1[2].y) ||
		(points2[3].x < points1[3].x) || (points2[3].y > points1[3].y));
}

POINT *Quadrangle::setQuadrangle(node leftTop, node rightTop, node rightBottom, node leftBottom)
{
	if (isBulge(leftTop, rightTop, rightBottom, leftBottom))
		throw exception("×åòûð¸õóãîëüíèê íå ÿâëÿåòñÿ âûïóêëûì!");
	points[0] = { leftTop.x, leftTop.y };
	points[1] = { rightTop.x, rightTop.y };
	points[2] = { rightBottom.x, rightBottom.y };
	points[3] = { leftBottom.x, leftBottom.y };
}

POINT* Quadrangle::getQuadrangle()
{
	return this->points;
}

Quadrangle::Quadrangle()
{
	points = new POINT[4];
	points[0] = { 300, 100 };
	points[1] = { 400, 100 };
	points[2] = { 300, 200 };
	points[3] = { 500, 300 };
}

Quadrangle::~Quadrangle()
{
	delete[] getQuadrangle();
}


Quadrangle::Quadrangle(node leftTop, node rightTop, node rightBottom, node leftBottom)
{
	if (isBulge(leftTop, rightTop, rightBottom, leftBottom))
		throw exception("×åòûð¸õóãîëüíèê íå ÿâëÿåòñÿ âûïóêëûì!");
	points = new POINT[4];
	points[0] = { leftTop.x, leftTop.y };
	points[1] = { rightTop.x, rightTop.y };
	points[2] = { rightBottom.x, rightBottom.y };
	points[3] = { leftBottom.x, leftBottom.y };
	int S = ((leftTop.x - rightTop.x)*(leftTop.y + rightTop.y) + (rightTop.x - rightBottom.x)*(rightTop.y + rightBottom.y) +
		(rightBottom.x - leftBottom.x)*(rightBottom.y + leftBottom.y) + (leftBottom.x - leftTop.x)*(leftBottom.y + leftTop.y));
	if (S >= 5000)
		notTrivialSign = "big  ";
	else
	{
		notTrivialSign = "small";
	}
}

void Quadrangle::enterCoordinatesFromFiles(string fd)
{
	ifstream in(fd, ios::in);
	if (in.is_open())
	{
		POINT *points = this->getQuadrangle();
		in >> points[0].x;
		in >> points[0].y;
		in >> points[1].x;
		in >> points[1].y;
		in >> points[2].x;
		in >> points[2].y;
		in >> points[3].x;
		in >> points[3].y;
		if (isBulge(leftTop, rightTop, rightBottom, leftBottom))
			throw exception("×åòûð¸õóãîëüíèê íå ÿâëÿåòñÿ âûïóêëûì!");
		in.close();
	}
	else
		throw exception("Â ýòîì ôàéëå íåò íóæíûõ äàííûõ!");
}

void Quadrangle::saveCoordinatesToFile(string fd)
{
	ofstream out(fd, ios::out);
	out << this->points[0].x;
	out << " ";
	out << this->points[0].y;
	out << " ";
	out << this->points[1].x;
	out << " ";
	out << this->points[1].y;
	out << " ";
	out << this->points[2].x;
	out << " ";
	out << this->points[2].y;
	out << " ";
	out << this->points[3].x;
	out << " ";
	out << this->points[3].y;
	out << " ";
	out.close();
}

void Quadrangle::changePosition(node *change)
{
	this->change = *change;
	setQuadrangle({ this->points[0].x + this->change.x, points[0].y + this->change.y },
	{ points[1].x + this->change.x, points[1].y + this->change.y },
	{ points[2].x + this->change.x, points[2].y + this->change.y },
	{ points[3].x + this->change.x, points[3].y + this->change.y });
}
