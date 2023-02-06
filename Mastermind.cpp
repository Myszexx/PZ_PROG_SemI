// Mastermind.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <string>
#include<random>
#include<fstream>
#include<windows.h>
#include <stdlib.h>
using namespace std;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

//Dla board 0-puste, 1-zielony, 2-czerwony, 3-niebieski, 4-żolty, 5-szary, 6-czerwony(zgadywanie), 7-bialy(zgadywanie)

//Tutaj widzimy struktury planszy, gracza, wyniku z poziomu trudności
struct board
{
    short pole1;
    short pole2;
    short pole3;
    short pole4;
    short pole5;
};
struct Player {
    int diff=0;
    int score=0;
    board MyBoard = {0,0,0,0,0};
    int round=0;
};
struct trud {
    int wins=0;
    float avg=0;
};
struct Score {
    int att=0;
    trud Easy;
    trud Med;
    trud Hard;
};
Player gracz;
Score wynik;
int tmpint1=0;

void cls() {
    SetConsoleTextAttribute(hConsole, 15);
    system("cls");
}

//Ta funkcja zwraca nam losowo wygenerowaną planszę
board generateMastermind() {
    board ret;
    default_random_engine generator((unsigned int)time(0));
    uniform_int_distribution<int> distribution(1, 5);
    ret.pole1 = distribution(generator);
        ret.pole2 = distribution(generator);
        ret.pole3 = distribution(generator);
        ret.pole4 = distribution(generator);
        ret.pole5 = distribution(generator);
    return ret;
}

//Tutaj krótka funkcja do tłumaczenia wartości liczbowych kolorów na kolory
string translate(short Num) {
    switch (Num) {
    case 0:
        SetConsoleTextAttribute(hConsole, 15);
        return "Nie trafiles";
        break;
    case 1:
        SetConsoleTextAttribute(hConsole, 47);
        return "Zielony";
        break;
    case 2:
        SetConsoleTextAttribute(hConsole, 79);
        return "Czerwony";
        break;
    case 3:
        SetConsoleTextAttribute(hConsole, 31);
        return "Niebieski";
        break;
    case 4:
        SetConsoleTextAttribute(hConsole,111);
        return "Zolty";
        break;
    case 5:
        SetConsoleTextAttribute(hConsole, 135);
        return "Szary";
        break;
    case 6:
        SetConsoleTextAttribute(hConsole, 240);
        return "Zgadles pozycje!";
        break;
    case 7:
        SetConsoleTextAttribute(hConsole, 192);
        return "Kolor jest, ale na innej pozycji";
        break;
    default:
            return "Null?";
        break;
    }
}

//Tutaj poprostu porównujemy dwa pola ze sobą (Jak teraz na to patrze to bezużyteczne w sumie)
bool porownaj(short pole, short pole2) {
    if (pole == pole2) {
        return true;
    }
    else {
        return false;
    }
}

