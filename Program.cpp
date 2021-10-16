#include <iostream>

using namespace std;

#if defined(_WIN32) || defined(_WIN64)
const bool osWindows = true;
const bool osLinux = false;
const bool osUnknown = false;
#else
const bool osWindows = false;
#ifdef __linux
const bool osLinux = true;
const bool osUnknown = false;
#else
const bool osLinux = false;
const bool osUnknown = true;
#endif
#endif

char field[9] { 0, 0, 0,
                0, 0, 0,
                0, 0, 0 };
bool wins[8][9] {
    { true, true, true, false, false, false, false, false, false }, // obere Reihe
    { false, false, false, true, true, true, false, false, false }, // mittlere Reihe
    { false, false, false, false, false, false, true, true, true }, // untere Reihe
    { true, false, false, true, false, false, true, false, false }, // linke Spalte
    { false, true, false, false, true, false, false, true, false }, // mittlere Spalte
    { false, false, true, false, false, true, false, false, true }, // rechte Spalte
    { true, false, false, false, true, false, false, false, true }, // Diagonale von links oben nach rechts unten
    { false, false, true, false, true, false, true, false, false }  // Diagonale von rechts oben nach links unten
};
char winner = 0;

bool canClaimField(int fieldIndex) {
    if (fieldIndex < 9 && field[fieldIndex] == 0) {
        return true;
    }
    else {
        return false;
    }
}
int getPlayerOneInput() {
    char ret = 20;
    while (ret < 0 || ret >= 9 || !canClaimField(ret)) {
        char input = 20;
        input = getchar();
        while (input != '\n' && getchar() != '\n') /* do nothing*/;
        ret = input - '1';
        cout << "\r";
    }
    return ret;
}
int getPlayerTwoInput() {
    return getPlayerOneInput();
}
void redrawField() {
    if (osLinux) { system("clear"); }
    if (osWindows) { system("cls"); }

    if (field[0] == 0) {
        cout << "   |";
    }
    else if (field[0] == 1) {
        cout << " X |";
    }
    else if (field[0] == 2) {
        cout << " O |";
    }

    if (field[1] == 0) {
        cout << "   |";
    }
    else if (field[1] == 1) {
        cout << " X |";
    }
    else if (field[1] == 2) {
        cout << " O |";
    }

    if (field[2] == 0) {
        cout << "   ";
    }
    else if (field[2] == 1) {
        cout << " X ";
    }
    else if (field[2] == 2) {
        cout << " O ";
    }

    cout << "\n---+---+---\n";

    if (field[3] == 0) {
        cout << "   |";
    }
    else if (field[3] == 1) {
        cout << " X |";
    }
    else if (field[3] == 2) {
        cout << " O |";
    }

    if (field[4] == 0) {
        cout << "   |";
    }
    else if (field[4] == 1) {
        cout << " X |";
    }
    else if (field[4] == 2) {
        cout << " O |";
    }

    if (field[5] == 0) {
        cout << "   ";
    }
    else if (field[5] == 1) {
        cout << " X ";
    }
    else if (field[5] == 2) {
        cout << " O ";
    }

    cout << "\n---+---+---\n";

    if (field[6] == 0) {
        cout << "   |";
    }
    else if (field[6] == 1) {
        cout << " X |";
    }
    else if (field[6] == 2) {
        cout << " O |";
    }

    if (field[7] == 0) {
        cout << "   |";
    }
    else if (field[7] == 1) {
        cout << " X |";
    }
    else if (field[7] == 2) {
        cout << " O |";
    }

    if (field[8] == 0) {
        cout << "   \n";
    }
    else if (field[8] == 1) {
        cout << " X \n";
    }
    else if (field[8] == 2) {
        cout << " O \n";
    }

    if (winner != 0) {
        if (winner == 1) {
            cout << "\nPlayer 'X' won the game!\n";
        }
        else if (winner == 2) {
            cout << "\nPlayer 'O' won the game!\n";
        }
        else {
            cout << "\nThe game is over and no winner could be found!\n";
        }
    }
}
bool updateGame(int playerNr, int playerInput) {
    bool won = false;
    if (canClaimField(playerInput)) {
        field[playerInput] = playerNr;

        for (int i = 0; i < 8; i++) {
            bool* win = wins[i];
            won = true;
            for (int j = 0; j < 9; j++) {
                bool important = win[j];
                if (important && field[j] != playerNr) {
                    won = false;
                    j = 10;
                }
            }
            if (won) {
                i = 10;
                winner = playerNr;
            }
        }
    }
    bool fieldsFree = false;
    for (int i = 0; i < 9; i++) {
        if (canClaimField(i)) {
            fieldsFree = true;
        }
    }
    if (!fieldsFree) {
        won = true;
        winner = 0xFF;
    }
    return won;
}

int main()
{
    while (winner == 0) {
        redrawField();
        bool won = updateGame(1, getPlayerOneInput());
        redrawField();
        if (!won) {
            updateGame(2, getPlayerTwoInput());
        }
    }
    redrawField();
    getchar();
}
