//
// Created by Gabi on 29/03/2021.
//

#include "board_actions.h"
bool insertDisc(char board[BOARD_HEIGHT][BOARD_WIDTH], char player, int position) {
    if (position > BOARD_WIDTH || position <= 0) {
        return false;
    }
    position--;
    // check if it is at the top of the board
    //TODO bug there
    if (board[0][position] != '.') {
        printf("Your move is not valid. You have reached the top of the board.\n");
        return false;
    }

    // iterate over the height
    int i = 0;
    while (i < BOARD_HEIGHT) {
        if (board[i][position] != '.') {
            break;
        }
        i++;
    }

    board[i - 1][position] = player;

    return true;
}

void updateBoard(char board[BOARD_HEIGHT][BOARD_WIDTH]) {
    // move numbers
    for (int i = 1; i <= BOARD_WIDTH; i++) {
        printf("%d", i);
    }
    printf("\n");

    for (int i = 0; i < BOARD_HEIGHT; i++) {
        char line[BOARD_WIDTH];
        for (int j = 0; j < BOARD_WIDTH; j++) {
            line[j] = board[i][j];
        }
        printf("%s", line);
        printf("\n");
    }
}

void fillBoard(char board[BOARD_HEIGHT][BOARD_WIDTH]) {
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            board[i][j] = '.';
        }
    }
}
