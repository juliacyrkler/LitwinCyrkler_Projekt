#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <conio.h>
#include <iostream>
#include <string>
#include "Sklep.h"

using namespace std;

Sklep::Sklep(sql::Connection *con) : polaczenie(con) {
	wczytajProdukty();
	ekranPowitalny();
}

void Sklep::ekranPowitalny() {
	cout << "Witamy w aplikacji sklepu ¯abka!" << endl;
	cout << "--> 1 - Zaloguj siê" << endl;
	cout << "--> 2 - Utwórz konto" << endl;
	cout << "--> 3 - WyjdŸ z aplikacji" << endl;
	int wybor;
	cin >> wybor;

	switch (wybor) {
		case 1: {
			string login, haslo;
			cout << "Podaj login: ";
			cin >> login;
			cout << "Podaj has³o: ";
			cin >> haslo;
			if (czyUserIstnieje(login, haslo)) {
				uzytkownik = zaloguj(login, haslo); //do zmiany, uytkownik tworzony na postawie danych z bazy
				if (uzytkownik->interfejsUzytkownika()) {
					ekranPowitalny();
				}
			}
			else {
				cout << endl << "B³êdny login lub has³o." << endl << endl;
				ekranPowitalny();
			}
			break;
		}
		case 2: {
			string imie, nazwisko, login, haslo, hasloPowtorzone;
			cout << "Podaj imiê: ";
			cin >> imie;
			cout << "Podaj nazwisko: ";
			cin >> nazwisko;
			cout << "Podaj login: ";
			cin >> login;
			cout << "Podaj has³o: ";
			cin >> haslo;
			while (haslo != hasloPowtorzone) {
				cout << "Powtórz has³o: ";
				cin >> hasloPowtorzone;
			}
			if (utworzKonto(imie, nazwisko, login, haslo)) {
				cout << endl << "Konto utworzone pomyœlnie." << endl << endl;
				ekranPowitalny();
			}
			else {
				cout << endl << "B³¹d podczas tworzenia konta." << endl << endl;
				ekranPowitalny();
			}
			break;
		}
		default:
			cout << endl << "Trwa zamykanie aplikacji. Do zobaczenia!";
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
				else {}//return new Kasjer(idPracownika, imie, nazwisko, stawka, liczba, polaczenie);} //a se kolega nie dzia³a bo tak

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
		catch(sql::SQLException& e){	cout << "B³¹d logowania SQL: " << e.what() << endl;}
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
	catch (sql::SQLException& e) {		cout << "B³¹d logowania SQL: " << e.what() << endl;    return false;	}
}

bool Sklep::utworzKonto(string imie, string nazwisko, string login, string haslo) {
	//dodanie nowego uzytkownika do bazy danych, zwrocenie odpowiedniej wartosci
	return true;
}

void Sklep::wczytajProdukty() {
	//wczytanie produktow z bazy danych do wektora produkty
}

Sklep::~Sklep() {
	delete uzytkownik;
	delete polaczenie;
}