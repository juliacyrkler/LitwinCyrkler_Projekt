#include <iostream>
#include <string>
#include "Pracownik.h"

using namespace std;

Pracownik::Pracownik(int id_, std::string imie_, std::string nazwisko_, double stawka_, int liczba_) : Uzytkownik(id_, imie_, nazwisko_) {
	this->stawkaGodzinowa = stawka_;
	this->liczbaGodzin = liczba_;
}

double Pracownik::obliczWynagrodzenie() {
	return this->stawkaGodzinowa * this->liczbaGodzin;
}

double Pracownik::zwrocStawkeGodzinowa() {
	return this->stawkaGodzinowa;
}

void Pracownik::ustawStawkeGodzinowa(double stawka) {
	this->stawkaGodzinowa = stawka;
}