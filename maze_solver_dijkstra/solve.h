
#ifndef SOLVE_H
#define SOLVE_H

#include <string>
#include <unordered_set>
#include "minpriorityqueue.h" // Includes <vector>, <unordered_map>, <utility>
#include "vertex.h"

using namespace std;

// For the mandatory running time, assume that the time for
// operations of queue, unordered_set, and map are O(1). 
// (They are for average-case, but not worst-case).
//
// For the mandatory running time below, s is the length of 
// the input string representing the maze.
// 
// For a complete description of the maze string 
// and maze solution formats, see the assignment pdf.
//
//
// Returns a string representing a shortest solution to the maze.
// Undefined behavior if the maze is not valid or has no solution.
//
// Must run in O(s*log(s)) time.
string solve(string maze);

void organize_layout(string &s, Vertex* &push, vector<char> &layout, vector<pair<Vertex*, int>> &layoutPtr, int r, int &c, int i, unordered_map<int, int> &key);
void organize_portal(string &s, Vertex* &push, vector<char> &layout, vector<pair<Vertex*, int>> &layoutPtr, int r, int &c, int i, unordered_map<int, int> &key, vector<pair<Vertex*, int>> &portal);
void relax();

#endif 

