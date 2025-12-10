#include <iostream>
#include <string>
#include <ctime>
#include <cppconn/statement.h>
#include "Menadzer.h"

using namespace std;

Menadzer::Menadzer(int id_, std::string imie_, std::string nazwisko_, double stawka_, int liczba_, sql::Connection* con) : Pracownik(id_, imie_, nazwisko_, stawka_, liczba_, con) {}

bool Menadzer::interfejsUzytkownika() {
	clearConsole();
	cout << "Witaj, " << this->zwrocImie() << "! Jesteś zalogowany jako menadżer.";

	bool wyloguj = false;
	while (!wyloguj) {
		cout << endl << "Co chcesz zrobić?" << endl;
		cout << "--> 1 - Edytuj asortyment" << endl;
		cout << "--> 2 - Wyświetl asortyment" << endl;
		cout << "--> 3 - Wyświetl pracowników" << endl;
		cout << "--> 4 - Wyświetl klientów" << endl;
		cout << "--> 5 - Edytuj dane pracownika" << endl;
		cout << "--> 6 - Generuj raport sprzedaży z ostatniego miesiąca" << endl;
		cout << "--> 7 - Wyloguj się" << endl;
		int wybor;
		cin >> wybor;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			wybor = 0;
		}

		switch (wybor) {
		case 1:
			clearConsole();
			this->edytujAsortyment();
			break;
		case 2:
			clearConsole();
			this->wyswietlAsortyment();
			break;
		case 3:
			clearConsole();
			this->wyswietlPracownikow();
			break;
		case 4:
			clearConsole();
			this->wyswietlKlientow();
			break;
		case 5:
			clearConsole();
			this->wyswietlPracownikow();
			this->edytujPracownika();
			break;
		case 6:
			clearConsole();
			this->generujRaportSprzedazy();
			break;
		case 7:
			clearConsole();
			wyloguj = true;
			break;
		default:
			break;
		}
	}
	return true;
}

void Menadzer::wyswietlPracownikow() {
	sql::Statement* kwerenda;
	kwerenda = polaczenie->createStatement();
	string select;
	cout << "Lista pracowników:" << endl;
	select = "select pracownik_id, imie, nazwisko, typ_pracownika, stawka_godzinowa, godz_w_tyg from pracownicy;";
	sql::ResultSet* wynik = kwerenda->executeQuery(select);
	while (wynik->next()) {
		cout << "ID: " << wynik->getInt("pracownik_id") << ". " << wynik->getString("imie") << " " << wynik->getString("nazwisko") << ", stanowisko: " << wynik->getString("typ_pracownika") << ", stawka: " << wynik->getDouble("stawka_godzinowa") << " zł/h, liczba godzin w tygodniu: " << wynik->getInt("godz_w_tyg") << endl;
	}
	delete wynik;
	delete kwerenda;
}

void Menadzer::wyswietlKlientow() {
	sql::Statement* kwerenda;
	kwerenda = polaczenie->createStatement();
	string select;
	cout << "Lista klientów:" << endl;
	select = "select klient_id, imie, nazwisko, srodki, pkt_znizkowe from klienci;";
	sql::ResultSet* wynik = kwerenda->executeQuery(select);
	while (wynik->next()) {
		cout << "ID: " << wynik->getInt("klient_id") << ". " << wynik->getString("imie") << " " << wynik->getString("nazwisko") << ", stan środków: " << wynik->getDouble("srodki") << " zł, punkty lojalnościowe: " << wynik->getInt("pkt_znizkowe") << endl;
	}
	delete wynik;
	delete kwerenda;
}

void Menadzer::edytujPracownika() {
	sql::Statement* kwerenda;
	kwerenda = polaczenie->createStatement();
	string update, select;
	int pracownikID, edytowanaWartosc;
	cout << "Podaj ID pracownika do edycji: ";
	cin >> pracownikID;
	select = "select * from pracownicy where pracownik_id = " + to_string(pracownikID) + ";";
	sql::ResultSet* wynik = kwerenda->executeQuery(select);
	if (cin.fail() || pracownikID < 1 || !wynik->next()) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		clearConsole();
		cout << "Podano nieprawidłowe dane." << endl;
		return;
	}
	cout << "Co chcesz edytować?" << endl;
	cout << "--> 1 - Stawkę godzinową" << endl;
	cout << "--> 2 - Liczbę godzin pracy w tygodniu" << endl;
	cin >> edytowanaWartosc;
	if (cin.fail() || (edytowanaWartosc != 1 && edytowanaWartosc != 2)) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		clearConsole();
		cout << "Podano nieprawidłowe dane." << endl;
		return;
	}
	string edytowanePole, nowaWartosc;
	cout << "Podaj nową wartość: ";
	if(edytowanaWartosc == 1) {
		double stawka;
		cin >> stawka;
		if (cin.fail() || stawka < 0) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			clearConsole();
			cout << "Nieprawidłowe dane." << endl;
			return;
		}
		edytowanePole = "stawka_godzinowa";
		nowaWartosc = to_string(stawka);
		nowaWartosc = nowaWartosc.replace(nowaWartosc.find(','), 1, ".");
	} else {
		int liczbaGodzin;
		cin >> liczbaGodzin;
		if (cin.fail() || liczbaGodzin < 0) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			clearConsole();
			cout << "Nieprawidłowe dane." << endl;
			return;
		}
		nowaWartosc = to_string(liczbaGodzin);
		edytowanePole = "godz_w_tyg";
	}
	update = "update pracownicy set " + edytowanePole + " = " + nowaWartosc + " where pracownik_id = " + to_string(pracownikID) + ";";
	kwerenda->execute(update);
	if (kwerenda->getUpdateCount() > 0) {
		clearConsole();
		cout << "Dane pracownika zaktualizowane pomyślnie." << endl;
	} else {
		clearConsole();
		cout << "Wystąpił błąd podczas aktualizacji danych pracownika." << endl;
	}
	delete kwerenda;
	delete wynik;
}

