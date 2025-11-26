#include <iostream>
#include <string>
#include "Kasjer.h"

using namespace std;

Kasjer::Kasjer(int id_, std::string imie_, std::string nazwisko_, double stawka_, int liczba_) : Pracownik(id_, imie_, nazwisko_, stawka_, liczba_) {}

void Kasjer::interfejsUzytkownika() {
	//interfejs pracownika
	cout << "Witaj, " << this->zwrocImie() << "! Jesteœ zalogowany jako kasjer." << endl;
}