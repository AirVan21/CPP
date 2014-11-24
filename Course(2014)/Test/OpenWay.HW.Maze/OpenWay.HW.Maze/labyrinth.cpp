#include <stdio.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <conio.h>

using namespace std;

// Use for convenient labyrinth representation 
typedef vector<vector<int>> grid;

// Walls in readfile should be equal to -1
const int wall = -1;

// Blanks in readfile should be equal to -2
const int blank = -2;

// Reads grid, which represents labyrinth from .txt file
// fInName - name of the .txt file
// playGrid - saves data, which we read  from .txt file
void readGridFromFile(const string &fInName, grid &playGrid)
{
	ifstream inStream(fInName);
	int widthOfGrid = 0;
	int heightOfGrid = 0;
	// First element(number) of file == amount of columns in labyrinth
	inStream >> widthOfGrid;
	// Second element(number) of file == amount of raws in labyrinth
	inStream >> heightOfGrid;
	// Reading Grid-Table in convenient grid
	playGrid = grid(heightOfGrid);
	int receiver = 0;
	for (int i = 0; i < heightOfGrid; i++) {
		for (int j = 0; j < widthOfGrid; j++) {
			inStream >> receiver;
			playGrid[i].push_back(receiver);
		}
	}
	inStream.close();
}

// Displays grid (which represents labyrinth)
// dispGrid - grid, which we will print on a screen
void dispGrid(const grid &dispGrid) 
{
	int widthOfGrid = dispGrid[0].size();
	int heightOfGrid = dispGrid.size();
	
	// Display column indexes
	cout << " ";
	for (int i = 0; i < widthOfGrid; i++) {
		cout << "   " << i;
	}
	cout << endl;
	cout << endl;
	
	// Draw Labyrinth with raw indexes  
	int rawCounter = 0;
	for (auto &row : dispGrid) {
		cout << rawCounter++;
		for (auto &element : row) {
			switch(element)
			{
				// in .txt file Wall == -1
				case  wall: 
					cout << "   W";
					break;
				// in .txt file Blank == -1
				case blank:
					cout << "   .";
					break;
				default:
					cout << "Wrong value in input table" << endl;
					break;
			}
		}
		cout << endl;
		cout << endl;
	}
}

// Finds the length of the shortest way between startPos and endPos
// startPos - point (x,y) in grid(labyrinth) from which we start algo
// endPos - point (x,y) in grid(labyrinth) which we search
// playGrid - labyrinth in grid representation 
int waveTraceSearch(const pair<int, int> &startPos, const pair<int, int> &endPos, grid &playGrid)
{
	// Defines amount of neighbor of the cell
	int const neighborAmount = 4;
	// Shift to the neighbor cell
	int xShift[neighborAmount] = { 1, 0, -1, 0 };
	int yShift[neighborAmount] = { 0, 1, 0, -1 };
	// Parameters of playGrid
	int widthOfGrid = playGrid[0].size();
	int heightOfGrid = playGrid.size();
	// Starts by puttinh zero in a startPos
	int waveCounter = 0;
	playGrid[startPos.second][startPos.first] = waveCounter;
	
	// Describes free cells (were they marked or not)
	bool terminate = false;

	// Describes counters
	int xAxis = 0;
	int yAxis = 0;
	int k = 0;

	int xPos = 0;
	int yPos = 0;

	// Helps to check bounds
	bool correctPlace = true;

	// While exist free cells and we hadn't reached endPos
	while (!terminate && playGrid[endPos.second][endPos.first] == blank)
	{
		terminate = true;
		for (yAxis = 0; yAxis < heightOfGrid; yAxis++) {
			for ( xAxis = 0; xAxis < widthOfGrid; xAxis++) {
				// Checks Wave iteration
				if (playGrid[yAxis][xAxis] == waveCounter) {
					for (k = 0; k < neighborAmount; k++) {
						// Defines neighbor cell coordinates
						xPos = xAxis + xShift[k];
						yPos = yAxis + yShift[k];
						// Check if x coordinate in a right range
						if ((0 > xPos) || (xPos >= widthOfGrid)) {
							correctPlace = false;
						}
						// Check if y coordinate in a right range
						if ((0 > yPos) || (yPos >= heightOfGrid)) {
							correctPlace = false;
						}
						// Spread the wave if exist unmarked cell with correct coordinates
						if (correctPlace && playGrid[yPos][xPos] == blank) {
							// Describes that found unmarked cells
							terminate = false; 
							playGrid[yPos][xPos] = waveCounter + 1;
						}
						correctPlace = true;
					}
				}
			}
		}
		waveCounter++;
	}
	// -2 if we hadn't reached endPos
	return playGrid[endPos.second][endPos.first];
}

// Checks correctness of user's input
// startPos - point (x,y) in grid(labyrinth) from which we start algo
// endPos - point (x,y) in grid(labyrinth) which we search
bool checkInput(const pair<int, int> &startPos, const pair<int, int> &endPos, grid &playGrid)
{

	// Parameters of playGrid
	int widthOfGrid = playGrid[0].size();
	int heightOfGrid = playGrid.size();

	// Check bounds of startPos
	if ((startPos.first >= widthOfGrid) || (startPos.first < 0)) {
		return false;
	}
	if ((startPos.second >= heightOfGrid) || (startPos.second < 0)) {
		return false;
	}
	
	// Check bounds of endPos
	if ((endPos.first >= widthOfGrid) || (endPos.first < 0)) {
		return false;
	}
	if ((endPos.second >= heightOfGrid) || (endPos.second < 0)) {
		return false;
	}

	// Check that points hadn't placed on a walls
	if (playGrid[startPos.second][startPos.first] == wall || playGrid[endPos.second][endPos.first] == wall) {
		return false;
	}
	return true;
}

int main() 
{
	// Work with loaded labyrinth 
	string inputFileName = "LabData.txt";
	grid playGrid;
	pair<int, int> startPos;
	pair<int, int> endPos;
	readGridFromFile(inputFileName, playGrid);
	dispGrid(playGrid);

	// User connection part
	cout << "\n\nThis Labyrinth was read from LabData.txt" << endl;
	cout << "\n Wall  == -1 (in file) == W " << endl;
	cout << "\n Blank == -2 (in file) == ." << endl;
	cout << "\n Please input coordinates for A (start point) :" << endl;
	cout << "\n X = ";
	cin >> startPos.first;
	cout << "\n Y = ";
	cin >> startPos.second;
	cout << "\n Please input coordinates for B (end point) :" << endl;
	cout << "\n X = ";
	cin >> endPos.first;
	cout << "\n Y = ";
	cin >> endPos.second;

	// If input correct => evaluate algorithm
	if (checkInput(startPos, endPos, playGrid)) {
		// Call main algorithm
		int answer = waveTraceSearch(startPos, endPos, playGrid);
		if (answer != blank) {
			cout << "\n Shortest way length between A -> B = " << answer << endl << endl;
		}
		else {
			cout << "\n The way between A -> B don't exist!" << endl << endl;
		}
	}
	else {
		cout << "\n	Wrong points in input!" << endl << endl;
	}
	
	_getch();

	return 0;
}