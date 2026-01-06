#ifndef HISTORY_H
#define HISTORY_H
#include "globals.h"
class Arena;

class History
    {
    private:
        int m_rows, m_cols;
        int m_record[MAXROWS][MAXCOLS] = {};
      public:
        History(int nRows, int nCols);
        bool record(int r, int c);
        void display() const;
    };


#endif // HISTORY_H
