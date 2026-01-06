#include "History.h"
#include "globals.h"
#include <iostream>
#include <string>
using namespace std;

History::History(int nRows, int nCols) : m_rows(nRows), m_cols(nCols) {}

bool History::record(int r, int c) {
    if (!(r >= 1  &&  r <= m_rows  &&  c >= 1  &&  c <= m_cols)) {
        return false;
    } else {
        m_record[r-1][c-1]++;
        return true;
    }
}

void History::display() const
{
    char displayGrid[MAXROWS][MAXCOLS];
    int r, c;
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    for (r = 1; r <= m_rows; r++) {
        for (c = 1; c <= m_cols; c++) {
            if (m_record[r-1][c-1] == 0) displayGrid[r-1][c-1] = '.';
            else if (m_record[r-1][c-1] > 26) displayGrid[r-1][c-1] = 'Z';
            else displayGrid[r-1][c-1] = alphabet[m_record[r-1][c-1]-1];
        }
    }

    clearScreen();
    for (r = 1; r <= m_rows; r++)
    {
        for (c = 1; c <= m_cols; c++)
            cout << displayGrid[r-1][c-1];
        cout << endl;
    }
    cout << endl;
}
