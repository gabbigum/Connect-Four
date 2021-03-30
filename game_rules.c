//
// Created by Gabi on 29/03/2021.
//

#include "game_rules.h"

bool areFourConsecutive(char player, const char *diagonals);

bool checkLeftDiagonal(char [BOARD_HEIGHT][BOARD_WIDTH], char);

bool checkRightDiagonal(char [BOARD_HEIGHT][BOARD_WIDTH], char);


bool checkVertical(char board[BOARD_HEIGHT][BOARD_WIDTH], char player) {
    // iterate columns

    for (int i = 0; i < BOARD_WIDTH; i++) {

        for (int start = BOARD_HEIGHT - 1, end = start - 4; end >= 0; start--, end--) {
            int consec = 0;

            for (int j = start; j >= end; j--) {
                if (board[j][i] == player) {
                    consec++;
                } else {
                    consec = 0;
                }
                if (consec == 4) {
                    return true;
                }
            }
        }
    }
    return false;
}

// loops over rows starting from the bottom and checks for horizontal connect four starting from left to right
bool checkHorizontal(char board[BOARD_HEIGHT][BOARD_WIDTH], char player) {
    // scope is WINNING_DISCS
    // use windowing for horizontal board

    for (int i = BOARD_HEIGHT - 1; i >= 0; i--) {

        // sliding window it would be better if it starts from the bottom
        for (int start = 0, end = WINNING_DISCS; end < BOARD_WIDTH; start++, end++) {
            int consec = 0;

            for (int j = start; j <= end; j++) {
                if (board[i][j] == player) {
                    consec++;
                } else {
                    consec = 0;
                }
                if (consec == 4) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool checkDiagonal(char board[BOARD_HEIGHT][BOARD_WIDTH], char player) {
    // diagonal windowing
    // check left diagonal
    // check right diagonal
    return checkLeftDiagonal(board, player) || checkRightDiagonal(board, player);
}


// windowing to see if diagonals contains four consecutive player letters
bool areFourConsecutive(char player, const char *diagonals) {
    for (int start = 0, end = WINNING_DISCS; end < BOARD_WIDTH; start++, end++) {
        int consec = 0;

        for (int ii = start; ii <= end; ii++) {
            if (diagonals[ii] == player) {
                consec++;
            } else {
                consec = 0;
            }
            if (consec == 4) {
                return true;
            }
        }
    }
    return false;
}

bool checkRightDiagonal(char board[BOARD_HEIGHT][BOARD_WIDTH], char player) {
    // lower half - works
    for (int k = BOARD_HEIGHT - 1; k >= 0; k--) {
        int i = k;
        int j = BOARD_WIDTH - 1;

        char diagonals[BOARD_HEIGHT];
        int counter = 0;
        // i must be board[max][max] starting
        while (i >= 0) {
            diagonals[counter] = board[i][j];
            i--;
            j--;
            counter++;
        }
        counter = 0;

        if (areFourConsecutive(player, diagonals)) {
            return true;
        }
    }

    // upper half

    return false;
}

bool checkLeftDiagonal(char board[BOARD_HEIGHT][BOARD_WIDTH], char player) {
    // start with lower diagonal
    for (int k = 1; k <= BOARD_WIDTH - 1; k++) {
        int i = BOARD_HEIGHT - 1;
        int j = k;

        // TODO might be board_height -1
        char diagonals[BOARD_HEIGHT];
        int counter = 0;

        while (j <= BOARD_WIDTH - 1) {
            diagonals[counter] = board[i][j];
            i--;
            j++;
            counter++;
        }
        counter = 0;

        if (areFourConsecutive(player, diagonals)) {
            return true;
        }
    }

    // upper diagonal
    for (int k = 0; k <= BOARD_HEIGHT - 1; k++) {
        int i = k;
        int j = 0;

        // create array to store the elements
        char diagonals[BOARD_HEIGHT];
        int counter = 0;

        while (i >= 0) {
            diagonals[counter] = board[i][j];
            i--;
            j++;
            counter++;
        }
        counter = 0;

        if (areFourConsecutive(player, diagonals)) {
            return true;
        }
    }
    return false;
}


bool isWinning(char board[BOARD_HEIGHT][BOARD_WIDTH], char player) {
    return checkHorizontal(board, player) || checkVertical(board, player) || checkDiagonal(board, player);
}