void Menadzer::wyswietlAsortyment() {
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

void Menadzer::edytujAsortyment() {
	int wybor, produktID;
	cout << "Co chcesz zrobić?" << endl;
	cout << "--> 1 - Dodaj produkt" << endl;
	cout << "--> 2 - Usuń produkt" << endl;
	cout << "--> 3 - Edytuj produkt" << endl;
	cin >> wybor;
	if (cin.fail() || wybor < 1 || wybor > 3) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		clearConsole();
		cout << "Nieprawidłowe dane." << endl;
		return;
	}
	if (wybor > 1) {
		Menadzer::wyswietlAsortyment();
		string tekst = (wybor == 2) ? "usunąć" : "edytować";
		cout << "Podaj ID produktu, który chcesz " << tekst << ": ";
		cin >> produktID;
		if(cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			clearConsole();
			cout << "Nieprawidłowe dane." << endl;
			return;
		}
		if (wybor == 2) Menadzer::usunProdukt(produktID);
		else Menadzer::modyfikujProdukt(produktID);
	}
	else {
		Menadzer::dodajProdukt();
	}
}

void Menadzer::generujRaportSprzedazy() {
	sql::Statement* kwerenda;
	kwerenda = polaczenie->createStatement();
	string select, select2;
	string miesiace[] = { "styczniu", "lutym", "marcu", "kwietniu", "maju", "czerwcu", "lipcu", "sierpniu", "wrześniu", "październiku", "listopadzie", "grudniu" };
	int aktualnyMiesiac, aktualnyRok;
	time_t teraz = time(0);
	tm* ltm = localtime(&teraz);
	aktualnyMiesiac = 1 + ltm->tm_mon;
	aktualnyRok = 1900 + ltm->tm_year;
	cout << "Raport sprzedaży w " << miesiace[aktualnyMiesiac - 2] << " " << to_string(aktualnyRok) << ":" << endl;
	select = "select a.ID, a.nazwa, sum(s.ilosc) as sprzedane_ilosc, sum(s.ilosc * a.cena) as przychod from sprzedaze s join asortyment a on s.id_produktu = a.ID join transakcje t on s.id_transakcji = t.id_transakcji where MONTH(t.data_transakcji) = " + to_string(aktualnyMiesiac - 1) + " and YEAR(t.data_transakcji) = " + to_string(aktualnyRok) + " group by a.ID, a.nazwa;";
	kwerenda->executeQuery(select);
	sql::ResultSet* wynik = kwerenda->executeQuery(select);
	if (wynik->rowsCount() == 0)
	{
		clearConsole();
		cout << "Brak sprzedaży w podanym okresie." << endl;
		delete wynik;
		delete kwerenda;
		return;
	}
	while (wynik->next()) {
		cout << "ID produktu: " << wynik->getInt("ID") << ", nazwa: " << wynik->getString("nazwa") << ", sprzedana ilość: " << wynik->getInt("sprzedane_ilosc") << ", przychód: " << wynik->getDouble("przychod") << " zł" << endl;
	}
	select2 = "select sum(s.ilosc * a.cena) as laczny_przychod from sprzedaze s join asortyment a on s.id_produktu = a.ID join transakcje t on s.id_transakcji = t.id_transakcji where MONTH(t.data_transakcji) = " + to_string(aktualnyMiesiac - 1) + " and YEAR(t.data_transakcji) = " + to_string(aktualnyRok) + ";";
	sql::ResultSet* wynik2 = kwerenda->executeQuery(select2);
	if (wynik2->next()) {
		cout << endl << "Łączny przychód w zeszłym miesiącu: " << wynik2->getDouble("laczny_przychod") << " zł" << endl;
	}
	delete wynik;
	delete wynik2;
	delete kwerenda;
}

