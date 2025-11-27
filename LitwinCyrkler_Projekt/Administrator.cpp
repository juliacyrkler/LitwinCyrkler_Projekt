#include <iostream>
#include <string>
#include "Administrator.h"

using namespace std;

Administrator::Administrator(int id_, std::string imie_, std::string nazwisko_, double stawka_, int liczba_) : Pracownik(id_, imie_, nazwisko_, stawka_, liczba_) {}

bool Administrator::interfejsUzytkownika() {
	cout << endl << "Witaj, " << this->zwrocImie() << "! Jesteœ zalogowany jako administrator." << endl;

	bool wyloguj = false;
	while (!wyloguj) {
		cout << "Co chcesz zrobiæ?" << endl;
		cout << "--> 1 - Dodaj nowego u¿ytkownika" << endl;
		cout << "--> 2 - Usuñ u¿ytkownika" << endl;
		//mo¿e edycja danych u¿ytkownika?
		cout << "--> 3 - Wyloguj siê" << endl;
		int wybor;
		cin >> wybor;

		switch (wybor) {
		case 1:
			this->dodajUzytkownika();
			break;
		case 2:
			this->usunUzytkownika();
			break;
		case 3:
			wyloguj = true;
			break;
		default:
			break;
		}
	}
	return true;
}

void Administrator::dodajUzytkownika() {
	//dodawanie uzytkownika
}

void Administrator::usunUzytkownika() {
	//usuwanie uzytkownika
}