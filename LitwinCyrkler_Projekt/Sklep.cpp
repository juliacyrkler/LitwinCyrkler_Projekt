#include <iostream>
#include <string>
#include "Sklep.h"

using namespace std;

Sklep::Sklep() {
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
			if (zaloguj(login, haslo)) {
				uzytkownik = new Klient(1, "Jan", "Kowalski", 0, 0); //do zmiany, uytkownik tworzony na postawie danych z bazy
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

bool Sklep::zaloguj(string login, string haslo) {
	//sprawdzenie czy login i haslo znajduja sie w bazie danych, zwrocenie odpowiedniej wartosci i utworzenie obiektu uzytkownika
	return true;
}

bool Sklep::utworzKonto(string imie, string nazwisko, string login, string haslo) {
	//dodanie nowego uzytkownika do bazy danych, zwrocenie odpowiedniej wartosci
	return true;
}

void Sklep::wczytajProdukty() {
	//wczytanie produktow z bazy danych do wektora produkty
}