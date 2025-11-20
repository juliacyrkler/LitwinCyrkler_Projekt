#ifndef PRACOWNIK_H
#define PRACOWNIK_H

#include <string>
#include "Uzytkownik.h"

using namespace std;

class Pracownik : public Uzytkownik {
public:
	Pracownik(int id_, std::string imie_, std::string nazwisko_);
	void interfejsUzytkownika() override;
};

#endif