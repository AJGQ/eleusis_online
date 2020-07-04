#include "card.h"
#include <stdbool.h>

void card_init(Card* card, Value value, Suit suit){
    card->value = value;
    card->suit = suit;
}

int card_order(Card c1, Card c2){
    if(c1.value < c2.value){
        return -1;
    }else if(c1.value > c2.value){
        return 1;
    }

    if(c1.suit < c2.suit){
        return -1;
    }else if(c1.suit > c2.suit){
        return 1;
    }

    return 0;

}

bool card_equals(Card c1, Card c2){
    return card_order(c1, c2) == 0;
}

void card_by_id(int id, Card* card){
    Suit suit = id % 4;
    Value value = id / 4;
    card_init(card, value, suit);
}

// suit + value*4
void card_id(Card card, int* id){
    *id = card.suit + card.value*4;
}
