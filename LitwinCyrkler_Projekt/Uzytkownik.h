#ifndef UZYTKOWNIK_H
#define UZYTKOWNIK_H

#include <string>

using namespace std;

class Uzytkownik {
private:
	int id;
	std::string imie;
	std::string nazwisko;
public:
	Uzytkownik(int id_, std::string imie_, std::string nazwisko_);
};

#endif