#include <iostream>
#include <string>
#include "Produkt.h"

using namespace std;

Produkt::Produkt(string nazwa, string kategoria, float cena, int stan) {
	this->nazwaProduktu = nazwa;
	this->kategoriaProduktu = kategoria;
	this->cenaProduktu = cena;
	this->stanMagazynowy = stan;
}

void Produkt::aktualizujStanMagazynowy(int nowyStanMagazynowy) {
	this->stanMagazynowy = nowyStanMagazynowy;
}

void Produkt::aktualizujCene(float nowaCena) {
	this->cenaProduktu = nowaCena;
}

float Produkt::zwrocCene() {
	return this->cenaProduktu;
}
string Produkt::zwrocNazwe() {
	return this->nazwaProduktu;
}

int Produkt::zwrocStanMagazynowy() {
	return this->stanMagazynowy;
}

void Produkt::wyswietlProdukt() {
	cout << this->nazwaProduktu << endl;
	cout << "Kategoria: " << this->kategoriaProduktu << endl;
	cout << "Cena: " << this->cenaProduktu << " z³" << endl;
	cout << "Stan magazynowy: " << this->stanMagazynowy << endl;
}