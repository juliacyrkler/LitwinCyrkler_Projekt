#include <iostream>
#include <string>
#include "Produkt.h"

using namespace std;

Produkt::Produkt(int id, string nazwa, string kategoria, float cena, int ilosc) {
	this->idProduktu = id;
	this->nazwaProduktu = nazwa;
	this->kategoriaProduktu = kategoria;
	this->cenaProduktu = cena;
	this->iloscWKoszyku = ilosc;
}

float Produkt::zwrocCene() {
	return this->cenaProduktu*this->iloscWKoszyku;
}
string Produkt::zwrocNazwe() {
	return this->nazwaProduktu;
}
int Produkt::zwrocID() {
	return this->idProduktu;
}
int Produkt::zwrociloscWKoszyku() {
	return this->iloscWKoszyku;
}
void Produkt::NowaIloscWKoszyku(int nowaIlosc) {
	this->iloscWKoszyku = nowaIlosc;
}

void Produkt::wyswietlProdukt() {
	cout << "Id. "<<this->idProduktu << " -- " << this->nazwaProduktu << " -- " << this->cenaProduktu << " pln (x" << this->iloscWKoszyku << ")" << endl;
}