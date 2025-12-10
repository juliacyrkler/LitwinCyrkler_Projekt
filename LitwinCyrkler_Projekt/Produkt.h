#ifndef PRODUKT_H
#define PRODUKT_H

#include <string>

using namespace std;

class Produkt {
private:
    int idProduktu;
    string nazwaProduktu;
    string kategoriaProduktu;
    float cenaProduktu;
    int iloscWKoszyku;
public:
    Produkt(int id, string nazwa, string kategoria, float cena, int ilosc);
    string zwrocNazwe();
    float zwrocCene();
    int zwrocID();
    int zwrociloscWKoszyku();
    void NowaIloscWKoszyku(int ilosc);
    void wyswietlProdukt();
};

#endif