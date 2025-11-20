#include <iostream>
#include <string>
#include "Klient.h"

using namespace std;

Klient::Klient(int id_, std::string imie_, std::string nazwisko_) : Uzytkownik(id_, imie_, nazwisko_) {}

void Klient::interfejsUzytkownika() {
	//interfejs uzytkownika...
	cout << "Lorem ipsum" << endl;
}