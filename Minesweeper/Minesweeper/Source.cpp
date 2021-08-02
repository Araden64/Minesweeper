#include<iostream>
#include<iomanip>

using namespace std;

void initializeArray(char[][30], int, int);
void insertBombs(char[][30],int, int, int);
void printArray(char[][30],int, int, int);
void menu();
void selectSquare(char[][30], char[][30], int, int, bool&);
void checkSquare(char[][30], char[][30], int, int, int, int, bool&);
void checkAbove(char[][30], int&, int, int, int, int);
void checkBelow(char[][30], int&, int, int, int, int);
void checkInline(char[][30], int&, int, int, int, int);
void placeFlag(char[][30], int&);
void placeQuestionMark(char[][30]);
bool winCondition(char[][30], int, int);

int main()
{
	// Declare gameBoard and userBoard
	char gameBoard[24][30];
	char userBoard[24][30];

	// Declare and initialize game variables
	int row = 0;
	int column = 0;
	int bomb = 0;
	int bombCounter = 0;
	
	// Declare and initialize bool variables for win/loss
	bool boom = false;
	bool win = false;
	
	// Ouput main menu
	cout << "    __  __    ___  __   __ ______ _____ __     __ ______ ______ ____   ______ ____" << endl;
	cout << "   /  |/  |  /   //  | / // ____/ ____// / _  / // ____// ____// __ \\ / ____// __ \\ " << endl;
	cout << "  / /| /| |  / / / /||/ // /___ \\_  \\ / / // / // /___ / /___ / /_/ // /___ / /_/ /" << endl;
	cout << " / / |/ | | / / / / |  // /___ __/  // /_//_/ // /___ / /___ / /___// /___ / / / /" << endl;
	cout << "/_/     |_/___//_/  |_//_____/_____//____/\\__//_____//_____//_/    /_____//_/  |_|" << endl;
	cout << "===================================================================================" << endl;
	cout << "1. Easy - 9x9; 10 Bombs" << endl;
	cout << "2. Medium - 16x16; 40 Bombs" << endl;
	cout << "3. Expert - 30x16; 99 Bombs" << endl;
	cout << "4. Custom" << endl;

	// Variables for switch statement
	int selection = 0;
	bool valid = false;

	// Prompt user to choose game mode
	cout << "Choose a game mode: ";
	cin >> selection;

	// Switch statement for main menu selection
	switch (selection) {
	case 1: // Case 1 creates the boards for easy mode
		// Initialize variables for easy mode board
		row = 9;
		column = 9;
		bomb = 10;
		bombCounter = bomb;
		break;
	case 2: // Case 2 creates the board for medium mode
		// Initialize variables for medium mode board
		row = 16;
		column = 16;
		bomb = 40;
		bombCounter = bomb;
		break;
	case 3: // Case 3 creates the board for expert mode
		// Initialize variables for expert mode board
		row = 16;
		column = 30;
		bomb = 99;
		bombCounter = bomb;
		break;
	case 4: // Case 4 allows the user to create his own custom board
		// While loop to enter number of rows
		while (valid == false) {

			// Prompt user to input number of rows
			cout << "Enter the number of rows (minimum: 9, maximum: 24): ";
			cin >> row;

			// Check if number of rows is valid
			if (row >= 9 && row <= 24)
				valid = true;
			else
				cout << "Invalid Entry!!!  Invalid number of rows entered" << endl;
		}

		// Reset valid to false
		valid = false;

		// While loop to enter number of columns
		while (valid == false) {

			// Prompt user to input number of columns
			cout << "Enter the number of columns (minimum: 9, maximum: 30): ";
			cin >> column;

			// Check if number of columns is valid
			if (column >= 9 && column <= 30)
				valid = true;
			else
				cout << "Invalid Entry!!!  Invalid number of columns entered" << endl;
		}

		// Reset valid to false
		valid = false;

		// While loop to enter the number of bombs
		while (valid == false) {

			// Prompt user to input number of bombs
			cout << "Enter the number of bombs (minimum: 10, maximum: " << (.9 * (row * column)) << ": ";
			cin >> bomb;

			// Check if number of bombs is valid
			if (bomb > 10 && bomb <= (.9 * (row * column))) {
				bombCounter = bomb;
				valid = true;
			}
			else
				cout << "Invalid Entry!!!  Invalid number of bombs entered" << endl;
		}
		break;
	default: // Default case for invalid inputs
		cout << "ERROR: Invalid selection!!!" << endl;
		break;
	}

	// Initialize and print the userBoard
	initializeArray(userBoard, row, column);
	printArray(userBoard, row, column, bombCounter);

	// Initialize and insert bombs into the gameBoard
	initializeArray(gameBoard, row, column);
	insertBombs(gameBoard, row, column, bomb);

	// Call menu function and print the game menu
	menu();

	// Switch statement for gameplay
	while (boom == false) {

		// Prompt user to select a game option
		cout << "Make a selection: ";
		cin >> selection;

		// Switch statement for gameplay
		switch (selection) {
		case 1: // Case 1 lets the user select a square to check for mines
			// Calls the selectSquare function to check a square
			selectSquare(gameBoard, userBoard, row, column, boom);

			// If checking the square sets off a mine then display gameBoard and end game
			if (boom == true)
				printArray(gameBoard, row, column, bombCounter);
			// Else display the userBoard and continue the game
			else
				printArray(userBoard, row, column, bombCounter);

			// Call the winCondition function to check win condition
			win = winCondition(gameBoard, row, column);

			// If win is true display end game
			if (win == true) {
				cout << "\nYOU WIN!!!" << endl;
				boom = true;
			}
			break;
		case 2: // Case 2 lets the user place a flag to mark a bomb location
			// Call placeFlag function to place a flag
			placeFlag(userBoard, bombCounter);
			printArray(userBoard, row, column, bombCounter);
			break;
		case 3: // Case 3 lets the user place a question mark to mark a suspected bomb location
			// Call placeQuestionMark function to place a question mark
			placeQuestionMark(userBoard);
			printArray(userBoard, row, column, bombCounter);
			break;
		case 4: // Case 4 will print the game menu for the user
			menu();
			break;
		case 64: // Cheat code for debugging, prints the gameBoard
			printArray(gameBoard, row, column, bombCounter);
			break;
		default: // Default case for invalid inputs
			cout << "ERROR: Invalid selection!!!" << endl;
			break;
		}
	}
}

