#ifndef Board_h
#define Board_h

#include "Side.h"
#include <vector>

class Board {
private:
    int m_holes;
    int m_beans;
    std::vector<int> beansInHoles;
    bool isPot(int hole) const;
    int size() const;
    int sidemap(Side s, int hole) const;
    Side side(int hole);
public:
    Board();
    Board(int nHoles, int nInitialBeansPerHole);
    Board(const Board& other);
    Board& operator=(const Board& other);
    int holes() const;
    int beans(Side s, int hole) const;
    int beansInPlay(Side s) const;
    int totalBeans() const;
    bool sow(Side s, int hole, Side& endSide, int& endHole);
    bool moveToPot(Side s, int hole, Side potOwner);
    bool setBeans(Side s, int hole, int beans);
};


#endif /* Board_h */
