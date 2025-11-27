#include <iostream>
#include <string>
#include "Menadzer.h"

using namespace std;

Menadzer::Menadzer(int id_, std::string imie_, std::string nazwisko_, double stawka_, int liczba_) : Pracownik(id_, imie_, nazwisko_, stawka_, liczba_) {}

bool Menadzer::interfejsUzytkownika() {
	cout << endl << "Witaj, " << this->zwrocImie() << "! Jesteœ zalogowany jako menad¿er.";

	bool wyloguj = false;
	while (!wyloguj) {
		cout << endl << "Co chcesz zrobiæ?" << endl;
		cout << "--> 1 - Edytuj asortyment" << endl;
		cout << "--> 2 - Wyœwietl pracowników" << endl;
		cout << "--> 3 - Wyœwietl klientów" << endl;
		cout << "--> 4 - Generuj raport sprzeda¿y" << endl;
		cout << "--> 5 - Wyloguj siê" << endl;
		int wybor;
		cin >> wybor;

		switch (wybor) {
		case 1:
			this->edytujAsortyment();
			break;
		case 2:
			this->wyswietlPracownikow();
			break;
		case 3:
			this->wyswietlKlientow();
			break;
		case 4:
			this->generujRaportSprzedazy();
			break;
		case 5:
			wyloguj = true;
			break;
		default:
			break;
		}
	}
	return true;
}

void Menadzer::wyswietlPracownikow() {
	//wyœwietlanie danych z bazy danych
}

void Menadzer::wyswietlKlientow() {
	//wyœwietlanie danych z bazy danych
}

void Menadzer::edytujAsortyment() {
	//wyœwietlanie asortymentu, wybór produktu do edycji, wybór edytowanej cechy, zapisanie zmian w bazie danych
}

void Menadzer::generujRaportSprzedazy() {
	//generowanie raportu sprzeda¿y z ostatniego miesi¹ca na podstawie tabeli z transakcjami???
}