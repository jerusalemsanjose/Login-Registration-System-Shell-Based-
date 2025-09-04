#include <iostream>
#include <windows.h>
#include <conio.h>   
#include "auth.h"
using namespace std;

void SetColor(int textColor, int bgColor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (bgColor << 4) | textColor);
}

int main() {
    int select = 0; // current selection index: 0=Register, 1=Login, 2=Exit
    char key;

    while (true) {
        system("cls"); // clear screen

        // Title
        SetColor(15, 0);
        cout << "+----------------------+\n";
        cout << "| LOGIN & REGISTRATION |\n";
        cout << "+----------------------+\n";
        SetColor(7, 0);

        // Menu Items with ">" for current selection
        string options[] = {"Register", "Login", "Exit"};
        for (int i = 0; i < 3; i++) {
            if (i == select)
                cout << "> " << options[i] << endl;
            else
                cout << "  " << options[i] << endl;
        }

        // Separator
        cout << "+---------------------------+\n";
        cout << "Use UP/DOWN arrows to select and press ENTER.\n";

        // Read key press
        key = _getch();
        if (key == 72) { // up arrow
            select--;
            if (select < 0) select = 2;
        } else if (key == 80) { // down arrow
            select++;
            if (select > 2) select = 0;
        } else if (key == 13) { // Enter
            // call functions based on selection
            switch (select) {
                case 0: registerUser(); break;
                case 1: loginUser(); break;
                case 2: 
                    cout << "Exiting program.\n";
                    return 0;
            }
        }
    }

    return 0;
}
