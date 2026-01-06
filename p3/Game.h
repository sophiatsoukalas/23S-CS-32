#ifndef Game_h
#define Game_h

#include "Side.h"
#include "Board.h"
#include "Player.h"

class Game {
private:
    Board m_b;
    Player* m1;
    Player* m2;
public:
    Game(const Board& b, Player* south, Player* north);
    void display() const;
    void status(bool& over, bool& hasWinner, Side& winner) const;
    bool move(Side s);
    void play();
    int beans(Side s, int hole) const;
};

#endif /* Game_h */

