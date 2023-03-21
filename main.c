/**
 * "Palindrom"
 * 
 * autor: Wojciech Krolikowski <wk450245@students.mimuw.edu.pl>
 * wersja: 1.0
 * data: 2022-11-27
 */

#include <stdio.h>
#include <limits.h>

// Liczba wierszy planszy.
#ifndef WIERSZE
    #define WIERSZE 8
#endif
// Liczba kolumn planszy.
#ifndef KOLUMNY
    #define KOLUMNY 8
#endif
// Dlugosc szukanego palindromu.
#ifndef DLUGOSC
    #define DLUGOSC 5
#endif

// Funkcja wyznaczajaca minimum z dwoch liczb.
int min(int x, int y)
{
    if(x <= y) return x;
    else return y;
}

// Funkcja przypisujaca kolumnom kolejne litery alfabetu.
void wypelnijAdresyKolumn(unsigned char adresyKolumn[])
{
    int litera = (int)'a';
    for(int i = 0; i < KOLUMNY; i++)
    {
        adresyKolumn[i] = (unsigned char)litera; 
        litera++;
    }
}

// Funkcja wypelniajaca na starcie plansze oznaczeniami pustego pola ('-').
void wypelnijDiagram(unsigned char plansza[][KOLUMNY])
{
    for(int i = 0; i < WIERSZE; i++)
    {
        for(int j = 0; j < KOLUMNY; j++) plansza[i][j] = '-'; 
    }
}

// Funkcja wyswietlajaca aktualny stan planszy.
void wyswietlDiagram(unsigned char plansza[][KOLUMNY], unsigned char adresyKolumn[])
{
    for(int i = WIERSZE-1; i >= 0; i--)
    {
        for(int j = 0; j < KOLUMNY; j++) printf(" %c", plansza[i][j]);
        printf("\n");
    }
    for(int i = 0; i < KOLUMNY; i++) printf(" %c", adresyKolumn[i]);
    printf("\n");
}

// Funkcja wstawiajaca do planszy pion gracza.
int uzupelnijPlansze(unsigned char plansza[][KOLUMNY], int ktoraKolumna, int gracz, int ileWKolumnach[])
{
    for(int i = 0; i < WIERSZE; i++)
    {
        if(plansza[i][ktoraKolumna] == '-')
        {
            plansza[i][ktoraKolumna] = (unsigned char)(gracz+'0');
            // Aktualizacja tablicy ileWKolumnach, mowiaca o ilosci pionow 
            // w poszczegolnych kolumnach.
            ileWKolumnach[ktoraKolumna]++; 
            
            // i+1 (index wiersza) to informacja dla funkcji palindromPoziomy/Ukosny1/Ukosny2, 
            // ktory wiersz ma sprawdzac.
            return i+1; 
        }
    }

    return 0;
}

// Funkcja sprawdzajaca, czy istnieje palindrom pionowy o okreslonej dlugosci.
int czyPalindromPionowy(unsigned char plansza[][KOLUMNY], int ileWKolumnach[], int ktoraKolumna)
{
    // Blok kodu uruchamiający się, jezeli w ogole mozliwe 
    // jest istnienie palindromu w kolumnie wybranej przez gracza,
    // tj. jezeli ilosc pionow w kolumnie jest niemniejsza niz DLUGOSC.
    if(ileWKolumnach[ktoraKolumna] >= DLUGOSC) 
    {
        // p, q - "wierzcholki" potencjalnego palindromu.
        int q = ileWKolumnach[ktoraKolumna]-1;
        int p = q-DLUGOSC+1;
        while((p < q) && (plansza[p][ktoraKolumna] == plansza[q][ktoraKolumna]))
        {
            p++;
            q--; 
        }
        // Jeżeli to palindrom - funkcja przyjmie wartość 1.
        if((p == q) || (p-q == 1)) return 1;
    }

    // Funkcja przyjmie wartosc 0, jezeli niemozliwe jest istnienie palindromu/jezeli nie znaleziono palindromu.
    return 0;
}