// Function that prints the game menu
void menu() {
	cout << "\n=====Minesweeper Menu=====" << endl;
	cout << "1. Check Square" << endl;
	cout << "2. Place/Remove Flag" << endl;
	cout << "3. Place/Remove Question Mark" << endl;
	cout << "4. Print Menu" << endl;
}

// Function that iterates through the array and initializes it with '*'
void initializeArray(char arr[][30], int row, int column) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			arr[i][j] = '*';
		}
	}
}

// Function that iterates through the arrray and inserts bombs randomly
void insertBombs(char arr[][30], int row, int column, int bomb) {
	// Initialize and declare variables for bomb location
	int tempRow = 0;
	int tempCol = 0;

	// Variable for random number Generation
	srand(time(NULL));

	// For loop that loops until all bombs are place
	for (int i = 1; i <= bomb; i++) {

		// Generate a random x and y location for the bombs
		tempRow = (rand() % row);
		tempCol = (rand() % column);

		// If the random location already has abomb then decrement 'i' and continue
		if (arr[tempRow][tempCol] == 'X') {
			i--;
			continue;
		}
		// Else place a bomb in that location
		else
			arr[tempRow][tempCol] = 'X';
	}
}

// Function that prints the array and remaining bombs
void printArray(char arr[][30], int row, int column, int bombCounter) {

	// Prints the remaining bombs
	cout << "\nBombs Remaining: " << bombCounter << endl;
	
	// Function that sets the beginning of the column header
	cout << "\n" << setw(4) << " ";

	// For loops that print the column index headers and top border
	for(int i = 0; i < column; i++) {
		cout << setw(2) << i << " ";
	}
	cout << "\n" << setw(4) << " ";
	for (int i = 0; i < column; i++) {
		cout << "___";
	}
	cout << "\n";

	// For loops that print the actual array board
	for (int i = 0; i < row; i++) {
		// Prints the row index headers and border
		cout << setw(2) << i << " |";

		// For loop that prints the values of the array
		for (int j = 0; j < column; j++) {
			cout << setw(2) << arr[i][j] << " ";
		}

		// Starts a new line after each row is printed
		cout << endl;
	}
}

// Function that allows the user to select a square for checking
void selectSquare(char arr[][30], char arr2[][30], int row, int column, bool& boom) {

	// Initialize and declare variables for the location the user is checking
	int tempRow = 0;
	int tempCol = 0;

	// Prompt the user to input coordinates of square to check
	cout << "Choose a square to check: ";
	cin >> tempRow;
	cin >> tempCol;

	// If at that location there is a bomb then end the game
	if (arr[tempRow][tempCol] == 'X') {
		cout << "\nYOU HIT A BOMB!!!" << endl;
		boom = true;
	}
	// Else run the checkSquare function to check around the square for bombs
	else
		checkSquare(arr, arr2, row, column, tempRow, tempCol, boom);


}

