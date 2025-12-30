
#include <iostream>
#include <fstream>
#include<ctime>
#include <string>
#include <cctype>
using namespace std;

void playQuiz();
void viewScores();

int main() {
    int choice;
    do {
        cout << "\n===== QUIZ GAME =====\n";
        cout << "1. Play Quiz\n";
        cout << "2. View Scores\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: playQuiz(); break;
            case 2: viewScores(); break;
            case 3: cout << "Goodbye!\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 3);

    return 0;
}

void playQuiz() {
    int level, timeLimit;
    string fileName;

    cout << "\nSelect Difficulty:\n";
    cout << "1. Easy\n2. Medium\n3. Hard\n";
    cin >> level;

    if (level == 1) { fileName = "easy.txt"; timeLimit = 20; }
    else if (level == 2) { fileName = "medium.txt"; timeLimit = 15; }
    else { fileName = "hard.txt"; timeLimit = 10; }

    ifstream file(fileName.c_str());
    if (!file) {
        cout << "Question file not found!\n";
        return;
    }

    string question, A, B, C, D;
    char correct, answer;
    int score = 0;

    cin.ignore();

    while (getline(file, question)) {
        getline(file, A);
        getline(file, B);
        getline(file, C);
        getline(file, D);
        file >> correct;
        file.ignore();

        cout << "\n" << question << endl;
        cout << "A. " << A << endl;
        cout << "B. " << B << endl;
        cout << "C. " << C << endl;
        cout << "D. " << D << endl;

        clock_t start=clock();
        clock_t end = clock();
        int timeTaken = (end -start)/CLOCKS_PER_SEC;
        cout << "Answer (Time " << timeLimit << "s): ";
        cin >> answer;


        if (timeTaken > timeLimit) {
            cout << "Time up! ❌\n";
            score -= 5;
        }
        else if (toupper(answer) == correct) {
            cout << "Correct! ✅\n";
            score += 10;
        }
        else {
            cout << "Wrong! Correct: " << correct << endl;
            score -= 5;
        }
    }

    file.close();

    string name;
    cout << "\nEnter your name: ";
    cin >> name;

    ofstream out("scores.txt", ios::app);
    out << name << " " << score << endl;
    out.close();

    cout << "Final Score: " << score << endl;
}

void viewScores() {
    ifstream file("scores.txt");
    string name;
    int score;

    if (!file) {
        cout << "No scores found.\n";
        return;
    }

    cout << "\n--- Leaderboard ---\n";
    while (file >> name >> score) {
        cout << name << " : " << score << endl;
    }
    file.close();
}
