#include <iostream>
#include <string>
#include "Klient.h"

using namespace std;

Klient::Klient(int id_, std::string imie_, std::string nazwisko_, int punkty_, double srodki_) : Uzytkownik(id_, imie_, nazwisko_) {
	this->punktyLojalnosciowe = punkty_;
	this->srodkiNaKoncie = srodki_;
}

bool Klient::interfejsUzytkownika() {
	cout << endl << "Witaj, " << this->zwrocImie() << "! Jesteœ zalogowany jako klient." << endl;

	bool wyloguj = false;
	while (!wyloguj) {
		cout << "Co chcesz zrobiæ?" << endl;
		cout << "--> 1 - Wyœwietl produkty" << endl;
		cout << "--> 2 - PrzejdŸ do koszyka" << endl;
		cout << "--> 3 - Poka¿ œrodki na koncie" << endl;
		cout << "--> 4 - Wyloguj siê" << endl;
		int wybor;
		cin >> wybor;

		switch (wybor) {
		case 1:
			this->wyswietlProdukty();
			break;
		case 2:
			this->pokazKoszyk();
			break;
		case 3:
			this->pokazStanKonta();
			break;
		case 4:
			wyloguj = true;
			break;
		default:
			break;
		}
	}
	return true;
}

void Klient::pokazStanKonta() {
	cout << "Stan konta: " << this->srodkiNaKoncie << " z³" << endl;
	cout << "Punkty lojalnoœciowe: " << this->punktyLojalnosciowe << endl;
}

void Klient::wyswietlProdukty() {
	//to be changed
}

void Klient::pokazKoszyk() {
	//to be changed
}