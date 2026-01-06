#ifndef Side_h
#define Side_h


// Side defs + global constants

enum Side { NORTH, SOUTH };

const int NSIDES = 2;
const int POT = 0;
const int MAX = 100000;
const int NUM_LEVELS = 3;


inline
Side opponent(Side s)
{
    return Side(NSIDES - 1 - s);
}



// Timer class declarations

#include <chrono>

class Timer
{
  public:
    Timer();
    void start();
    double elapsed() const;
  private:
    std::chrono::high_resolution_clock::time_point m_time;
};

class JumpyTimer
{
  public:
    JumpyTimer(int jumpInterval);
    double elapsed();
    double actualElapsed();
  private:
    Timer m_timer;
    int m_jumpInterval;
    int m_callsMade;
    int m_lastElapsed;
};





#endif /* Side_h */
