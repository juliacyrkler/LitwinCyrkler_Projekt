#include <iostream>
#include <string>
#include "Administrator.h"

using namespace std;

Administrator::Administrator(int id_, std::string imie_, std::string nazwisko_) : Uzytkownik(id_, imie_, nazwisko_) {}

void Administrator::interfejsUzytkownika() {
	//interfejs administratora
}

void Administrator::dodajUzytkownika() {
	//dodawanie uzytkownika
}

void Administrator::usunUzytkownika() {
	//usuwanie uzytkownika
}