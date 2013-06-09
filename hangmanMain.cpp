#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <time.h>
using namespace std;

string s;
vector<char> losuj(vector<char> word, int c)   //funkcja, ktora losuje slowo z pliku i wpisuje je do vectora of chars
{
    time_t t;
    srand((unsigned)time(&t));
    int x = 1;
    fstream plik;
    size_t rozmiar = 41;
    vector<string> wyrazy(rozmiar);
    plik.open("hangman wyrazy.txt", ios::in);

    while (!plik.eof())
    {
        getline(plik, wyrazy[x]);
        x++;
    }
    plik.close();
    int wylosowana;
    switch(c)
    {
    case 1:
        wylosowana = rand()%10+1;
        break;
    case 2:
        wylosowana = rand()%10+11;
        break;
    case 3:
        wylosowana = rand()%10+21;
        break;
    case 4:
        wylosowana = rand()%10+31;
        break;
    case 5:
        wylosowana = rand()%40+1;
        break;
    }

    s = wyrazy[wylosowana];
    word.reserve(s.length());

    for (int i=0; i<s.length()+1; i++)
    {
        word.push_back(s[i]);
    }
return word;
}

void ludzik(int trial)
{
    switch(trial)
    {
        case 6:
            cout << "          ----------          "<<endl;
            break;
        case 5:
            cout << "              |               "<<endl;
            cout << "              |               "<<endl;
            cout << "              |               "<<endl;
            cout << "          ----------          "<<endl;
            break;
        case 4:
            cout << "               ____           "<<endl;
            cout << "              |               "<<endl;
            cout << "              |               "<<endl;
            cout << "              |               "<<endl;
            cout << "          ----------          "<<endl;
            break;
        case 3:
            cout << "               ____           "<<endl;
            cout << "              |   O           "<<endl;
            cout << "              |               "<<endl;
            cout << "              |               "<<endl;
            cout << "          ----------          "<<endl;
            break;
        case 2:
            cout << "               ____           "<<endl;
            cout << "              |   O           "<<endl;
            cout << "              |   |           "<<endl;
            cout << "              |               "<<endl;
            cout << "          ----------          "<<endl;
            break;
        case 1:
            cout << "               ____           "<<endl;
            cout << "              |   O           "<<endl;
            cout << "              |  /|\\          "<<endl;
            cout << "              |               "<<endl;
            cout << "          ----------          "<<endl;
            break;
        case 0:
            cout << "               ____           "<<endl;
            cout << "              |   O           "<<endl;
            cout << "              |  /|\\          "<<endl;
            cout << "              |  / \\         "<<endl;
            cout << "          ----------          "<<endl;
            break;


    }
}

