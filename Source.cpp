#include <iostream>
#include <vector>

using namespace std;

const int SIZE = 3;

void printDesk(const vector<vector<char>>& desk) {
    cout << "  0   1   2" << endl;
    cout << " +---+---+---+" << endl;
    for (int i = 0; i < SIZE; ++i) {
        cout << i << "|";
        for (int j = 0; j < SIZE; ++j) {
            cout << " " << desk[i][j] << " |";
        }
        cout << endl;
        cout << " +---+---+---+" << endl;
    }
}

bool checkWin(const vector<vector<char>>& desk, char player) {
    for (int i = 0; i < SIZE; ++i) {
        if ((desk[i][0] == player && desk[i][1] == player && desk[i][2] == player) ||
            (desk[0][i] == player && desk[1][i] == player && desk[2][i] == player)) {
            return true;
        }
    }
    if ((desk[0][0] == player && desk[1][1] == player && desk[2][2] == player) ||
        (desk[0][2] == player && desk[1][1] == player && desk[2][0] == player)) {
        return true;
    }
    return false;
}

bool isBoardFull(const vector<vector<char>>& desk) {
    for (const auto& row : desk) {
        for (char cell : row) {
            if (cell == ' ') {
                return false;
            }
        }
    }
    return true;
}

void printMessage(const string& message, const string& lang) {
    if (lang == "ru") {
        cout << message << endl;
    }
    else if (lang == "eng") {
        if (message == "������������ ���. ���������� �����.") {
            cout << "Invalid move. Please try again." << endl;
        }
        else if (message == "����� ") {
            cout << "Player " << endl;
        }
        else if (message == "�������!") {
            cout << "has won!" << endl;
        }
        else if (message == "�����!") {
            cout << "Draw!" << endl;
        }
    }
}

int main() {
    string lang;
    cout << "�������� ���� / Choose language (ru/eng): ";
    cin >> lang;

    while (lang != "ru" && lang != "eng") {
        cout << "������������ ����. ����������, �������� ���� (ru/eng): ";
        cin >> lang;
    }

    if (lang == "ru") {
        setlocale(LC_ALL, "rus");
    }

    vector<vector<char>> desk(SIZE, vector<char>(SIZE, ' '));
    char currentPlayer = 'X';

    while (true) {
        printDesk(desk);
        int row, col;

        printMessage("����� " + string(1, currentPlayer) + ", ������� ����� ������ � ������� (0-2): ", lang);

        cin >> row >> col;

        if (cin.fail() || row < 0 || row >= SIZE || col < 0 || col >= SIZE || desk[row][col] != ' ') {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            printMessage("������������ ���. ���������� �����.", lang);
            continue;
        }

        desk[row][col] = currentPlayer;

        if (checkWin(desk, currentPlayer)) {
            printDesk(desk);
            printMessage("����� " + string(1, currentPlayer) + " �������!", lang);
            break;
        }

        if (isBoardFull(desk)) {
            printDesk(desk);
            printMessage("�����!", lang);
            break;
        }

        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    return 0;
}
