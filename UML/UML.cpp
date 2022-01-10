#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <cstdlib>
#include <conio.h>
#include <cctype>
#include <stdlib.h>
using namespace std;
fstream zapis;
static int numer_klienta = 0;
static int numer_restauracji = 0;
static int numer_menu = 0;
static int numer_zamowienia = 0;

void czy_pliki_zapisu_istnieja()
{
    zapis.open("Restauracja.txt"); if (zapis.good() == false) { zapis.open("Restauracja.txt", ios::out); } zapis.close();
    zapis.open("Klient.txt"); if (zapis.good() == false) { zapis.open("Klient.txt", ios::out); } zapis.close();
}

class Klient
{
public:
    string imie, nazwisko, login, haslo;
    Klient() : imie("NULL") { }
    ~Klient() {}
    void wyswietl_dane()
    {
        cout << "Imie: " << imie << "\nNazwisko: " << nazwisko << "\nLogin: " << login << "\nHaslo: " << haslo;
    }
    void Nowy_Klient(Klient* klient)
    {
    powrot:
        system("cls");
        cout << "WPROWADZ DANE ZATWIERDZAJAC JE KLAWISZEM 'ENTER'\n";
        cout << "Podaj imie: "; cin >> imie;
        cout << "\nPodaj nazwisko: "; cin >> nazwisko;
        cout << "\nWprowadz login: "; cin >> login;
        cout << "\nWprowadz haslo: "; cin >> haslo;

        system("cls");
        cout << "Jesli sie zgadza daj TAK, a jesli nie to NIE - ponowne wprowadzanie danych\n";
        wyswietl_dane();
        cout << "\nZgadza sie?\n1. TAK\n2. NIE\n3. POWROT DO MENU\n";
        switch (_getch())
        {
        case '1':
        {
            for (int i = 0; i < numer_klienta; i++)
            {
                if (login == klient[i].login)
                {
                    cout << "\nLogin jest juz zajety!\n";
                    system("pause");
                    goto powrot;
                }
            }
            cout << "\nRejestracja udana!\n"; system("pause"); system("cls");
            numer_klienta++;
        }
        break;
        case '2': { goto powrot; } break;
        case '3': { return; } break;
        }
    }
    void zalogowany(int nr_klienta)
    {
        cout << "Klient: " << imie << " " << nazwisko << endl;


    }
};

void zapisywanie_klient(Klient* obiekt, string miejsce_zapisu)
{
    zapis.open(miejsce_zapisu, ios::ate | ios::out | ios::trunc);
    if (zapis.good() == false) { cout << "\n\t\tBlad zapisu pliku!!!\n"; Sleep(2000); }
    for (int i = 1;; i++)
    {
        if (obiekt[i].imie == "NULL") { break; }
        zapis << obiekt[i].imie << endl;
        zapis << obiekt[i].nazwisko << endl;
        zapis << obiekt[i].login << endl;
        zapis << obiekt[i].haslo << endl;
    }
    zapis.close();
}

void wczytywanie_klient(Klient* obiekt, string miejsce_zapisu)
{
    zapis.open(miejsce_zapisu, ios::in);
    if (zapis.good() == false) { cout << "\n\t\tBlad odczytu pliku!!!\n"; Sleep(2000); }
    int nr_linii = 1;
    int i = 1;
    int i_pom;
    string linia;
    while (getline(zapis, linia))
    {
        i_pom = (i - 1) * 4;
        if (nr_linii == 1 + i_pom)    obiekt[i].imie = linia;
        if (nr_linii == 2 + i_pom)    obiekt[i].nazwisko = linia;
        if (nr_linii == 3 + i_pom)    obiekt[i].login = linia;
        if (nr_linii == 4 + i_pom) { obiekt[i].haslo = linia; i++; numer_klienta++; }

        nr_linii++;
    }

    zapis.close();
}

int nr_klienta(Klient* obiekt)
{
    string login, haslo;
    cout << "Wprowadz login: "; cin >> login;
    cout << "Wprowadz haslo: "; cin >> haslo;
    for (int i = 0; i < numer_klienta; i++)
    {
        if (login == obiekt[i].login && haslo == obiekt[i].haslo)
        {
            cout << "\nLogowanie powiodlo sie!\n"; Sleep(1500); system("cls");
            return i;
        }

    }
    cout << "\nLogowanie nie powiodlo sie!\n"; Sleep(1500); system("cls");
    return -1;
}

class Restauracja
{
public:
    string nazwa, opinia, lokalizacja;
    Restauracja() :nazwa("NULL") {}
    void wyswietl()
    {
        cout << nazwa << "\nOpinia: " << opinia << "\nLokalizacja: " << lokalizacja << endl << endl;
    }
};