//to jest nasza funkcja odpowiadająca za turę, zwraca czy wygraliśmy czy nie
bool playerTurn(board AiBoard) {
    short color_arr[5];
    bool ava[5];
    //Dwa powiazane ze sobą array, jeden z kolorami, drugi z dostępnością kolorów
    short tmp, tmp1;
    fill(color_arr, color_arr + 5, 0);
    //Wypelniamy nasz array domyślnie zerami;

    //Patrzymy czy pola pasują do siebie

    //cls();
    SetConsoleTextAttribute(hConsole, 15);
    cout << "Runda nr " << tmpint1+1 <<endl << endl;
    SetConsoleTextAttribute(hConsole, 47);
    cout << "1 - zielony, " << flush;
    SetConsoleTextAttribute(hConsole, 79);
    cout << " 2 - czerwony,";
    SetConsoleTextAttribute(hConsole, 31);
    cout << "3 - niebieski,";
    SetConsoleTextAttribute(hConsole, 111);
    cout << "4 - zolty,";
    SetConsoleTextAttribute(hConsole, 135);
   cout << "5 - szary\n";

   SetConsoleTextAttribute(hConsole, 15);
    //Szybka pętla do przechwycenia wszystkich pól w danej turzę
    for (int i = 1; i <= 5; i++) {
        cout << "Podaj pole "<<i<<": ";
        cin >> tmp;
        while (!tmp == 1 || !tmp == 2 || !tmp == 3 || !tmp == 4 || !tmp == 5) {
            cout << "Podaj poprawna wartosc pola " << i << ": ";
            cin >> tmp;
        }
        switch(i) {
            case 1:
                if (!porownaj(AiBoard.pole1, tmp)) {
                    color_arr[i - 1] = tmp;
                    ava[i - 1] = true;
                }
                else {
                    color_arr[i - 1] = 0;
                    gracz.MyBoard.pole1 = 6;
                    ava[i - 1] = false;   
                };
                break;
            case 2:
                if (!porownaj(AiBoard.pole2, tmp)) {
                    color_arr[i - 1] = tmp;
                    ava[i - 1] = true;
                }
                else {
                    color_arr[i - 1] = 0;
                    gracz.MyBoard.pole2 = 6;
                    ava[i - 1] = false;
                    
                };
                break;
            case 3:
                if (!porownaj(AiBoard.pole3, tmp)) {
                    color_arr[i - 1] = tmp;
                    ava[i - 1] = true;
                }
                else {
                    color_arr[i - 1] = 0;
                    gracz.MyBoard.pole3 = 6;
                    ava[i - 1] = false;
                    
                };
                break;
            case 4:
                if (!porownaj(AiBoard.pole4, tmp)) {
                    color_arr[i - 1] = tmp;
                    ava[i - 1] = true;
                }
                else {
                    color_arr[i - 1] = 0;
                    gracz.MyBoard.pole4 = 6;
                    ava[i - 1] = false;
                    
                };
                break;
            case 5:
                if (!porownaj(AiBoard.pole5, tmp)) {
                    color_arr[i - 1] = tmp;
                    ava[i - 1] = true;
                }
                else {
                    color_arr[i - 1] = 0;
                    gracz.MyBoard.pole5 = 6;
                    ava[i - 1] = false;
                   
                };
                break;
        }
        
    }
    //Tutaj dodajemy do licznika tur
    tmpint1++;
    //A poniżej jest funkcja która sprawiła najwięcej problemów
    //Dla pól które są "puste", czyli nie zgadnięte lub jeszcze nieoznaczone
    // iteruje się po nich i dla każdego pola sprawdza czy nie ma innego dostępnego zgodnego pola
    // Co jezeli to pole jest zgodne z odpowiednikiem? (AI.pole2 = Gracz.pole2) 
    // Nie dojedzie do takiej sytuacji gdyż flagujemy to pole jako już użyte w sprawdzaniu, pomijam fakt, że nie iterujemy się wogóle po nim bo ma wartość "Zgadniete"
    //
    
    for (size_t i = 0; i < 5; i++)
    {
        if (color_arr[i] != 0) {
            for (size_t j = 0; j < 5; j++)
            {
                switch (j) {
                case 0:
                    tmp1 = AiBoard.pole1; 
                    break;
                case 1:
                    tmp1 = AiBoard.pole2;
                    break;
                case 2:
                    tmp1 = AiBoard.pole3;
                    break;
                case 3:
                    tmp1 = AiBoard.pole4;
                    break;
                case 4:
                    tmp1 = AiBoard.pole5;
                    break;
                }

                if (ava[j] && color_arr[i]==tmp1) {
                    switch (i) {
                    case 0:
                        gracz.MyBoard.pole1= 7;
                        break;
                    case 1:
                        gracz.MyBoard.pole2 = 7;
                        break;
                    case 2:
                        gracz.MyBoard.pole3 = 7;
                        break;
                    case 3:
                        gracz.MyBoard.pole4 = 7;
                        break;
                    case 4:
                        gracz.MyBoard.pole5 = 7;
                        break;
                    }
                    ava[j] = false;
                }

            }
        }
    }
    
    //sprawdz(color_arr, AiBoard);
    //Tu wypisujemy pola
    cout << endl;
    cout << "Pole 1: " << translate(gracz.MyBoard.pole1);
    SetConsoleTextAttribute(hConsole, 15);

    cout << endl;
    cout << "Pole 2: " << translate(gracz.MyBoard.pole2);
    SetConsoleTextAttribute(hConsole, 15);
    cout<< endl;
    cout << "Pole 3: " << translate(gracz.MyBoard.pole3);
    SetConsoleTextAttribute(hConsole, 15);
    cout << endl;
    cout << "Pole 4: " << translate(gracz.MyBoard.pole4);
    SetConsoleTextAttribute(hConsole, 15);
    cout << endl;
    cout << "Pole 5: " << translate(gracz.MyBoard.pole5);
    SetConsoleTextAttribute(hConsole, 15);
    cout << endl;
    
        //DEBUG
    //cout << "Pola AVA: " << ava[0] << ava[1] << ava[2] << ava[3] << ava[4] << endl;
    //cout << "Pola AI: " << translate(AiBoard.pole1) << ", " << translate(AiBoard.pole2) << ", " << translate(AiBoard.pole3) << ", " << translate(AiBoard.pole4) << ", " << translate(AiBoard.pole5) << endl;
    //cout << "Pola ARR: " << translate(color_arr[0]) << ", " << translate(color_arr[1]) << ", " << translate(color_arr[2]) << ", " << translate(color_arr[3]) << ", " << translate(color_arr[4]) << endl;

    if (gracz.MyBoard.pole1 == 6 && gracz.MyBoard.pole2 == 6 && gracz.MyBoard.pole3 == 6 && gracz.MyBoard.pole4 == 6 && gracz.MyBoard.pole5 == 6) {
        cout << "Pola AI: " << translate(AiBoard.pole1) << ", " << translate(AiBoard.pole2) << ", " << translate(AiBoard.pole3) << ", " << translate(AiBoard.pole4) << ", " << translate(AiBoard.pole5) << endl;
        //cout << "Moj arr: " << translate(color_arr[0]) << ", " << translate(color_arr[1]) << ", " << translate(color_arr[2]) << ", " << translate(color_arr[3]) << ", " << translate(color_arr[4]) << endl;

        return true;
    }
    else {
        return false;
    }

}
//To nasza główna funkcja kontrolująca liczbe tur, poziom trudnosci
bool game(short difficulty) {
    Player Ai; 
    int i = 1;
    Ai.MyBoard = generateMastermind();
    while (i<(6+2*difficulty))
    {
       if (playerTurn(Ai.MyBoard)) {
            cout << "Koniec z tego";
            gracz.round = i;
            SetConsoleTextAttribute(hConsole, 192);
            return true;
        };
        i++;
    }
    return false;
};
//funkcja która zapisuje wyniki gracza, oczywiscie wczesniej odczytując poprzednie statystyki, przeliczając i wpisując na nowo
void zapiszStaty(Player gracz) {
    fstream plik;
    string s, val;
    bool isval=false;


    plik.open("wyniki.txt", ios::in);
    int i = 0;
    float f;
   
    if (plik.good()) {
        while(!plik.eof()) {
             plik >> s;
             if (isval) {
                 isval = false;
                 switch (i) {
                 case 0:
                     wynik.Easy.avg = stof(s);
                     break;
                 case 1:
                     wynik.Easy.wins = stoi(s);
                     break;
                 case 2:
                     wynik.Med.avg = stof(s);
                     break;
                 case 3:
                     wynik.Med.wins = stoi(s);
                     break;
                 case 4:
                     wynik.Hard.avg = stof(s);
                     break;
                 case 5:
                     wynik.Hard.wins = stoi(s);
                     break;
                 }
                 i++;

             }
             else {
                 if (s == "kol") {
                     isval=true;
                 }
             }
                
             
             
        }
    }
    plik.close();
    switch (gracz.diff)
    {
    case 1:
        f = wynik.Hard.avg*wynik.Hard.wins;
        f += tmpint1;
        wynik.Hard.wins++;
        wynik.Hard.avg = f / wynik.Hard.wins;
        break;
    case 2:
        f = wynik.Med.avg * wynik.Med.wins;
        f += tmpint1;
        wynik.Med.wins++;
        wynik.Med.avg = f / wynik.Med.wins;
        break;
    case 3:
        f = wynik.Easy.avg * wynik.Easy.wins;
        f += tmpint1;
        wynik.Easy.wins++;
        wynik.Easy.avg = f / wynik.Easy.wins;
        break;
    default:
        break;
    }
    plik.open("wyniki.txt", ios::out);
    if (plik.good())
    {
        plik << "kol " << wynik.Easy.avg << endl;
        plik << "kol " << wynik.Easy.wins << endl;
        plik << "kol " << wynik.Med.avg << endl;
        plik << "kol " << wynik.Med.wins << endl;
        plik << "kol " << wynik.Hard.avg << endl;
        plik << "kol " << wynik.Hard.wins << endl;
    };
    
};
//Funkcja do wczytywania statystyk
void pokazStaty() {
    fstream plik;
    string s, val;
    bool isval = false;


    plik.open("wyniki.txt", ios::in);
    int i = 0;
    if (plik.good()) {
        while (!plik.eof()) {
            plik >> s;
            if (isval) {
                isval = false;
                switch (i) {
                case 0:
                    cout << "Latwy avg: " << s << endl;
                    break;
                case 1:
                    cout << "Latwy winy: " << s << endl;
                    break;
                case 2:
                    cout << "Medium avg: " << s << endl;
                    break;
                case 3:
                    cout << "Medium winy: " << s << endl;
                    break;
                case 4:
                    cout << "Hard avg: " << s << endl;
                    break;
                case 5:
                    cout << "Hard winy: " << s << endl;
                    break;
                }
                i++;

            }
            else {
                if (s == "kol") {
                    isval = true;
                }
            }



        }
    }
    plik.close();
};

