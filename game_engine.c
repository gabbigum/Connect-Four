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
    int posX;
    int posY;
    struct Move *nextMove;
    struct Move *prevMove;
};

struct Move *addToEnd(struct Move **queue, char player, int posX, int posY) {
    struct Move *iterator, *newMove;

    newMove = (struct Move *) malloc(sizeof(struct Move));
    newMove->player = player;
    newMove->posX = posX;
    newMove->posY = posY;
    newMove->nextMove = NULL;
    newMove->prevMove = NULL;

    if (*queue == NULL) {
        *queue = newMove;
    } else {
        iterator = *queue;

        while (iterator->nextMove != NULL) {
            iterator = iterator->nextMove;
        }

        iterator->nextMove = newMove;
        iterator->nextMove->prevMove = iterator;
    }
    return newMove;
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
    struct Move *qHead = NULL;
    struct Move *currentLast = NULL;
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

            while (action < 0 || action > 3) {
                printf("Action does not exist in the list.\n");
                printActionsMenu(PLAYER_B);
                scanf("%d", &action);
            }

            switch (action) {
                case 1: // make this separate method
                    printChoosePosition(PLAYER_B);
                    scanf("%d", &position);

                    int posY;

                    while ((posY = insertDisc(board, PLAYER_B, position)) == -1) {
                        printChoosePosition(PLAYER_B);
                        scanf("%d", &position);
                    }

                    currentLast = addToEnd(&qHead, PLAYER_B, position, posY);

                    if (isWinning(board, PLAYER_B)) {
                        updateBoard(board);
                        printf("Player B wins!\n"); // might use string
                        hasWinner = true;
                    }
                    break;
                case 2:
                    if (currentLast == NULL) {
                        printf("No moves to undo.\n");
                    } else {
                        printf("Undoing move.\n");
                        deleteDisc(board, currentLast->posX, currentLast->posY);
                        currentLast = currentLast->prevMove;
                    }
                    break;
                case 3:
                    if (currentLast == NULL) {
                        if (qHead == NULL) {
                            printf("No moves to redo.\n");
                            break;
                        } else {
                            currentLast = qHead;
                            insertDisc(board, currentLast->player, currentLast->posX);
                            break;
                        }
                    }
                    if (currentLast->nextMove == NULL) {
                        printf("No moves to redo.\n");
                    } else {
                        printf("Redoing move.\n");
                        currentLast = currentLast->nextMove;
                        insertDisc(board, currentLast->player, currentLast->posX);

                    }

                    break;
                default:
                    break;
            }

        } else {
            printActionsMenu(PLAYER_A);

            int action;
            scanf("%d", &action);

            while (action < 0 || action > 3) {
                printf("Action does not exist in the list.\n");
                printActionsMenu(PLAYER_A);

                scanf("%d", &action);
            }

            switch (action) {
                case 1: // make this separate method
                    printChoosePosition(PLAYER_A);
                    scanf("%d", &position);
                    int posY;

                    while ((posY = insertDisc(board, PLAYER_A, position)) == -1) {
                        printChoosePosition(PLAYER_A);
                        scanf("%d", &position);
                    }

                    currentLast = addToEnd(&qHead, PLAYER_A, position, posY);

                    if (isWinning(board, PLAYER_A)) {
                        updateBoard(board);
                        printf("Player A wins!\n"); // might use string
                        hasWinner = true;
                    }
                    break;
                case 2:
                    if (currentLast == NULL) {
                        printf("No moves to undo.\n");
                    } else {
                        printf("Undoing move.\n");
                        deleteDisc(board, currentLast->posX, currentLast->posY);
                        currentLast = currentLast->prevMove;
                    }
                    break;
                case 3:
                    if (currentLast == NULL) {
                        if (qHead == NULL) {
                            printf("No moves to redo.\n");
                            break;
                        } else {
                            currentLast = qHead;
                            insertDisc(board, currentLast->player, currentLast->posX);
                            break;
                        }
                    }
                    if (currentLast->nextMove == NULL) {
                        printf("No moves to redo.\n");
                    } else {
                        printf("Redoing move.\n");
                        currentLast = currentLast->nextMove;
                        insertDisc(board, currentLast->player, currentLast->posX);
                    }
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
           "2. Undo move.\n"
           "3. Redo move.\n", player);
}

void printChoosePosition(char player) {
    printf("Player %c choose position: \n", player);
}