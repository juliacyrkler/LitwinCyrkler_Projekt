#ifndef SKLEP_H
#define SKLEP_H

#include <string>
#include <vector>
#include "Administrator.h"
#include "Klient.h"
#include "Pracownik.h"
#include "Menadzer.h"
#include "Produkt.h"
#include "Uzytkownik.h"
#include <cppconn/driver.h>

using namespace std;

class Sklep {
private:
    Uzytkownik* uzytkownik;
    vector <Produkt> produkty;
	sql::Connection* polaczenie;
public:
    Sklep(sql::Connection *con);
	~Sklep();
	void ekranPowitalny();
	bool czyUserIstnieje(string login, string haslo);
	Uzytkownik* zaloguj(string login, string haslo);
	bool utworzKonto(string imie, string nazwisko, string login, string haslo);
	void wczytajProdukty();
};

#endif