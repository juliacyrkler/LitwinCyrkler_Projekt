#include <iostream>
#include <string>
#include "Kasjer.h"

using namespace std;

Kasjer::Kasjer(int id_, std::string imie_, std::string nazwisko_, double stawka_, int liczba_, sql::Connection* con) : Pracownik(id_, imie_, nazwisko_, stawka_, liczba_, con) {}

bool Kasjer::interfejsUzytkownika() {
	cout << endl << "Witaj, " << this->zwrocImie() << "! Jesteœ zalogowany jako kasjer.";

	bool wyloguj = false;
	while (!wyloguj) {
		cout << endl << "Co chcesz zrobiæ?" << endl;
		cout << "--> 1 - Obs³u¿ klienta" << endl;
		cout << "--> 2 - Aktualizuj asortyment" << endl;
		cout << "--> 3 - Wyloguj siê" << endl;
		//???
		int wybor;
		cin >> wybor;

		switch (wybor) {
		case 1:

			break;
		case 2:

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