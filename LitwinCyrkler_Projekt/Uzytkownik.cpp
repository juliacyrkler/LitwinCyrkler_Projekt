#include <iostream>
#include <string>
#include "Uzytkownik.h"

using namespace std;

Uzytkownik::Uzytkownik(int id_, string imie_, string nazwisko_) {
	this->id = id_;
	this->imie = imie_;
	this->nazwisko = nazwisko_;
	this->interfejsUzytkownika();
}

void Uzytkownik::interfejsUzytkownika() { }

string Uzytkownik::zwrocImie() {
	return this->imie;
}