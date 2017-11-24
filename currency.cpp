// curency.cpp: определяет точку входа для консольного приложения.
//
/*Определить абстрактный класс Сurrency для работы с денежными суммами.
Определить в нем методы перевода в рубли и вывода на экран.
На его основе реализовать классы Dollar, Euro и Pound (фунт стерлингов)
с возможностью пересчета в центы и пенсы соответственно и указанием текущего курса.
Создать класс Purse (кошелек), содержащий массив объектов этих классов в динамической памяти.
Предусмотреть возможность случайного наполнения кошелька купюрами различного типа и подсчета общей суммы кошелька при изменении курса валют.
В программе продемонстрировать функциональность разработанных классов.
Реализуйте метод print печатающий историю пополнения кошелька.*/
#include "stdafx.h"
#include <iostream>
#include <iomanip>//setprecision
#include <vector>
#include <initializer_list>
#include <numeric>//accumulate
#include <conio.h>
#include <string>
using namespace std;

class Currency {
public:
	virtual double convert() = 0;
	virtual void print()const = 0;
	virtual ~Currency() {}
};

class Dollar : public Currency {
private:
	double amount;
public:
	static double valuta;//в 1 $ руб, kyрc
	Dollar() : amount(0) {}
	Dollar(double a)// : amount(a) {}//amount=a
	{
		amount = a;
	}
	~Dollar() {}
	double convert() {
		return amount*valuta;
	}
	void print()const {
		cout << fixed << setprecision(2) << "+ " << amount << " USD=" << amount*valuta << " RUB" << endl;
	}
	int cent(Dollar& y) {
		return (y.amount - (int)y.amount) * 100;
	}
	Dollar& operator =(const Dollar& y) {
		amount = y.amount;
	}
	friend ostream& operator <<(ostream& out, const Dollar& y) {
		out << fixed << setprecision(2) << y.amount << " USD" << endl;// << " cent: " << cent(y) << endl;
		return out;
	}
};
double Dollar::valuta = 59.63;

class Euro : public Currency {
private:
	double amount;
public:
	static double valuta;//в 1 $ руб, kyрc
	Euro() : amount(0) {}
	Euro(double a) :amount(a) {}
	~Euro() {}
	double convert() {
		return amount*valuta;
	}
	void print()const {
		cout << fixed << setprecision(2) << "+ " << amount << " EUR=" << amount*valuta << " RUB" << endl;
	}
	Euro& operator =(const Euro& y) {
		amount = y.amount;
	}
	friend ostream& operator <<(ostream& out, const Euro& y) {
		out << fixed << setprecision(2) << y.amount << " EUR" << endl;
		return out;
	}
};
double Euro::valuta = 70.42;

class Pound : public Currency {
private:
	double amount;
public:
	static double valuta;//в 1 $ руб, kyрc
	Pound() : amount(0) {}
	Pound(double b) :amount(b) {}
	~Pound() {}
	double convert() {
		return amount*valuta;
	}
	void print()const {
		cout << fixed << setprecision(2) << "+ " << amount << " GBP=" << amount*valuta << " RUB" << endl;
	}
	Pound& operator =(const Pound& y) {
		amount = y.amount;
	}
	friend ostream& operator <<(ostream& out, const Pound& y) {
		out << fixed << setprecision(2) << y.amount << " GBP" << endl;
		return out;
	}
};
double  Pound::valuta = 78.74;

class Purse {
private:
	vector <Currency*> p;//вектор для хранения объектов разных классов 
public:
	Purse() = default;
	Purse(Currency *c) { p.push_back(c); }//добовление в к0нёц
	Purse(const Purse &p) = default;
	Purse& operator =(const Purse &p) = default;
	Purse(initializer_list<Currency*> &&r) :p(move(r)) {}//перемещение в p
	~Purse() {}
	void add(Currency *c) {//добовление в вектор
		p.push_back(c);
	}
	void showM()const {//вывод истории пополнения
		for (vector<Currency*>::const_iterator iter = p.begin(); iter != p.end(); iter++) {
			(*iter)->print();
			//cout << "ddd";
		}

	}
	double amountOfRub() {
		return accumulate(p.begin(), p.end(), 0.0, [](double x, Currency *c) {
			return x + c->convert(); });//суммирование всех элементов кошелька, в рублях
	}
	void show() {
		cout << fixed << setprecision(2) << "В кошельке " << amountOfRub() << " RUB" << endl;
	}
};

Purse pp{};

void menu() {
	double val();//првёрка валюты
	double valS();//пр0вёрка суммы
	system("cls");//0чистка экраана
	char option;//выб0р
	cout << "1) Пополнить кошелек" << endl;
	cout << "2) Вывести историю пополнения" << endl;
	cout << "3) Изменить курс валют" << endl;
	cout << "Сейчас в кошельке : "; pp.show();
	cin >> option;
	cout << "_________________________________________________________" << endl;
	int opt = option - 48;//ascii
	if (opt < 1 || opt > 3 || !isdigit(option)) menu();
	switch (opt)
	{
	case 1:
		goto addMoney;
		break;
	case 2:
		pp.showM();
		_getch();
		menu();
		break;
	case 3:
		goto change;
		break;
	}
addMoney: {
	cout << "1) USD" << endl;
	cout << "2) EUR" << endl;
	cout << "3) GBP" << endl;
	cout << "4) Назад" << endl;
	cin >> option;
	opt = option - 48;
	cout << "_________________________________________________________" << endl;
	if (opt < 1 || opt > 4 || !isdigit(option)) menu();
	switch (opt)
	{
	case 1:
		goto doll;
		break;
	case 2:
		goto euro;
		break;
	case 3:
		goto pound;
		break;
	case 4:
		menu();
		break;
	}
doll: {
	Currency*d = new Dollar(valS());
	pp.add(d);
	d->print();
	_getch();
	menu();
	}
  euro: {
	  Currency* e = new Euro(valS());
	  pp.add(e);
	  e->print();
	  _getch();
	  menu();
}
	pound: {
		Currency* p = new Pound(valS());
		pp.add(p);
		p->print();
		_getch();
		menu();
  }
	};
	  change: {
		  cout << "1) USD" << endl;
		  cout << "2) EUR" << endl;
		  cout << "3) GBP" << endl;
		  cout << "4) Назад" << endl;
		  cin >> option;
		  cout << "_________________________________________________________" << endl;
		  opt = option - 48;
		  if (opt < 1 || opt > 4 || !isdigit(option)) menu();
		  switch (opt)
		  {
		  case 1:
			  Dollar::valuta = val();
			  menu();
			  break;
		  case 2:
			  Euro::valuta = val();
			  menu();
			  break;
		  case 3:
			  Pound::valuta = val();
			  menu();
			  break;
		  case 4:
			  menu();
			  break;
		  }
}
}
double val() {
	double v;
	cout << "Введите новый курс : "; cin >> v;
	if (v < 1 || v>100) {
		cout << "Заново" << endl;
		_getch();
		menu();
	}
	return v;
}
double valS() {
	double v;
	cout << "Введите сумму : "; cin >> v;
	if (v < 1 || v>1000000) {
		cout << "Заново" << endl;
		_getch();
		menu();
	}
	return v;
}

void main() {
	setlocale(LC_ALL, "rus");
	menu();
	_getch();
}
