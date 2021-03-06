/*
* @author: Hirthanan, Ashwin
* Text based chess game using oop design
*/

#include <iostream>
#include <stdlib.h>
#include "class/Piece.cpp"
#include "class/Pawn.cpp"
#include <string>
#include <algorithm>

using namespace std;

void movePiece(string[8][8]);
void drawBoard(string[8][8]);
void resetBoard(string[8][8], char[2][8], char[2][8]);
void skipLine(int);

/* validates if user input is correct */

bool isValidCoord(int xCoord, int yCoord) { //pass xCoord as char but is converted to ascii number
    if((97 <= xCoord && xCoord<= 104) && (0 <= yCoord && yCoord <= 7)) {
        return true;
    }
    return false;
}

bool isLengthTwo(string str) {
    if(str.length() == 2) {
        return true;
    }
    return false;
}

/* gets the location of the piece from user
*  converts from string to 2 ints
*  the letter gets converted using the letter array
*  the number gets converted using atoi from stdlib.h
*/

void movePiece(string board[8][8]) {
    char raw[2], raw2[2];
    string userInput, userInput2;
    char letters[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    int y, x, y2, x2;

    drawBoard(board);
    cout << "Enter the piece you want to move: ";
    cin >> userInput;
    raw[0] = userInput[0];
    raw[1] = userInput[1];
    raw[0] = tolower(raw[0]);
    y = 8 - (raw[1] - '0'); //converts to proper number by subtracting ascii '0'
    char temp = raw[0];
    for (int i=0; i<8; i++) {
        if (letters[i] == temp) {
            x = i;
            break;
        }
    }

    if(isValidCoord(raw[0], y) && isLengthTwo(userInput)) {
        if(board[y][x] == " "){
            cout << "Cannot Select Empty Space" << endl;
            movePiece(board);
            return;
        }
    }
    else {
        cout <<"Invalid input, please input correctly using the format (a-h)(1-8)" << endl;
        movePiece(board);
        return;

    }

    cout << "Enter the location you want to move to: ";
    cin >> userInput2;
    raw2[0] = userInput2[0];
    raw2[1] = userInput2[1];
    y2 = 8 - (raw2[1] - '0');
    raw2[0] = tolower(raw2[0]);
    char temp2 = raw2[0];
    for (int i=0; i<8; i++) {
        if (letters[i] == temp2) {
            x2 = i;
            break;
        }
    }

    if(isValidCoord(raw2[0], y2) && isLengthTwo(userInput2)){
        board[y2][x2] = board[y][x];
        board[y][x] = ' ';
    }
    else {
        cout <<"Invalid input, please input correctly using the format (a-h)(1-8)" << endl;
        movePiece(board);
        return;
    }

    movePiece(board);
}

void drawBoard(string board[8][8]) {
    skipLine(2);
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            if (j==0)
                cout << 8-(i) << "  " << '[' << board[i][j] << ']';
            else
                cout << "[" << board[i][j] << "]";
        }
        cout << endl;
    }
    cout << "" << endl;
    cout << "    a  b  c  d  e  f  g  h" << endl;
}

/* string piece1[][] and piece2[][]
*  will be piece arrays eventually instead of string arrrays
*/

void resetBoard(string board[8][8], char piece1[2][8], char piece2[2][8]) {
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            if (i<2)
                board[i][j] = piece1[i][j];
            else if (i>5) {
                if (i==6)
                    board[i][j] = piece2[i-5][j];
                else
                    board[i][j] = piece2[i-7][j];
            }
            else
                board[i][j] = ' ';
        }
    }
}

void skipLine(int x) {
    for (int i=0; i<x; i++)
        cout << "" << endl;
}

int main() {
    string board[8][8];
    char piece1[2][8] = {{'c','k','b','q','k','b','k','c'},{'p','p','p','p','p','p','p','p'}};
    char piece2[2][8] = {{'C','K','B','Q','K','B','K','C'},{'P','P','P','P','P','P','P','P'}};

    Pawn pawn("Pawn","white", 0, 5);
    pawn.itsTurn += 1;

    cout << pawn.itsTurn << endl;

    resetBoard(board, piece1, piece2);
    movePiece(board);

    return 0;
}