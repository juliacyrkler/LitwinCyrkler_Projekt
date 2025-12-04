#include <iostream>
#include <string>
#include <cppconn/statement.h>
#include <stdio.h>
#include <time.h>
#include "Kasjer.h"

using namespace std;

Kasjer::Kasjer(int id_, std::string imie_, std::string nazwisko_, double stawka_, int liczba_, sql::Connection* con) : Pracownik(id_, imie_, nazwisko_, stawka_, liczba_, con) {}

bool Kasjer::interfejsUzytkownika() {
	cout << endl << "Witaj, " << this->zwrocImie() << "! Jesteś zalogowany jako kasjer.";

	bool wyloguj = false;
	while (!wyloguj) {
		cout << endl << "Co chcesz zrobić?" << endl;
		cout << "--> 1 - Obsłuż klienta" << endl;
		cout << "--> 2 - Wyświetl listę klientów" << endl;
		cout << "--> 3 - Dodaj nowego klienta" << endl;
		cout << "--> 4 - Wyloguj się" << endl;
		int wybor;
		cin >> wybor;
		if (cin.fail() || wybor < 1 || wybor > 4) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Nieprawidłowe dane." << endl;
		}
		else {
			switch (wybor) {
			case 1:
				this->obsluzKlienta();
				break;
			case 2:
				this->wyswietlKlientow();
				break;
			case 3:
				this->dodajKlienta();
				break;
			case 4:
				wyloguj = true;
				break;
			default:
				break;
			}
		}
	}
	return true;
}

void Kasjer::wyswietlKlientow() {
	sql::Statement* kwerenda;
	kwerenda = polaczenie->createStatement();
	string select;
	cout << "Lista klientów:" << endl;
	select = "select klient_id, imie, nazwisko, srodki, pkt_znizkowe, max(data_transakcji) as ostatnia_transakcja from klienci left join transakcje on klienci.klient_id = transakcje.kupujacy group by klienci.klient_id;";
	sql::ResultSet* wynik = kwerenda->executeQuery(select);
	while (wynik->next()) {
		string dataTransakcji = wynik->getString("ostatnia_transakcja") == "" ? "brak transakcji" : wynik->getString("ostatnia_transakcja");
		cout << "ID: " << wynik->getInt("klient_id") << ". " << wynik->getString("imie") << " " << wynik->getString("nazwisko") << ", stan środków: " << wynik->getDouble("srodki") << " zł, punkty lojalnościowe: " << wynik->getInt("pkt_znizkowe") << ", data ostatniej transakcji: " << dataTransakcji << endl;
	}
	delete wynik;
	delete kwerenda;
}

void Kasjer::dodajKlienta() {
	string imie, nazwisko, login, haslo, hasloPowtorzone;
	cout << "Podaj imię: ";
	cin >> imie;
	cout << "Podaj nazwisko: ";
	cin >> nazwisko;
	cout << "Podaj login: ";
	cin >> login;
	cout << "Podaj hasło: ";
	cin >> haslo;
	while (haslo != hasloPowtorzone) {
		cout << "Powtórz hasło: ";
		cin >> hasloPowtorzone;
	}
	sql::Statement* kwerenda;
	kwerenda = polaczenie->createStatement();
	string loginSelect = "select * from users where login = \"" + login + "\";";
	sql::ResultSet* wynik = kwerenda->executeQuery(loginSelect);
	if (wynik->next()) {
		cout << "Użytkownik o podanym loginie już istnieje." << endl;
		delete wynik;
		delete kwerenda;
		return;
	}
	string insert1 = "insert into users values(null, \"" + login + "\", \"" + haslo + "\");";
	kwerenda->execute(insert1);
	string select = "select max(id) as max_id from users;", id = "";
	wynik = kwerenda->executeQuery(select);
	if (wynik->next()) {
		id = wynik->getString("max_id");
	}
	string insert2 = "insert into klienci values(" + id + ", null, \"" + imie + "\", \"" + nazwisko + "\", 0, 0);";
	kwerenda->execute(insert2);
	if (kwerenda->getUpdateCount() > 0) {
		cout << "Pomyślnie dodano nowego klienta." << endl;
	} else {
		cout << "Wystąpił błąd podczas dodawania nowego klienta." << endl;
	}
	delete wynik;
	delete kwerenda;
}

void Kasjer::obsluzKlienta() {
	bool zakoncz = false;
	while (!zakoncz) {
		cout << "--> 1 - Dodaj produkt do koszyka klienta." << endl;
		cout << "--> 2 - Wyświetl koszyk klienta." << endl;
		cout << "--> 3 - Usuń produkt z koszyka klienta." << endl;
		cout << "--> 4 - Przeprowadź transakcję." << endl;
		cout << "--> 5 - Anuluj transakcję." << endl;
		int wybor;
		cin >> wybor;
		if (cin.fail() || wybor < 1 || wybor > 5) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Nieprawidłowe dane." << endl;
			return;
		}
		switch (wybor) {
		case 1:
			this->dodajDoKoszyka();
			break;
		case 2:
			this->wyswietlKoszyk();
			break;
		case 3:
			this->usunZKoszyka();
			break;
		case 4:
			if(this->przeprowadzTransakcje()) zakoncz = true;
			break;
		case 5:
			return;
		default:
			zakoncz = true;
			break;
		}
	}
}

