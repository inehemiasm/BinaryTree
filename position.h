// FILE: position.h (part of the namespace p3_maze) version 0.2
// PROVIDES: A class to keep track of one maze location.  Row, Column, and steps from entry
//
// CONSTRUCTOR for the node<Item> class:
//   position(const int &r=0,const int &c=0,const int &s=0) { setpos(r,c);nsteps=s; }
//     Postcondition: The position contains the default items
//
// MODIFICATION MEMBER FUNCTIONS
// void row(const int &r)
//   Precondition: none
//   Postcondition: row member variable updated
//
// void col(const int &c) {pcol = c;}
//   Precondition: none
//   Postcondition: col member variable updated
//
// void setpos(const int &r, const int &c) {prow=r; pcol=c;}
//   Precondition: none
//   Postcondition: Member variables row and column are updated
//
// void stepup() {nsteps++;}
//   Precondition: None
//   Postcondition: steps is incremented by one
//
// CONSTANT MEMBER FUNCTIONS
// int row() const {return prow;}
//   Precondition: none
//   Postcondition: Returns the row member variable value
//
// int col() const {return pcol;}
//   Precondition: none
//   Postcondition: Returns the column member variable value
//
// int steps() const {return nsteps;}
//   Precondition: None
//   Postcondition: Returns the # of steps from entry

#ifndef DS_POSITION
#define DS_POSITION
#include <iostream>

namespace ds_maze
{
    class position {
        public:
        position(const int &r=0,const int &c=0,const int &s=0) { setpos(r,c);nsteps=s; }
        // MODIFICATION MEMBER FUNCTIONS
        void row(const int &r) {prow = r;}
        void col(const int &c) {pcol = c;}
        void setpos(const int &r, const int &c) {prow=r; pcol=c;}
        void stepup() {nsteps++;}
        // CONSTANT MEMBER FUNCTIONS
        int row() const {return prow;}
        int col() const {return pcol;}
        int steps() const {return nsteps;}
        private:
        int prow, pcol,nsteps;
    };
    
}


#endif
