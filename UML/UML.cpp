#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <cstdlib>
#include <conio.h>
#include <cctype>
#include <stdlib.h>
#include <ctype.h>
using namespace std;
static int numer_klienta = 0;
static int numer_restauracji = 0;
static int numer_menu = 0;
static int numer_zamowienia = 0;

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
    void nowy_klient(Klient* klient)//Funkcja tworzy nowy obiekt klient oraz wpisuje go na liste
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
        case '3': { imie = "NULL"; break; } break;
        default: { goto powrot; } break;
        }
    }
    int nr_klienta(Klient* obiekt)// Zwracanie numeru klienta o podanym loginie i hasle
    {
        string login, haslo;
        cout << "Wprowadz login: "; cin >> login;
        cout << "Wprowadz haslo: "; cin >> haslo;
        for (int i = 0; i <= numer_klienta; i++)
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
};

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

class Zamowienie
{
public:
    string imie, nazwa, nazwisko;
    int numer;
    float kwota;
    Zamowienie() { numer = 0; }
    void przypisz(Klient zamawiajacy_obj, Restauracja restauracja_obj, float kwota_pom)// przypisanie zamowienia do klienta
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

class Baza {
public:
    Klient* lista_klientow = new Klient[30];
    Restauracja* lista_restauracji = new Restauracja[30];
    Menu* menu_restauracji = new Menu[30];
    Zamowienie* lista_zamowien = new Zamowienie[30];
    fstream zapis;

    Baza() { }
    //Funkcje do obslugi danych z pilkow txt
    void czy_pliki_zapisu_istnieja()
    {
        zapis.open("Restauracja.txt"); if (zapis.good() == false) { zapis.open("Restauracja.txt", ios::out); } zapis.close();
        zapis.open("Klient.txt"); if (zapis.good() == false) { zapis.open("Klient.txt", ios::out); } zapis.close();
        zapis.open("Zamowienie.txt"); if (zapis.good() == false) { zapis.open("Zamowienie.txt", ios::out); } zapis.close();
        zapis.open("1.txt"); if (zapis.good() == false) { zapis.open("1.txt", ios::out); } zapis.close();
        zapis.open("2.txt"); if (zapis.good() == false) { zapis.open("2.txt", ios::out); } zapis.close();
        zapis.open("3.txt"); if (zapis.good() == false) { zapis.open("3.txt", ios::out); } zapis.close();
        zapis.open("4.txt"); if (zapis.good() == false) { zapis.open("4.txt", ios::out); } zapis.close();
        zapis.open("5.txt"); if (zapis.good() == false) { zapis.open("5.txt", ios::out); } zapis.close();
    }
    void wczytywanie_klient(string miejsce_zapisu)
    {
        zapis.open(miejsce_zapisu, ios::in);
        if (zapis.good() == false) { cout << "\n\t\tBlad odczytu pliku!!!\n"; Sleep(2000); }
        int nr_linii = 1;
        int i = 1;
        int i_pom;
        string linia;
        numer_klienta = 0;
        while (getline(zapis, linia))
        {
            i_pom = (i - 1) * 4;
            if (nr_linii == 1 + i_pom)    lista_klientow[i].imie = linia;
            if (nr_linii == 2 + i_pom)    lista_klientow[i].nazwisko = linia;
            if (nr_linii == 3 + i_pom)    lista_klientow[i].login = linia;
            if (nr_linii == 4 + i_pom) { lista_klientow[i].haslo = linia; i++; numer_klienta++; }

            nr_linii++;
        }

        zapis.close();
    }
    void zapisywanie_klient(string miejsce_zapisu)
    {
        zapis.open(miejsce_zapisu, ios::ate | ios::out | ios::trunc);
        if (zapis.good() == false) { cout << "\n\t\tBlad zapisu pliku!!!\n"; Sleep(2000); }
        for (int i = 1;; i++)
        {
            if (lista_klientow[i].imie == "NULL") { break; }
            zapis << lista_klientow[i].imie << endl;
            zapis << lista_klientow[i].nazwisko << endl;
            zapis << lista_klientow[i].login << endl;
            zapis << lista_klientow[i].haslo << endl;
        }
        zapis.close();
    }
    void wczytywanie_restauracja(string miejsce_zapisu)
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
            if (nr_linii == 1 + i_pom)    lista_restauracji[i].nazwa = linia;
            if (nr_linii == 2 + i_pom)    lista_restauracji[i].opinia = linia;
            if (nr_linii == 3 + i_pom) { lista_restauracji[i].lokalizacja = linia; i++; numer_restauracji++; }

            nr_linii++;
        }

