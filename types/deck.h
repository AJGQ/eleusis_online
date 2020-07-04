#ifndef DECK_H
#define DECK_H

#include <stdlib.h>
#include <stdbool.h>
#include "card.h"

#define MAX_CARDS 80
#define MAX_NORMAL MAX_CARDS>>1

struct deck {
    Card** cards;
    size_t len_cards;
};

typedef struct deck Deck;

void deck_init(Deck*);

void deck_shuffle(Deck*);

int deck_put(Deck*, Card*);
int deck_get(Deck*, Card**);

#endif
