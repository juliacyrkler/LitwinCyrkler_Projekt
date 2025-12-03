#ifndef KLIENT_H
#define KLIENT_H

#include <string>
#include <vector>
#include "Uzytkownik.h"
#include "Produkt.h"
#include <cppconn/driver.h>

using namespace std;

class Klient : public Uzytkownik {
private:
	int punktyLojalnosciowe;
	double srodkiNaKoncie;
	vector<Produkt> koszyk;
public:
	Klient(int id_, std::string imie_, std::string nazwisko_, int punkty_, double srodki_, sql::Connection* con);
	bool interfejsUzytkownika() override;
	void pokazStanKonta();
	void wyswietlProdukty();
	void pokazKoszyk();
	void wplacSrodki();
};

#endif