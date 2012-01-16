#include "game.h"

Game::Game(LBDatabase::Row *row, LBDatabase::Context *context) :
    Entity(row, context)
{
}

GamesContext::GamesContext(LBDatabase::Row *row, LBDatabase::Storage *parent) :
    Context(row, parent)
{
    registerEntityType<Game>("game");
}
