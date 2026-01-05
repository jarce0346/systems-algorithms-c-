#ifndef MINPRIORITYQUEUE_H
#define MINPRIORITYQUEUE_H

// NOTE: You may not include any other libraries!
#include <unordered_map>
#include <vector>
#include <utility> // Has pair and swap

using namespace std;

template <typename T>
class MinPriorityQueue
{
	// For the mandatory running times below:
	//
	// n is the number of elements in the MinPriorityQueue.
	//
	// Assume that the operations of unordered_map are O(1) time 
	// (they are average case, but not worst-case).

	public:
		// Creates an empty MinPriorityQueue
		MinPriorityQueue()
		{
			// TODO
			H.clear();
		}

		// Returns the number of elements in the MinPriorityQueue.
		//
		// Must run in O(1) time.
		int size()
		{
			// TODO	
			return H.size();
		}	

		// Pushes a new value x with priority p
		// into the MinPriorityQueue.
		//
		// Must run in O(log(n)) time.		 
		void push(T x, int p)
		{
			// TODO
			pair<T, int> pairtemp(x, p);
			H.push_back(pairtemp);
			int index  = H.size() - 1;
			pair<T, int> pairIN(x, index);
			I[x] = index;
			bubble_up(index);
		}

		// Returns the value at the front of the MinPriorityQueue.
		// Undefined behavior if the MinPriorityQueue is empty.
		// 
		// Must run in O(1) time.
		T front()
		{
			// TODO	
			if(H.empty()){
				throw out_of_range("Undefined behavior");
			}
			return H[0].first;
		}

		// Removes the value at the front of the MinPriorityQueue.
		// Undefined behavior if the MinPriorityQueue is empty.
		//
		// Must run in O(log(n)) time. 
		void pop() {
			if (H.empty()) return;
		
			I.erase(H[0].first);
		
			if (H.size() == 1) {
				H.pop_back();
				return;
			}
		
			H[0] = H.back();
			I[H[0].first] = 0;
			H.pop_back();
		
			bubble_down();
		}

		// If x is in the MinPriorityQueue 
		// with current priority at least new_p,  
		// then changes the priority of x to new_p.
		// Undefined behavior otherwise.
		//
		// Must run in O(log(n)) time. 
		void decrease_key(T x, int new_p)
		{
			// TODO
			if(I.find(x) == I.end()){
				return;
			}
			int i = I[x];
			if(H[i].second <= new_p){
				return;
			}
			H[i].second = new_p;
			bubble_up(i);
		}

	private:
		// You don't need any other instance variables,
		// but you can add some if you want to.
		vector< pair<T, int> > H; // The heap.
		unordered_map<T, int> I;  // Maps values to their indices in H.

		// helper functions
		int find_parent(int index){
			if(index % 2 == 1){
				index++;
			}
			return index / 2 - 1;
		}

		int right_child(int index){
			return index * 2 + 2;
		}

		int left_child(int index){
			return index * 2 + 1;
		}

		void bubble_up(int index) {
			if (index == 0) return;
			int i = index;
			while (i > 0 && H[i].second < H[find_parent(i)].second) {
				int parent = find_parent(i);
				swap(H[i], H[parent]);
				I[H[i].first] = i;
				I[H[parent].first] = parent;
				i = parent;
			}
		}
		

		void bubble_down(int index = 0) {
			int i = index;
		
			while (true) {
				int left = left_child(i);
				int right = right_child(i);
				int smallest = i;
		
				if (left < H.size() && H[left].second < H[smallest].second) {
					smallest = left;
				}
				if (right < H.size() && H[right].second < H[smallest].second) {
					smallest = right;
				}
				if (smallest == i) break;

				swap(H[i], H[smallest]);
		
				I[H[i].first] = i;
				I[H[smallest].first] = smallest;
				i = smallest;
			}
		}
			
};
#endif 