void Menadzer::dodajProdukt() {
	string nazwa, kategoria, insert;
	double cena;
	int stanMagazynowy;
	cout << "Podaj nazwę nowego produktu: ";
	getline(cin >> ws, nazwa);
	cout << "Podaj kategorię nowego produktu: ";
	getline(cin >> ws, kategoria);
	cout << "Podaj cenę nowego produktu: ";
	cin >> cena;
	if (cin.fail() || cena < 0) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		clearConsole();
		cout << "Nieprawidłowe dane." << endl;
		return;
	}
	string cena2 = to_string(cena).replace(to_string(cena).find(','), 1, ".");
	cout << "Podaj stan magazynowy nowego produktu: ";
	cin >> stanMagazynowy;
	if (cin.fail() || stanMagazynowy < 0) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		clearConsole();
		cout << "Nieprawidłowe dane." << endl;
		return;
	}
	sql::Statement* kwerenda;
	kwerenda = polaczenie->createStatement();
	insert = "insert into asortyment values (null, \"" + nazwa + "\", \"" + kategoria + "\", " + cena2 + ", " + to_string(stanMagazynowy) + ");";
	kwerenda->execute(insert);
	if (kwerenda->getUpdateCount() > 0) {
		clearConsole();
		cout << "Produkt dodany pomyślnie." << endl;
	} else {
		clearConsole();
		cout << "Wystąpił błąd podczas dodawania produktu." << endl;
	}
	delete kwerenda;
}

void Menadzer::usunProdukt(int produktID) {
	sql::Statement* kwerenda;
	kwerenda = polaczenie->createStatement();
	string deleteQuery, select;
	select = "select * from asortyment where ID = " + to_string(produktID) + ";";
	sql::ResultSet* wynik = kwerenda->executeQuery(select);
	if (!wynik->next()) {
		clearConsole();
		cout << "Produkt o podanym ID nie istnieje." << endl;
		delete wynik;
		delete kwerenda;
		return;
	}
	deleteQuery = "delete from asortyment where ID = " + to_string(produktID) + ";";
	kwerenda->execute(deleteQuery);
	if (kwerenda->getUpdateCount() > 0) {
		clearConsole();
		cout << "Produkt usunięty pomyślnie." << endl;
	} else {
		clearConsole();
		cout << "Wystąpił błąd podczas usuwania produktu." << endl;
	}
	delete kwerenda;
	delete wynik;
}

void Menadzer::modyfikujProdukt(int produktID) {
	sql::Statement* kwerenda;
	kwerenda = polaczenie->createStatement();
	string update, select, edytowanePole, nowaWartosc;
	select = "select * from asortyment where ID = " + to_string(produktID) + ";";
	sql::ResultSet* wynik = kwerenda->executeQuery(select);
	if (!wynik->next()) {
		clearConsole();
		cout << "Produkt o podanym ID nie istnieje." << endl;
		delete wynik;
		delete kwerenda;
		return;
	}
	cout << "Co chcesz edytować?" << endl;
	cout << "--> 1 - Nazwę produktu" << endl;
	cout << "--> 2 - Kategorię produktu" << endl;
	cout << "--> 3 - Cenę produktu" << endl;
	cout << "--> 4 - Stan magazynowy produktu" << endl;
	int wybor;
	cin >> wybor;
	if (cin.fail() || wybor < 1 || wybor > 4) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		clearConsole();
		cout << "Nieprawidłowe dane." << endl;
		delete wynik;
		delete kwerenda;
		return;
	}
	cout << "Podaj nową wartość: ";
	switch (wybor) {
		case 1:
			getline(cin >> ws, nowaWartosc);
			nowaWartosc = "\"" + nowaWartosc + "\"";
			edytowanePole = "nazwa";
			break;
		case 2:
			getline(cin >> ws, nowaWartosc);
			nowaWartosc = "\"" + nowaWartosc + "\"";
			edytowanePole = "kategoria";
			break;
		case 3: {
			double cena;
			cin >> cena;
			if (cin.fail() || cena < 0) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				clearConsole();
				cout << "Nieprawidłowe dane." << endl;
				delete wynik;
				delete kwerenda;
				return;
			}
			nowaWartosc = to_string(cena);
			nowaWartosc = nowaWartosc.replace(nowaWartosc.find(','), 1, ".");
			edytowanePole = "cena";
			break;
		}
		case 4: {
			int stanMagazynowy;
			cin >> stanMagazynowy;
			if (cin.fail() || stanMagazynowy < 0) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				clearConsole();
				cout << "Nieprawidłowe dane." << endl;
				delete wynik;
				delete kwerenda;
				return;
			}
			nowaWartosc = to_string(stanMagazynowy);
			edytowanePole = "na_magazynie";
			break;
		}
	}
	update = "update asortyment set " + edytowanePole + " = " + nowaWartosc + " where ID = " + to_string(produktID) + ";";
	kwerenda->execute(update);
	if (kwerenda->getUpdateCount() > 0) {
		clearConsole();
		cout << "Dane produktu zaktualizowane pomyślnie." << endl;
	} else {
		clearConsole();
		cout << "Wystąpił błąd podczas aktualizacji danych produktu." << endl;
	}
	delete kwerenda;
	delete wynik;
}