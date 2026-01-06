#include "Board.h"
#include <iostream>

Board::Board() : m_holes(1), m_beans(0) {
    for (int i = 0; i < size(); i++) {
        int beans = (isPot(i)) ? 0 : m_beans;
        beansInHoles.push_back(beans);
    }
}

Board::Board(int nHoles, int nInitialBeansPerHole) : m_holes(nHoles), m_beans(nInitialBeansPerHole) {
    if (nHoles <= 0) m_holes = 1;
    if (nInitialBeansPerHole < 0) m_beans = 0;
    for (int i = 0; i < size(); i++) {
        int beans = (isPot(i)) ? 0 : m_beans;
        beansInHoles.push_back(beans);
    }
}

Board::Board(const Board& other) {
    this->m_beans = other.m_beans;
    this->m_holes = other.m_holes;
    for (int i = 0; i < other.size(); i++) {
        beansInHoles.push_back(other.beansInHoles[i]);
    }
}

Board& Board::operator=(const Board& other) {
    if (this != &other) {
        this->beansInHoles = other.beansInHoles;
        this->m_beans = other.m_beans;
        this->m_holes = other.m_holes;
    }
    return *this;
}

int Board::holes() const {
    return m_holes;
}
int Board::beans(Side s, int hole) const {
    if (hole > m_holes || hole < 0) return -1;
    return beansInHoles[sidemap(s, hole)];
}
int Board::beansInPlay(Side s) const {
    int beans = 0;
    for (int i = 1; i <= m_holes; i++)
        beans += beansInHoles[sidemap(s, i)];
    return beans;

}
int Board::totalBeans() const {
    return beansInPlay(SOUTH) + beansInPlay(NORTH) + beans(SOUTH, POT) + beans(NORTH, POT);
}
bool Board::sow(Side s, int hole, Side& endSide, int& endHole) {
    int i = sidemap(s, hole);
    bool empty = (beansInHoles[i] == 0);
    if (empty || isPot(hole) || hole < 1 || hole > size()) return false;
    while (beans(s, hole)) {
        i = (i+1) % size();
        if (isPot(i) && side(i) != s) continue;
        beansInHoles[i]++;
        beansInHoles[sidemap(s, hole)]--;
    }
    if (i >= 1 && i <= m_holes+1) {
        endSide = SOUTH;
        endHole = (isPot(i)) ? POT : i;
    }
    else {
        endSide = NORTH;
        endHole = (isPot(i)) ? POT : size()-i;
    }
    
    
    return true;
}


bool Board::moveToPot(Side s, int hole, Side potOwner) {
    if (isPot(sidemap(s, hole)) || hole < 1 || hole > size())
        return false;

    int beans = beansInHoles[sidemap(s, hole)];
    beansInHoles[sidemap(s, hole)] = 0;
    beansInHoles[sidemap(potOwner, 0)] += beans;

    return true;
}
bool Board::setBeans(Side s, int hole, int beans) {
    if (hole < 0 || hole > m_holes || beans < 0)
        return false;
    beansInHoles[sidemap(s, hole)] = beans;
    return true;
}
bool Board::isPot(int hole) const {
    return (hole == 0 || hole == m_holes+1);
}

int Board::size() const {
    return 2*(m_holes+1);
}

int Board::sidemap(Side side, int hole) const {
    if (hole == POT) return (side == SOUTH) ? m_holes+1 : 0;
    return (side == SOUTH) ? hole : size()-hole;
}

Side Board::side(int hole) {
    return (hole > 0 && hole <= m_holes+1) ? SOUTH : NORTH;
}


