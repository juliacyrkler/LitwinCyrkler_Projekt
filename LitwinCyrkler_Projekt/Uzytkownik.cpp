#include <iostream>
#include <string>
#include "Uzytkownik.h"
#include <stdlib.h>

using namespace std;

Uzytkownik::Uzytkownik(int id_, string imie_, string nazwisko_, sql::Connection* con) : polaczenie(con) {
	this->id = id_;
	this->imie = imie_;
	this->nazwisko = nazwisko_;
}

bool Uzytkownik::interfejsUzytkownika() {
	return true;
}

string Uzytkownik::zwrocImie() {
	return this->imie;
}
void Uzytkownik::clearConsole() {
	system("cls");
}
Uzytkownik::~Uzytkownik() {
	delete polaczenie;
}