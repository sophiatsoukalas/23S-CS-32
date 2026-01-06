#include <iostream>
#include <cassert>
#include "Game.h"
#include "Player.h"
#include "Board.h"
#include "Side.h"
using namespace std;


void doBoardTests()
{
    Board b(3, 2);
    assert(b.holes() == 3  &&  b.totalBeans() == 12  &&
                    b.beans(SOUTH, POT) == 0  &&  b.beansInPlay(SOUTH) == 6);
    b.setBeans(SOUTH, 1, 1);
    b.moveToPot(SOUTH, 2, SOUTH);
    assert(b.totalBeans() == 11  &&  b.beans(SOUTH, 1) == 1  &&
                b.beans(SOUTH, 2) == 0  &&  b.beans(SOUTH, POT) == 2  &&
        b.beansInPlay(SOUTH) == 3);
    Side es;
    int eh;
    b.sow(SOUTH, 3, es, eh);
    assert(es == NORTH  &&  eh == 3  &&  b.beans(SOUTH, 3) == 0  &&
                b.beans(NORTH, 3) == 3  &&  b.beans(SOUTH, POT) == 3  &&
        b.beansInPlay(SOUTH) == 1  &&  b.beansInPlay(NORTH) == 7);
}

void doPlayerTests()
{
    HumanPlayer hp("Marge");
    assert(hp.name() == "Marge"  &&  hp.isInteractive());
    BadPlayer bp("Homer");
    assert(bp.name() == "Homer"  &&  !bp.isInteractive());
    SmartPlayer sp("Lisa");
    assert(sp.name() == "Lisa"  &&  !sp.isInteractive());
    Board b(3, 2);
    b.setBeans(SOUTH, 2, 0);
    cout << "=========" << endl;
    int n = hp.chooseMove(b, SOUTH);
    cout << "=========" << endl;
    assert(n == 1  ||  n == 3);
    n = bp.chooseMove(b, SOUTH);
    assert(n == 1  ||  n == 3);
    n = sp.chooseMove(b, SOUTH);
    assert(n == 1  ||  n == 3);
}

void doGameTests()
{
    BadPlayer bp1("Bart");
    BadPlayer bp2("Homer");
    Board b(3, 0);
    b.setBeans(SOUTH, 1, 2);
    b.setBeans(NORTH, 2, 1);
    b.setBeans(NORTH, 3, 2);
    Game g(b, &bp1, &bp2);
    bool over;
    bool hasWinner;
    Side winner;
      //    Homer
      //   0  1  2
      // 0         0
      //   2  0  0
      //    Bart
    g.status(over, hasWinner, winner);
    assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 0 &&
    g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1 && g.beans(NORTH, 3) == 2 &&
    g.beans(SOUTH, 1) == 2 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 0);

    g.move(SOUTH);
      //   0  1  0
      // 0         3
      //   0  1  0
    g.status(over, hasWinner, winner);
    assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
    g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1 && g.beans(NORTH, 3) == 0 &&
    g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 1 && g.beans(SOUTH, 3) == 0);

    g.move(NORTH);
      //   1  0  0
      // 0         3
      //   0  1  0
    g.status(over, hasWinner, winner);
    assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
    g.beans(NORTH, 1) == 1 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
    g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 1 && g.beans(SOUTH, 3) == 0);

    g.move(SOUTH);
      //   1  0  0
      // 0         3
      //   0  0  1
    g.status(over, hasWinner, winner);
    assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
    g.beans(NORTH, 1) == 1 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
    g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 1);

    g.move(NORTH);
      //   0  0  0
      // 1         4
      //   0  0  0
    g.status(over, hasWinner, winner);
    assert(over && g.beans(NORTH, POT) == 1 && g.beans(SOUTH, POT) == 4 &&
    g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
    g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 0);
    assert(hasWinner && winner == SOUTH);
}

int main()
{
//    doBoardTests();
//    doPlayerTests();
//    doGameTests();
    /*Board b;
    Board b1(-1, -1);
    Board b2(6, 4);
    
    
    HumanPlayer me("Sophia");
    BadPlayer you("Computer");
    Game g(b, &me, &you);
    //g.play();
    assert(b.beans(SOUTH, 1) == 0);
    bool over, hw;
    Side win;
    g.status(over, hw, win);
    assert(over);
    b.setBeans(SOUTH, 1, 4);
    assert(b.beans(SOUTH, 1) == 4);*/
    Board b(6, 4);
    BadPlayer me("Alice");
    BadPlayer you("Bob");
    Game game1(b, &me, &you);
    b.setBeans(SOUTH, 1, 4);
    b.setBeans(SOUTH, 2, 2);
    b.setBeans(SOUTH, 3, 6);
    b.setBeans(SOUTH, 4, 1);
    b.setBeans(SOUTH, 5, 3);
    b.setBeans(SOUTH, 6, 5);

    b.setBeans(NORTH, 1, 2);
    b.setBeans(NORTH, 2, 5);
    b.setBeans(NORTH, 3, 3);
    b.setBeans(NORTH, 4, 4);
    b.setBeans(NORTH, 5, 6);
    b.setBeans(NORTH, 6, 1);

    assert(game1.move(SOUTH) == true);
    assert(b.beans(SOUTH, 1) == 0);
    assert(b.beans(SOUTH, 2) == 2);
    // Add more assertions to validate the board state after the move

    assert(game1.move(NORTH) == true);
    assert(b.beans(NORTH, 2) == 0);
    assert(b.beans(NORTH, 3) == 4);
    // Add more assertions to validate the board state after the move

    assert(game1.move(SOUTH) == true);
    assert(b.beans(SOUTH, 3) == 0);
    assert(b.beans(SOUTH, 4) == 2);
    // Add more assertions to validate the board state after the move

    cout << "Passed all tests" << endl;
}








// Timer


Timer::Timer()
{
    start();
}
void Timer::start()
{
    m_time = std::chrono::high_resolution_clock::now();
}
double Timer::elapsed() const
{
    std::chrono::duration<double, std::milli> diff =
                      std::chrono::high_resolution_clock::now() - m_time;
    return diff.count();
}



JumpyTimer::JumpyTimer(int jumpInterval)
 : m_jumpInterval(jumpInterval), m_callsMade(0)
{
    actualElapsed();
}
double JumpyTimer::elapsed()
{
    m_callsMade++;
    if (m_callsMade == m_jumpInterval)
    {
        m_lastElapsed = m_timer.elapsed();
        m_callsMade = 0;
    }
    return m_lastElapsed;
}
double JumpyTimer::actualElapsed()
{
    m_lastElapsed = m_timer.elapsed();
    return m_lastElapsed;
}
