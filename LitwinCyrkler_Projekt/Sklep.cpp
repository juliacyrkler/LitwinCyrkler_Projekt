#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <conio.h>
#include <iostream>
#include <string>
#include "Sklep.h"
#include "stdlib.h"
#include "Kasjer.h"

using namespace std;

Sklep::Sklep(sql::Connection *con) : polaczenie(con) {
	ekranPowitalny();
}

void Sklep::ekranPowitalny() {
	cout << "Witamy w aplikacji sklepu Żabka!" << endl;
	cout << "--> 1 - Zaloguj się" << endl;
	cout << "--> 2 - Utwórz konto" << endl;
	cout << "--> 3 - Wyjdź z aplikacji" << endl;
	int wybor;
	cin >> wybor;
	clearConsole();
	if(cin.fail()){
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		wybor = 0;
	}

	switch (wybor) {
		case 1: {
			clearConsole();
			string login, haslo;
			cout << "Podaj login: ";
			getline(cin >> ws, login);
			cout << "Podaj hasło: ";
			getline(cin >> ws, haslo);
			if (czyUserIstnieje(login, haslo)) {
				uzytkownik = zaloguj(login, haslo);
				if (uzytkownik->interfejsUzytkownika()) {
					ekranPowitalny();
				}
			}
			else {
				clearConsole();
				cout << endl << "Błędny login lub hasło." << endl << endl;
				ekranPowitalny();
			}
			break;
		}
		case 2: {
			clearConsole();
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
			if (utworzKonto(imie, nazwisko, login, haslo)) {
				clearConsole();
				cout << endl << "Konto utworzone pomyślnie." << endl << endl;
				ekranPowitalny();
			}
			else {
				clearConsole();
				cout << endl << "Błąd podczas tworzenia konta." << endl << endl;
				ekranPowitalny();
			}
			break;
		}
		case 3:
			clearConsole();
			cout << endl << "Trwa zamykanie aplikacji. Do zobaczenia!" << endl;
			break;
		default:
			clearConsole();
			cout << endl << "Nieprawidłowy wybór. Spróbuj ponownie." << endl << endl;
			ekranPowitalny();
			break;
	}
}
Uzytkownik* Sklep::zaloguj(string login, string haslo) {
	if (czyUserIstnieje(login, haslo)) {
		try {
			sql::PreparedStatement* pstmt;
			sql::ResultSet* res;
			int id = 0;

			pstmt = polaczenie->prepareStatement("SELECT `id` FROM users WHERE login = ? AND haslo = ?");pstmt->setString(1, login);pstmt->setString(2, haslo);
			res = pstmt->executeQuery();
			if (res->next()) {id = res->getInt("id"); }
			delete res;delete pstmt;

			pstmt = polaczenie->prepareStatement("SELECT * FROM pracownicy WHERE user_id = ?"); pstmt->setInt(1,id); res = pstmt->executeQuery();
			if (res->next()) {
				int idPracownika = res->getInt("pracownik_id");
				string imie =  res->getString("imie");
				string nazwisko = res->getString("nazwisko");
				string stanowisko = res->getString("typ_pracownika");
				double stawka = res->getDouble("stawka_godzinowa");
				int liczba = res->getInt("godz_w_tyg");

				if (stanowisko == "administrator") { return new Administrator(idPracownika, imie, nazwisko, stawka, liczba, polaczenie); }
				else if (stanowisko == "menadzer") { return new Menadzer(idPracownika, imie, nazwisko, stawka, liczba, polaczenie); }
				else { return new Kasjer(idPracownika, imie, nazwisko, stawka, liczba, polaczenie); } 
				delete res; delete pstmt;
			}
			else {
				pstmt = polaczenie->prepareStatement("SELECT * FROM klienci WHERE user_id = ?"); pstmt->setInt(1, id); res = pstmt->executeQuery();
				res = pstmt->executeQuery();
				if(res->next()){
					int idKlienta = res->getInt("klient_id");
					string imie = res->getString("imie");
					string nazwisko = res->getString("nazwisko");
					double srodki = res->getDouble("srodki");
					int pkt = res->getInt("pkt_znizkowe");

					return new Klient(idKlienta, imie, nazwisko, pkt, srodki, polaczenie);
				}
				delete res; delete pstmt;
			}
		}
		catch(sql::SQLException& e){	cout << "Błąd logowania SQL: " << e.what() << endl;}
	}
}

bool Sklep::czyUserIstnieje(string login, string haslo) { //sprawdzenie czy login i haslo znajduja sie w bazie danych
	try {
		sql::PreparedStatement* pstmt;
		sql::ResultSet* res;

		pstmt = polaczenie->prepareStatement("SELECT * FROM users WHERE login = ? AND haslo = ?");

		pstmt->setString(1, login);
		pstmt->setString(2, haslo);

		res = pstmt->executeQuery();

		bool czyIstnieje = res->next();

		delete res;
		delete pstmt;
		return czyIstnieje;
	}
	catch (sql::SQLException& e) {		cout << "Błąd logowania SQL: " << e.what() << endl;    return false;	}
}

bool Sklep::utworzKonto(string imie, string nazwisko, string login, string haslo) {
	sql::Statement* kwerenda;
	kwerenda = polaczenie->createStatement();
	string loginSelect = "select * from users where login = \"" + login + "\";";
	sql::ResultSet* wynik = kwerenda->executeQuery(loginSelect);
	if (wynik->next()) {
		cout << "Użytkownik o podanym loginie już istnieje." << endl;
		delete wynik;
		delete kwerenda;
		return false;
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
	delete wynik;
	delete kwerenda;
	return true;
}
void Sklep::clearConsole() { system("cls"); }
Sklep::~Sklep() {
	delete uzytkownik;
	delete polaczenie;
}
