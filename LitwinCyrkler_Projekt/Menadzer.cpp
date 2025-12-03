#include <iostream>
#include <string>
#include <ctime>
#include <cppconn/statement.h>
#include "Menadzer.h"

using namespace std;

Menadzer::Menadzer(int id_, std::string imie_, std::string nazwisko_, double stawka_, int liczba_, sql::Connection* con) : Pracownik(id_, imie_, nazwisko_, stawka_, liczba_, con) {}

bool Menadzer::interfejsUzytkownika() {
	cout << endl << "Witaj, " << this->zwrocImie() << "! Jesteœ zalogowany jako menad¿er.";

	bool wyloguj = false;
	while (!wyloguj) {
		cout << endl << "Co chcesz zrobiæ?" << endl;
		cout << "--> 1 - Edytuj asortyment" << endl;
		cout << "--> 2 - Wyœwietl asortyment" << endl;
		cout << "--> 3 - Wyœwietl pracowników" << endl;
		cout << "--> 4 - Wyœwietl klientów" << endl;
		cout << "--> 5 - Edytuj dane pracownika" << endl;
		cout << "--> 6 - Generuj raport sprzeda¿y z ostatniego miesi¹ca" << endl;
		cout << "--> 7 - Wyloguj siê" << endl;
		int wybor;
		cin >> wybor;

		switch (wybor) {
		case 1:
			this->edytujAsortyment();
			break;
		case 2:
			this->wyswietlAsortyment();
			break;
		case 3:
			this->wyswietlPracownikow();
			break;
		case 4:
			this->wyswietlKlientow();
			break;
		case 5:
			this->wyswietlPracownikow();
			this->edytujPracownika();
			break;
		case 6:
			this->generujRaportSprzedazy();
			break;
		case 7:
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
		cout << "ID: " << wynik->getInt("pracownik_id") << ". " << wynik->getString("imie") << " " << wynik->getString("nazwisko") << ", stanowisko: " << wynik->getString("typ_pracownika") << ", stawka: " << wynik->getDouble("stawka_godzinowa") << " z³/h, liczba godzin w tygodniu: " << wynik->getInt("godz_w_tyg") << endl;
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
		cout << "ID: " << wynik->getInt("klient_id") << ". " << wynik->getString("imie") << " " << wynik->getString("nazwisko") << ", stan œrodków: " << wynik->getDouble("srodki") << " z³, punkty lojalnoœciowe: " << wynik->getInt("pkt_znizkowe") << endl;
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
		cout << "Podano nieprawid³owe dane." << endl;
		return;
	}
	cout << "Co chcesz edytowaæ?" << endl;
	cout << "--> 1 - Stawkê godzinow¹" << endl;
	cout << "--> 2 - Liczbê godzin pracy w tygodniu" << endl;
	cin >> edytowanaWartosc;
	if (cin.fail() || (edytowanaWartosc != 1 && edytowanaWartosc != 2)) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Podano nieprawid³owe dane." << endl;
		return;
	}
	string edytowanePole, nowaWartosc;
	cout << "Podaj now¹ wartoœæ: ";
	if(edytowanaWartosc == 1) {
		double stawka;
		cin >> stawka;
		if (cin.fail() || stawka < 0) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Nieprawid³owe dane." << endl;
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
			cout << "Nieprawid³owe dane." << endl;
			return;
		}
		nowaWartosc = to_string(liczbaGodzin);
		edytowanePole = "godz_w_tyg";
	}
	update = "update pracownicy set " + edytowanePole + " = " + nowaWartosc + " where pracownik_id = " + to_string(pracownikID) + ";";
	kwerenda->execute(update);
	if (kwerenda->getUpdateCount() > 0) {
		cout << "Dane pracownika zaktualizowane pomyœlnie." << endl;
	} else {
		cout << "Wyst¹pi³ b³¹d podczas aktualizacji danych pracownika." << endl;
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
		cout << "ID: " << wynik->getInt("ID") << ". " << wynik->getString("nazwa") << " - " << wynik->getString("kategoria") << ", cena: " << wynik->getDouble("cena") << " z³, stan magazynowy: " << wynik->getInt("na_magazynie") << endl;
	}
	delete wynik;
	delete kwerenda;
}