void wczytywanie_restauracja(Restauracja* obiekt, string miejsce_zapisu)
{
    zapis.open(miejsce_zapisu, ios::in);
    if (zapis.good() == false) { cout << "\n\t\tBlad odczytu pliku!!!\n"; Sleep(2000); }
    int nr_linii = 1;
    int i = 1;
    int i_pom;
    string linia;
    while (getline(zapis, linia))
    {
        i_pom = (i - 1) * 3;
        if (nr_linii == 1 + i_pom)    obiekt[i].nazwa = linia;
        if (nr_linii == 2 + i_pom)    obiekt[i].opinia = linia;
        if (nr_linii == 3 + i_pom) { obiekt[i].lokalizacja = linia; i++; numer_restauracji++; }

        nr_linii++;
    }

    zapis.close();
}

class Menu
{
public:
    int numer[20];
    string nazwa[20];
    float cena[20];
    Menu() { for (int i = 1; i < 20; i++) { nazwa[i] = "NULL"; } }
    void wyswietl()
    {
        for (int j = 1; nazwa[j] != "NULL"; j++)
            cout << numer[j] << ". " << nazwa[j] << " - " << cena[j] << " zl" << endl;
    }

};

void wczytywanie_menu(Menu& obiekt, string miejsce_zapisu)
{
    zapis.open(miejsce_zapisu, ios::in);
    if (zapis.good() == false) { cout << "\n\t\tBlad odczytu pliku!!!\n"; Sleep(2000); }
    int nr_linii = 1;
    int i = 1;
    int i_pom;
    string linia;
    while (getline(zapis, linia))
    {
        i_pom = (i - 1) * 2;
        if (nr_linii == 1 + i_pom) { obiekt.numer[i] = i; obiekt.nazwa[i] = linia; }
        if (nr_linii == 2 + i_pom) { obiekt.cena[i] = stof(linia); i++; }

        nr_linii++;
    }
    numer_menu++;
    zapis.close();
}

class Zamowienie : public Klient, public Restauracja
{
public:
    int numer;
    float kwota;
    Klient zamawiajacy;
    Restauracja restauracja;
    Zamowienie() { numer = 0; }
    Zamowienie(Klient zamawiajacy_obj, Restauracja restauracja_obj, float kwota_pom) : zamawiajacy(zamawiajacy_obj), restauracja(restauracja_obj), kwota(kwota_pom)
    {
        numer_zamowienia++; numer = numer_zamowienia;
    }
    void przypisz(Klient zamawiajacy_obj, Restauracja restauracja_obj, float kwota_pom)
    {
        imie = zamawiajacy_obj.imie; nazwa = restauracja_obj.nazwa; kwota = kwota_pom; nazwisko = zamawiajacy_obj.nazwisko;
        numer_zamowienia++; numer = numer_zamowienia;
    }
    void wyswietl()
    {
        cout << "\nZamawiajacy: " << imie << " " << nazwisko << endl;
        cout << "W restauracji: " << nazwa << "\nNa kwote: " << kwota << endl;
    }
};

void zapisywanie_zamowienie(Zamowienie* obiekt, string miejsce_zapisu)
{
    zapis.open(miejsce_zapisu, ios::ate | ios::out | ios::trunc);
    if (zapis.good() == false) { cout << "\n\t\tBlad zapisu pliku!!!\n"; Sleep(2000); }
    for (int i = 1;; i++)
    {
        if (obiekt[i].numer == 0) { break; }
        zapis << obiekt[i].numer << endl;
        zapis << obiekt[i].imie << endl;
        zapis << obiekt[i].nazwisko << endl;
        zapis << obiekt[i].nazwa << endl;
        zapis << obiekt[i].kwota << endl;
    }
    zapis.close();
}

void wczytywanie_zamowienie(Zamowienie* obiekt, string miejsce_zapisu)
{
    zapis.open(miejsce_zapisu, ios::in);
    if (zapis.good() == false) { cout << "\n\t\tBlad odczytu pliku!!!\n"; Sleep(2000); }
    int nr_linii = 1;
    int i = 1;
    int i_pom;
    string linia;
    while (getline(zapis, linia))
    {
        i_pom = (i - 1) * 5;
        if (nr_linii == 1 + i_pom)    obiekt[i].numer = stof(linia);
        if (nr_linii == 2 + i_pom)    obiekt[i].imie = linia;
        if (nr_linii == 3 + i_pom)    obiekt[i].nazwisko = linia;
        if (nr_linii == 4 + i_pom)    obiekt[i].nazwa = linia;
        if (nr_linii == 5 + i_pom) { obiekt[i].kwota = stof(linia); i++; numer_zamowienia++; }

        nr_linii++;
    }

    zapis.close();
}

int main()
{


    return 0;
}