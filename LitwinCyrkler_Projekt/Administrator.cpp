#include <iostream>
#include <string>
#include "Administrator.h"

using namespace std;

Administrator::Administrator(int id_, std::string imie_, std::string nazwisko_, double stawka_, int liczba_) : Pracownik(id_, imie_, nazwisko_, stawka_, liczba_) {}

void Administrator::interfejsUzytkownika() {
	//interfejs administratora
	cout << "Witaj, " << this->zwrocImie() << "! Jesteœ zalogowany jako administrator." << endl;
}

void Administrator::dodajUzytkownika() {
	//dodawanie uzytkownika
}

void Administrator::usunUzytkownika() {
	//usuwanie uzytkownika
}