
#include "tiling.h"
#include "vertex.h"
#include <string>

using namespace std;


// Finds a (shortest according to edge length) augmenting path
// from s to t in a graph with vertex set V.
// Returns whether there is an augmenting path.
bool augmenting_path(Vertex* s, Vertex* t, 
        unordered_set<Vertex*> V, vector<Vertex*> &P)
{
        // Check that s and t aren't nullptr
        if (s == nullptr || t == nullptr)
	{
		cerr << "augmenting_path() was passed nullptr s or t." << endl;
		abort();
	}

        // Check that s and t are in the graph
        if (V.find(s) == V.end() || V.find(t) == V.end())
	{
		cerr << "augmenting_path() was passed s or t not in V." << endl;
		abort();
	}

	// Check that every vertex has valid neighs/weights.
	for (Vertex* v : V)
		for (Vertex* vn : v->neighs)
			if (v->weights.find(vn) == v->weights.end())
			{
				cerr << "augmenting_path() was passed invalid vertex." << endl;
				abort();
			}

        // Since augmenting paths should have the fewest edges,
	// not the minimum weight, run BFS.
	queue<Vertex*> Q;
	Q.push(s);

	unordered_set<Vertex*> R;
	R.clear(); 
	R.insert(s);

	unordered_map<Vertex*, Vertex*> prev;

	while (!Q.empty())
	{
		Vertex* cur = Q.front();
		Q.pop();

		for (Vertex* nei : cur->neighs)
		{
			// Must have positive edge weight
			if (cur->weights[nei] == 0)
				continue;

			if (R.find(nei) == R.end())
			{
				Q.push(nei);
				R.insert(nei);
				prev[nei] = cur; 
			}
		}
	}      

        // If BFS never reached t
        if (R.find(t) == R.end())
                return false;

        // Reconstruct shortest path backwards
        P.clear();
        P.push_back(t);
        while (P[P.size()-1] != s)
                P.push_back(prev[P[P.size()-1]]);

        // Reverse shortest path
        for (int i = 0; i < P.size()/2; ++i)
		swap(P[i], P[P.size()-1-i]);

        return true;
}

// Returns the maximum flow from s to t in a weighted graph with vertex set V.
// Assumes all edge weights are non-negative.
int max_flow(Vertex* s, Vertex* t, unordered_set<Vertex*> V)
{
	// If s or t is invalid.
        if (s == nullptr || t == nullptr)
	{
		cerr << "max_flow() was passed nullptr s or t." << endl;
		abort(); 
	}

	// If s or t is not in the vertex set.
        if (V.find(s) == V.end() || V.find(t) == V.end())
	{
		cerr << "max_flow() was passed s or t not in V." << endl;
		abort(); 
	}

	// Check that every vertex has valid neighs/weights.
	for (Vertex* v : V)
		for (Vertex* vn : v->neighs)
			if (v->weights.find(vn) == v->weights.end())
			{
				cerr << "max_flow() was passed invalid vertex." << endl;
				abort();
			}

        // Create a deep copy of V to use as the residual graph
        unordered_set<Vertex*> resV;
        unordered_map<Vertex*, Vertex*> C; // Maps vertices in V to copies in resV
        for (Vertex* vp : V)
        {
                Vertex* rp = new Vertex;
                resV.insert(rp);
                C[vp] = rp;
        }
        for (Vertex* vp : V)
                for (Vertex* np : vp->neighs)
                {
                        C[vp]->neighs.insert(C[np]);
                        C[vp]->weights[C[np]] = vp->weights[np];
                }
	// Add any missing necessary "back" edges. 
        for (Vertex* vp : V)
                for (Vertex* np : vp->neighs)
		{
			if (C[np]->neighs.find(C[vp]) == C[np]->neighs.end())
			{
				C[np]->neighs.insert(C[vp]);
				C[np]->weights[C[vp]] = 0;
			}
		}

        // Run Edmonds-Karp
        while (true)
        {
                // Find an augmenting path
                vector<Vertex*> P;
                if (!augmenting_path(C[s], C[t], resV, P))
                        break;  
                // Update residual graph
                for (int i = 0; i < P.size()-1; ++i)
                {
                        --((*(resV.find(P[i])))->weights[P[i+1]]);
                        ++((*(resV.find(P[i+1])))->weights[P[i]]);
                }
        }

        // Compute actual flow amount
        int flow = 0;
        for (Vertex* snp : C[s]->neighs)
                flow += 1 - C[s]->weights[snp];

        // Delete residual graph
        for (Vertex* vp : resV)
                delete vp;

        return flow;
}