// Funkcja sprawdzajaca, czy istnieje palindrom poziomy o okreslonej dlugosci.
int czyPalindromPoziomy(unsigned char plansza[][KOLUMNY], int ileWKolumnach[], int ktoryWiersz)
{
    // Zmienna akt kontroluje dlugosci slowa/slow znajdujacych sie w wierszu.
    int akt = 1;
    for(int i = 1; i < KOLUMNY; i++)
    {   
        // Blok kodu uruchamiajacy sie jezeli istnieja piony obok siebie w wierszu.
        if((ileWKolumnach[i-1] >= ktoryWiersz) && (ileWKolumnach[i] >= ktoryWiersz))
        {
            akt++;
            if(akt > DLUGOSC) akt = DLUGOSC;
            if(akt == DLUGOSC)
            {
                // p, q - "wierzcholki" potencjalnego palindromu.
                int q = i;
                int p = i-DLUGOSC+1;
                while((p < q) && (plansza[ktoryWiersz-1][p] == plansza[ktoryWiersz-1][q]))
                {
                    p++;
                    q--;
                }
                // Jeżeli to palindrom - funkcja przyjmie wartość 1.
                if((p == q)||(p-q == 1)) return 1;
            }
        }
        // Przypisujemy wartosc 1 do zmiennej akt (Skonczylo sie poprzednie slowo w wierszu).
        else akt = 1;
    }
    // Funkcja przyjmie wartosc 0, jezeli niemozliwe jest istnienie palindromu/jezeli nie znaleziono palindromu.
    return 0;
}

// Funkcja sprawdzajaca, czy istnieje palindrom ukosny "rosnacy" o okreslonej dlugosci. 
int czyPalindromNaUkos1(unsigned char plansza[][KOLUMNY], int ktoryWiersz, int ktoraKolumna)
{
    // p, q - wspolrzedne pionu.
    int p = ktoryWiersz-1;
    int q = ktoraKolumna;

    // Wyznaczenie wspolrzednych krancowego pola planszy na przekatnej, na ktorej lezy pion.
    int x = min(p, q);
    int p1 = p-x;
    int q1 = q-x;

    // Wyznaczenie wspolrzednych drugiego krancowego pola planszy na przekatnej, na ktorej lezy pion
    int y = min((WIERSZE-1)-p, (KOLUMNY-1)-q);
    int p2 = p+y;
    int q2 = q+y;

    // Zmienna akt kontroluje dlugosc slowa po przekatnej.
    int akt = 0; 
    // Wyznaczenie dlugosci przekatnej.
    int dlugoscDiagonal = (q2-q1)+1;
    do
    {
        if(plansza[p1][q1] != '-')
        {
            akt++;
            if(akt > DLUGOSC) akt = DLUGOSC;
            if(akt == DLUGOSC)
            {
                // Wspolrzedne "wierzcholkow" potencjalnego palindromu o zadanej DLUGOSCI.
                int p0 = p1-DLUGOSC+1;
                int q0 = q1-DLUGOSC+1;
                int p01 = p1;
                int q01 = q1;

                while((p0 < p01) && (plansza[p0][q0] == plansza[p01][q01]))
                {
                    p0++;
                    q0++;
                    p01--;
                    q01--;
                }
                // Jeżeli to palindrom - funkcja przyjmie wartość 1.
                if(((p0 == p01))||((p0-p01 == 1))) return 1;
            }
        }
        // Przypisujemy wartosc 0 do zmiennej akt (Skonczylo sie poprzednie slowo na przekatnej).
        else akt = 0;
        // Poruszamy sie wzdluz przekatnej (p1++, q1++).
        p1++; 
        q1++;
    }while((q2 >= q1) && (p2 >= p1) && (dlugoscDiagonal >= DLUGOSC));

    // Funkcja przyjmie wartosc 0, jezeli niemozliwe jest istnienie palindromu/jezeli nie znaleziono palindromu.
    return 0;
}

