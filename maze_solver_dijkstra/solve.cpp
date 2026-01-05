#include <iostream>
#include <cstdlib>
#include <string>
#include "solve.h"
#include <string>
#include <unordered_set>
#include "minpriorityqueue.h" // Includes <vector>, <unordered_map>, <utility>

//O(1)
void organize_layout(string &s, Vertex* &push, vector<char> &layout, vector<Vertex*> &layoutPtr, int r, int &c, int i, unordered_map<int, int> &key){
    push = new Vertex(r,c);
    layoutPtr.push_back(push);
    layout.push_back(s[i]);
    int tempI = (r * 100) + c;
    key[tempI] = i + 1 - r;
    c++;
}
//O(1)
void organize_portal(string &s, Vertex* &push, vector<char> &layout, vector<Vertex*> &layoutPtr, int r, int &c, int i, unordered_map<int, int> &key, unordered_map<int, vector<Vertex*>> &portalMap){
    push = new Vertex(r,c);
    int tempint = s[i] - '0';
    portalMap[tempint].push_back(push);
    layoutPtr.push_back(push);
    layout.push_back(s[i]);
    int tempI = (r * 100) + c;
    key[tempI] = i + 1 - r;
    c++;
}
//O(logn)
void relax(Vertex * &parent, Vertex * &child, int distance, unordered_map<int, int> &key, vector<int> &weight, unordered_map<Vertex*, Vertex*> &bc, MinPriorityQueue<int> &Q1){
    if(weight[key[(parent->row * 100)+parent->col]] + distance < weight[key[(child->row * 100) + child->col]]){
        bc[child] = parent;
        Q1.decrease_key(key[(child->row * 100) + child->col], weight[key[(parent->row * 100)+parent->col]] + distance);
        weight[key[(child->row * 100) + child->col]] = weight[key[(parent->row * 100)+parent->col]] + distance;
    }
}

string solve(string maze){
    vector<char> layout;
    vector<Vertex*> layoutPtr;

    Vertex * start = nullptr;
    Vertex * end = nullptr;

    unordered_map<int, int> key;
    unordered_map<Vertex*, Vertex*> bc;

    unordered_map<int, vector<Vertex*>> portalMap;


    //O(1)
    int max_col = 0;
    while(maze[max_col] != '\n'){
        max_col++;
    }

    int max_row = 0;
    //O(s)
    for(int i = 0; i < maze.length(); i++){
        if(maze[i] == '\n'){
            max_row++;
        }
    }

    int c = 1;
    int r = 1;
    bool foundStart = false;
    bool foundEnd = false;
    //O(s)
    for (int i = 0; i < maze.length(); i++) {
        Vertex* temp = nullptr;
        if (maze[i] == '\n') {
            r++;
            c = 1;
            continue;
        }
        bool isBorder = (r == 1 || r == max_row) || (c == 1 || c == max_col);
        if (!foundStart && maze[i] == ' ' && isBorder) {
            organize_layout(maze, start, layout, layoutPtr, r, c, i, key);
            foundStart = true;
            continue;
        }
        if (!foundEnd && maze[i] == ' ' && isBorder) {
            organize_layout(maze, end, layout, layoutPtr, r, c, i, key);
            foundEnd = true;
            continue;
        }
        if (maze[i] >= '0' && maze[i] <= '9') {
            if (!foundStart && isBorder) {
                organize_portal(maze, start, layout, layoutPtr, r, c, i, key, portalMap);
                foundStart = true;
            }
            else if (!foundEnd && isBorder) {
                organize_portal(maze, end, layout, layoutPtr, r, c, i, key, portalMap);
                foundEnd = true;
            } else {
                organize_portal(maze, temp, layout, layoutPtr, r, c, i, key, portalMap);
            }
            continue;
        }
        organize_layout(maze, temp, layout, layoutPtr, r, c, i, key);
    }
    //O(s)
    for (int i = 0; i < layout.size(); i++) {
        if (layout[i] == ' ') {
            Vertex* parent = layoutPtr[i];
            // north
            if (parent->row - 1 >= 1) {
                int loc = key[(parent->row - 1) * 100 + parent->col];
                if (layout[loc] != '#') {
                    parent->neighs.push_back({layoutPtr[loc], 1});
                }
            }

            // south
            if (parent->row + 1 <= max_row) {
                int loc = key[(parent->row + 1) * 100 + parent->col];
                if (layout[loc] != '#') {
                    parent->neighs.push_back({layoutPtr[loc], 1});
                }
            }

            // west
            if (parent->col - 1 >= 1) {
                int loc = key[(parent->row * 100) + (parent->col - 1)];
                if (layout[loc] != '#') {
                    parent->neighs.push_back({layoutPtr[loc], 1});
                }
            }

            // east
            if (parent->col + 1 <= max_col) {
                int loc = key[(parent->row * 100) + (parent->col + 1)];
                if (layout[loc] != '#') {
                    parent->neighs.push_back({layoutPtr[loc], 1});
                }
            }

        }
        if(layout[i] >= '0' && layout[i] <= '9'){
            Vertex* parent = layoutPtr[i];
            // north
            if (parent->row - 1 >= 1) {
                int loc = key[(parent->row - 1) * 100 + parent->col];
                if (layout[loc] != '#') {
                    parent->neighs.push_back({layoutPtr[loc], 1});
                }
            }

            // south
            if (parent->row + 1 <= max_row) {
                int loc = key[(parent->row + 1) * 100 + parent->col];
                if (layout[loc] != '#') {
                    parent->neighs.push_back({layoutPtr[loc], 1});
                }
            }

            // west
            if (parent->col - 1 >= 1) {
                int loc = key[(parent->row * 100) + (parent->col - 1)];
                if (layout[loc] != '#') {
                    parent->neighs.push_back({layoutPtr[loc], 1});
                }
            }

            // east
            if (parent->col + 1 <= max_col) {
                int loc = key[(parent->row * 100) + (parent->col + 1)];
                if (layout[loc] != '#') {
                    parent->neighs.push_back({layoutPtr[loc], 1});
                }
            }
        }
    }

    for (auto& [digit, vertices] : portalMap) {
        for (Vertex* from : vertices) {
            for (Vertex* to : vertices) {
                if (from != to) {
                    from->neighs.push_back({to, digit});
                }
            }
        }
    }

    vector<int> weight;
    MinPriorityQueue<int> Q1;

    //O(V(logV))
    for(int i = 0; i < layout.size(); i++){
        weight.push_back(999);
        Q1.push(i, 999);
    }
    
    //O(logV)
    int sIndex = key[(start->row * 100) + start->col];
    Q1.decrease_key(sIndex, 0);
    weight[sIndex] = 0;
    
    //O((v+E)logV)
    while(Q1.size() > 0){
        int index = Q1.front();
        Q1.pop();
        Vertex * x = layoutPtr[index];
        for(int i = 0; i < x->neighs.size(); i++){
            relax(x, x->neighs[i].first, x->neighs[i].second, key, weight, bc, Q1);
        }
    }
    //O(V)
    Vertex* current = end;
    while (bc.find(current) != bc.end()) {
        layout[key[(current->row * 100) + current->col]] = 'o';
        current = bc[current];
    }
    layout[key[(current->row * 100) + current->col]] = 'o';
    
    string answer = "";
    //O(s)
    for(int i = 0; i < layout.size(); i++){
        if(i % max_col == 0 && i != 0){
            answer+= '\n';
        }
        answer+= layout[i];
    }
    answer += '\n';

    for(int i = 0; i < layoutPtr.size(); i++){
        delete layoutPtr[i];
    }
    portalMap.clear();
    return answer;
}