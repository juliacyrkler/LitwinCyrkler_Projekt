#include <iostream>
#include <string>
#include "Uzytkownik.h"

using namespace std;

Uzytkownik::Uzytkownik(int id_, std::string imie_, std::string nazwisko_) {
	this->id = id_;
	this->imie = imie_;
	this->nazwisko = nazwisko_;
	cout << "Utworzono uzytkownika" << endl;
}