void Kasjer::wyswietlProdukty() {
	sql::Statement* kwerenda;
	kwerenda = polaczenie->createStatement();
	string select;
	cout << "Asortyment sklepu:" << endl;
	select = "select ID, nazwa, kategoria, cena, na_magazynie from asortyment;";
	sql::ResultSet* wynik = kwerenda->executeQuery(select);
	while (wynik->next()) {
		cout << "ID: " << wynik->getInt("ID") << ". " << wynik->getString("nazwa") << " - " << wynik->getString("kategoria") << ", cena: " << wynik->getDouble("cena") << " zł, stan magazynowy: " << wynik->getInt("na_magazynie") << endl;
	}
	delete wynik;
	delete kwerenda;
}

void Kasjer::dodajDoKoszyka() {
	int idProduktu, ilosc;
	this->wyswietlProdukty();
	cout << "Podaj ID produktu, który chcesz dodać do koszyka: ";
	cin >> idProduktu;
	sql::Statement* kwerenda;
	kwerenda = polaczenie->createStatement();
	string select;
	select = "select * from asortyment where ID = " + to_string(idProduktu) + ";";
	sql::ResultSet* wynik = kwerenda->executeQuery(select);
	if (cin.fail() || !wynik->next()) {
		cout << "Nieprawidłowe ID." << endl;
		return;
	}
	cout << "Podaj ilość sztuk produktu dodawanych do koszyka: ";
	cin >> ilosc;
	if (cin.fail() || wynik->getInt("na_magazynie") < ilosc) {
		cout << "Nieprawidłowe ilość." << endl;
		return;
	}
	Produkt p(wynik->getInt("ID"), wynik->getString("nazwa"), wynik->getString("kategoria"), wynik->getDouble("cena"), ilosc);
	koszyk.push_back(p);
	delete kwerenda;
	delete wynik;
	cout << "Dodano produkt do koszyka." << endl;
}

void Kasjer::wyswietlKoszyk() {
	if (koszyk.empty()) {
		cout << "Koszuk jest pusty." << endl;
		return;
	}
	for(Produkt p : koszyk) {
		cout << p.zwrocID() << ". " << p.zwrocNazwe() << " x " << p.zwrociloscWKoszyku() << " - " << to_string(p.zwrocCene() * p.zwrociloscWKoszyku()) << " zł" << endl;
	}
}

void Kasjer::usunZKoszyka() {
	if (koszyk.empty()) {
		cout << "Koszuk jest pusty." << endl;
		return;
	}
	this->wyswietlKoszyk();
	int idProduktu;
	cout << "Podaj ID produktu, który chcesz usunąć z koszyka: ";
	cin >> idProduktu;
	int licznik = 0, znaleziono = 0;
	if (cin.fail()) {
		cout << "Nieprawidłowe dane." << endl;
		return;
	}
	for (Produkt p : koszyk) {
		if (p.zwrocID() == idProduktu) {
			znaleziono = 1;
			break;
		}
		licznik++;
	}
	if (znaleziono) {
		koszyk.erase(koszyk.begin() + licznik);
		cout << "Usunięto produkt z koszyka." << endl;
	}
	else {
		cout << "Nieprawidłowe dane." << endl;
		return;
	}
}

bool Kasjer::przeprowadzTransakcje() {
	if (koszyk.empty()) {
		cout << "Koszuk jest pusty." << endl;
		return false;
	}
	sql::Statement* kwerenda;
	kwerenda = polaczenie->createStatement();
	string select, insert, update;
	char data[80], godzina[80];
	time_t now = time(0);
	struct tm tstruct;
	tstruct = *localtime(&now);
	strftime(data, sizeof(data), "%Y-%m-%d", &tstruct);
	strftime(godzina, sizeof(godzina), "%X", &tstruct);
	insert = "insert into transakcje values (NULL, " + to_string(this->zwrocID()) + ", 0, \"" + data + "\", \"" + godzina + "\"); ";
	kwerenda->execute(insert);
	if (kwerenda->getUpdateCount() == 0) {
		cout << "Błąd przy przeprowadzaniu transakcji." << endl;
		return false;
	}
	select = "select max(id_transakcji) as id from transakcje;";
	sql::ResultSet* wynik = kwerenda->executeQuery(select);
	if (!wynik->next()) {
		cout << "Błąd przy przeprowadzaniu transakcji." << endl;
		return false;
	}
	int id = wynik->getInt("id");
	for (Produkt p : koszyk) {
		insert = "insert into sprzedaze values (" + to_string(id) + ", " + to_string(p.zwrocID()) + ", " + to_string(p.zwrociloscWKoszyku()) + " );";
		kwerenda->execute(insert);
		update = "update asortyment set na_magazynie = na_magazynie - " + to_string(p.zwrociloscWKoszyku()) + " where ID = " + to_string(p.zwrocID()) + ";";
		kwerenda->execute(update);
	}
	delete kwerenda;
	delete wynik;
	cout << "Pomyślnie przeprowadzono transakcję." << endl;
	return true;
}