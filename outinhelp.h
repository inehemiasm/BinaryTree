/*
 * outputhelp.h
 *
 * The following functions are provided to make it a lot easier to match your output to the expected results.
 * It is recommended that your code contain NO direct cout calls.
 *
 *  bool readMaze(char * filename, std::vector< std::vector<int> >& maze);
 *  Precondition: maze is an empty vector of vector and filename exists and is readable
 *  Postcondition: Multidim array is set as indicated in file with BOUNDARIES added, returns true if success
 *
 *  bool void outputMaze(const std::vector< std::vector<int> >& maze);
 *  Precondition: Maze is a vector of vectors containing 1's and 0's
 *  Postcondion: The maze it output to stdout
 *
 * 	void OutputPath(ds_stack::stack<position> *path)
 *	Precondition: path is the top of the stack
 * 	Postcondition: The stack with me output to stdout.  STACK WILL BE FULLY POPPED!!
 *
 * 	void OutputPath(ds_stack::stack<position> path)
 *	Precondition: path is the top of the stack
 * 	Postcondition: The stack with me output to stdout.  STACK WILL BE FULLY POPPED!!
 * 	NOTE: This is a convenience function, you should be sending &path to OutputPath to avoid a COPY
 *
 *	void outUsage(char *thisCmd)
 *	Precondition: thisCmd is argv[0]
 *	Postcondition: The correct usage of the program will be output
 *
 *	outFileError(char* filename)
 *	Precondition: filename is the file name that was unable to be opened
 *	Postcondition: Error message is sent to stderr
 *
 *	void outProcessing(char* filename)
 *	Precondition: filename is the file name of a maze
 *	Postcondition: Status message sent to stdout
 */

#ifndef OUTINHELP_H_
#define OUTINHELP_H_

#include <iostream>
#include <stack>
#include <fstream>
#include <vector>
#include "position.h"

namespace ds_maze {
    
    bool readMaze(char *, std::vector< std::vector<int> >&);
    void outputMaze(const std::vector< std::vector<int> >&);
    std::ostream& operator <<(std::ostream&, const position&);
    void OutputPath(std::stack<position>*);
    void OutputPath(std::stack<position>);
    void outUsage(char *);
    void outFileError(char*);
    void outProcessing(char*);
    
    bool readMaze(char *fname, std::vector< std::vector<int> >& maze) {
        unsigned int mr,mc;
        std::ifstream fmaze;
        
        fmaze.open(fname);
        if ( fmaze.is_open() ) {
            outProcessing(fname);
            fmaze >> mr;
            fmaze >> mc;
            
            //maze.reserve(m);
            
            for (unsigned int i = 0; i <= mr+1; i++) {
                maze.push_back(std::vector<int>(mc+2)); // Add the row to the main vector
            }
            
            for (unsigned int c = 0; c <= mc+1; ++c) {
                maze[0][c] = 1;
            }
            
            for (unsigned int r = 1; r <= mr; ++r) {
                maze[r][0] = maze[r][mc+1] = 1;
                for (unsigned int c = 1; c <= mc; ++c) {
                    fmaze >> maze[r][c];
                }
            }
            
            for (unsigned int c = 0; c <= mc+1; ++c) {
                maze[mr+1][c] = 1;
            }
            fmaze.close();
            return true;
        } else {
            outFileError(fname);
            return false;
        }
        
    }
    
    void outputMaze(const std::vector< std::vector<int> >& maze) {
        
        std::vector<int>::const_iterator it;
        std::vector< std::vector<int> >::const_iterator ot;
        
        for( ot=maze.begin() ; ot < maze.end(); ++ot ) {
            for( it=ot->begin() ; it < ot->end(); ++it ) {
                std::cout << *it << " ";
            }
            std::cout << std::endl;
        }
    }
    
    std::ostream& operator <<(std::ostream& outs, const position& source) {
        outs << "(" << source.row() << "," << source.col() << ")";
        return outs;
    }
    
    void OutputPath(std::stack<position> *path)
    {
        if ( !path->empty() ) {
            std::cout << "Path Found" << std::endl;
            position ptop;
            ptop = path->top();
            path->pop();
            std::cout << "Steps:" << ptop.steps() << std::endl;
            std::cout << "Path:" << ptop;
            
            while (!path->empty()) {
                ptop = path->top();
                path->pop();
                std::cout << "<-" << ptop;
            }
            std::cout << std::endl << std::endl;
        } else {
            std::cout << "No path found!" << std::endl << std::endl;
        }
    }
    
    void OutputPath(std::stack<position> path)
    {
        //This is not optimal since the programmer can use to overloaded function themselves by sending Address of the stacks path
        OutputPath(&path);
    }
    
    void outUsage(char *thisCmd) {
        std::cerr << "Usage: " << thisCmd << " mazefile [mazefile2] ... [mazefilen]" << std::endl;
    }
    
    void outFileError(char* filename) {
        std::cerr << filename << ": File unable to be opened for read." << std::endl;
    }
    
    void outProcessing(char* filename) {
        std::cout << filename << ": Processing Maze" << std::endl;
    }
    
    
}



#endif /* OUTINHELP_H_ */
