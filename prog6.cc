/********************************************
 * NAME        :  PROG6.CC "OUR FRIEND THE ATOM"
 * AUTHOR      :  AKASH Z1717009
 * SUBMISSION  :  10/13/2015
 * ******************************************/

#include "prog6.h"

const int GRID_SIZE=25;
const int MIN_CYCLES=1;
const int MAX_CYCLES=4;
const int PRN_CYCLES=10;
const int TERMINATED=30;

/*************************************************
 * FUNCTION  :  INIT_SIM
 * INPUTS    :  VECTIR< VECTOR<BOOL> >, VEECTOR <UNSIGNED>
 * USAGE     :  INITIALIZE BOTH VECTORS, SET SRAND .
 ***********************************************/

void init_sim (vector<vector<bool> >& traps, vector <unsigned >& ballCycles){
   srand(time(0));
   for(unsigned i=0;i<GRID_SIZE;i++){
      vector<bool> dummy;
      for(unsigned j=0;j<GRID_SIZE;j++)
         dummy.push_back(true);
      traps.push_back(dummy);
   }
   ballCycles.push_back(1);
}

/*************************************************
 *  FUNCTION  :  RELEASEBALLS
 *  INPUTS    :  CONST VECTOR<VECTOR<BOOL> >, CONST VECTOR<UNSIGNED>
 *  USAGE     :  THIS FUNCTION IS USED TO GENERATE RANDOM TRAPS, CHECK
 *               THE TRAP IF OPENED OR NOT, AND GENERATE RANDOM CYCLES
 *               AND RETURN NUMBER OF BALLS IN AIR IN THEAT CYCLE.  
 ***********************************************/

unsigned releaseBalls (vector<vector<bool> >& traps, vector <unsigned>& ballCycles){
   int count=0;
   int length=ballCycles.size();
   for(int i=0;i<length;i++)    { if(ballCycles[i]!=0&&ballCycles[i]<=MAX_CYCLES) ballCycles[i]-=1;} // REDUCING THE CYCLES BY 1

   for(int i=0;i<length;i++)     {
      if(ballCycles[i]==0){     // CHECKING AL THE CYCLES THAT ARE ZERO
         ballCycles[i]==TERMINATED; // ASSIGN TERMINATED VALUE TO THE BALL THAT IS TERMINATED
         unsigned x=randPos(0,GRID_SIZE-1); // GENERATE A RANDOM TRAP
         unsigned y=randPos(0,GRID_SIZE-1);
         if(traps[x][y]==true){        // CHECK IF THE TRAP IS OPENED OR NOT
            unsigned m=randPos(MIN_CYCLES,MAX_CYCLES); // IF THE TRAP IS NOT OPENED GENERATE RANDOM CYCLES FOR EACH BALL
            unsigned n=randPos(MIN_CYCLES,MAX_CYCLES);
            traps[x][y]=false;               // SET THE TRAP VALUE TO FALSE
            ballCycles.push_back(m); // INSERT THE BALL CYCLES GENERATED INTO THE VECTOR
            ballCycles.push_back(n);
         }
      }
   }
   // CHECK ALL THE BALLS THAT ARE IN AIR. I.E., ALL THE BALLS THAT HAVE CYCLES GREATER THAN ZERO AND NOT EQUAL TO TERMINATED
   for(unsigned i=0;i<ballCycles.size();i++) if(ballCycles[i]!=0 && ballCycles[i]!=TERMINATED ) count++;
   return count;
}

/*************************************************
 *FUNCTION  :  RANDPOS
 *INPUTS    :  UNSIGNED LOW AND GIGH
 *USAGE     :  GENERATED A RANDOM VALUE BETWEEN LOW AND HIGH
 *             INCLUDING 
 * **********************************************/
unsigned randPos(unsigned low, unsigned high) {
   high++;
   unsigned randNumber = rand()%(high-low)+low;
   return randNumber;
}

