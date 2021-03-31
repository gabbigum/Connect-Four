//
// Created by Gabi on 29/03/2021.
//

#ifndef CONNECT_FOUR_BOARD_ACTIONS_H
#define CONNECT_FOUR_BOARD_ACTIONS_H

#include "game_rules.h"
#include "stdio.h"

void updateBoard(char [BOARD_HEIGHT][BOARD_WIDTH]);

void fillBoard(char [BOARD_HEIGHT][BOARD_WIDTH]);

int insertDisc(char [BOARD_HEIGHT][BOARD_WIDTH], char, int);

bool deleteDisc(char [BOARD_HEIGHT][BOARD_WIDTH], int, int);

#endif
