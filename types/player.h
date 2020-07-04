#ifndef PLAYER_H
#define PLAYER_H

#include <stdlib.h>
#include "card.h"
#include "hand.h"

struct player {
    Hand* hand;
    int sockfd;
};

typedef struct player Player;

void player_init(Player*, int);

void player_give_hand(Player*, Hand*);

void player_send_hand(Player*);

#endif