int main()
{
    short lvl;
    char stats;
    Player gracz;
   
    cout << "Witaj w grze MasterMind!\n";
    cout << "Wybierz poziom trundosci:\n1) Trudny\n2) Sredni\n3) Latwy\n";
    //Tutaj wybieramy poziom trudności
    cin >> lvl;
    while (!lvl == 1 || !lvl == 2 || !lvl == 3 ) {
        cout << "Podaj poprawna wartosc poziomu trudnosc";
        cin >> lvl;
    }
    gracz.diff = lvl;
    cls();
    //Tautaj wywołujemy naszą funkcję, gdy zdązymy w wyznaczonym limicie turowym to wygrywamy, jezeli nie zdazymy, to przegrana
    if (game(lvl)) {
        cls();
        SetConsoleTextAttribute(hConsole, 15);
        zapiszStaty(gracz);
        cout << "Gratulacje! Wygrales! Chcesz zobaczyc statystyki?(Y/N)\n";

        cin >> stats;
        //Tutaj sprawdzamy input oraz zapisujemy (i pokazujemy)
        while (true)
        {
            if ((stats != 'Y' || stats != 'N')) {
                break;
            }
            cout << "Gratulacje! Wygrales! Chcesz zobaczyc statystyki?(Y/N)\n Podaj poprawna warosc\n";
            cin >> stats;

        }
        if (stats == 'Y') {
            pokazStaty();
        }
        
    }
    return 0;
}
