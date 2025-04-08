#include <iostream>
#include <fstream>
#include <cctype>
#include <string>

using namespace std;

constexpr int LETTER = 0;
constexpr int DIGIT = 1;
constexpr int UNKNOWN = 99;
constexpr int END_OF_FILE = -1;

constexpr int INT_LIT = 10;
constexpr int IDENT = 11;
constexpr int ASSIGN_OP = 20;
constexpr int ADD_OP = 21;
constexpr int SUB_OP = 22;
constexpr int MULT_OP = 23;
constexpr int DIV_OP = 24;
constexpr int LEFT_PAREN = 25;
constexpr int RIGHT_PAREN = 26;

int   charClass;
string lexeme;
char  nextChar;
int   nextToken;
ifstream in_fp;

void addChar() {
    lexeme.push_back(nextChar);
}

void getChar() {
    if (!in_fp.get(nextChar)) {
        charClass = END_OF_FILE;
    }
    else {
        if (isalpha(static_cast<unsigned char>(nextChar))) {
            charClass = LETTER;
        }
        else if (isdigit(static_cast<unsigned char>(nextChar))) {
            charClass = DIGIT;
        }
        else {
            charClass = UNKNOWN;
        }
    }
}

void getNonBlank() {
    while (isspace(static_cast<unsigned char>(nextChar))) {
        getChar();
    }
}

int lookup(char ch) {
    switch (ch) {
    case '(':
        addChar();
        nextToken = LEFT_PAREN;
        break;
    case ')':
        addChar();
        nextToken = RIGHT_PAREN;
        break;
    case '+':
        addChar();
        nextToken = ADD_OP;
        break;
    case '-':
        addChar();
        nextToken = SUB_OP;
        break;
    case '*':
        addChar();
        nextToken = MULT_OP;
        break;
    case '/':
        addChar();
        nextToken = DIV_OP;
        break;
    default:
        addChar();
        nextToken = END_OF_FILE;
        break;
    }
    return nextToken;
}

int lex() {
    lexeme.clear();
    getNonBlank();

    switch (charClass) {
    case LETTER:
        addChar();
        getChar();
        while (charClass == LETTER || charClass == DIGIT) {
            addChar();
            getChar();
        }
        nextToken = IDENT;
        break;

    case DIGIT:
        addChar();
        getChar();
        while (charClass == DIGIT) {
            addChar();
            getChar();
        }
        nextToken = INT_LIT;
        break;

    case UNKNOWN:
        lookup(nextChar);
        getChar();
        break;

    case END_OF_FILE:
        nextToken = END_OF_FILE;
        lexeme = "EOF";
        break;
    }

    cout << "Next token is: " << nextToken
        << ", Next lexeme is: " << lexeme << endl;

    return nextToken;
}

int main() {
    in_fp.open("front.in");
    if (!in_fp.is_open()) {
        cerr << "ERROR - cannot open the input file (front.in)\n";
        return 1;
    }

    getChar();

    do {
        lex();
    } while (nextToken != END_OF_FILE);

    in_fp.close();
}
