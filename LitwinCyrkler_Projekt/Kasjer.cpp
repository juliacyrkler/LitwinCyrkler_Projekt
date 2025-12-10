#include <iostream>
#include <string>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include "Kasjer.h"

using namespace std;

Kasjer::Kasjer(int id_, std::string imie_, std::string nazwisko_, double stawka_, int liczba_, sql::Connection* con) : Pracownik(id_, imie_, nazwisko_, stawka_, liczba_, con) {}

bool Kasjer::interfejsUzytkownika() {
	clearConsole();
	cout <<"Witaj, " << this->zwrocImie() << "! Jesteś zalogowany jako kasjer.";

	bool wyloguj = false;
	while (!wyloguj) {
		cout << endl << "Co chcesz zrobić?" << endl;
		cout << "--> 1 - Wyświetl transakcje" << endl;
		cout << "--> 2 - Zatwierdź transakcje" << endl; 
		cout << "--> 3 - Wyświetl listę klientów" << endl;
		cout << "--> 4 - Dodaj nowego klienta" << endl;
		cout << "--> 5 - Wyloguj się" << endl;

		int wybor;
		cin >> wybor;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			wybor = 0;
		}

		switch (wybor) {
		case 1:clearConsole();
			this->wyswietlTransakcje();
			break;
		case 2:clearConsole();
			this->zatwierdzTransakcje();
			break;
		case 3:clearConsole();
			this->wyswietlKlientow();
			break;
		case 4:clearConsole();
			this->dodajKlienta();
			break;
		case 5:clearConsole();
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
	getline(cin >> ws, imie);
	cout << "Podaj nazwisko: ";
	getline(cin >> ws, nazwisko);
	cout << "Podaj login: ";
	getline(cin >> ws, login);
	cout << "Podaj hasło: ";
	getline(cin >> ws, haslo);
	while (haslo != hasloPowtorzone) {
		cout << "Powtórz hasło: ";
		getline(cin >> ws, hasloPowtorzone);
	}
	sql::Statement* kwerenda;
	kwerenda = polaczenie->createStatement();
	string loginSelect = "select * from users where login = \"" + login + "\";";
	sql::ResultSet* wynik = kwerenda->executeQuery(loginSelect);
	if (wynik->next()) {
		clearConsole();
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
		clearConsole();
		cout << "Wystąpił błąd podczas dodawania nowego klienta." << endl;
	}
	delete wynik;
	delete kwerenda;
}

void Kasjer::wyswietlTransakcje() {
	sql::PreparedStatement* pstmt;
	sql::ResultSet* res;
	try {
		pstmt = polaczenie->prepareStatement("SELECT id_transakcji, imie, nazwisko, data_transakcji, godzina_transakcji, CenaTransakcji, Zatwierdzona FROM transakcje, klienci where klienci.klient_id = transakcje.kupujacy;");
		res = pstmt->executeQuery();
		while (res->next()) {
			cout << "Transakcja ID: " << res->getInt("id_transakcji") << ", Klient: " << res->getString("imie") << " " << res->getString("nazwisko") << ", Data: " << res->getString("data_transakcji") << ", Godzina: " << res->getString("godzina_transakcji") << ", Cena: " << res->getDouble("CenaTransakcji") << " zł, Zatwierdzona: " << (res->getInt("Zatwierdzona") ? "Tak" : "Nie") << endl;
		}
		delete pstmt; delete res;
	}
	catch (sql::SQLException& e) { cout << "Błąd pobierania transakcji: " << e.what() << endl; }
}

void Kasjer::wyswietlTransakcjeDoZatwierdzenia() {
	sql::PreparedStatement* pstmt;
	sql::ResultSet* res;
	try {
		pstmt = polaczenie->prepareStatement("SELECT id_transakcji, imie, nazwisko, data_transakcji, godzina_transakcji, CenaTransakcji FROM transakcje, klienci where klienci.klient_id = transakcje.kupujacy AND Zatwierdzona = 0;");
		res = pstmt->executeQuery();
		while (res->next()) {
			cout << "Transakcja ID: " << res->getInt("id_transakcji") << ", Klient: " << res->getString("imie") << " " << res->getString("nazwisko") << ", Data: " << res->getString("data_transakcji") << ", Godzina: " << res->getString("godzina_transakcji") << ", Cena: " << res->getDouble("CenaTransakcji") << " zł" << endl;
		}
		delete pstmt; delete res;
	}
	catch (sql::SQLException& e) { clearConsole(); cout << "Błąd pobierania transakcji do zatwierdzenia: " << e.what() << endl; }
}

void Kasjer::zatwierdzTransakcje() {
	this->wyswietlTransakcjeDoZatwierdzenia();
	int idTransakcji;
	cout << "Podaj ID transakcji do zatwierdzenia: ";
	cin >> idTransakcji;
	if (cin.fail()) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		clearConsole();
		cout << "Nieprawidłowe ID transakcji." << endl;
		return;
	}
	sql::PreparedStatement* pstmt;
	sql::ResultSet* res;
	try {
		pstmt = polaczenie->prepareStatement("UPDATE transakcje SET sprzedajacy = ?, Zatwierdzona = 1 WHERE id_transakcji = ?;");
		pstmt->setInt(1, this->id);
		pstmt->setInt(2, idTransakcji);
		int zmodyfikowane = pstmt->executeUpdate();
		if (zmodyfikowane > 0) {
			cout << "Pomyślnie zatwierdzono transakcję." << endl;
			pstmt = polaczenie->prepareStatement(
				"SELECT klienci.klient_id, transakcje.CenaTransakcji FROM transakcje inner join klienci ON transakcje.kupujacy = klienci.klient_id WHERE id_transakcji = ?;"
			);
			pstmt->setInt(1, idTransakcji);
			res = pstmt->executeQuery();
			if (res->next()) {
				int idKlienta = res->getInt("klient_id");
				double cenaTransakcji = res->getDouble("CenaTransakcji");
				delete res;
				pstmt = polaczenie->prepareStatement(
					"UPDATE klienci SET srodki = srodki - ? WHERE klient_id = ?;"
				);
				pstmt->setDouble(1, cenaTransakcji);
				pstmt->setInt(2, idKlienta);
				if (pstmt->executeUpdate() > 0) {
					clearConsole();
					cout << "Środki zostały pobrane z konta klienta." << endl;
				} else {
					clearConsole(); cout << "Wystąpił błąd podczas pobierania środków z konta klienta." << endl;
				}
			}
			delete pstmt;
			pstmt = polaczenie->prepareStatement(
				"SELECT id_produktu, ilosc FROM sprzedaze WHERE id_transakcji = ?;"
			);
			pstmt->setInt(1, idTransakcji);
			res = pstmt->executeQuery();
			while (res->next()) {
				int idProduktu = res->getInt("id_produktu");
				int iloscSprzedana = res->getInt("ilosc");
				sql::PreparedStatement* pstmt2;
				pstmt2 = polaczenie->prepareStatement(
					"UPDATE asortyment SET na_magazynie = na_magazynie - ? WHERE ID = ?;"
				);
				pstmt2->setInt(1, iloscSprzedana);
				pstmt2->setInt(2, idProduktu);
				if (pstmt2->executeUpdate() > 0) {
					clearConsole();
					cout << "Zaktualizowano stan magazynowy dla produktu ID: " << idProduktu << endl;
				} else {
					clearConsole();
					cout << "Wystąpił błąd podczas aktualizacji stanu magazynowego dla produktu ID: " << idProduktu << endl;
				}
				delete pstmt2;
			}
			delete res;
		}
		else {
			clearConsole();
			cout << "Nie znaleziono transakcji o podanym ID lub transakcja już została zatwierdzona." << endl;
		}
		delete pstmt;
	}
	catch (sql::SQLException& e) { clearConsole();  cout << "Błąd zatwierdzania transakcji: " << e.what() << endl; }
}