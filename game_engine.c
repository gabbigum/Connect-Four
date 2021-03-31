//
// Created by Gabi on 30/03/2021.
//

#include <malloc.h>
#include "game_engine.h"

void printActionsMenu(char);
void printChoosePosition(char);

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

    if (*queue == NULL) {
        *queue = newMove;
    } else {
        iterator = *queue;
        currentPrev = iterator;

        while (iterator->nextMove != NULL) {
            currentPrev = iterator;
            iterator = iterator->nextMove;
        }

        iterator->nextMove = newMove;
        newMove->prevMove = currentPrev;
        iterator->prevMove = currentPrev;
    }
}

void playDefaultGame() {
    char board[BOARD_HEIGHT][BOARD_WIDTH];

    fillBoard(board);

    // THIS WHOLE THING UNDER COULD BE SEPARATE METHOD TO BE SELECTED FROM THE MENU
    // FOR EXAMPLE THE GAME COULD BE PLAYED BY MORE THAN 1 PLAYER
    int movesCounter = 1;
    bool hasWinner = false;

    while (!hasWinner) {
        updateBoard(board);

        int position;

        if (movesCounter % 2 == 0) {
            printChoosePosition(PLAYER_B);
            scanf("%d", &position);

            while (insertDisc(board, PLAYER_B, position) == -1) {
                printChoosePosition(PLAYER_B);
                scanf("%d", &position);
            }
            if (isWinning(board, PLAYER_B)) {
                updateBoard(board);
                printf("Player B wins!\n"); // might use string
                hasWinner = true;
            }
        } else {
            printChoosePosition(PLAYER_A);
            scanf("%d", &position);

            while (insertDisc(board, PLAYER_A, position) == -1) {
                printChoosePosition(PLAYER_A);
                scanf("%d", &position);
            }

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

void playGameWithFeatures() {
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
            printActionsMenu(PLAYER_B);

            int action;
            scanf("%d", &action);

            while (action < 0 || action > 2) {
                printf("Action does not exist in the list.");
                printActionsMenu(PLAYER_B);
                scanf("%d", &action);
            }

            switch (action) {
                case 1: // make this separate method
                    printf("Player B choose a position :");
                    scanf("%d", &position);

                    while (insertDisc(board, PLAYER_B, position) == -1) {
                        printf("Player B choose a position :");
                        scanf("%d", &position);
                    }

                    addToEnd(&qHead, PLAYER_B, position);

                    if (isWinning(board, PLAYER_B)) {
                        updateBoard(board);
                        printf("Player B wins!\n"); // might use string
                        hasWinner = true;
                    }
                    break;
                case 2:
                    printf("Undoing move.\n");
                    break;
                case 3:
                    printf("Redoing move.\n");
                    break;
                default:
                    break;
            }

        } else {
            printActionsMenu(PLAYER_A);

            int action;
            scanf("%d", &action);

            while (action < 0 || action > 2) {
                printf("Action does not exist in the list.");
                printActionsMenu(PLAYER_A);

                scanf("%d", &action);
            }

            switch (action) {
                case 1: // make this separate method
                    printf("Player A choose a position :");
                    scanf("%d", &position);

                    while (insertDisc(board, PLAYER_A, position) == -1) {
                        printf("Player A choose a position :");
                        scanf("%d", &position);
                    }

                    addToEnd(&qHead, PLAYER_A, position);

                    if (isWinning(board, PLAYER_A)) {
                        updateBoard(board);
                        printf("Player A wins!\n"); // might use string
                        hasWinner = true;
                    }
                    break;
                case 2:
                    printf("Undoing move.\n");
                    break;
                case 3:
                    printf("Redoing move.\n");
                    break;
                default:
                    break;
            }

        }
        movesCounter++;
        position = 0;
    }
}


void printActionsMenu(char player) {
    printf("Player %c choose an action\n"
           "1. Insert move.\n"
           "1. Undo move.\n"
           "2. Redo move.\n", player);
}

void printChoosePosition(char player) {
    printf("Player %c choose position: \n", player);
}