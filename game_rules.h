//
// Created by Gabi on 29/03/2021.
//
#pragma once

#include <stdbool.h>

#define BOARD_WIDTH 7
#define BOARD_HEIGHT 6
#define WINNING_DISCS 4

bool isWinning(char [BOARD_HEIGHT][BOARD_WIDTH], char);

bool checkHorizontal(char [BOARD_HEIGHT][BOARD_WIDTH], char);

bool checkVertical(char [BOARD_HEIGHT][BOARD_WIDTH], char);

bool checkDiagonal(char [BOARD_HEIGHT][BOARD_WIDTH], char);

bool checkLeftDiagonal(char [BOARD_HEIGHT][BOARD_WIDTH], char);
