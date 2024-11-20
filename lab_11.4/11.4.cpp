#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
using namespace std;

// Funktsiya stvorennya faylu z koefitsiyentamy pryamykh
void CreateFile(const char* filename) {
    ofstream fout(filename);
    if (!fout) {
        cerr << "Pomilka vidkrittya faylu dlya zapisu!" << endl;
        return;
    }

    char ch;
    do {
        double A, B, C;
        cout << "Vvedit koefitsiyenty A, B, C dlya rivnyannya Ax + By + C = 0: ";
        cin >> A >> B >> C;
        fout << A << " " << B << " " << C << endl;

        cout << "Prodovzhyty vvedennya? (y/n): ";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');

    fout.close();
}

// Funktsiya dlya pereglyadu faylu
void ViewFile(const char* filename) {
    ifstream fin(filename);
    if (!fin) {
        cerr << "Pomilka vidkrittya faylu dlya chytannya!" << endl;
        return;
    }

    string line;
    while (getline(fin, line)) {
        cout << line << endl;
    }

    fin.close();
}

// Funktsiya dlya perevirky paralelnosti dvokh pryamykh
bool AreParallel(double A1, double B1, double A2, double B2) {
    return fabs(A1 * B2 - A2 * B1) < 1e-6;
}

// Funktsiya dlya perevirky perpendykulyarnosti dvokh pryamykh
bool ArePerpendicular(double A1, double B1, double A2, double B2) {
    return fabs(A1 * A2 + B1 * B2) < 1e-6;
}

// Funktsiya dlya obrobky faylu i stvorennya novogo z rozmistannyam pryamykh
void ProcessFile(const char* inputFilename, const char* outputFilename) {
    ifstream fin(inputFilename);
    ofstream fout(outputFilename);

    if (!fin) {
        cerr << "Pomilka vidkrittya faylu dlya chytannya!" << endl;
        return;
    }
    if (!fout) {
        cerr << "Pomilka vidkrittya faylu dlya zapisu!" << endl;
        return;
    }

    // Chytayemo vsi pary pryamykh iz faylu
    double A1, B1, C1, A2, B2, C2;
    while (fin >> A1 >> B1 >> C1) {
        ifstream temp(inputFilename);
        while (temp >> A2 >> B2 >> C2) {
            if (A1 == A2 && B1 == B2 && C1 == C2) continue; // Propuskayemo odnakovi pryam
            if (AreParallel(A1, B1, A2, B2)) {
                fout << A1 << " " << B1 << " " << C1 << " "
                    << A2 << " " << B2 << " " << C2 << " Parallel" << endl;
            }
            else if (ArePerpendicular(A1, B1, A2, B2)) {
                fout << A1 << " " << B1 << " " << C1 << " "
                    << A2 << " " << B2 << " " << C2 << " Perpendicular" << endl;
            }
            else {
                fout << A1 << " " << B1 << " " << C1 << " "
                    << A2 << " " << B2 << " " << C2 << " Intersecting" << endl;
            }
        }
        temp.close();
    }

    fin.close();
    fout.close();
}

// Menyu prohramy
void Menu() {
    char inputFilename[100], outputFilename[100];
    cout << "Vvedit imya vkhidnogo faylu: ";
    cin >> inputFilename;

    int choice;
    do {
        cout << "\nMenyu:\n"
            << "1. Stvoryty fayl\n"
            << "2. Perehlyanuty fayl\n"
            << "3. Obrobyty fayl i stvoryty novyy fayl\n"
            << "4. Perehlyanuty obroblenyy fayl\n"
            << "0. Vykhid\n"
            << "Vash vybir: ";
        cin >> choice;

        switch (choice) {
        case 1:
            CreateFile(inputFilename);
            break;
        case 2:
            ViewFile(inputFilename);
            break;
        case 3:
            cout << "Vvedit imya vykhidnogo faylu: ";
            cin >> outputFilename;
            ProcessFile(inputFilename, outputFilename);
            break;
        case 4:
            cout << "Vvedit imya vykhidnogo faylu: ";
            cin >> outputFilename;
            ViewFile(outputFilename);
            break;
        case 0:
            cout << "Do pobachennya!" << endl;
            break;
        default:
            cout << "Nekorektnyy vybir. Sprobuyte shche raz." << endl;
        }
    } while (choice != 0);
}

int main() {
    Menu();
    return 0;
}
