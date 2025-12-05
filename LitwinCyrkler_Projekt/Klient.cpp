#include <iostream>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <ctime>
#include <string>
#include "Klient.h"
#include "Produkt.h"

using namespace std;

Klient::Klient(int id_, std::string imie_, std::string nazwisko_, int punkty_, double srodki_, sql::Connection* con) : Uzytkownik(id_, imie_, nazwisko_, con) {
	this->punktyLojalnosciowe = punkty_;
	this->srodkiNaKoncie = srodki_;
}

bool Klient::interfejsUzytkownika() {
	cout << endl << "Witaj, " << this->zwrocImie() << "! Jesteś zalogowany jako klient.";

	bool wyloguj = false;
	while (!wyloguj) {
		cout << endl << "Co chcesz zrobić?" << endl;
		cout << "--> 1 - Wyświetl produkty" << endl;
		cout << "--> 2 - Przejdź do koszyka" << endl;
		cout << "--> 3 - Dokonaj zakupu" << endl;
		cout << "--> 4 - Dodaj do koszyka" << endl;
		cout << "--> 5 - Wyjmij z koszyka" << endl;
		cout << "--> 6 - Pokaż środki na koncie" << endl;
		cout << "--> 7 - Wpłać środki na konto" << endl;
		cout << "--> 8 - Moje transakcje" << endl;
		cout << "--> 9 - Wyloguj się" << endl;
		int wybor;
		cin >> wybor;

		switch (wybor) {
		case 1:this->wyswietlProdukty(); break;
		case 2:this->pokazKoszyk(); break;
		case 3:this->dokonajZakupu(); break;
		case 4:this->dodajDoKoszyka(); break;
		case 5:this->wyjmijZKoszyka(); break;
		case 6:this->pokazStanKonta(); break;
		case 7:this->wplacSrodki(); break;
		case 8:this->mojeTransakcje(); break;
		case 9:clearConsole(); wyloguj = true; break;
		default:break;
		}
	}
	return true;
}
void Klient::dodajDoKoszyka() {
	sql::PreparedStatement* pstmt;
	sql::ResultSet* res;
	wyswietlProdukty();

	int dodawanyProduktId;
	cout << "Proszę podać Nr produktu do dodania: " << endl;
	cin >> dodawanyProduktId;

	try {

		pstmt = polaczenie->prepareStatement("SELECT* FROM asortyment WHERE ID = ?");
		pstmt->setInt(1, dodawanyProduktId);
		res = pstmt->executeQuery();

		if (res->next()) {
			int id = res->getInt("ID");
			string nazwa = res->getString("nazwa");
			string kategoria = res->getString("kategoria");
			double DoubleCena = res->getDouble("cena"); float FloatCena = (float)DoubleCena;
			int ilosc;

			cout << "Ile sztuk produktu dodać?: "; cin >> ilosc; cout << endl;
			if (res->getInt("na_magazynie")<ilosc) {
				cout << "Niewystarczająca ilość produktu w magazynie!" << endl;
				return;
			}
			koszyk.emplace_back(id, nazwa, kategoria, FloatCena, ilosc);
		}
		else {
			cout << "Błąd dodawania produktu do koszyka" << endl;
		}
	}
	catch (sql::SQLException& e) { cout << "Błąd dodawania produktu do koszyka: " << e.what() << endl; }

}
void Klient::wyjmijZKoszyka() {
	int idProduktu, iloscDoOdjecia, nowaIlosc;

	if (koszyk.empty()) { cout << "Koszyk jest pusty." << endl; return; }
	for (Produkt& p : koszyk) { p.wyswietlProdukt(); }

	cout << "Produkt o jakim id chciałbyć wyjąć?:"; cin >> idProduktu; cout << endl;
	for (auto it = koszyk.begin(); it != koszyk.end(); ++it) {

		if (it->zwrocID() == idProduktu) {

			it->wyswietlProdukt();
			cout << "Ilość w koszyku: " << it->zwrociloscWKoszyku() << endl;
			cout << "Ile chcesz zabrać?: "; cin >> iloscDoOdjecia; cout << endl;

			nowaIlosc = it->zwrociloscWKoszyku() - iloscDoOdjecia;

			if (nowaIlosc > 0) {
				it->NowaIloscWKoszyku(nowaIlosc);
				cout << "Zaktualizowano ilość." << endl;
			}
			else if (nowaIlosc == 0) {
				koszyk.erase(it);
				cout << "Produkt usunięty z koszyka." << endl;
			}
			else { cout << "Podana nie poprawna wartość!" << endl; }

			return;
		}
	}
}

