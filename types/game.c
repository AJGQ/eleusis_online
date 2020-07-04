#include "game.h"
#include <assert.h>

void game_init(Game* game, Player* players, size_t len_players){
    game->players = players;
    game->len_players = len_players;
    deck_init(&game->deck);
    card_init(&game->sequence, ACE, SPADES);
}

void game_give_n_to_all(Game* game, size_t n){
    for(size_t player_idx = 0; player_idx < game->len_players; player_idx++){

        Card** cards = (Card**)malloc(n*sizeof(Card*));

        for(size_t card_idx = 0; card_idx < n; card_idx++){
            cards[card_idx] = (Card*)malloc(sizeof(Card));
            int err = deck_get(&game->deck, &cards[card_idx]);
            assert(err == 0);
        }

        Hand* hand = (Hand*)malloc(sizeof(Hand));
        hand_create(hand, cards, n);
        player_give_hand(&game->players[player_idx], hand);
    }
}

void game_send_hand_to_all(Game* game){
    for(size_t player_idx = 0; player_idx < game->len_players; player_idx++){
        player_send_hand(&game->players[player_idx]);
    }
}
