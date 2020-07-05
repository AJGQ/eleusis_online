#include "card.h"
#include "deck.h"
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

void deck_init(Deck* deck){
    deck->cards = (Card**)malloc(MAX_CARDS*sizeof(Card*));
    for(size_t card_idx = 0; card_idx < MAX_CARDS; card_idx++){
        deck->cards[card_idx] = (Card*)malloc(sizeof(Card));
    }
    deck->len_cards = 0;

    int put_err1 = 0;
    int put_err2 = 0;

    for(size_t card_id = 0; card_id < MAX_NORMAL; card_id++){
        Card* card1 = deck->cards[2*card_id]; 
        Card* card2 = deck->cards[2*card_id + 1];
        card_by_id(card_id, card1);
        card_by_id(card_id, card2);

        put_err1 = deck_put(deck, card1);
        assert(put_err1 == 0);

        put_err2 = deck_put(deck, card2);
        assert(put_err2 == 0);
    }

    deck_shuffle(deck);
}

void deck_shuffle(Deck* deck){
    time_t t;
    srand((unsigned) time(&t));

    for(size_t card_idx = 0; card_idx < MAX_CARDS; card_idx++){
        size_t rand_card_idx = rand() % MAX_CARDS;

        // swap
        Card* temp;
        temp = deck->cards[card_idx];
        deck->cards[card_idx] = deck->cards[rand_card_idx];
        deck->cards[rand_card_idx] = temp;
    }
}

int deck_put(Deck* deck, Card* card){
    if(deck->len_cards >= MAX_CARDS){
        return 1;
    }

    deck->cards[deck->len_cards++] = card;
    return 0;
}

int deck_get(Deck* deck, Card** card){
    assert(card != NULL);
    if(deck->len_cards == 0){
        return 1;
    }

    *card = deck->cards[--deck->len_cards];
    return 0;
}