// Funkcja sprawdzajaca, czy istnieje palindrom ukosny "malejacy" o okreslonej dlugosci.
int czyPalindromNaUkos2(unsigned char plansza[][KOLUMNY], int ktoryWiersz, int ktoraKolumna)
{
    // p, q - wspolrzedne pionu.
    int p = ktoryWiersz-1;
    int q = ktoraKolumna;

    // Wyznaczenie wspolrzednych krancowego pola planszy na przekatnej, na ktorej lezy pion.
    int x = min(p, (KOLUMNY-1)-q);
    int p1 = p-x;
    int q1 = q+x;

    // Wyznaczenie wspolrzednych drugiego krancowego pola planszy na przekatnej, na ktorej lezy pion
    int y = min((WIERSZE-1)-p, q);
    int p2 = p+y;
    int q2 = q-y;

    // Zmienna akt kontroluje dlugosc slowa po przekatnej.
    int akt = 0; 
    // Wyznaczenie dlugosci przekatnej.
    int dlugoscDiagonal = (q1-q2)+1; 
    do
    {
        if(plansza[p1][q1] != '-')
        {
            akt++;
            if(akt > DLUGOSC) akt = DLUGOSC;
            if(akt == DLUGOSC)
            {
                // Wspolrzedne "wierzcholkow" potencjalnego palindromu o zadanej DLUGOSCI.
                int p0 = p1-DLUGOSC+1;
                int q0 = q1+DLUGOSC-1;
                int p01 = p1;
                int q01 = q1;

                while((q0 > q01) && (plansza[p0][q0] == plansza[p01][q01]))
                {
                    p0++;
                    q0--;
                    p01--;
                    q01++;
                }
                // Jeżeli to palindrom - funkcja przyjmie wartość 1.
                if(((p0 == p01)) || ((p0-p01 == 1))) return 1;
            }
        }
        // Przypisujemy wartosc 0 do zmiennej akt (skonczylo sie poprzednie slowo na przekatnej).
        else akt = 0;
        // Poruszamy sie wzdluz przekatnej (p1++, q1--).
        p1++;
        q1--;
    }while((q1 >= q2) && (p1 <= p2) && (dlugoscDiagonal >= DLUGOSC));

    // Funkcja przyjmie wartosc 0, jezeli niemozliwe jest istnienie palindromu, badz
    // jezeli nie znaleziono palindromu.
    return 0; 
}

int main(void)
{
    // Plansza gry o wymiarach WIERSZExKOLUMNY.
    unsigned char plansza[WIERSZE][KOLUMNY];

    // Tablica symbolizujaca adresy kolumn.
    unsigned char adresyKolumn[KOLUMNY];

    // Tablica pomocnicza, liczaca ilosc pionow postawionych w poszczegolnych kolumnach.
    int ileWKolumnach[KOLUMNY];

    // Zmienna sterujaca kolejka graczy.
    int i = 0;

    // Tablica mieszczaca graczy.
    int gracz[2] = {1, 2};

    int ktoraKolumna, ktoryWiersz;
    unsigned char wyborGracza;

    // Uzupelniamy tablice ileWKolumnach zerami.
    for(int j = 0; j < KOLUMNY; j++) ileWKolumnach[j] = 0; 
    
    wypelnijDiagram(plansza);
    wypelnijAdresyKolumn(adresyKolumn);

    do
    {
        wyswietlDiagram(plansza, adresyKolumn);
        printf("%d:", gracz[i%2]);
        scanf(" %c", &wyborGracza);
        printf("\n");
        if(wyborGracza != '.')
        {
            // index kolumny, ktora wybral gracz.
            ktoraKolumna = wyborGracza-'a'; 
            
            // Przekazanie przez funkcje uzupelnijPlansze indexu wiersza, w ktorym jestesmy.
            ktoryWiersz = uzupelnijPlansze(plansza, ktoraKolumna, gracz[i%2], ileWKolumnach);
            
            // Jezeli i jest mniejszy od ograniczenia typu int - inkrementacja,
            // jeżeli nie - i staje sie 0.
            if(i < INT_MAX) i++;
            else i = 0;
        }
    }while((wyborGracza != '.') && 
    (czyPalindromPionowy(plansza, ileWKolumnach, ktoraKolumna) == 0) &&  
    (czyPalindromPoziomy(plansza, ileWKolumnach, ktoryWiersz) == 0) &&  
    (czyPalindromNaUkos1(plansza, ktoryWiersz, ktoraKolumna) == 0) && 
    (czyPalindromNaUkos2(plansza, ktoryWiersz, ktoraKolumna) == 0));

    if(wyborGracza != '.')
    {
        wyswietlDiagram(plansza, adresyKolumn);
        printf("%d!\n", gracz[(i-1)%2]);
    }   

    return 0;
}
