#ifndef SKLEP_H
#define SKLEP_H

#include <string>
#include <vector>
#include "Produkt.h"
#include "Uzytkownik.h"

using namespace std;

class Sklep {
private:
    Uzytkownik* uzytkownik;
    vector <Produkt> produkty;
public:
    Sklep();
	void ekranPowitalny();
	bool zaloguj(string login, string haslo);
	bool utworzKonto(string imie, string nazwisko, string login, string haslo);
};

#endif