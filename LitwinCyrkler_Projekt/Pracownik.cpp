#include <iostream>
#include <string>
#include "Pracownik.h"

using namespace std;

Pracownik::Pracownik(int id_, std::string imie_, std::string nazwisko_) : Uzytkownik(id_, imie_, nazwisko_) {}

void Pracownik::interfejsUzytkownika() {
	//interfejs pracownika
}