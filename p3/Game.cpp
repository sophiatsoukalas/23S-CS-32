#include "Game.h"
#include <iostream>
#include <string>
using namespace std;

Game::Game(const Board& b, Player* south, Player* north) : m_b(b), m1(south), m2(north) {}

void Game::display() const {
    string nBeans = "";
    string sBeans = "";
    string spacing = "                ";
    string holes = "";
    string side_space = "";
    string dashes = "";
    string pot_space = "";
    
    
    for (int i = 1; i <= m_b.holes(); i++) {
        holes += to_string(i) + "  ";
        nBeans += to_string(m_b.beans(NORTH, i)) + "  ";
        sBeans += to_string(m_b.beans(SOUTH, i)) + "  ";

    }
    
    for (int i = 1; i <= (holes.size()/2)-3; i++) side_space += " ";
    for (int i = 1; i <= holes.size()-2; i++) {
        dashes += "-";
        pot_space += " ";
    }

    cout << spacing << side_space << "North" << endl;
    
    
    cout << spacing << holes << endl;
    cout << spacing << dashes << endl;
    cout << spacing << nBeans << endl;
    
    
    cout << "North's Pot " << m_b.beans(NORTH, 0) << "   " << pot_space << "   " << m_b.beans(SOUTH, 0) << " South's Pot" << endl;
    
    
    cout << spacing << sBeans << endl;
    cout << spacing << dashes << endl;
    cout << spacing << holes << endl;
    
    cout << spacing << side_space << "South" << endl;
}

void Game::status(bool& over, bool& hasWinner, Side& winner) const {
    if (m_b.beansInPlay(NORTH) == 0 && m_b.beansInPlay(SOUTH) == 0) {
        over = true;
        if (m_b.beans(SOUTH, 0) != m_b.beans(NORTH, 0)) {
            hasWinner = true;
            winner = (m_b.beans(SOUTH, 0) > m_b.beans(NORTH, 0)) ? SOUTH : NORTH;
        } else hasWinner = false;
    }
    else over = false;
}

bool Game::move(Side s) {
    this->display();
    if (this->m_b.beansInPlay(s) == 0) {
        for (int i = 1; i <= m_b.holes(); i++)
            this->m_b.moveToPot(opponent(s), i, opponent(s));
        return false;
    }
    Side endSide;
    int endHole;
    Player* p = (s == SOUTH) ? m1 : m2;
    this->m_b.sow(s, p->chooseMove(m_b, s), endSide, endHole);
    if (endSide == s && endHole == POT)
        move(s);
    if (endSide == s && m_b.beans(s, endHole) == 1 && m_b.beans(opponent(s), endHole) != 0) {
        m_b.moveToPot(s, endHole, s);
        m_b.moveToPot(opponent(s), endHole, s);
    }
    return true;
}

void Game::play() {
    bool over = false;
    bool hasWinner;
    Side winner;
    Side current = SOUTH;
    while (!over) {
        Player* p = (current == SOUTH) ? m1 : m2;
        this->move(current);
        if (!p->isInteractive())
            cout << "Press enter to continue." << endl;
        cin.ignore(10000, '\n');
        current = opponent(current);
        this->status(over, hasWinner, winner);
    }
    std::string victor = (winner) ? "South" : "North";
    if (hasWinner)
        cout << victor << " wins!" << endl;
    else
        cout << "Tie!" << endl;
    
}

int Game::beans(Side s, int hole) const {
    return (hole >= 0 && hole <= m_b.holes()) ? m_b.beans(s, hole) : -1;
}
