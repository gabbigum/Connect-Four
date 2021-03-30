//
// Created by Gabi on 30/03/2021.
//

#include "game_engine.h"

struct Move {
    char player;
    int position;
    struct Move *nextMove;
};

struct MovesQueue {
    struct Move *currentMove, *rear;
    // the logic will look like that
    // on UNDO - if the currentMove is rear
    // -> get that data and remove the disc from the board ->removeDisc(board, player, position)
    // on REDO -> read currentMove.nextMove and insertDisc(board, player, position)
};

void playGame() {
    char board[BOARD_HEIGHT][BOARD_WIDTH];
    // moves queue


    fillBoard(board);

    // THIS WHOLE THING UNDER COULD BE SEPARATE METHOD TO BE SELECTED FROM THE MENU
    // FOR EXAMPLE THE GAME COULD BE PLAYED BY MORE THAN 1 PLAYER
    int movesCounter = 1;
    bool hasWinner = false;

    while (!hasWinner) {
        updateBoard(board);

        int position;

        if (movesCounter % 2 == 0) {
            printf("Player B choose a position :");
            scanf("%d", &position);
            insertDisc(board, PLAYER_B, position);

            if (isWinning(board, PLAYER_B)) {
                printf("Player B wins!\n"); // might use string
                hasWinner = true;
            }
        } else {
            printf("Player A choose a position :");
            scanf("%d", &position);
            insertDisc(board, PLAYER_A, position);
            if (isWinning(board, PLAYER_A)) {
                printf("Player A wins!\n"); // might use string
                hasWinner = true;
            }
        }
        movesCounter++;
        position = 0;
    }
}