void Klient::dokonajZakupu() {
	sql::PreparedStatement* pstmt;
	int wybor;

	pokazKoszyk();
	cout << "Czy napewno chcesz dokonać zakupu wybranych artykułów?\n -> 1 - Tak\n -> 2 - Nie" << endl;
	cin >> wybor;

	if (wybor != 1) { return; }

	try {
		time_t teraz = time(nullptr);
		tm* lokalny = localtime(&teraz);

		char data[11];
		strftime(data, sizeof(data), "%Y-%m-%d", lokalny);

		char godzina[9];
		strftime(godzina, sizeof(godzina), "%H:%M:%S", lokalny);

		pstmt = polaczenie->prepareStatement(
			"INSERT INTO transakcje "
			"(sprzedajacy, kupujacy, data_transakcji, godzina_transakcji, CenaTransakcji, Zatwierdzona) "
			"VALUES (?, ?, ?, ?, ?, ?)"
		);

		pstmt->setNull(1, sql::DataType::INTEGER);
		pstmt->setInt(2, this->id);
		pstmt->setString(3, data);
		pstmt->setString(4, godzina);
		pstmt->setDouble(5, cenaKoszyka());
		pstmt->setInt(6, 0);

		if (this->srodkiNaKoncie > cenaKoszyka()) {
			pstmt->execute();
			cout << "Po zaakceptowaniu tej transakcji przez kasjera zostaną ściągnięte środki z twojego konta" << endl;
			for (Produkt& p : koszyk) {
				sql::PreparedStatement* pstmt2;
				pstmt2 = polaczenie->prepareStatement("INSERT INTO sprzedaze (id_transakcji, id_produktu, ilosc) values ( ?, ?, ?);");
				int idTransakcji;
				sql::ResultSet* res2;
				res2 = polaczenie->createStatement()->executeQuery("SELECT max(id_transakcji) as max_id FROM transakcje;");
				if (res2->next()) {
					idTransakcji = res2->getInt("max_id");
					pstmt2->setInt(1, idTransakcji);
					pstmt2->setInt(2, p.zwrocID());
					pstmt2->setInt(3, p.zwrociloscWKoszyku());
				}	
				pstmt2->execute();
				delete res2;
				delete pstmt2;
			}
			koszyk.clear();
		}
		else {
			cout << "Niewystarczająca liczba zł na koncie!" << endl; return;
		}


		delete pstmt;
	}
	catch (sql::SQLException& e) { cout << "Błąd SQL: " << e.what() << endl; }
}

double Klient::cenaKoszyka() {
	double suma = 0;
	for (Produkt& p : koszyk) { suma += p.zwrocCene(); }
	return suma;
}

void Klient::pokazStanKonta() {
	cout << "Stan konta: " << this->srodkiNaKoncie << " zł" << endl;
	cout << "Punkty lojalnościowe: " << this->punktyLojalnosciowe << endl;
}

void Klient::wyswietlProdukty() {
	sql::PreparedStatement* pstmt;
	sql::ResultSet* res;

	//int wybor;	cout << "-----> 1. Wszystkie produkty" << endl << "-----> 2. Produkty tylko z danej kategorii" << endl;	cin >> wybor;
	pstmt = polaczenie->prepareStatement("SELECT* FROM asortyment order by kategoria DESC");
	res = pstmt->executeQuery();
	int lp = 1;

	//switch (wybor) {
	//case 1:
	while (res->next()) {
		string nazwaProduktu = res->getString("nazwa");
		double cena = res->getDouble("cena");
		int idProduktu = res->getInt("ID");

		cout << /*lp << ". " <<*/ "Nr." << idProduktu << " -- " << nazwaProduktu << " -- " << cena << "zł" << endl;
		lp++;

	}//break;

//case 2:cout << "Lmao nie." << endl; break; //to be changed
//default: cout << "Niepoprawny wybór!" << endl;
//}
	delete pstmt; delete res;
}

void Klient::pokazKoszyk() {
	if (koszyk.empty()) { cout << "Koszyk jest pusty." << endl; return; }

	cout << "Zawartość koszyka:" << endl << "------------------" << endl;
	int lp = 1;
	float suma = 0;

	for (Produkt& p : koszyk) {
		p.wyswietlProdukt();
		suma += p.zwrocCene();
	}
	cout << "------------------" << endl << "Suma: " << suma << " zł" << endl;
}

void Klient::wplacSrodki() {
	double kwota;
	cout << "Podaj kwotę do wpłacenia: ";
	cin >> kwota;
	if (cin.fail() || kwota <= 0) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Nieprawidłowa kwota." << endl;
		return;
	}

	try {
		sql::PreparedStatement* pstmt;

		pstmt = polaczenie->prepareStatement("UPDATE klienci SET srodki = srodki + ? WHERE klient_id = ?");

		pstmt->setDouble(1, kwota);
		pstmt->setInt(2, this->id);

		int zmodyfikowane = pstmt->executeUpdate();

		if (zmodyfikowane > 0) {
			this->srodkiNaKoncie += kwota;
			cout << "Wpłacono " << kwota << " zł. Stan konta: " << this->srodkiNaKoncie << " zł." << endl;
		}
		else { cout << "Błąd doładowania środków" << endl; }

		delete pstmt;
	}
	catch (sql::SQLException& e) { cout << "Błąd doładowania środków: " << e.what() << endl; }
}

void Klient::mojeTransakcje() {
	sql::PreparedStatement* pstmt;
	sql::ResultSet* res;
	try {
		pstmt = polaczenie->prepareStatement("SELECT * FROM transakcje WHERE kupujacy = ?");
		pstmt->setInt(1, this->id);
		res = pstmt->executeQuery();
		while (res->next()) {
			cout << "Transakcja ID: " << res->getInt("id_transakcji") << ", Data: " << res->getString("data_transakcji") << ", Godzina: " << res->getString("godzina_transakcji") << ", Cena: " << res->getDouble("CenaTransakcji") << " zł, Zatwierdzona: " << (res->getInt("Zatwierdzona") ? "Tak" : "Nie") << endl;
		}
		delete pstmt; delete res;
	}
	catch (sql::SQLException& e) { cout << "Błąd pobierania transakcji: " << e.what() << endl; }
}
