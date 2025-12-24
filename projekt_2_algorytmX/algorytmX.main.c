#include <stdio.h>
#define W 200 // maksymalna liczba wierszy
#define Z 301 // maksymalna liczba znakow

int parsowanie_tablicy_dwuwymiarowej(char T[W][Z]) {
    // Chcę też policzyć wiersze.
    int i = 0;
    while (fgets(T[i], Z, stdin) != nullptr) {
        ++i;
    }
    return i;
}

int liczenie_kolumn(char T[W][Z]) {
    int i = 0;
    while (i < Z && T[0][i] != '\n' && T[0][i] != '\0') {
        ++i;
    }
    return i;
}

void parsowanie_filtra(char T[W][Z], char filtr[Z], int liczba_kolumn) {
    int i = 0;
    while (i < liczba_kolumn) {
        filtr[i] = T[0][i];
        ++i;
    }
}

void przesuwanie_wierszy(char T[W][Z]) {
    //Usuwam filtr z tablicy,
    //nie jest mi on potrzebny do szukania rozwiazania.
    //jego usunięcie zwiększa przejrzystość i ułatwiło mi pisanie programu
    for (int i = 0; i < W - 1; i++) {
        for (int j = 0; j < Z; j++) {
            T[i][j] = T[i + 1][j];
        }
    }
}

int szukaj_wolnej_kolumny(int zajete_k[Z], int liczba_k) {
    int i = 0;
    int wolna_kolumna = -1;
    while (i < liczba_k && wolna_kolumna == -1) {
        if (zajete_k[i] == -1) {
            wolna_kolumna = i;
        } else {
            ++i;
        }
    }
    return wolna_kolumna;
}

bool czy_wiersz_pasuje(char T[W][Z], int w, int zajete_k[Z], int liczba_k) {
    bool pasuje = true;
    int i = 0;
    while (i < liczba_k && pasuje) {
        if (T[w][i] != '_' && zajete_k[i] != -1) {
            pasuje = false;
        } else {
            ++i;
        }
    }
    return pasuje;
}

void dodaj_wiersz(char T[W][Z], int w, int zajete_k[Z], int liczba_k) {
    //Zajmujemy wszystkie kolumny w których wiersz posiada znak.
    //Dzięki ustawieniu zajete_k[i] na w wiemy,
    //który wiersz zajmuje daną kolumne.
    for (int i = 0; i < liczba_k; i++) {
        if (T[w][i] != '_') {
            zajete_k[i] = w;
        }
    }
}

void usun_wiersz(char T[W][Z], int w, int zajete_k[Z], int liczba_k) {
    // Przeglądamy cały wiersz w, który chcemy usunąć z rozwiazania
    for (int i = 0; i < liczba_k; i++) {
        // Jeśli w tym wierszu w kolumnie 'i' jest jakiś znak...
        if (T[w][i] != '_') {
            // ...to odznaczamy tę kolumnę jako wolną.
            // Wpisujemy -1, co oznacza "nikt tu nie stoi".
            zajete_k[i] = -1;
        }
    }
}

void drukuj(int liczba_k, char filtr[Z], char T[W][Z], int zajete_k[Z]) {
    for (int i = 0; i < liczba_k; i++) {
        //Sprawdzamy, z którego wiersza bierzemy znak.
        int wiersz = zajete_k[i];
        if (filtr[i] == '+') {
            printf("%c", T[wiersz][i]);
        }
    }
    printf("\n");
}

void algorytmX(char T[W][Z], int zajete_k[Z], int liczba_k,
    int liczba_w, char filtr[Z]) {
    int k = szukaj_wolnej_kolumny(zajete_k, liczba_k);
    // k == -1 oznacza, że nie ma wolnej kolumny - mamy rozwiązanie.
    if (k == -1) {
        drukuj(liczba_k, filtr, T, zajete_k);
    } else {
        for (int w = 0; w < liczba_w; w++) {
            if (T[w][k] != '_' && czy_wiersz_pasuje(T, w, zajete_k, liczba_k)) {
                dodaj_wiersz(T, w, zajete_k, liczba_k);
                algorytmX(T, zajete_k, liczba_k, liczba_w, filtr);
                usun_wiersz(T, w, zajete_k, liczba_k);
            }
        }
    }
}

int main() {
    //Tablica znaków:
    char T[W][Z];
    //Nie wliczamy filtra do liczby wierszy:
    int liczba_w = parsowanie_tablicy_dwuwymiarowej(T) - 1;
    int liczba_k = liczenie_kolumn(T);
    char filtr[Z];
    parsowanie_filtra(T, filtr, liczba_k);
    przesuwanie_wierszy(T);
    int zajete_k[Z];
    //-1 oznacza, że kolumna nie jest zajęta.
    for (int i = 0; i < Z; i++) {
        zajete_k[i] = -1;
    }
    algorytmX(T, zajete_k, liczba_k, liczba_w, filtr);
}