void guess(vector<char> wyraz, int hardness, string kategoria) //glowna funkcja, ktora wykonuje czarna robote (jestem swiadomy, ze mozna
{                                                              //ja rozbic na mniejsze fragmenty, ale nie wiem czy warto - podyskutujemy ;))
    char litera;
    int licznik;
    vector<char> zgadywane;
    vector<char> uzyte;
    uzyte.reserve(8);
    zgadywane.reserve(s.length());
    for (int y=0; y<s.length(); y++)
    {
        zgadywane.push_back('_');
    }
    if (hardness == 1)                       //wersja EASY
    {
        licznik = 7;
        bool flaga = false;
        while ((!flaga) && (licznik>0))
        {
            system("CLS");
            cout << "Category: " << kategoria << endl;
           for (int y=0; y<s.length(); y++)
            {
                cout << zgadywane[y];
                cout << " ";
            }

           cout << "\nYou have " << licznik << " trial(s) left.\t\t" << endl;
           ludzik(licznik);
           cout << "\nLetters already used: ";
           for (int z=0; z<uzyte.size(); z++)
           {
               cout << uzyte[z];
               cout << ", ";
           }
           cout << "\nEnter your letter: ";
           cin >> litera;
           uzyte.push_back(litera);
           for (int q=0; q<s.length();q++)
           {
               if (wyraz[q] == litera)
               {
                   zgadywane[q] = litera;
               }
           }
           flaga=true;
           bool flaga3=false;
           for (int j=0; j<s.length();j++)
           {
               if (flaga==true)
               {
                   if (wyraz[j] != zgadywane[j])
                   {
                       flaga=false;
                   }
               }
           }
           for (int k=0; k<s.length();k++)
           {
               if (wyraz[k]==litera)
               {
                   flaga3=true;
               }
           }
           if (flaga3==false)
           {
               licznik--;
           }
        }
    }
    else                 //wersja HARD
    {
        licznik = 5;
        bool flaga = false;
        while ((!flaga) && (licznik>0))
        {
            system("CLS");
            cout << "Category: " << kategoria << endl;
           for (int y=0; y<s.length(); y++)
            {
                cout << zgadywane[y];
                cout << " ";
            }

           cout << "\nYou have " << licznik << " trial(s) left.\t\t" << endl;
           ludzik(licznik);
           cout << "\nEnter your letter: ";
           cin >> litera;
           for (int q=0; q<s.length();q++)
           {
               if (wyraz[q] == litera)
               {
                   zgadywane[q] = litera;
               }
           }
           flaga=true;
           bool flaga3=false;
           for (int j=0; j<s.length();j++)
           {
               if (flaga==true)
               {
                   if (wyraz[j] != zgadywane[j])
                   {
                       flaga=false;
                   }
               }
           }
           for (int k=0; k<s.length();k++)
           {
               if (wyraz[k]==litera)
               {
                   flaga3=true;
               }
           }
           if (flaga3==false)
           {
               licznik--;
           }
        }
    }
        if (licznik>0)
        {
            cout << "Good job! You have correctly guessed the word ";
            for (int b=0; b<s.length(); b++)
            {
                cout << zgadywane[b];
            }
        }
        else if (licznik == 0)
        {
            ludzik(licznik);
            cout << "Unfortunately, you have failed. The word that killed you was ";
            for (int e=0; e<wyraz.size(); e++)
            {
                cout << wyraz[e];
            }
        }
}

int main()
{
    bool gramyDalej = true;
    while (gramyDalej==true)
    {
        system("CLS");
        int difficulty;
        int category;
        string categoryName;
        using namespace std;
        cout << "Welcome to HANGMAN - the ultimate survival game!" << endl;
        cout << "Please choose the difficulty. Press: " << endl;
        cout << "1. Easy mode - for beginners and pussies"<< endl;
        cout << "2. Hard mode - for gnomes and real men"<<endl;
        cin >> difficulty;
        if (difficulty == 1)
        {
            system("CLS");
            cout << "Very well then, since you have chosen the easier option, you can now pick the category of the word you will be guessing." <<endl;
            cout << "The categories are: " << endl;
            cout << "1. Human body" << endl;
            cout << "2. Animals" << endl;
            cout << "3. Sports" <<endl;
            cout << "4. Mathematics" << endl;
            cout << "Make your choice, please." << endl;
            cin >> category;
            switch(category)
            {
            case 1:
                categoryName = "Human body";
                break;
            case 2:
                categoryName = "Animals";
                break;
            case 3:
                categoryName = "Sports";
                break;
            case 4:
                categoryName = "Mathematics";
                break;

            }
        }
        else
        {
            system("CLS");
            cout << "Aha! So you're a smart ass now, huh? We shall see ;)" << endl;
            category = 5;
            categoryName = "Not so fast, cowboy! This is the hard version!";
        }
        vector<char> slowo;
        losuj(slowo, category);

        cout<< "Let the game begin!" << endl;
        system("PAUSE");
        system("CLS");

        guess(losuj(slowo, category), difficulty, categoryName);

        cout << endl;
        system("PAUSE");
        system("CLS");

        char decyzja;
        cout << "Would you like to play again?" << "\n(Y)es or (N)o?" << endl;
        cin >> decyzja;

        if (decyzja == 'N' or decyzja == 'n')
        {
            gramyDalej = false;
            cout << "Thank you for playing!";
        }
    }
    return 0;
}