// Function that checks around the square for bombs
void checkSquare(char arr[][30], char arr2[][30], int row, int column, int tempRow, int tempCol, bool& boom) {
	
	// Declare and initialize the counter variable to count number of bombs around a coordinate
	int counter = 0;

	// If the above row is within the bounds of the array then check row above
	if (tempRow - 1 >= 0)
		checkAbove(arr, counter, row, column, tempRow, tempCol);
	// If the below row is within the bounds of the array then check the row below
	if (tempRow + 1 < row)
		checkBelow(arr, counter, row, column, tempRow, tempCol);
	// Calls the function to check left and right of the chosen coordinates
	checkInline(arr, counter, row, column, tempRow, tempCol);

	// Set the gameBoard and the userBoard with the number of bombs around that square
	arr[tempRow][tempCol] = char(counter + 48);
	arr2[tempRow][tempCol] = char(counter + 48);

	// If there are no bombs around the square then run function recursively to check every index around it
	if (arr2[tempRow][tempCol] == '0') {

		if (tempRow - 1 >= 0 && tempCol - 1 >= 0 && arr2[tempRow - 1][tempCol - 1] == '*')
			checkSquare(arr, arr2, row, column, (tempRow - 1), (tempCol - 1), boom);
		
		if (tempRow - 1 >= 0 && arr2[tempRow - 1][tempCol] == '*')
			checkSquare(arr, arr2, row, column, (tempRow - 1), tempCol, boom);
		
		if (tempRow - 1 >= 0 && tempCol + 1 < column && arr2[tempRow - 1][tempCol + 1] == '*')
			checkSquare(arr, arr2, row, column, (tempRow - 1), (tempCol + 1), boom);
		
		if (tempCol - 1 >= 0 && arr2[tempRow][tempCol - 1] == '*')
			checkSquare(arr, arr2, row, column, tempRow, (tempCol - 1), boom);
		
		if (tempCol + 1 < column && arr2[tempRow][tempCol + 1] == '*')
			checkSquare(arr, arr2, row, column, tempRow, (tempCol + 1), boom);
		
		if (tempRow + 1 < row && tempCol - 1 >= 0 && arr2[tempCol + 1][tempCol - 1] == '*')
			checkSquare(arr, arr2, row, column, (tempRow + 1), (tempCol - 1), boom);
		
		if (tempRow + 1 < row && arr2[tempRow + 1][tempCol] == '*')
			checkSquare(arr, arr2, row, column, (tempRow + 1), tempCol, boom);
		
		if (tempRow + 1 < row && tempCol + 1 < column && arr2[tempRow + 1][tempCol + 1] == '*')
			checkSquare(arr, arr2, row, column, (tempRow + 1), (tempCol + 1), boom);
	}
}

void checkAbove(char arr[][30], int& counter, int row, int column, int tempRow, int tempCol) {

	if (arr[tempRow - 1][tempCol] == 'X')
		counter++;

	if (tempCol - 1 >= 0) {
		if (arr[tempRow - 1][tempCol - 1] == 'X')
			counter++;
	}
	if (tempCol + 1 < column) {
		if (arr[tempRow - 1][tempCol + 1] == 'X')
			counter++;
	}
}

void checkBelow(char arr[][30], int& counter, int row, int column, int tempRow, int tempCol) {
	if (arr[tempRow + 1][tempCol] == 'X')
		counter++;

	if (tempCol - 1 >= 0) {
		if (arr[tempRow + 1][tempCol - 1] == 'X')
			counter++;
	}
	if (tempCol + 1 < column) {
		if (arr[tempRow + 1][tempCol + 1] == 'X')
			counter++;
	}
}

void checkInline(char arr[][30], int& counter, int row, int column, int tempRow, int tempCol) {
	if (tempCol - 1 >= 0) {
		if (arr[tempRow][tempCol - 1] == 'X')
			counter++;
	}
	if (tempCol + 1 < column) {
		if (arr[tempRow][tempCol + 1] == 'X')
			counter++;
	}
}

void placeFlag(char arr[][30], int& bombCounter) {
	int row = 0;
	int column = 0;

	cout << "Choose a square to place/remove Flag: ";
	cin >> row;
	cin >> column;

	if (arr[row][column] == 'F') {
		arr[row][column] = '*';
		bombCounter++;
	}
	else if (arr[row][column] == '*') {
		arr[row][column] = 'F';
		bombCounter--;
	}
}

void placeQuestionMark(char arr[][30]) {
	int row = 0;
	int column = 0;

	cout << "Choose a square to place/remove Question Mark: ";
	cin >> row;
	cin >> column;

	if (arr[row][column] == '?')
		arr[row][column] = '*';

	else if (arr[row][column] == '*')
		arr[row][column] = '?';
}

bool winCondition(char arr[][30], int row, int column) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			if (arr[i][j] == '*')
				return false;
		}
	}
	return true;
}