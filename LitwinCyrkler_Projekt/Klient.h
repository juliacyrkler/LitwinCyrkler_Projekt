#ifndef KLIENT_H
#define KLIENT_H

#include <string>
#include "Uzytkownik.h"
#include <cppconn/driver.h>

using namespace std;

class Klient : public Uzytkownik {
private:
	int punktyLojalnosciowe;
	double srodkiNaKoncie;
public:
	Klient(int id_, std::string imie_, std::string nazwisko_, int punkty_, double srodki_, sql::Connection* con);
	bool interfejsUzytkownika() override;
	void pokazStanKonta();
	void wyswietlProdukty();
	void pokazKoszyk();
	void wplacSrodki();
};

#endif