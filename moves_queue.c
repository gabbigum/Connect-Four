//
// Created by Gabi on 30/03/2021.
//

#include <malloc.h>
#include "moves_queue.h"

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