        zapis.close();
    }
    void zapisywanie_zamowienie(string miejsce_zapisu)
    {
        zapis.open(miejsce_zapisu, ios::ate | ios::out | ios::trunc);
        if (zapis.good() == false) { cout << "\n\t\tBlad zapisu pliku!!!\n"; Sleep(2000); }
        for (int i = 1;; i++)
        {
            if (lista_zamowien[i].numer == 0) { break; }
            zapis << lista_zamowien[i].numer << endl;
            zapis << lista_zamowien[i].imie << endl;
            zapis << lista_zamowien[i].nazwisko << endl;
            zapis << lista_zamowien[i].nazwa << endl;
            zapis << lista_zamowien[i].kwota << endl;
        }
        zapis.close();
    }
    void wczytywanie_zamowienie(string miejsce_zapisu)
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
            if (nr_linii == 1 + i_pom)    lista_zamowien[i].numer = stof(linia);
            if (nr_linii == 2 + i_pom)    lista_zamowien[i].imie = linia;
            if (nr_linii == 3 + i_pom)    lista_zamowien[i].nazwisko = linia;
            if (nr_linii == 4 + i_pom)    lista_zamowien[i].nazwa = linia;
            if (nr_linii == 5 + i_pom) { lista_zamowien[i].kwota = stof(linia); i++; numer_zamowienia++; }

            nr_linii++;
        }

        zapis.close();
    }
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
    void menu(Klient& klient)//funkcja realizujaca zamowienie
    {
        int wybor_restauracji;
        int wybor_z_menu;
        string wybrane_produkty[11];
        float koszyk = 0;
        string produkty;
        char* pom_char = new char[2];
    wybor:
        system("cls");
        cout << "Klient: " << klient.imie << " " << klient.nazwisko << endl;
        cout << "\nWybierz restauracje z listy: \n";
        for (int i = 1; i <= numer_restauracji; i++)
        {
            cout << i << ". " << lista_restauracji[i].nazwa << endl;
        }
        cout << "\nWyloguj (wybierz 0)\nWybor: ";
        cin >> pom_char;
        if (isdigit(*pom_char))
            wybor_restauracji = atoi(pom_char);
        else { cout << "\nBledny wybor!"; Sleep(1000); goto wybor; }
        if (wybor_restauracji > 5) { cout << "\nBledny wybor!"; Sleep(1000); goto wybor; }
        if (wybor_restauracji == 0) return;

        system("cls");
        lista_restauracji[wybor_restauracji].wyswietl();
        menu_restauracji[wybor_restauracji].wyswietl();
        for (int j = 1; j < 11; j++)
        {
        zly_wybor:
            cout << "\nWybierz z menu, wroc (wybierz 0) lub wybierz 99 aby zatwierdzic zamowienie -> ";
            cin >> pom_char;
            if (isdigit(*pom_char))
                wybor_z_menu = atoi(pom_char);
            else { cout << "\nBledny wybor!"; Sleep(1000); goto zly_wybor; }
            if (wybor_z_menu == 0) goto wybor;
            if (wybor_z_menu == 99) break;
            system("cls");
            lista_restauracji[wybor_restauracji].wyswietl();
            menu_restauracji[wybor_restauracji].wyswietl();
            if (menu_restauracji[wybor_restauracji].nazwa[wybor_z_menu] == "NULL" || wybor_z_menu > 19)
            {
                cout << "\nBledny wybor!"; Sleep(1000); system("cls"); goto zly_wybor;
            }
            wybrane_produkty[j] = menu_restauracji[wybor_restauracji].nazwa[wybor_z_menu];
            koszyk = menu_restauracji[wybor_restauracji].cena[wybor_z_menu] + koszyk;
            cout << "\nWybrane produkty: " << j << " (maks. 10)\n";

            for (int p = 1; p < 11; p++)
            {
                if (wybrane_produkty[p] == "\0") break;
                cout << wybrane_produkty[p] << ", ";
            }
            cout << "\nLaczna cena: " << koszyk << " zl" << endl;
            if (j == 10)
            {
                cout << "\nMaksymalna liczba produktow!\nWybierz 99 aby zatwierdzic zamowienie lub 0 aby je anulowac -> ";
                cin >> wybor_z_menu;
                if (wybor_z_menu == 0) goto wybor;
                if (wybor_z_menu == 99) break;
            }
        }
        cout << "\nWybierz metode platnosci:\n1. Przelew tradycyjny\n2. Blik\n\n0. Anulowanie\n";
        switch (_getch()) //Funkcja wyboru metod platnosci
        {
        case '1':
        {
            cout << "\nWybrano przelew tradycyjny.\nKwota do zaplaty: " << koszyk << " zl" << endl;
            Sleep(1000);
            cout << "\nPlatnosc potwierdzona, zamowienie przyjete!\n";
            lista_zamowien[numer_zamowienia + 1].przypisz(klient, lista_restauracji[wybor_restauracji], koszyk);
            zapisywanie_zamowienie("Zamowienie.txt");
            system("pause");
            goto wybor;
        }
        break;
        case '2':
        {
            cout << "\nWybrano platnosc blik.\nKwota do zaplaty: " << koszyk << " zl" << endl;
            cout << "Wpisz 6-cyfrowy kod blik: ";
            for (int i = 0; i < 6; i++)
            {
                char pom = _getch();
                if (i < 5) cout << pom << " - ";
                if (i == 5) cout << pom << endl;
            }
            cout << "\nPlatnosc potwierdzona, zamowienie przyjete!\n";
            lista_zamowien[numer_zamowienia + 1].przypisz(klient, lista_restauracji[wybor_restauracji], koszyk);
            zapisywanie_zamowienie("Zamowienie.txt");
            system("pause");
            goto wybor;
        }
        break;
        case '0':
        {
            goto wybor;
        }
        break;
        }
    }
};

