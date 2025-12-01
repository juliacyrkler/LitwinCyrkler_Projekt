#include <iostream>
#include <stdlib.h>
#include <string>
#include "Administrator.h"
#include <cppconn/statement.h>

using namespace std;

Administrator::Administrator(int id_, std::string imie_, std::string nazwisko_, double stawka_, int liczba_, sql::Connection* con) : Pracownik(id_, imie_, nazwisko_, stawka_, liczba_, con) {}

bool Administrator::interfejsUzytkownika() {
	cout << endl << "Witaj, " << this->zwrocImie() << "! Jesteœ zalogowany jako administrator.";

	bool wyloguj = false;
	while (!wyloguj) {
		cout << endl << "Co chcesz zrobiæ?" << endl;
		cout << "--> 1 - Dodaj nowego u¿ytkownika" << endl;
		cout << "--> 2 - Usuñ u¿ytkownika" << endl;
		cout << "--> 3 - Wyloguj siê" << endl;
		int wybor;
		cin >> wybor;

		switch (wybor) {
		case 1:
			this->dodajUzytkownika();
			break;
		case 2:
			this->usunUzytkownika();
			break;
		case 3:
			wyloguj = true;
			system("cls");
			break;
		default:
			break;
		}
	}
	return true;
}

void Administrator::dodajUzytkownika() {
	int typ, liczba;
	double stawka;
	string imie, nazwisko, login, haslo, stanowisko, id, insert1, insert2;
	cout << "Podaj typ nowego u¿ytkownika (1 - klient, 2 - kasjer, 3 - menad¿er, 4 - administrator): ";
	cin >> typ;
	if (cin.fail() || typ < 1 || typ > 4) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Nieprawid³owy typ u¿ytkownika." << endl;
		return;
	}
	cout << "Podaj imiê nowego u¿ytkownika: ";
	cin >> imie;
	cout << "Podaj nazwisko nowego u¿ytkownika: ";
	cin >> nazwisko;
	cout << "Podaj login nowego u¿ytkownika: ";
	cin >> login;
	cout << "Podaj has³o nowego u¿ytkownika: ";
	cin >> haslo;

	if (typ > 1) {
		cout << "Podaj stawkê godzinow¹ nowego pracownika: ";
		cin >> stawka;
		if (cin.fail() || stawka < 30.5) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Nieprawid³owe dane." << endl;
			return;
		}
		cout << "Podaj liczbê godzin pracy na miesi¹c nowego pracownika: ";
		cin >> liczba;
		if (cin.fail() || liczba < 0) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Nieprawid³owe dane." << endl;
			return;
		}

		stanowisko = (typ == 2) ? "kasjer" : (typ == 3) ? "menadzer" : "administrator";
	}

	sql::Statement* kwerenda;
	kwerenda = polaczenie->createStatement();
	string loginSelect = "select * from users where login = \"" + login + "\";";
	sql::ResultSet* wynik = kwerenda->executeQuery(loginSelect);
	if (wynik->next()) {
		cout << "U¿ytkownik o podanym loginie ju¿ istnieje." << endl;
		delete wynik;
		delete kwerenda;
		return;
	}
	insert1 = "insert into users values(null, \"" + login + "\", \"" + haslo + "\");";
	kwerenda->execute(insert1);
	string select = "select max(id) as max_id from users;";
	wynik = kwerenda->executeQuery(select);
	if (wynik->next()) {
		id = wynik->getString("max_id");
	}
	if (typ > 1)  insert2 = "insert into pracownicy values(" + id + ", null, \"" + imie + "\", \"" + nazwisko + "\", \"" + stanowisko + "\", " + to_string(stawka) + ", " + to_string(liczba) + ");";
	else insert2 = "insert into klienci values(" + id + ", null, \"" + imie + "\", \"" + nazwisko + "\", 0, 0);";
	kwerenda->execute(insert2);
	delete wynik;
	delete kwerenda;
}

void Administrator::usunUzytkownika() {
	cout << "--> 1 - Usuñ pracownika" << endl;
	cout << "--> 2 - Usuñ klienta" << endl;
	int wybor;
	cin >> wybor;
	if (cin.fail() || (wybor != 1 && wybor != 2)) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Podano nieprawid³owe dane." << endl;
		return;
	}
	sql::Statement* kwerenda;
	kwerenda = polaczenie->createStatement();
	string delete1, delete2, select;
	string tabela = (wybor == 1) ? "pracownicy" : "klienci";
	cout << "Lista u¿ytkowników do usuniêcia:" << endl;
	select = (wybor == 1) ? "select user_id, imie, nazwisko, typ_pracownika from pracownicy;" : "select user_id, imie, nazwisko from klienci;";
	sql::ResultSet* wynik = kwerenda->executeQuery(select);
	while (wynik->next()) {
		cout << "ID: " << wynik->getInt("user_id") << ". " << wynik->getString("imie") << " " << wynik->getString("nazwisko");
		if (wybor == 1) cout << " - " << wynik->getString("typ_pracownika");
		cout << endl;
	}
	int id;
	cout << "Podaj ID u¿ytkownika do usuniêcia: ";
	cin >> id;
	if (cin.fail() || id < 1) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Podano nieprawid³owe dane." << endl;
		return;
	}
	delete1 = "delete from " + tabela + " where user_id = " + to_string(id) + ";";
	delete2 = "delete from users where id = " + to_string(id) + ";";
	kwerenda->execute(delete1);
	if (kwerenda->getUpdateCount() > 0) {
		kwerenda->execute(delete2);
		cout << "U¿ytkownik zosta³ usuniêty." << endl;
	} else {
		cout << "Nie znaleziono u¿ytkownika o podanym ID." << endl;
	}
	delete kwerenda;
	delete wynik;
}
