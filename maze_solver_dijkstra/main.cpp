#include <iostream>
#include <cstdlib>
#include <string>
#include "solve.cpp"

using namespace std;

int main()
{
	// Setup
	srand(2025 + 'f');
	string maze, tempEntry, answer;
	string completed = "finished";
	bool another_maze = true;

	do{
		cout << "Please enter a maze the walls being '#' , empty spots being '*', portals -> place a number twice to connect them and the number is the time it takes going through it if instant use 1, \nmake sure all rows are the same length enter '" << completed << "' when completed" << endl;
		cin >> tempEntry;
		while(tempEntry != completed){
			maze = maze +  tempEntry + "\n";
			cin >> tempEntry;
		}

		for(int i = 0; i < maze.size(); i++){
			if(maze[i] == '*') maze[i] = ' ';
		}
		cout << "Fastest route through maze \n";
		solve(maze);
		cout << "Another maze?(Y/N)";
		cin >> answer;
		if(answer == "N" || answer == "n") another_maze = false;
		maze = "";
	}while(another_maze);

	cout << "All mazes where solved" << endl;
}
