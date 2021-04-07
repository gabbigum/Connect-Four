//
// Created by Gabi on 30/03/2021.
//

#include <malloc.h>
#include "game_engine.h"

#define SAVE_SIZE 1024

void printActionsMenu(char);

void printChoosePosition(char);

void playerInteraction(char [BOARD_HEIGHT][BOARD_WIDTH], char, int);

bool isPlayerWinning(char [BOARD_HEIGHT][BOARD_WIDTH], char);

void saveGame(int[SAVE_SIZE]);

int loadGame(char *, int *);

void printActionsMenu(char player) {
    printf("Player %c choose an action\n"
           "1. Insert move.\n"
           "2. Undo move.\n"
           "3. Redo move.\n", player);
}

void printChoosePosition(char player) {
    printf("Player %c choose position: \n", player);
}


void saveGame(int save[SAVE_SIZE]) {
    FILE *file;
    char fileName[50];
    printf("Enter file name:\n");

    scanf("%s", fileName);

    file = fopen(fileName, "w");

    printf("Saving to %s...\n", fileName);

    int i = 0;
    while (save[i] < 8) {
        fprintf(file, "%d\n", save[i]);
        i++;
    }

    printf("Game saved!");
    fclose(file);

}

int loadGame(char *fileName, int *arr) {
    FILE *file;
    file = fopen(fileName, "r");

    if (file == NULL) {
        printf("Couldn't find the file.\n");
        return 0;
    }

    int index = 0;
    char line[100];
    while (fgets(line, sizeof(line), file)) {
        int num = atoi(line);
        arr[index] = num;
        index++;
    }

    fclose(file);
    return index;
}

void playerInteraction(char board[6][7], char player, int position) {
    printChoosePosition(player);
    scanf("%d", &position);

    while (insertDisc(board, player, position) == -1) {
        printChoosePosition(player);
        scanf("%d", &position);
    }
}

bool isPlayerWinning(char board[BOARD_HEIGHT][BOARD_WIDTH], char player) {
    if (isWinning(board, player)) {
        updateBoard(board);
        printf("Player %c wins!\n", player);
        return true;
    }
    return false;
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

            playerInteraction(board, PLAYER_B, position);

            hasWinner = isPlayerWinning(board, PLAYER_B);
        } else {

            playerInteraction(board, PLAYER_A, position);

            hasWinner = isPlayerWinning(board, PLAYER_A);
        }
        movesCounter++;
        position = 0;
    }
}

void playGameFromSavedFile() {
    char fileName[50];
    printf("Enter saved file name: ");
    scanf("%s", fileName);
    int arr[SAVE_SIZE];
    // read moves from file
    int lines = loadGame(fileName, &arr);

    for (int i = 0; i < lines; i++) {
        printf("%d\n", arr[i]);
    }

    char board[BOARD_HEIGHT][BOARD_WIDTH];

    fillBoard(board);

    // THIS WHOLE THING UNDER COULD BE SEPARATE METHOD TO BE SELECTED FROM THE MENU
    // FOR EXAMPLE THE GAME COULD BE PLAYED BY MORE THAN 1 PLAYER
    int movesCounter = 1;
    bool hasWinner = false;
    int movesIndex = 0;

    while (!hasWinner) {
        updateBoard(board);

        int position;

        if (movesCounter % 2 == 0) {
            insertDisc(board, PLAYER_B, arr[movesIndex]);

            hasWinner = isPlayerWinning(board, PLAYER_B);
        } else {

            insertDisc(board, PLAYER_A, arr[movesIndex]);

            hasWinner = isPlayerWinning(board, PLAYER_A);
        }
        movesIndex++;
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
    int save[SAVE_SIZE];
    int saveCounter = 0;

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

                    save[saveCounter] = position;
                    saveCounter++;

                    int posY;

                    while ((posY = insertDisc(board, PLAYER_B, position)) == -1) {
                        printChoosePosition(PLAYER_B);
                        scanf("%d", &position);
                    }

                    currentLast = addToEnd(&qHead, PLAYER_B, position, posY);

                    hasWinner = isPlayerWinning(board, PLAYER_B);
                    break;
                case 2:
                    if (currentLast == NULL) {
                        printf("No moves to undo.\n");
                    } else {
                        printf("Undoing move.\n");
                        saveCounter--;
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
                            saveCounter++;
                            insertDisc(board, currentLast->player, currentLast->posX);
                            break;
                        }
                    }
                    if (currentLast->nextMove == NULL) {
                        printf("No moves to redo.\n");
                    } else {
                        printf("Redoing move.\n");
                        saveCounter++;
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

                    save[saveCounter] = position;
                    saveCounter++;

                    while ((posY = insertDisc(board, PLAYER_A, position)) == -1) {
                        printChoosePosition(PLAYER_A);
                        scanf("%d", &position);
                    }

                    currentLast = addToEnd(&qHead, PLAYER_A, position, posY);

                    hasWinner = isPlayerWinning(board, PLAYER_A);
                    break;
                case 2:
                    if (currentLast == NULL) {
                        printf("No moves to undo.\n");
                    } else {
                        printf("Undoing move.\n");
                        saveCounter--;
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
                            saveCounter++;
                            insertDisc(board, currentLast->player, currentLast->posX);
                            break;
                        }
                    }
                    if (currentLast->nextMove == NULL) {
                        printf("No moves to redo.\n");
                    } else {
                        printf("Redoing move.\n");
                        saveCounter++;
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

    saveGame(save);
}