bool has_tiling(string floor)
{
        // TODO
		//find width and height 
		bool answer = false;
		int MaxCol = 0;
		int MaxRow = 0;
		int row = 0;
		int col = 0;
		int i = 0;
		while(i < floor.size()){
			if(floor[i] == '\n'){
				row++;
				MaxCol = col;
				col = 0;
				i++;
				continue;
			}
			col++;
			i++;
		}
		MaxRow = row;

		// Make vertex for empty space and put them in unordered_map index = (row * 100) + col
		// keep count of number of nodes in the tiles
		unordered_set<Vertex*> V;
		unordered_map<int, Vertex*> layout;
		int count = 0;
		i = 0;
		row = 1;
		col = 0;
		while(i < floor.size()){
			if(floor[i] == ' '){
				Vertex * temp = new Vertex;
				V.insert(temp);
				layout[(row * 100) + col] = temp;
				count++;
			}
			else if(floor[i] == '\n'){
				row++;
				i++;
				col = 0;
				continue;
			}
			i++;
			col++;
		}
		// connect neighbors
		Vertex * s = new Vertex;
		Vertex * t = new Vertex;
		V.insert(s);
		V.insert(t);
		row = 1;
		col = 0;
		int tempRow = 0;
		int tempCol = 0;
		i = 0;
		while(i < floor.size()){
			if(layout.find((row * 100) + col) != layout.end()){
				Vertex * current = layout[(row * 100) + col];
				// connect source to red
				if ((row + col) % 2 == 0) {
					s->neighs.insert(current);
					s->weights[current] = 1;
				
					// connect red to blue
					// connect north
					tempRow = row - 1;
					int northKey = (tempRow * 100) + col;
					if (row > 1 && row <= MaxRow && layout.find(northKey) != layout.end()) {
						current->neighs.insert(layout[northKey]);
						current->weights[layout[northKey]] = 1;
					}
				
					// connect south
					tempRow = row + 1;
					int southKey = (tempRow * 100) + col;
					if (row >= 1 && row < MaxRow && layout.find(southKey) != layout.end()) {
						current->neighs.insert(layout[southKey]);
						current->weights[layout[southKey]] = 1;
					}
				
					// connect west
					tempCol = col - 1;
					int westKey = (row * 100) + tempCol;
					if (col > 0 && col <= MaxCol - 1 && layout.find(westKey) != layout.end()) {
						current->neighs.insert(layout[westKey]);
						current->weights[layout[westKey]] = 1;
					}
				
					// connect east
					tempCol = col + 1;
					int eastKey = (row * 100) + tempCol;
					if (col >= 0 && col < MaxCol - 1 && layout.find(eastKey) != layout.end()) {
						current->neighs.insert(layout[eastKey]);
						current->weights[layout[eastKey]] = 1;
					}
				
				} 
				else {
					// connect blue to sink
					current->neighs.insert(t);
					current->weights[t] = 1;
				}	
			}			
			else if(floor[i] == '\n'){
				row++;
				i++;
				col = 0;
				continue;
			}
			i++;
			col++;
		}
		if(count % 2 != 0) answer = false;
		else if((count / 2) == (max_flow(s, t, V))) answer = true;

		// deallocate ptrs
		for(Vertex * ptr: V){
			delete ptr;
		}
		
		V.clear();
        return answer;
}