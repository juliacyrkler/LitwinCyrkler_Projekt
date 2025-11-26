#ifndef MENADZER_H
#define MENADZER_H

#include <string>
#include "Pracownik.h"

using namespace std;

class Menadzer : public Pracownik {
public:
	Menadzer(int id_, std::string imie_, std::string nazwisko_, double stawka_, int liczba_);
	void interfejsUzytkownika() override;
};

#endif