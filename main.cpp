#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>

using namespace std;

class GameModel {
    int punkty = 0;
    int poziom = 0;
    public:
        void dodajPunkty() {
            punkty++;

        }
    void dodajLevel() {
        if(punkty % 5 == 0)
        {
            poziom++;
        }

    }
        int podajPunkty() {
            return punkty;
        }
        int podajLevel() {
            return poziom;
        }

    void Zapisz() {
        ofstream plik("wyniki.txt");// W trybie trunc usuwa zawartosc pliku i pozwala na nadpisywanie
        plik << "Punkty: " << punkty << " || " << "Level: " << poziom;
        plik.close();
    }

    void Załaduj() {
        ifstream file("wyniki.txt");

        if (file.fail() == 1) {
            cout << "Plik nie istnieje, tworzymy plik" << endl;
            punkty = 0;
            poziom = 0;
            return;
        }

        string str;
        if (getline(file, str)) {
            punkty = atoi(str.c_str());
            file.close();
            cout << "Nie znaleziono pliku! Twoje punkty to " << punkty << endl;
            punkty = 0;
        }

    }
};
class GameView {
    public:
        void TekstPoczatkowy() {
            cout << endl;
            cout << "Wytaj w programie kliker!" << endl;
            cout << endl;
            cout << " Gra polega na tym, aby wpisać haslo, ktore dodaje punkty (haslo to b).\n Za kazde 5 zdobytych punktow, poziom zwiekszy sie o 1 w gore.\n Zasady sa proste wiec zaczynajmy\n" << endl;
            cout << "Kliknij b aby zdobyc punkty lub kliknij e aby wyjsc" << endl;
        }
        void wypiszDane1(int points) {
            cout << "Points: " << points << endl;
        }
    void wypiszDane2(int level) {
        cout << "Level: " << level << endl;
    }
        char podajDane()
        {
            return _getch();
        }
};
class GameController {
    public:
        GameModel model;
        GameView view;

        void dzialaj() {
            model.Załaduj();
            view.TekstPoczatkowy();
        }

        GameController(GameModel model, GameView view) {
            this->model = model;
            this->view = view;
        }
};

int main() {

    GameController game = *new GameController(*new GameModel, *new GameView);
    game.dzialaj();

    char input;
    do {
        input = game.view.podajDane();
        if (input == 'b') {
            game.model.dodajPunkty();
            game.model.dodajLevel();
            game.model.Zapisz();
            game.view.wypiszDane1(game.model.podajPunkty());
            game.view.wypiszDane2(game.model.podajLevel());
        }
    } while(input != 'e');

    return 0;
}