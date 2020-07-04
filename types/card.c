#include "card.h"
#include <assert.h>
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
    Value value = (id / 4) + 2;
    card_init(card, value, suit);
}

// suit + (value-2)*4
void card_id(Card card, int* id){
    *id = card.suit + (card.value - 2)*4;
}

char card_suit_char(Suit suit){
    switch(suit){
    case CLUBS: return 'C';
    case DIAMONDS: return 'D';
    case HEARTS: return 'H';
    case SPADES: return 'S';
    default: return '?';
    }
}

char card_value_char(Value value){
    assert(value >= 2 && value <= ACE);
    if(value >= 2 && value <= 7){
        return '0' + value;
    }

    switch(value){
    case JACK: return 'J';
    case QUEEN: return 'Q';
    case KING: return 'K';
    case ACE: return 'A';
    default: return '?';
    }
}

size_t card_print(Card* card, char* buff){
    buff[0] = card_value_char(card->value);
    buff[1] = card_suit_char(card->suit);
    return 2;
}
