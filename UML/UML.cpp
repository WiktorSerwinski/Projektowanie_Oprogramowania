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
        case '3': { break; } break;
        default: { goto powrot; } break;
        }
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
    numer_klienta = 0;
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

class Zamowienie 
{
public:
    string imie, nazwa, nazwisko;
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

void menu(Klient& klient, Restauracja* restauracja, Menu* menu_restauracji, Zamowienie* zamowienie)
{
    int wybor_restauracji;
    int wybor_z_menu;
    string wybrane_produkty[11];
    float koszyk = 0;
    string produkty;
wybor:
    system("cls");
    cout << "Klient: " << klient.imie << " " << klient.nazwisko << endl;
    cout << "\nWybierz restauracje z listy: \n";
    for (int i = 1; i <= numer_restauracji; i++)
    {
        cout << i << ". " << restauracja[i].nazwa << endl;
    }
    cout << "\nWyloguj (wybierz 0)\nWybor: ";
    cin >> wybor_restauracji;
    if (wybor_restauracji == 0) return;
    system("cls");
    restauracja[wybor_restauracji].wyswietl();
    menu_restauracji[wybor_restauracji].wyswietl();
    for (int j = 1; j < 11; j++)
    {
    zly_wybor:
        cout << "\nWybierz z menu, wroc (wybierz 0) lub wybierz -1 aby zatwierdzic zamowienie -> ";
        cin >> wybor_z_menu;
        if (wybor_z_menu == 0) goto wybor;
        if (wybor_z_menu == -1) break;
        system("cls");
        restauracja[wybor_restauracji].wyswietl();
        menu_restauracji[wybor_restauracji].wyswietl();
        if (menu_restauracji[wybor_restauracji].nazwa[wybor_z_menu] == "NULL")
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
            cout << "\nMaksymalna liczba produktow!\nWybierz -1 aby zatwierdzic zamowienie lub 0 aby je anulowac -> ";
            cin >> wybor_z_menu;
            if (wybor_z_menu == 0) goto wybor;
            if (wybor_z_menu == -1) break;
        }
    }
    cout << "\nWybierz metode platnosci:\n1. Przelew tradycyjny\n2. Blik\n\n0. Anulowanie\n";
    switch (_getch())
    {
    case '1':
    {
        cout << "\nWybrano przelew tradycyjny.\nKwota do zaplaty: " << koszyk << " zl" << endl;
        Sleep(1000);
        cout << "\nPlatnosc potwierdzona, zamowienie przyjete!\n";
        zamowienie[numer_zamowienia + 1].przypisz(klient, restauracja[wybor_restauracji], koszyk);
        zapisywanie_zamowienie(zamowienie, "Zamowienie.txt");
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
        zamowienie[numer_zamowienia + 1].przypisz(klient, restauracja[wybor_restauracji], koszyk);
        zapisywanie_zamowienie(zamowienie, "Zamowienie.txt");
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

int main()
{
    Klient* klient = new Klient[30];
    Restauracja* restauracja = new Restauracja[30];
    Menu* menu_restauracji = new Menu[30];
    Zamowienie* zamowienie = new Zamowienie[30];
    czy_pliki_zapisu_istnieja();
    wczytywanie_klient(klient, "Klient.txt");
    wczytywanie_restauracja(restauracja, "Restauracja.txt");
    wczytywanie_zamowienie(zamowienie, "Zamowienie.txt");
    wczytywanie_menu(menu_restauracji[1], "1.txt");
    wczytywanie_menu(menu_restauracji[2], "2.txt");
    wczytywanie_menu(menu_restauracji[3], "3.txt");
    wczytywanie_menu(menu_restauracji[4], "4.txt");
    wczytywanie_menu(menu_restauracji[5], "5.txt");
    cout << "Zamawianie jedzenia online - Witaj!\n\n";
    system("pause"); system("cls");
menu:
    system("cls");
    cout << "1. Rejestracja\n2. Logowanie\n3. Logowanie operatora\n";
    switch (_getch())
    {
    case '1':
    {
        klient[numer_klienta + 1].Nowy_Klient(klient);

        zapisywanie_klient(klient, "Klient.txt");
        wczytywanie_klient(klient, "Klient.txt");
        goto menu;
    }
    break;

    case '2':
    {
        int nr_klienta_pom; 
        nr_klienta_pom = nr_klienta(klient);
        if (nr_klienta_pom == -1) { goto menu; }
        menu(klient[nr_klienta_pom], restauracja, menu_restauracji, zamowienie);
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
                cout << i << ". " << klient[i].imie << "  " << klient[i].nazwisko << endl;
            }
            system("pause");
            goto admin;
        }
        break;
        case '2':
        {
            int wyb_rest;
        lista_restauracji_admin:
            system("cls");
            for (int i = 1; i <= numer_restauracji; i++)
            {
                cout << i << ". " << restauracja[i].nazwa << endl;
            }
            cout << "\n\n0. Wroc\nWybor: ";
            cin >> wyb_rest;
            system("cls");
            if (wyb_rest == 0) goto admin;
            restauracja[wyb_rest].wyswietl();
            menu_restauracji[wyb_rest].wyswietl();
            system("pause");
            goto lista_restauracji_admin;
        }
        break;
        case '3':
        {
            system("cls");
            for (int i = 1; i <= numer_zamowienia; i++)
            {
                zamowienie[i].wyswietl();
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
        { goto menu; }
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