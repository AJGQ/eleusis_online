#include "card.h"
#include "player.h"
#include <stdlib.h>
#include <stdbool.h>

void player_init(Player* player, Card* cards, size_t len_cards, size_t capacity){
    player->cards = cards;
    player->len_cards = len_cards;
    player->capacity = capacity;
}

int player_give(Player* player, Card card){
    if(player->len_cards >= player->capacity)
        return 1;

    player->cards[player->len_cards++] = card;
    return 0;
}

int player_take(Player* player, Card card){
    if(player->len_cards == 0)
        return 1;
    
    size_t idx_take;
    if(player_index_card(player, card, &idx_take)){
        for(size_t idx = idx_take; idx + 1 < player->len_cards; idx++){
            player->cards[idx] = player->cards[idx+1];
        }
        player->len_cards--;
        return 0;
    }

    return 1;
}

bool player_index_card(Player* player, Card card, size_t* idx_ptr){
    for(size_t idx = 0; idx < player->len_cards; idx++){
        if(card_equals(player->cards[idx], card)){
            if(idx_ptr){
                *idx_ptr = idx;
            }
            return true;
        }
    }
    return false;
}
