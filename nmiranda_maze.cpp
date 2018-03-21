/*
 Name:       Nehemias Miranda
 Assignment: Program 3
 Proffesor:  Steve Miller
 Inputs:     This program takes as input command line arguments,
 which are composed of 0s and 1s which will as a maze.
 Purpose:    The Purpose is to develop an algorithm or set of functions
 that will find a path if there is one.
 Problem:    A maze is a rectangular area with an entrance and an exit. The interior of the maze contains walls or
 obstacles that one cannot walk through. In our mazes these obstacles are placed along rows and columns
 that are parallel to the rectangular boundary of the maze. The entrance is at the upper-left corner, and the
 exit is at the lower-right corner.
 The rat-in-a-maze problem is to find a path from the entrance to the exit of the maze. A path is a
 sequence of positions, none of which is blocked, such that each (other than the first) is the north, south,
 east or west neighbor of the preceding position.
 Solution:   Begin with the entrance as your
 starting position. If the present position is the exit, then you have found a path and you are done. If
 you are not at the exit, then block the present position (i.e., place an obstacle there) so as to prevent
 the search from returning here. Next see whether there is an adjacent maze position that is not
 blocked. If so, move to this new adjacent position and attempt to find a path from there to the exit. If
 unsuccessful, attempt to move to some other unblocked adjacent maze position and try to find a path
 from there. To facilitate this move, save the current position on a Stack before advancing to a new
 adjacent position. If all adjacent unblocked positions have been tried and no path is found, there is no
 path from entrance to exit in the maze.
 Remember that from interior (i.e. nonboundary) positions of the maze, four moves are possible:
 right, down, left, and up. From positions on the boundary of the maze, either two or three moves are
 possible. To avoid having to handle positions on the boundaries of the maze differently from interior
 positions, you may find it useful to surround the entire maze with a wall of obstacles. For an m by n
 maze, this wall will occupy rows 0 and m + 1 and columns 0 and n + 1 of the matrix
 All positions in the maze are now within the boundary of the surrounding wall, so you can move to
 four possible positions from each position (some of these four positions may have obstacles.) Being
 able to handle each position in the same way should significantly simplify the search algorithm,
 although this simplification is achieved at the cost of a slightly increased space requirement for the
 matrix.
 */
#include <cstdlib>
#include <iostream>
#include <stack>
#include "outinhelp.h"

