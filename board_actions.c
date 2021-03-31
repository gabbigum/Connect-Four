//
// Created by Gabi on 29/03/2021.
//

#include "board_actions.h"

// returns the Y coordinate of the inserted move
int insertDisc(char board[BOARD_HEIGHT][BOARD_WIDTH], char player, int position) {
    if (position > BOARD_WIDTH || position <= 0) {
        printf("Your move is not valid. Your posX must be between %d and %d. Please select another posX.\n", 1, BOARD_WIDTH);
        return -1;
    }
    position--;
    // check if it is at the top of the board
    if (board[0][position] != '.') {
        printf("Your move is not valid. You have reached the top of the board. Please select another posX.\n");
        return -1;
    }


    // iterate over the height
    int i = 0;
    while (i < BOARD_HEIGHT) {
        if (board[i][position] != '.') {
            break;
        }
        i++;
    }

    int resultIndex = i - 1; // because we don't want to overlap existing elements in the board
    board[resultIndex][position] = player;

    return resultIndex;
}

bool deleteDisc(char board[BOARD_HEIGHT][BOARD_WIDTH], int posX, int posY) {
    if (posX > BOARD_WIDTH || posY <= 0) {
        return false;
    }
    posX--;

    board[posY][posX] = '.';

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
