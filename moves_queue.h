//
// Created by Gabi on 30/03/2021.
//

#ifndef CONNECT_FOUR_MOVES_QUEUE_H
#define CONNECT_FOUR_MOVES_QUEUE_H

// Queue implementation as doubly linked list
struct Move {
    char player;
    int posX;
    int posY;
    struct Move *nextMove;
    struct Move *prevMove;
};

struct Move *addToEnd(struct Move **queue, char player, int posX, int posY);

#endif //CONNECT_FOUR_MOVES_QUEUE_H