int main()
{
    Baza B;
    B.czy_pliki_zapisu_istnieja();
    B.wczytywanie_klient("Klient.txt");
    B.wczytywanie_restauracja("Restauracja.txt");
    B.wczytywanie_zamowienie("Zamowienie.txt");
    B.wczytywanie_menu(B.menu_restauracji[1], "1.txt");
    B.wczytywanie_menu(B.menu_restauracji[2], "2.txt");
    B.wczytywanie_menu(B.menu_restauracji[3], "3.txt");
    B.wczytywanie_menu(B.menu_restauracji[4], "4.txt");
    B.wczytywanie_menu(B.menu_restauracji[5], "5.txt");
    cout << "Zamawianie jedzenia online - Witaj!\n\n";
    system("pause"); system("cls");
menu:
    system("cls");
    cout << "1. Rejestracja\n2. Logowanie\n3. Logowanie operatora\n";
    switch (_getch())//funkcja do poruszania sie po menu programu
    {
    case '1':
    {
        B.lista_klientow[numer_klienta + 1].nowy_klient(B.lista_klientow);
        B.zapisywanie_klient("Klient.txt");
        B.wczytywanie_klient("Klient.txt");
        goto menu;
    }
    break;

    case '2':
    {
        int nr_klienta_pom = B.lista_klientow[1].nr_klienta(B.lista_klientow);
        if (nr_klienta_pom == -1) { goto menu; }
        B.menu(B.lista_klientow[nr_klienta_pom]);
        system("cls");
        goto menu;
    }
    break;

    case '3':
    {
        string login, haslo;
        cout << "Wprowadz login: "; cin >> login;
        cout << "Wprowadz haslo: "; cin >> haslo;
        if (login != "admin" || haslo != "admin")
        {
            cout << "\nBledny login lub haslo!";
            Sleep(1000);
            system("cls");
            goto menu;
        }
    admin:
        system("cls");
        cout << "1. Wyswietl klientow z bazy\n2. Wyswietl liste restauracji\n3. Wyswietl liste zamowien\n4. Wyloguj\n";
        switch (_getch())
        {
        case '1':
        {
            system("cls");
            for (int i = 1; i <= numer_klienta; i++)
            {
                cout << i << ". " << B.lista_klientow[i].imie << "  " << B.lista_klientow[i].nazwisko << endl;
            }
            system("pause");
            goto admin;
        }
        break;
        case '2':
        {
            int wyb_rest;
            char* wyb_char = new char;
        lista_restauracji_admin:
            system("cls");
            for (int i = 1; i <= numer_restauracji; i++)
            {
                cout << i << ". " << B.lista_restauracji[i].nazwa << endl;
            }
            cout << "\n\n0. Wroc\nWybor: ";
            cin >> wyb_char;
            if (isdigit(*wyb_char))
                wyb_rest = atoi(wyb_char);
            else { cout << "\nBledny wybor!"; Sleep(1000); goto lista_restauracji_admin; }
            if (wyb_rest > 5) { cout << "\nBledny wybor!"; Sleep(1000); goto lista_restauracji_admin; }
            if (wyb_rest == 0) goto admin;
            system("cls");
            B.lista_restauracji[wyb_rest].wyswietl();
            B.menu_restauracji[wyb_rest].wyswietl();
            system("pause");
            goto lista_restauracji_admin;
        }
        break;
        case '3':
        {
            system("cls");
            for (int i = 1; i <= numer_zamowienia; i++)
            {
                B.lista_zamowien[i].wyswietl();
                cout << endl;
            }
            system("pause");
            goto admin;
        }
        break;
        case '4':
        { goto menu; }
        break;
        default:
        { cout << "\nBledny wybor!"; Sleep(700); goto admin; }
        break;
        }
    }
    break;
    default:
    {
        goto menu;
    }
    break;


    }
}


