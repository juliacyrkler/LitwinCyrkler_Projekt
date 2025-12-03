#ifndef UZYTKOWNIK_H
#define UZYTKOWNIK_H

#include <string>
#include <cppconn/driver.h>

using namespace std;

class Uzytkownik {
protected:
	int id;
	string imie;
	string nazwisko;
	sql::Connection* polaczenie;
public:
	Uzytkownik(int id_, string imie_, string nazwisko_, sql::Connection* con);
	~Uzytkownik();
	virtual bool interfejsUzytkownika();
	string zwrocImie();
	void clearConsole();
};

#endif