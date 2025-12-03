#ifndef PRODUKT_H
#define PRODUKT_H

#include <string>

using namespace std;

class Produkt {
private:
    string nazwaProduktu;
    string kategoriaProduktu;
    float cenaProduktu;
    int stanMagazynowy;
public:
    Produkt(string nazwa, string kategoria, float cena, int stan);
    void aktualizujStanMagazynowy(int nowyStanMagazynowy);
    void aktualizujCene(float nowaCena);
    string zwrocNazwe();
    float zwrocCene();
    int zwrocStanMagazynowy();
    void wyswietlProdukt();
};

#endif