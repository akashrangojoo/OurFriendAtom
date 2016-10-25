/****************************************************************
 *    PROGRAM:   PROG6.H
 *    AUTHOR:    AKASH RANGOJOO
 *    LOGON ID:  Z1717009
 *    DUE DATE:  10/13/2015
 ****************************************************************/

#include "/home/cs689/common/689.h"

#ifndef prog6_h
#define prog6_h

// DECLARE CONSTANTS
extern const int GRID_SIZE;
extern const int MIN_CYCLES;
extern const int MAX_CYCLES;
extern const int PRN_CYCLES;

// DECLARE METHODS

extern unsigned randPos(unsigned,unsigned);
extern void init_sim (vector<vector<bool> >& traps, vector <unsigned>& ballCycles);
extern unsigned release_balls(vector<vector<bool> >& traps, vector <unsigned>& ballCycles);
extern void printGrid(const vector<vector<bool> >& traps , const unsigned& clock, const unsigned& noBallsinAir);
extern void print_stat(const vector<vector<bool> >& traps, const unsigned& maxNoBallsInAir, const unsigned& clock);


#endif

