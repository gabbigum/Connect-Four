//
// Created by Gabi on 29/03/2021.
//

#pragma once
#include "game_rules.h"
#include "stdio.h"

void updateBoard(char [BOARD_HEIGHT][BOARD_WIDTH]);

void fillBoard(char [BOARD_HEIGHT][BOARD_WIDTH]);

bool insertDisc(char [BOARD_HEIGHT][BOARD_WIDTH], char, int);
