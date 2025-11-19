#include <iostream>
#include <locale.h>
#include <vector>
#include "Administrator.h"
#include "Klient.h"
#include "Pracownik.h"
#include "Menadzer.h"
#include "Produkt.h"
#include "Sklep.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "");

    Sklep* zabka = new Sklep();

	//Administrator user(1, "Jan", "Kowalski");

    return 0;
}
