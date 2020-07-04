#include "game.h"

void game_init(Game* game, Player* players, size_t len_players){
    game->players = players;
    game->len_players = len_players;
    deck_init(&game->deck);
    card_init(&game->sequence, ACE, SPADES);
}
