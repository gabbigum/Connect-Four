//
// Created by Gabi on 30/03/2021.
//

#include <malloc.h>
#include "game_engine.h"

//TODO I might want to use doubly linked list
struct Move {
    char player;
    int position;
    struct Move *nextMove;
    struct Move *prevMove;
};

void addToEnd(struct Move **queue, char player, int position) {
    struct Move *iterator, *newMove, *currentPrev;

    newMove = (struct Move *) malloc(sizeof(struct Move));
    newMove->player = player;
    newMove->position = position;
    newMove->nextMove = NULL;
    newMove->prevMove = NULL;

    if(*queue == NULL) {
        *queue = newMove;
    } else {
        iterator = *queue;
        currentPrev = iterator;

        while(iterator->nextMove != NULL) {
            currentPrev = iterator;
            iterator = iterator->nextMove;
        }

        iterator->nextMove = newMove;
        newMove->prevMove = currentPrev;
        iterator->prevMove = currentPrev;
    }
}


void playGame() {
    char board[BOARD_HEIGHT][BOARD_WIDTH];
    // moves queue
    struct Move *qHead;
  //  struct Move *currentMove;

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

            while(insertDisc(board, PLAYER_B, position) == -1) {
                printf("Player B choose a position :");
                scanf("%d", &position);
            }

            addToEnd(&qHead, PLAYER_B, position);

            if (isWinning(board, PLAYER_B)) {
                updateBoard(board);
                printf("Player B wins!\n"); // might use string
                hasWinner = true;
            }
        } else {
            printf("Player A choose a position :");
            scanf("%d", &position);
            insertDisc(board, PLAYER_A, position);

            addToEnd(&qHead, PLAYER_A, position); // test this

            if (isWinning(board, PLAYER_A)) {
                updateBoard(board);
                printf("Player A wins!\n"); // might use string
                hasWinner = true;
            }
        }
        movesCounter++;
        position = 0;
    }
}