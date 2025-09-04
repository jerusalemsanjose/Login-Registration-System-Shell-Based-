#include "auth.h" 
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <conio.h>   // For _getch()
#include <windows.h>;
using namespace std;

void registerUser() {
    string username, password;
    cout << "Enter a username: ";
    cin >> username;

    cout << "Enter a password: ";
    cin >> password;

    // Stores to a text (I'm gonna change it to json later)
    ifstream file("output/users.txt");
    string line, storedUsername, storedPassword;

    // Check if username already exists
    while (getline(file, line)) {
        istringstream iss(line);
        iss >> storedUsername >> storedPassword;

        if (storedUsername == username) {
            cout << "This username already exists. Try another one.\n";
            file.close();
            return;
        }
    }
    file.close();

    ofstream outFile("output/users.txt", ios::app);
    outFile << username << " " << password << endl;
    outFile.close();

    cout << "Registration Successful!\n";
    system("pause");
}

// This is connected to (void LoginUser) function //
void changeUsername(const string& username) {
    string newUsername;
    cout << "Enter a new username: ";
    cin >> newUsername;
    // Reads the file //
    ifstream file("output/users.txt");
    if (!file) {
        cout << "No users found!\n";
        return;
    }
    file.close();
    // Stores here temporarily
    vector<pair<string,string>> users;
    string line, storedUsername, storedPassword;

    while (getline(file, line)) {
        istringstream iss(line);
        iss >> storedUsername >> storedPassword;

        if (storedUsername == username) {
            users.push_back({newUsername, storedPassword});

            ofstream outFile("output/users.txt");
            for (auto& user : users) {
                outFile << user.first << " " << user.second << endl;
            }
            outFile.close();
            SetColor(10, 1);
            cout << "Username updated successfully!\n";
            system("pause");
            SetColor(7, 0);
        } else {
            users.push_back({storedUsername, storedPassword});
        }
    }
    file.close();
}

void changePassword(const string& username) {
    string newPassword;
    cout << "Enter a new password: ";
    cin >> newPassword;

    ifstream file("output/users.txt");
    if (!file) {
        cout << "No users found!\n";
        return;
    }

    vector<pair<string,string>> users;
    string line, storedUsername, storedPassword;

    // Read all users and update the password for the matching username
    while (getline(file, line)) {
        istringstream iss(line);
        iss >> storedUsername >> storedPassword;

        if (storedUsername == username) {
            // Replace the old password with the new one
            users.push_back({storedUsername, newPassword});
        } else {
            users.push_back({storedUsername, storedPassword});
        }
    }
    file.close();

    // Overwrite the file with updated data
    ofstream outFile("output/users.txt");
    for (auto& user : users) {
        outFile << user.first << " " << user.second << endl;
    }
    outFile.close();
    SetColor(10, 0);
    cout << "Password updated successfully!\n";
    system("pause");
    SetColor(7, 0);
}

void loginUser() {
    int attempts = 0;
    const int maxAttempts = 3;

    while (attempts < maxAttempts) {
        string username, password;
        cout << "Enter a username: ";
        cin >> username;

        cout << "Enter a password: ";
        cin >> password;

        ifstream file("output/users.txt");
        if (!file) {
            cout << "No users registered yet!\n";
            return;
        }

        string line, storedUsername, storedPassword;

        // Reads each line of the file
        while (getline(file, line)) {
            istringstream iss(line);
            iss >> storedUsername >> storedPassword;

            if (storedUsername == username && storedPassword == password) {
                cout << "Login successfully!\n";
                system("pause");
                file.close();

                int choice = 0;
                char key;
                string options[] = {"Change Username", "Change Password", "Logout"};

                while (true) {
                    system("cls"); // clear screen

                    SetColor(15, 0);
                    cout << "+----------------------+\n";
                    cout << "|      LOGIN MENU      |\n";
                    cout << "+----------------------+\n";
                    cout << "\n+--- Welcome User! ---+\n";
                    SetColor(7, 0);

                    // Draw menu items with ">"
                    for (int i = 0; i < 3; i++) {
                        if (i == choice)
                            cout << "> " << options[i] << endl;
                        else
                            cout << "  " << options[i] << endl;
                    }

                    key = _getch();
                    if (key == 72) { // up arrow
                        choice--;
                        if (choice < 0) choice = 2;
                    } else if (key == 80) { // down arrow
                        choice++;
                        if (choice > 2) choice = 0;
                    } else if (key == 13) { // Enter
                        switch (choice) {
                            case 0: changeUsername(username); break;
                            case 1: changePassword(username); break;
                            case 2:
                                cout << "Logging-Out...\n";
                                return;
                        }
                    }
                }
            }
        }
        file.close();

        attempts++;
        SetColor(4, 0);
        cout << "Invalid login. Please try again! Attempts left: " << (maxAttempts - attempts) << "\n";
        system("pause");
        SetColor(7, 0);
    }
    SetColor(4, 0);
    cout << "Too many failed attempts. Access locked.\n";
        system("pause");
    SetColor(7, 0);
}
