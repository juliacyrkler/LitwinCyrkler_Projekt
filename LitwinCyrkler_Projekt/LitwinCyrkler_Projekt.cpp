#include <iostream>
#include <locale.h>
#include <vector>

using namespace std;

//dane wiadomo można w pliku zapisywać i z niego odczytywać ale imo do przemyślenia zaciąganie danych z bazy sql (telicki chyba mówił że można spróbować)
//klasy fajnie by było potem jako osobne pliki zapisywać żeby móc nad nimi w dwójke pracować bez przeszkadzania sobie
//pytanie jak robimy płatność - czy dodajemy do klienta jakieś pole z kwotą na koncie czy jak

class Product {
private:
    string productName;
    string productCategory; //jeśli by było np jakieś filtrowanie produktów po kategoriach przy kupowaniu??
    float productPrice;
    int stockStatus;
public:
    Product(string name, string category, float price, int stock) {
        this->productCategory = name;
        this->productCategory = category;
        this->productPrice = price;
        this->stockStatus = stock;
    }
    void updateStock(int newStockStatus) {
        this->stockStatus = newStockStatus;
        //chyba ładniej by było przekazywać do funkcji np ile sztuk produktu kupiono i obliczać nowy stock w funkcji + np zrobić dodatkową funkcję do restocku ale idk więc wstępnie tak XD
    }
    void updatePrice(float newPrice) {
        this->productPrice = newPrice;
    }
    float getPrice() {
        return this->productPrice;
    }
    int getStockStatus() {
        return this->stockStatus;
    }
    //te get i update możnaby zrobić też do innych zmiennych ale idk czy byłyby potrzebne?
    void showProduct() {
        cout << this->productName << "\t" << this->productPrice << endl;
        //do użycia np przy wypisywaniu produktów do kupienia, to co jest wypisywane i tak pewnie do zmiany
    }
};

class User {
private:
    string username;
    string password;
public:
    User(string username_, string password_) {
        this->username = username_;
        this->password = password_;
    }
    bool logIn(string username, string password) {
        //sprawdzenie, czy podany username istnieje w bazie/pliku, jeśli tak - sprawdzenie czy hasło się zgadza
        //login successful - zwraca true, w przeciwnym razie false
        return false;
    }
};

class Admin : User {
public:
    Admin(string username_, string password_) : User(username_, password_) {}
};

class Client : User {
private:
    vector <Product> shoppingKart;
public:
    Client(string username_, string password_) : User(username_, password_) {}
};

class Employee : User {
public:
    Employee(string username_, string password_) : User(username_, password_) {}
};

//admin, client, employee etc można zrobić jako klasy dziedziczne/ewentualnie dodając userType czy coś takiego do User i wszystkie funkcje pisząc tam ze sprawdzeniem UserType???
//admin funkcja tworzenia i usuwania użytkowników, client wiadomo kupowanie itd,
//employee dodawanie i usuwanie produktów, updateowanie stocku itd, może coś w stylu wyświetlania historii transakcji czy czegoś takiego?
//może przy uruchomieniu aplikacji wyświetla się logowanie + możliwość utworzenia konta (tylko z uprawnieniami klienta)??

class Shop {
private:
    vector <Product> products;
public:
    Shop() {
        cout << "Hello world";
    }
};

int main()
{
    setlocale(LC_ALL, "");

    Shop* zabka = new Shop();

    return 0;
}
