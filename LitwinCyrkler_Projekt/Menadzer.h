#ifndef MENADZER_H
#define MENADZER_H

#include <string>
#include "Pracownik.h"
#include <cppconn/driver.h>

using namespace std;

class Menadzer : public Pracownik {
public:
	Menadzer(int id_, std::string imie_, std::string nazwisko_, double stawka_, int liczba_, sql::Connection* con);
	bool interfejsUzytkownika() override;
	void wyswietlPracownikow();
	void wyswietlKlientow();
	void edytujAsortyment();
	void generujRaportSprzedazy();
	void dodajProdukt();
	void usunProdukt(int produktID);
	void modyfikujProdukt(int produktID);
	void edytujPracownika();
	void wyswietlAsortyment();
};

#endif