void Menadzer::edytujAsortyment() {
	int wybor, produktID;
	cout << "Co chcesz zrobiæ?" << endl;
	cout << "--> 1 - Dodaj produkt" << endl;
	cout << "--> 2 - Usuñ produkt" << endl;
	cout << "--> 3 - Edytuj produkt" << endl;
	cin >> wybor;
	if (cin.fail() || wybor < 1 || wybor > 3) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Nieprawid³owe dane." << endl;
		return;
	}
	if (wybor > 1) {
		Menadzer::wyswietlAsortyment();
		string tekst = (wybor == 2) ? "usun¹æ" : "edytowaæ";
		cout << "Podaj ID produktu, który chcesz " << tekst << ": ";
		cin >> produktID;
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
	string miesiace[] = { "styczniu", "lutym", "marcu", "kwietniu", "maju", "czerwcu", "lipcu", "sierpniu", "wrzeœniu", "paŸdzierniku", "listopadzie", "grudniu" };
	int aktualnyMiesiac, aktualnyRok;
	time_t teraz = time(0);
	tm* ltm = localtime(&teraz);
	aktualnyMiesiac = 1 + ltm->tm_mon;
	aktualnyRok = 1900 + ltm->tm_year;
	cout << "Raport sprzeda¿y w " << miesiace[aktualnyMiesiac - 2] << " " << to_string(aktualnyRok) << ":" << endl;
	select = "select a.ID, a.nazwa, sum(s.ilosc) as sprzedane_ilosc, sum(s.ilosc * a.cena) as przychod from sprzedaze s join asortyment a on s.id_produktu = a.ID join transakcje t on s.id_transakcji = t.id_transakcji where MONTH(t.data_transakcji) = " + to_string(aktualnyMiesiac - 1) + " and YEAR(t.data_transakcji) = " + to_string(aktualnyRok) + " group by a.ID, a.nazwa;";
	kwerenda->executeQuery(select);
	sql::ResultSet* wynik = kwerenda->executeQuery(select);
	if (wynik->rowsCount() == 0)
	{
		cout << "Brak sprzeda¿y w podanym okresie." << endl;
		delete wynik;
		delete kwerenda;
		return;
	}
	while (wynik->next()) {
		cout << "ID produktu: " << wynik->getInt("ID") << ", nazwa: " << wynik->getString("nazwa") << ", sprzedana iloœæ: " << wynik->getInt("sprzedane_ilosc") << ", przychód: " << wynik->getDouble("przychod") << " z³" << endl;
	}
	select2 = "select sum(s.ilosc * a.cena) as laczny_przychod from sprzedaze s join asortyment a on s.id_produktu = a.ID join transakcje t on s.id_transakcji = t.id_transakcji where MONTH(t.data_transakcji) = " + to_string(aktualnyMiesiac - 1) + " and YEAR(t.data_transakcji) = " + to_string(aktualnyRok) + ";";
	sql::ResultSet* wynik2 = kwerenda->executeQuery(select2);
	if (wynik2->next()) {
		cout << endl << "£¹czny przychód w zesz³ym miesi¹cu: " << wynik2->getDouble("laczny_przychod") << " z³" << endl;
	}
	delete wynik;
	delete wynik2;
	delete kwerenda;
}

void Menadzer::dodajProdukt() {
	string nazwa, kategoria, insert;
	double cena;
	int stanMagazynowy;
	cout << "Podaj nazwê nowego produktu: ";
	getline(cin >> ws, nazwa);
	cout << "Podaj kategoriê nowego produktu: ";
	getline(cin >> ws, kategoria);
	cout << "Podaj cenê nowego produktu: ";
	cin >> cena;
	if (cin.fail() || cena < 0) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Nieprawid³owe dane." << endl;
		return;
	}
	string cena2 = to_string(cena).replace(to_string(cena).find(','), 1, ".");
	cout << "Podaj stan magazynowy nowego produktu: ";
	cin >> stanMagazynowy;
	if (cin.fail() || stanMagazynowy < 0) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Nieprawid³owe dane." << endl;
		return;
	}
	sql::Statement* kwerenda;
	kwerenda = polaczenie->createStatement();
	insert = "insert into asortyment values (null, \"" + nazwa + "\", \"" + kategoria + "\", " + cena2 + ", " + to_string(stanMagazynowy) + ");";
	kwerenda->execute(insert);
	if (kwerenda->getUpdateCount() > 0) {
		cout << "Produkt dodany pomyœlnie." << endl;
	} else {
		cout << "Wyst¹pi³ b³¹d podczas dodawania produktu." << endl;
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
		cout << "Produkt o podanym ID nie istnieje." << endl;
		delete wynik;
		delete kwerenda;
		return;
	}
	deleteQuery = "delete from asortyment where ID = " + to_string(produktID) + ";";
	kwerenda->execute(deleteQuery);
	if (kwerenda->getUpdateCount() > 0) {
		cout << "Produkt usuniêty pomyœlnie." << endl;
	} else {
		cout << "Wyst¹pi³ b³¹d podczas usuwania produktu." << endl;
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
		cout << "Produkt o podanym ID nie istnieje." << endl;
		delete wynik;
		delete kwerenda;
		return;
	}
	cout << "Co chcesz edytowaæ?" << endl;
	cout << "--> 1 - Nazwê produktu" << endl;
	cout << "--> 2 - Kategoriê produktu" << endl;
	cout << "--> 3 - Cenê produktu" << endl;
	cout << "--> 4 - Stan magazynowy produktu" << endl;
	int wybor;
	cin >> wybor;
	if (cin.fail() || wybor < 1 || wybor > 4) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Nieprawid³owe dane." << endl;
		delete wynik;
		delete kwerenda;
		return;
	}
	cout << "Podaj now¹ wartoœæ: ";
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
				cout << "Nieprawid³owe dane." << endl;
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
				cout << "Nieprawid³owe dane." << endl;
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
		cout << "Dane produktu zaktualizowane pomyœlnie." << endl;
	} else {
		cout << "Wyst¹pi³ b³¹d podczas aktualizacji danych produktu." << endl;
	}
	delete kwerenda;
	delete wynik;
}