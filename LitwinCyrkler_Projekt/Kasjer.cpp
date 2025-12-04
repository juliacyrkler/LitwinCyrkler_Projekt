#include <iostream>
#include <string>
#include <cppconn/statement.h>
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

		switch (wybor) {
		case 1:

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