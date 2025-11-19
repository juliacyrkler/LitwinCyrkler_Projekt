#ifndef SKLEP_H
#define SKLEP_H

#include <string>
#include <vector>
#include "Produkt.h"

using namespace std;

class Sklep {
private:
    vector <Produkt> produkty;
public:
    Sklep();
	bool zaloguj(string login, string haslo);
};

#endif