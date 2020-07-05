#include "card.h"
#include "hand.h"
#include <stdlib.h>
#include <stdbool.h>

void hand_init(Hand* hand){
    hand->cards = (Card**)malloc(MAX_HAND*sizeof(Card*));
    for(size_t card_idx = 0; card_idx < MAX_HAND; card_idx++){
        hand->cards[card_idx] = (Card*)malloc(sizeof(Card));
    }
    hand->len_cards = 0;
}

int hand_insert(Hand* hand, Card* card){
    if(hand->len_cards >= MAX_HAND)
        return 1;

    hand->cards[hand->len_cards++] = card;
    return 0;
}

int hand_remove(Hand* hand, Card card){
    if(hand->len_cards == 0)
        return 1;
    
    size_t idx_take;
    if(hand_index_card(hand, card, &idx_take)){
        for(size_t idx = idx_take; idx + 1 < hand->len_cards; idx++){
            hand->cards[idx] = hand->cards[idx+1];
        }
        hand->len_cards--;
        return 0;
    }

    return 1;
}

bool hand_index_card(Hand* hand, Card card, size_t* idx_ptr){
    for(size_t idx = 0; idx < hand->len_cards; idx++){
        if(card_equals(*hand->cards[idx], card)){
            if(idx_ptr){
                *idx_ptr = idx;
            }
            return true;
        }
    }
    return false;
}

void hand_create(Hand* hand, Card** cards, size_t len_cards){
    hand->cards = cards;
    hand->len_cards = len_cards;
}

int hand_print(Hand* hand, char* buf){
    if(hand->len_cards == 0){
        return 0;
    }

    size_t acc = 0;
    acc += card_print(hand->cards[0], buf + acc);
    for(size_t card_idx = 1; card_idx < hand->len_cards; card_idx++){
        buf[acc++] = ',';
        buf[acc++] = ' ';
        acc += card_print(hand->cards[card_idx], buf + acc);
    }
    return acc;
}
