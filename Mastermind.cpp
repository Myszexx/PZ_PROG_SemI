// Mastermind.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <string>
#include<random>
#include<fstream>
using namespace std;
//Dla board 0-puste, 1-zielony, 2-czerwony, 3-niebieski, 4-żolty, 5-szary, 6-czerwony(zgadywanie), 7-bialy(zgadywanie)
struct board
{
    short pole1;
    short pole2;
    short pole3;
    short pole4;
    short pole5;
};
struct Player {
    int diff;
    int score=0;
    board MyBoard;
    int round;
};
struct trud {
    int wins=0;
    float avg=0;
};
struct Score {
    int att;
    trud Easy;
    trud Med;
    trud Hard;
};
Player gracz;
Score wynik;
int tmpint1=0;
board generateMastermind() {
    board ret;
    default_random_engine generator;
    uniform_int_distribution<int> distribution(1, 5);
    ret.pole1 = 1;//distribution(generator);
        ret.pole2 = 2;//distribution(generator);
        ret.pole3 = 3;//distribution(generator);
        ret.pole4 = 4;//distribution(generator);
        ret.pole5 = 5;//distribution(generator);
    return ret;

}

string translate(short Num) {
    switch (Num) {
    case 0:
        return "Nie trafiles";
        break;
    case 1:
        return "Zielony";
        break;
    case 2:
        return "Czerwony";
        break;
    case 3:
        return "Niebieski";
        break;
    case 4:
        return "Zolty";
        break;
    case 5:
        return "Szary";
        break;
    case 6:
        return "Zgadles pozycje!";
        break;
    case 7:
        return "Kolor jest, ale na innej pozycji";
        break;
    default:
            return "Null?";
        break;
    }
}

//dodac funkcje do porownywania 
bool porownaj(short pole, short pole2) {
    if (pole == pole2) {
        return true;
    }
    else {
        return false;
    }
}

bool playerTurn(board AiBoard) {
    short color_arr[5];
    bool ava[5];
    short tmp, tmp1;
    fill(color_arr, color_arr + 5, 0);
    //Patrzymy czy pola pasują do siebie
    cout << "1 - zielony, 2 - czerwony, 3 - niebieski, 4 - zolty, 5 - szary\n";
    for (int i = 1; i <= 5; i++) {
        cout << "Podaj pole "<<i<<": ";
        cin >> tmp;
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
    tmpint1++;
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
                    //ava[i] = false;
                }

            }
        }
    }
    
    //sprawdz(color_arr, AiBoard);
    cout << "Pole 1: " << translate(gracz.MyBoard.pole1) << endl;
    cout << "Pole 2: " << translate(gracz.MyBoard.pole2) << endl;
    cout << "Pole 3: " << translate(gracz.MyBoard.pole3 )<< endl;
    cout << "Pole 4: " << translate(gracz.MyBoard.pole4) << endl;
    cout << "Pole 5: " << translate(gracz.MyBoard.pole5) << endl;
    //Sprawdzimy czy kolory sa nie na swoich miejscach
    
        //DEBUG
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

bool game(short difficulty) {
    Player Ai; 
    int i = 1;
    Ai.MyBoard = generateMastermind();
    while (i<(6+2*difficulty))
    {
       if (playerTurn(Ai.MyBoard)) {
            cout << "Koniec z tego";
            gracz.round = i;
            return true;
        };
        i++;
    }
    return false;
};

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
        wynik.Hard.avg = f * wynik.Hard.wins;
        break;
    case 2:
        f = wynik.Med.avg * wynik.Med.wins;
        f += tmpint1;
        wynik.Med.wins++;
        wynik.Med.avg = f * wynik.Med.wins;
        break;
    case 3:
        f = wynik.Easy.avg * wynik.Easy.wins;
        f += tmpint1;
        wynik.Easy.wins++;
        wynik.Easy.avg = f * wynik.Easy.wins;
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
    cin >> lvl;
    gracz.diff = lvl;
    if (game(lvl)) {
        zapiszStaty(gracz);
        cout << "Gratulacje! Wygrales! Chcesz zobaczyc statystyki?(Y/N)\n";

        cin >> stats;
        while (true)
        {
            if (stats != 'Y' || stats != 'N') {
                break;
            }
            cout << "Gratulacje! Wygrales! Chcesz zobaczyc statystyki?(Y/N)\n Podaj poprawna warosc\m";
            cin >> stats;

        }
        if (stats == 'Y') {
            pokazStaty();
        }
        
    }
}

// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
