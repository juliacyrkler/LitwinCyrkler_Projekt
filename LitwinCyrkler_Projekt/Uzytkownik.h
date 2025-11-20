#ifndef UZYTKOWNIK_H
#define UZYTKOWNIK_H

#include <string>

using namespace std;

class Uzytkownik {
private:
	int id;
	string imie;
	string nazwisko;
public:
	Uzytkownik(int id_, string imie_, string nazwisko_);
	virtual void interfejsUzytkownika();
};

#endif