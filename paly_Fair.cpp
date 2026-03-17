#include <iostream>
#include <string>
#include <cctype>
using namespace std;

char matrix[5][5];


void generateMatrix(string key) {
    bool used[26] = {false};
    used['J' - 'A'] = true;   // Treat J as I

    int row = 0, col = 0;

  
    for (char ch : key) {
        if (isalpha(ch)) {
            ch = toupper(ch);
            if (ch == 'J') ch = 'I';

            if (!used[ch - 'A']) {
                matrix[row][col++] = ch;
                used[ch - 'A'] = true;

                if (col == 5) {
                    col = 0;
                    row++;
                }
            }
        }
    }

  
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (!used[ch - 'A']) {
            matrix[row][col++] = ch;
            used[ch - 'A'] = true;

            if (col == 5) {
                col = 0;
                row++;
            }
        }   
    }
}


    cout << "\nKey Matrix:\n";
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++)
            cout << matrix[i][j] << " ";
        cout << endl;
    }
}


void findPosition(char ch, int &row, int &col) {
    if (ch == 'J') ch = 'I';

    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            if (matrix[i][j] == ch) {
                row = i;
                col = j;
                return;
            }
}


string prepareText(string text) {
    string result = "";

    // Remove spaces and convert to uppercase
    for (char ch : text) {
        if (isalpha(ch)) {
            ch = toupper(ch);
            if (ch == 'J') ch = 'I';
            result += ch;
        }
    }


    for (int i = 0; i < result.length(); i += 2) {
        if (i + 1 < result.length() && result[i] == result[i + 1])
            result.insert(i + 1, 1, 'X');
    }

    // If odd length, add X
    if (result.length() % 2 != 0)
        result += 'X';

    return result;
}


string encrypt(string text) {
    text = prepareText(text);
    string cipher = "";

    for (int i = 0; i < text.length(); i += 2) {
        int r1, c1, r2, c2;
        findPosition(text[i], r1, c1);
        findPosition(text[i + 1], r2, c2);

        if (r1 == r2) {
            cipher += matrix[r1][(c1 + 1) % 5];
            cipher += matrix[r2][(c2 + 1) % 5];
        }
        else if (c1 == c2) {
            cipher += matrix[(r1 + 1) % 5][c1];
            cipher += matrix[(r2 + 1) % 5][c2];
        }
        else {
            cipher += matrix[r1][c2];
            cipher += matrix[r2][c1];
        }
    }

    return cipher;
}


string decrypt(string text) {
    string plain = "";

    for (int i = 0; i < text.length(); i += 2) {
        int r1, c1, r2, c2;
        findPosition(text[i], r1, c1);
        findPosition(text[i + 1], r2, c2);

        if (r1 == r2) {
            plain += matrix[r1][(c1 + 4) % 5];
            plain += matrix[r2][(c2 + 4) % 5];
        }
        else if (c1 == c2) {
            plain += matrix[(r1 + 4) % 5][c1];
            plain += matrix[(r2 + 4) % 5][c2];
        }
        else {
            plain += matrix[r1][c2];
            plain += matrix[r2][c1];
        }
    }

    return plain;
}

int main() {
    string key, text;

    cout << "Enter Key: ";
    getline(cin, key);

    generateMatrix(key);
    printMatrix();
    // input plain text
    cout << "\nEnter Plaintext: ";
    getline(cin, text);

    string encrypted = encrypt(text);
    cout << "\nEncrypted Text: " << encrypted << endl;

    string decrypted = decrypt(encrypted);
    cout << "Decrypted Text: " << decrypted << endl;

    return 0;
}

