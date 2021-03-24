#include <stdio.h>

#define BOARD_WIDTH 7
#define BOARD_HEIGHT 6

void displayBoard(char [BOARD_HEIGHT][BOARD_WIDTH]);

int main() {

    char board[BOARD_HEIGHT][BOARD_WIDTH];

    // fill board
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            board[i][j] = '.';
        }
    }
    // display board
    displayBoard(board);
    return 0;
}


void displayBoard(char board[BOARD_HEIGHT][BOARD_WIDTH]) {
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        char line[BOARD_WIDTH];
        for (int j = 0; j < BOARD_WIDTH; j++) {
            line[j] = board[i][j];
        }
        printf("%s", line);
        printf("\n");
    }
}
