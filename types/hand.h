#ifndef HAND_H
#define HAND_H

#include <stdlib.h>
#include <stdbool.h>
#include "card.h"

#define MAX_HAND 80

struct hand {
    Card** cards;
    size_t len_cards;
};

typedef struct hand Hand;

void hand_init(Hand*);

void hand_create(Hand*, Card**, size_t);

int hand_insert(Hand*, Card*);

int hand_remove(Hand*, Card);

// return true if it found, false otherwise,
// if it found stores it in the 3rd param
bool hand_index_card(Hand*, Card, size_t*);

int hand_print(Hand*, char*);


#endif
