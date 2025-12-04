#ifndef KASJER_H
#define KASJER_H

#include <string>
#include "Pracownik.h"
#include <cppconn/driver.h>
#include "Produkt.h"

using namespace std;

class Kasjer : public Pracownik {
private:
	vector <Produkt> koszyk;
public:
	Kasjer(int id_, std::string imie_, std::string nazwisko_, double stawka_, int liczba_, sql::Connection* con);
	bool interfejsUzytkownika() override;
	void wyswietlKlientow();
	void dodajKlienta();
	void obsluzKlienta();
	void wyswietlProdukty();
	void dodajDoKoszyka();
	void usunZKoszyka();
	void wyswietlKoszyk();
	bool przeprowadzTransakcje();
};

#endif