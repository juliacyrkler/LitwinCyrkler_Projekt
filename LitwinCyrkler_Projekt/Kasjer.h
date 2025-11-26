#ifndef KASJER_H
#define KASJER_H

#include <string>
#include "Pracownik.h"

using namespace std;

class Kasjer : public Pracownik {
public:
	Kasjer(int id_, std::string imie_, std::string nazwisko_, double stawka_, int liczba_);
	bool interfejsUzytkownika() override;
};

#endif