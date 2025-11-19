#ifndef MENADZER_H
#define MENADZER_H

#include <string>
#include "Uzytkownik.h"

using namespace std;

class Menadzer : public Uzytkownik {
public:
	Menadzer(int id_, std::string imie_, std::string nazwisko_);
};

#endif