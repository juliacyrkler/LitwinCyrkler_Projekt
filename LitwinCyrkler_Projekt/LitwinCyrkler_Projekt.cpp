#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/statement.h>
#include <mysql_connection.h>
#include <mysql_driver.h>
#include <iostream>
#include <locale.h>
#include <vector>
#include <Windows.h>
#include "Sklep.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "pl_PL.UTF-8");
    std::locale::global(std::locale("pl_PL.UTF-8"));
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    try {
        sql::mysql::MySQL_Driver* driver;
        sql::Connection* con;

        driver = sql::mysql::get_mysql_driver_instance();
		con = driver->connect("tcp://127.0.0.1:3306", "root", ""); //Zmienić hasło jeśli jest ustawione
        con->setSchema("sklep");

        sql::Statement* stmt = con->createStatement();
        stmt->execute("SET NAMES utf8mb4");
        delete stmt;

        Sklep* zabka = new Sklep(con);

        delete con;
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQL Error: " << e.what() << std::endl;
    }

    return 0;
}
