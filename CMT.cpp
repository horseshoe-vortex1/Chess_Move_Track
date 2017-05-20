#include <iostream>
#include <fstream>
#include "src/main_menu.h"
#include "src/Board.h"
using namespace std;



int main () {

	//Declaration of Board object
	Board	ChessBoard;

	// Dispaly the menu
	//menu();	
	
	//Operations
	ChessBoard.read_data();
	ChessBoard.printBoard(0);
	ChessBoard.printBoard(1);
	ChessBoard.printBoard(2);
return 0;
}
