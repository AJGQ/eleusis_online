#ifndef PLAYER_H
#define PLAYER_H

#include <stdlib.h>
#include <stdbool.h>
#include "card.h"

struct player {
    Card* cards;
    size_t len_cards;
    size_t capacity;
};

typedef struct player Player;

void player_init(Player*, Card*, size_t, size_t);

int player_give(Player*, Card);
int player_take(Player*, Card);

// return true if it found, false otherwise,
// if it found stores it in the 3rd param
bool player_index_card(Player*, Card, size_t* );

#endif