/*************************************************
 *  FUNCTION  :  PRINT_GRID
 *  INPUTS    :  CONST VECTOR<VECTOR<BOOL> >, CONST UNSIGNED ,CONST UNSIGNED
 *  USAGE     :  PRINT THE TRAPS GRID                
 * **********************************************/

void print_grid(const vector<vector<bool> >& traps,const unsigned& clock,const unsigned& noBallsInAir){
   cout<<"Clock Timing  :"<<clock<<endl;
   cout<<"Number Of Balls in Air  :"<<noBallsInAir<<endl;
   if(clock%PRN_CYCLES==0)
   {
      for(unsigned i=0;i<traps.size();i++){
         for(unsigned j=0;j<GRID_SIZE;j++){
            if(traps[i][j]) cout<<" X ";  // IF TRAP NOT OPENED PRINT  X
            else cout<<" . ";             // ELSE PRINT . 
         }
         cout<<endl;
      }
   }
}

/*************************************************
 * FUNCTION  :  PRINT_STAT
 * INPUTS    :  CONST VECTOR<VECTOR<BOOL> >, CONST UNSIGNED ,CONST UNSIGNED
 * USAGE     :  GENERATED A RANDOM VALUE BETWEEN LOW AND HIGH
 *              INCLUDING
 * **********************************************/

void print_stat(const vector<vector<bool> >& traps,const unsigned& maxNoBallsInAir,const unsigned& clock){
   unsigned trueCount=0;
   unsigned falseCount=0;
   cout<<endl<<endl;
   cout<<"Total Time taken : "<<clock<<endl;
   cout<<"Maximum number of Balls in the air at any point of time : "<<maxNoBallsInAir<<endl;
   for(unsigned i=0;i<traps.size();i++){
      for(unsigned j=0;j<GRID_SIZE;j++){
         if(traps[i][j]==true) trueCount++;  // CALC NUMBER OF TRAPS NOT OPENED
         else falseCount++;
      }
   }
   cout<<"Number of Mouse traps sprung  : "<<falseCount<<endl; 
   double percentage=(falseCount*100)/(GRID_SIZE*GRID_SIZE);   // CALC PERCENTAGE OPENED
   cout<<"Percentage of Mouse traps sprung  : "<<percentage<<"%"<<endl;
}

/*************************************************
 * FUNCTION  :  MAIN
 * INPUTS    :  NONE
 * USAGE     :  USED TO INITIALIZE AND CALL THE FUNCTIONS
 *              REQUIRED FOR SIMULATION                  
 **********************************************/

int main(){
   vector<vector<bool> > traps;  // TWO DIMENTIONAL VECTOR FOR TRAPS
   vector<unsigned> ballCycles;  // VECTOR FOR BALL CYCLES
   unsigned noBallsInAir=1;
   unsigned maxNoBallsInAir=0;
   int clock=0;

   init_sim(traps,ballCycles);   // CALL TO INITIALIZE VECTORS
   print_grid(traps,clock,noBallsInAir);
   while(noBallsInAir!=0){
      noBallsInAir= releaseBalls(traps,ballCycles); // GET NUMBER BALLS IN AIR
      if(maxNoBallsInAir<noBallsInAir) maxNoBallsInAir=noBallsInAir;
      print_grid(traps,clock,noBallsInAir);  // PRINT  THE GRID
      clock++;
   }
   cout<<endl<<"******************END OF SIMULATION***************"<<endl;;
   for(unsigned i=0;i<traps.size();i++){
      for(unsigned j=0;j<GRID_SIZE;j++){
         if(traps[i][j]) cout<<" X ";  // IF TRAP NOT OPENED PRINT  X
         else cout<<" . ";             // ELSE PRINT .
      }
      cout<<endl;
   }

   cout<<endl<<"******************STATISTICS********************";
   print_stat(traps,maxNoBallsInAir,clock);  // PRINT STATISTICS
   return 0;
}
