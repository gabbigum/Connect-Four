#include <stdio.h>
#include <stdbool.h>

#define BOARD_WIDTH 7
#define BOARD_HEIGHT 6

#define PLAYER_1 'A'
#define PLAYER_2 'B'

#define WINNING_DISCS 4


void updateBoard(char [BOARD_HEIGHT][BOARD_WIDTH]);

void fillBoard(char [BOARD_HEIGHT][BOARD_WIDTH]);

bool insertDisc(char [BOARD_HEIGHT][BOARD_WIDTH], char, int);

bool checkHorizontal(char [BOARD_HEIGHT][BOARD_WIDTH], char);

bool checkVertical(char [BOARD_HEIGHT][BOARD_WIDTH], char);

int main() {
    char board[BOARD_HEIGHT][BOARD_WIDTH];

    fillBoard(board);


    int movesCounter = 1;
    bool hasWinner = false;

    while (!hasWinner) {
        updateBoard(board);

        int position;

        if (movesCounter % 2 == 0) {
            printf("Player 2 choose a position :");
            scanf("%d", &position);
            insertDisc(board, PLAYER_2, position);
            if (checkHorizontal(board, PLAYER_2) || checkVertical(board, PLAYER_2)) {
                printf("Player 2 wins\n"); // might use string
                hasWinner = true;
            }
        } else {
            printf("Player 1 choose a position :");
            scanf("%d", &position);
            insertDisc(board, PLAYER_1, position);
            if (checkHorizontal(board, PLAYER_1) || checkVertical(board, PLAYER_1)) {
                printf("Player 1 wins\n"); // might use string
                hasWinner = true;
            }
        }
        movesCounter++;
        position = 0;
    }
    return 0;
}

// loops over columns and checks for vertical connect four starting from the bottom
bool checkVertical(char board[BOARD_HEIGHT][BOARD_WIDTH], char player) {
    // iterate columns

    for (int i = 0; i < BOARD_WIDTH; i++) {

        // it would be better if it starts from the bottom
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

bool insertDisc(char board[BOARD_HEIGHT][BOARD_WIDTH], char player, int position) {
    if (position > BOARD_WIDTH || position <= 0) {
        return false;
    }
    position--;
    // check if it is at the top of the board
    if (board[0][position] == PLAYER_1 ||
        board[0][position] == PLAYER_2) {
        return false;
    }

    // iterate over the height
    int i = 0;
    while (i < BOARD_HEIGHT) {
        if (board[i][position] == PLAYER_1 ||
            board[i][position] == PLAYER_2) {
            //  i--;
            break;
        }
        i++;
    }

    board[i - 1][position] = player;

    return true;
}

void updateBoard(char board[BOARD_HEIGHT][BOARD_WIDTH]) {
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
