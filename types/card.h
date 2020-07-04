#ifndef CARD_H
#define CARD_H

#include <stdbool.h>

enum suit {
    CLUBS,
    DIAMONDS,
    HEARTS,
    SPADES
};

enum value {
    JACK = 8,
    QUEEN = 9,
    KING = 10,
    ACE = 11
};

typedef enum suit Suit;
typedef enum value Value;

struct card {
    Value value;
    Suit suit;
};

typedef struct card Card;


void card_init(Card*, Value, Suit);

int card_order(Card, Card);
bool card_equals(Card, Card);

#endif