using namespace ds_maze;
using namespace std;
const int mark = 1;
const int blocked =mark;
//const int blocked = 1;
//overload operators for position comparison
//Operator to Compare left rows and left columns to right rows and right columns.
bool operator == (const position& l , const position& r);
//Operator to Compare left rows and left columns to right rows and right columns.
bool operator != (const position& l, const position& r);
bool isSafe(vector<vector<int>>& Maze, int row, int col);
bool isSafe1(vector<vector<int>>& Maze, position p);
bool isSafe2(vector<vector<int>>& Maze, position p, int col);
bool isSafe3(vector<vector<int>>& Maze, int row, position p);
void Path(vector<vector<int>>& Maze, position p, int Status = mark);
void Path(vector<vector<int>>& Maze, int row, int col, int Status = mark);
void Path1(vector<vector<int>>& Maze, stack<position>& Sol, int Status = mark);
int main(int argc, char* argv[])
{
    //Stack of Path
    stack<position>Sol;
    //Entrance is at 2nd Position because there is wall around the original maze.
    position Entrance= position(1, 1);
    position Exit;
    //Stores Maze Arguments.
    vector< vector<int> > Maze;
    //read from command line Args.
    for (int i = 1; i < argc; ++i)
    {
        if (readMaze(argv[i], Maze))
        {
            int rows = Maze.size() - 2;
            int columns = Maze[0].size() - 2;
            
            //Show Maze
            outputMaze(Maze);
            
            //if entrance and exit points are not blocked
            if (isSafe1(Maze, Entrance) && isSafe(Maze, rows, columns))
            {
                //set row and col exit position
                Exit.setpos(rows, columns);
                //Push the first Intersection to the Solution
                Sol.push(Entrance);
                //Stores valid Positions
                stack<stack<position>> Aswer;
                // Marks Path Walked
                Path(Maze, Entrance, mark);
                while (Sol.size() && Sol.top() != Exit)
                {
                    if (isSafe2(Maze, Sol.top(), 1))
                    {
                        //Try to move to the Right.
                        Sol.push(position(Sol.top().row(), Sol.top().col() + 1 ) );
                        //marks new position to prevent looping again
                        Path1(Maze, Sol, mark);
                    }
                    else if (isSafe2(Maze, Sol.top(), -1))
                    {   //Try to move to the Left.
                        Sol.push(position(Sol.top().row(), Sol.top().col() - 1));
                        //marks new position to prevent looping again
                        Path1(Maze, Sol, mark);
                    }
                    else if (isSafe3(Maze, 1, Sol.top()))
                    {   //Try to move up
                        Sol.push(position(Sol.top().row() + 1, Sol.top().col()));
                        //marks new position to prevent looping again
                        Path1(Maze, Sol, mark);
                    }
                    else if (isSafe3(Maze, -1, Sol.top()))
                    {   //Try to move down
                        Sol.push(position(Sol.top().row() - 1, Sol.top().col()));
                        //marks new position to prevent looping again
                        Path1(Maze, Sol, mark);
                    }
                    else
                    {
                        Path1(Maze, Sol, blocked);
                        Sol.pop();
                    }
                    
                    if (!Sol.empty() && Sol.top() == Exit)
                        
                    {
                        Aswer.push(Sol);
                        Sol.pop();
                        
                    }
                }
                if (!Aswer.empty())
                {   //Loop to find the number of steps.
                    while (Aswer.top().top().steps() < Aswer.top().size()-1)
                    {
                        //counts steps
                        Aswer.top().top().stepup();
                    }   //Displaying the path.
                        OutputPath(&Aswer.top());
                    }
                 else
                    {   //Displaying "No Path Found" when there is no path Availible.
                        OutputPath(Sol);
                    }
            }
            //Resets the vector, to store the new Incoming Maze Argument.
            Maze.clear();
        }
    }
    return 0;
}
//Operator to Compare left rows and left columns to right rows and right columns.
bool operator == (const position& left, const position& right)
{
    return (left.row() == right.row()) && (left.col() == right.col());
}
//Operator to Compare left rows and left columns to right rows and right columns.
bool operator != (const position& left, const position& right)
{
    return (left.row() != right.row()) || (left.col() != right.col());
}

//Function to control limits of where the rat can move
bool isSafe(vector<vector<int>>& Maze, int row, int col)
{
    if (row >= 0 && col >= 0 && row < Maze.size() && col < Maze[0].size())
    {
        if (Maze[row][col]==mark)
        {
            return false;
        }
        return true;
    }
    return false;
}

//Functions to check where is safe to go.
//Calls the above Function to check for Boundaries
bool isSafe1(vector<vector<int>>& Maze, position p)
{
    return isSafe(Maze, p.row(), p.col());
}

bool isSafe2(vector<vector<int>>& Maze, position p, int col)

{   //Checks if right  or left directions open or blocked
    return isSafe(Maze, p.row(), p.col() + col);
}

bool isSafe3(vector<vector<int>>& Maze, int row, position p)

{   //Checks if up or Down are open or closed
    return isSafe(Maze, p.row() + row, p.col());
}


//Helper functions to find path using their intersections

void Path(vector<vector<int>>& Maze, int row, int col, int Intersection)
{
    if (row >= 0 && col >= 0 && row < Maze.size() && col < Maze[0].size())
    {
        Maze[row][col] = Intersection;
    }
}

void Path(vector<vector<int>>& Maze, position p, int Intersection)
{
    return Path(Maze, p.row(), p.col(), Intersection);
}

void Path1(vector<vector<int>>& Maze, stack<position>& Answer, int Status)
{
    if (Answer.size())
        return Path(Maze, Answer.top(), Status);
}


