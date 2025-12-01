#include <iostream>
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
	insert1 = "insert into users values(null, \"" + login + "\", \"" + haslo + "\");";
	kwerenda->execute(insert1);
	string select = "select max(id) as max_id from users;";
	sql::ResultSet* wynik = kwerenda->executeQuery(select);
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
	//wyœwietlenie wszystkch u¿ytkowników, wpisanie id u¿ytkownika do usuniêcia i usuniêcie go z bazy danych
}