#include <iostream>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <string>
#include "Klient.h"
#include "Produkt.h"

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
	sql::PreparedStatement* pstmt;
	sql::ResultSet* res;

	int wybor;	cout << "-----> 1. Wszystkie produkty" << endl << "-----> 2. Produkty tylko z danej kategorii" << endl;	cin >> wybor;
	pstmt = polaczenie->prepareStatement("SELECT* FROM asortyment order by kategoria DESC");
	res = pstmt->executeQuery();
	int lp = 1;

	switch (wybor) {
	case 1:
		while(res->next()) {
			string nazwaProduktu = res->getString("nazwa");
			double cena = res->getDouble("cena");

			cout << lp << ". " << nazwaProduktu << " -- " << cena << "z³" << endl;
			lp++;

		}break;

	case 2:cout << "Lmao nie." << endl; break; //to be changed
	default: cout << "Niepoprawny wybór!" << endl;
	}
	delete pstmt; delete res;
}

void Klient::pokazKoszyk() {
		if (koszyk.empty()) {cout << "Koszyk jest pusty." << endl;return;}

		cout << "Zawartoœæ koszyka:" << endl << "------------------" << endl;
		int lp = 1;
		float suma = 0;

		for (Produkt& p : koszyk) {
			cout << lp++ << ". "<< p.zwrocNazwe()<< " | Cena: " << p.zwrocCene() << " z³"<< endl;
			suma += p.zwrocCene();
		}
		cout << "------------------" << endl << "Suma: " << suma << " z³" << endl;
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

	try {
		sql::PreparedStatement* pstmt;

		pstmt = polaczenie->prepareStatement("UPDATE klienci SET srodki = srodki + ? WHERE klient_id = ?");

		pstmt->setDouble(1, kwota);
		pstmt->setInt(2, this->id);

		int zmodyfikowane = pstmt->executeUpdate();

		if (zmodyfikowane > 0){
			this->srodkiNaKoncie += kwota;
			cout << "Wp³acono " << kwota << " z³. Stan konta: "<< this->srodkiNaKoncie << " z³." << endl;
		}
		else{cout << "B³¹d do³adowania œrodków" << endl;}

		delete pstmt;
	}
	catch (sql::SQLException& e) {cout << "B³¹d do³adowania œrodków: " << e.what() << endl;}
}