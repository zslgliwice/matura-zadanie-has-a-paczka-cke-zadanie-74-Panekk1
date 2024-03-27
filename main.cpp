#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

//odczyt haseł z pliku
vector<string> odczytajHaslaZPliku(const string& nazwaPliku) {
    vector<string> hasla;
    ifstream plik(nazwaPliku);
    string haslo;
    while (plik >> haslo) {
        hasla.push_back(haslo);
    }
    return hasla;
}

//zliczanie haseł złożonych jedynie z cyfr
int policzHaslaNumeryczne(const vector<string>& hasla) {
    int liczba = 0;
    for (const string& haslo : hasla) {
        if (all_of(haslo.begin(), haslo.end(), ::isdigit)) {
            liczba++;
        }
    }
    return liczba;
}

//znalezienie zduplikowanych haseł
vector<string> znajdzZduplikowaneHasla(const vector<string>& hasla) {
    unordered_set<string> unikalneHasla;
    vector<string> zduplikowaneHasla;
    for (const string& haslo : hasla) {
        if (!unikalneHasla.insert(haslo).second) {
            zduplikowaneHasla.push_back(haslo);
        }
    }
    sort(zduplikowaneHasla.begin(), zduplikowaneHasla.end());
    return zduplikowaneHasla;
}

//zliczanie haseł złożonych z cyfr i liter
int policzFragmentyAscii(const vector<string>& hasla) {
    int liczba = 0;
    for (const string& haslo : hasla) {
        for (size_t i = 0; i <= haslo.length() - 4; i++) {
            string podciag = haslo.substr(i, 4);
            bool poprawnyPodciag = all_of(podciag.begin(), podciag.end(), ::isalnum);
            if (poprawnyPodciag) {
                liczba++;
                break;
            }
        }
    }
    return liczba;
}


//zliczanie haseł spełniających warunki zawierania cyfr, małej i dużej litery
int policzHaslaSkomplikowane(const vector<string>& hasla) {
    int liczba = 0;
    for (const string& haslo : hasla) {
        bool maCyfre = any_of(haslo.begin(), haslo.end(), ::isdigit);
        bool maMaleLitery = any_of(haslo.begin(), haslo.end(), ::islower);
        bool maDuzeLitery = any_of(haslo.begin(), haslo.end(), ::isupper);
        if (maCyfre && maMaleLitery && maDuzeLitery) {
            liczba++;
        }
    }
    return liczba;
}

//zapis wyników do pliku
void zapiszWynikiDoPliku(int liczbaHaselNumerycznych, const vector<string>& zduplikowaneHasla,
                          int liczbaFragmentowAscii, int liczbaHaselSkomplikowanych) {
    ofstream plik("wyniki_hasla.txt");
    if (plik.is_open()) {
        plik << "4.1. " << "\n" << liczbaHaselNumerycznych << endl;
        plik << "4.2. " << endl;
        for (const string& haslo : zduplikowaneHasla) {
            plik << haslo << endl;
        }
        plik << "4.3. " << "\n" << liczbaFragmentowAscii << endl;
        plik << "4.4. " << "\n" << liczbaHaselSkomplikowanych << endl;
        plik.close();
    } else {
        cout << "Nie mozna otworzyc pliku wynikowego." << endl;
    }
}

int main() {
    // Odczyt haseł z pliku
    vector<string> hasla = odczytajHaslaZPliku("hasla.txt");

    // Wykonanie zadań
    int liczbaHaselNumerycznych = policzHaslaNumeryczne(hasla);
    vector<string> zduplikowaneHasla = znajdzZduplikowaneHasla(hasla);
    int liczbaFragmentowAscii = policzFragmentyAscii(hasla);
    int liczbaHaselSkomplikowanych = policzHaslaSkomplikowane(hasla);

    // Zapis wyników do pliku
    zapiszWynikiDoPliku(liczbaHaselNumerycznych, zduplikowaneHasla, liczbaFragmentowAscii, liczbaHaselSkomplikowanych);

    return 0;
}
