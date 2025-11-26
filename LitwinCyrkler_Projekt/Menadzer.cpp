#include <iostream>
#include <string>
#include "Menadzer.h"

using namespace std;

Menadzer::Menadzer(int id_, std::string imie_, std::string nazwisko_, double stawka_, int liczba_) : Pracownik(id_, imie_, nazwisko_, stawka_, liczba_) {}

void Menadzer::interfejsUzytkownika() {
	//interfejs menad¿era
	cout << "Witaj, " << this->zwrocImie() << "! Jesteœ zalogowany jako menad¿er." << endl;
}