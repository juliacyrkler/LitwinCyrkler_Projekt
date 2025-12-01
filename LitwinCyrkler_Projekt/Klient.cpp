#include <iostream>
#include <string>
#include "Klient.h"

using namespace std;

Klient::Klient(int id_, std::string imie_, std::string nazwisko_, int punkty_, double srodki_, sql::Connection* con) : Uzytkownik(id_, imie_, nazwisko_, con) {
	this->punktyLojalnosciowe = punkty_;
	this->srodkiNaKoncie = srodki_;
}

bool Klient::interfejsUzytkownika() {
	cout << endl << "Witaj, " << this->zwrocImie() << "! Jesteœ zalogowany jako klient.";

	bool wyloguj = false;
	while (!wyloguj) {
		cout << endl << "Co chcesz zrobiæ?" << endl;
		cout << "--> 1 - Wyœwietl produkty" << endl;
		cout << "--> 2 - PrzejdŸ do koszyka" << endl;
		cout << "--> 3 - Poka¿ œrodki na koncie" << endl;
		cout << "--> 4 - Wp³aæ œrodki na konto" << endl;
		cout << "--> 5 - Wyloguj siê" << endl;
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
			this->wplacSrodki();
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

void Klient::wplacSrodki() {
	double kwota;
	cout << "Podaj kwotê do wp³acenia: ";
	cin >> kwota;
	if (cin.fail() || kwota <= 0) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Nieprawid³owa kwota." << endl;
		return;
	}
	this->srodkiNaKoncie += kwota;
	//zmiana stanu konta w bazie danych
	cout << "Wp³acono " << kwota << " z³ na konto. Twój stan œrodków wynosi teraz " << this->srodkiNaKoncie << " z³." << endl;
}