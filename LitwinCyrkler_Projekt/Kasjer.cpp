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
		cout << "--> 3 - Wyloguj się" << endl;

		int wybor;
		cin >> wybor;

		switch (wybor) {
		case 1:

			break;
		case 2:
			this->wyswietlKlientow();
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