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


int main() {
    char board[BOARD_HEIGHT][BOARD_WIDTH];

    fillBoard(board);

    // PLAYER A
    // PLAYER B

    // test disc insertion
    insertDisc(board, PLAYER_1, 3);
    insertDisc(board, PLAYER_2, 1);
    insertDisc(board, PLAYER_1, 4);
    insertDisc(board, PLAYER_1, 5);
    insertDisc(board, PLAYER_2, 6);

    insertDisc(board, PLAYER_2, 3);
    insertDisc(board, PLAYER_2, 1);
    insertDisc(board, PLAYER_2, 4);
    insertDisc(board, PLAYER_2, 5);
    insertDisc(board, PLAYER_2, 6);


    bool isPlayerOneWinning = checkHorizontal(board, PLAYER_1);

    updateBoard(board);

    if(isPlayerOneWinning) {
        printf("Player 1 wins\n");
    }

    bool isPlayerTwoWinning = checkHorizontal(board, PLAYER_2);

    if(isPlayerTwoWinning) {
        printf("Player 2 wins\n");
    }

    return 0;
}

bool checkHorizontal(char board[BOARD_HEIGHT][BOARD_WIDTH], char player) {
    // scope is WINNING_DISCS
    // use windowing for horizontal board

    //int start, end;


    for(int i = 0; i < BOARD_HEIGHT; i++) {

        // sliding window
        for(int start = 0, end = WINNING_DISCS; end < BOARD_WIDTH; start++, end++) {
            int consec = 0;

            for(int j = start; j <= end; j++) {
                if(board[i][j] == player) {
                    consec++;
                } else {
                    consec = 0;
                }
                if(consec == 4) {
                    return true;
                }
            }
        }
        //start = 0;
        //end = WINNING_DISCS;
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
