#ifndef KLIENT_H
#define KLIENT_H

#include <string>
#include "Uzytkownik.h"

using namespace std;

class Klient : public Uzytkownik {
public:
	Klient(int id_, std::string imie_, std::string nazwisko_);
};

#endif