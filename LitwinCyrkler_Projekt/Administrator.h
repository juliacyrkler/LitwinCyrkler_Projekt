#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include <string>
#include "Uzytkownik.h"

using namespace std;

class Administrator : public Uzytkownik {
public:
	Administrator(int id_, std::string imie_, std::string nazwisko_);
};

#endif