#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include <string>
#include "Pracownik.h"

using namespace std;

class Administrator : public Pracownik {
public:
	Administrator(int id_, std::string imie_, std::string nazwisko_, double stawka_, int liczba_);
	bool interfejsUzytkownika() override;
	void dodajUzytkownika();
	void usunUzytkownika();
};

#endif