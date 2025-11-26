#ifndef PRACOWNIK_H
#define PRACOWNIK_H

#include <string>
#include "Uzytkownik.h"

using namespace std;

class Pracownik : public Uzytkownik {
private:
	double stawkaGodzinowa;
	int liczbaGodzin;
public:
	Pracownik(int id_, std::string imie_, std::string nazwisko_, double stawka_, int liczba_);
	double obliczWynagrodzenie();
	double zwrocStawkeGodzinowa();
	void ustawStawkeGodzinowa(double stawka);
};

#endif