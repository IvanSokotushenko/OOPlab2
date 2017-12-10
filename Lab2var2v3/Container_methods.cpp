#include "Container.h"
using namespace std;

Container::Container()
{
	head = NULL;
	tail = NULL;
	count = 0;
}

Container::~Container()
{
	while (head)
	{
		tail = head->next;
		delete head;
		head = tail;
	}
}

void Container::addFigure(Quadrangle &quadrangle)
{
	link *temp = new link;
	temp->next = NULL;
	temp->quadrangle = &quadrangle;
	if (head != NULL)
	{
		temp->prev = tail;
		tail->next = temp;
		tail = temp;
	}
	else
	{
		temp->prev = NULL;
		head = tail = temp;

	}
	count++;
}

void Container::printInfo()
{
	link *temp = head;
	int id = 1;
	cout << "№" << "|Категория" << "|\t        Координаты точек\t      |";
	cout << "\n";
	while (temp != NULL)
	{
		cout << id;
		cout << "   " << temp->quadrangle->notTrivialSign << " ";
		cout << "\t(" << temp->quadrangle->points[0].x << ";" << temp->quadrangle->points[0].y << ")";
		cout << "(" << temp->quadrangle->points[1].x << ";" << temp->quadrangle->points[1].y << ")";
		cout << "(" << temp->quadrangle->points[2].x << ";" << temp->quadrangle->points[2].y << ")";
		cout << "(" << temp->quadrangle->points[3].x << ";" << temp->quadrangle->points[3].y << ")";
		cout << "\n";
		id++;
		temp = temp->next;
	}
	cout << "\n";
}

void Container::printInfoBack()
{
	link *temp = tail;
	int id = count;
	cout << "№" << "|Категория" << "|\t        Координаты точек\t      |";
	cout << "\n";
	while (temp != NULL)
	{
		cout << id;
		cout << "   " << temp->quadrangle->notTrivialSign << " ";
		cout << "\t(" << temp->quadrangle->points[0].x << ";" << temp->quadrangle->points[0].y << ")";
		cout << "(" << temp->quadrangle->points[1].x << ";" << temp->quadrangle->points[1].y << ")";
		cout << "(" << temp->quadrangle->points[2].x << ";" << temp->quadrangle->points[2].y << ")";
		cout << "(" << temp->quadrangle->points[3].x << ";" << temp->quadrangle->points[3].y << ")";
		cout << "\n";
		id--;
		temp = temp->prev;
	}
	cout << "\n";
}

void Container::saveInFile(string fd)
{
	ofstream out(fd, ios::out);
	link *temp = head;
	int id = 1;
	out << "№" << "|Категория" << "|\t        Координаты точек\t      |";
	out << "\n";
	while (temp != NULL)
	{
		out << id;
		out << "   " << temp->quadrangle->notTrivialSign << " ";
		out << "\t(" << temp->quadrangle->points[0].x << ";" << temp->quadrangle->points[0].y << ")";
		out << "(" << temp->quadrangle->points[1].x << ";" << temp->quadrangle->points[1].y << ")";
		out << "(" << temp->quadrangle->points[2].x << ";" << temp->quadrangle->points[2].y << ")";
		out << "(" << temp->quadrangle->points[3].x << ";" << temp->quadrangle->points[3].y << ")";
		out << "\n";
		id++;
		temp = temp->next;
	}
	out << "\n";
	out.close();
}

void Container::removeFigure(int number)
{
	if (number<1 || number > count)
		throw exception("Такого номера не существует.\n");
	link *temp = head;
	if (number == 1 && head->next)
	{
		head = head->next;
		head->prev = NULL;
		delete temp;
		count--;
		return;
	}
	else if (count == 1 && head == tail)
	{
		head->next = NULL;
		head = NULL;
		delete head;
		count = 0;
		return;
	}

	int pos = 0;
	while (temp != NULL)
	{
		temp = temp->next;
		pos++;
	}

	if (number == pos)
	{
		link *temp = tail;
		tail = tail->prev;
		tail->next = NULL;
		delete temp;
		count--;
		return;
	}
	link *tempNew = head;
	link *tempDel;
	for (int i = 0; i < number - 1; i++)
	{
		tempNew = tempNew->next;
	}
	tempDel = tempNew;
	tempDel->prev->next = tempNew->next;
	tempDel->next->prev = tempNew->prev;
	delete tempNew;
	count--;
}

void Container::searchFigureOnNumber(int number)
{
	if (number<1 || number > count)
		throw exception("Такого номера не существует.\n");
	link *temp = head;
	int id = 1;
	while (temp != NULL)
	{
		if (id == number)
		{
			cout << "№" << "|Категория" << "|\t        Координаты точек\t      |";
			cout << "\n";
			cout << id;
			cout << "   " << temp->quadrangle->notTrivialSign << " ";
			cout << "\t(" << temp->quadrangle->points[0].x << ";" << temp->quadrangle->points[0].y << ")";
			cout << "(" << temp->quadrangle->points[1].x << ";" << temp->quadrangle->points[1].y << ")";
			cout << "(" << temp->quadrangle->points[2].x << ";" << temp->quadrangle->points[2].y << ")";
			cout << "(" << temp->quadrangle->points[3].x << ";" << temp->quadrangle->points[3].y << ")";
			cout << "\n";
			cout << "\n";
			return;
		}
		id++;
		temp = temp->next;
	}
}

void Container::searchFigureOnSign(string sign)
{
	if (sign != "big  " && sign != "small")
		throw exception("Такой категории не существует.\n");
	link *temp = head;
	int id = 1;
	cout << "№" << "|Категория" << "|\t        Координаты точек\t      |";
	cout << "\n";
	while (temp != NULL)
	{
		if (sign == temp->quadrangle->notTrivialSign)
		{
			cout << id;
			cout << "   " << temp->quadrangle->notTrivialSign << " ";
			cout << "\t(" << temp->quadrangle->points[0].x << ";" << temp->quadrangle->points[0].y << ")";
			cout << "(" << temp->quadrangle->points[1].x << ";" << temp->quadrangle->points[1].y << ")";
			cout << "(" << temp->quadrangle->points[2].x << ";" << temp->quadrangle->points[2].y << ")";
			cout << "(" << temp->quadrangle->points[3].x << ";" << temp->quadrangle->points[3].y << ")";
			cout << "\n";
		}
		id++;
		temp = temp->next;
	}
	cout << "\n";
}