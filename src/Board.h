// Class to perform all operations related to the chess board
#include <vector>
#include "Piece.h"
#include <iostream>
#include <string>
using namespace std;

class Board
{
	public:	

		// Constructors
		Board()
		{
			// init
			init();
		}

		// Initializations
		void init()
		{
			input_path = "data/input.dat";
			BSize 	   = 64;
			Brows	   = 8;
			Bcol	   = 8;
			Nloc.resize(2);	// Store the moves in chess notation
		}

		// Function to read from file and store the data in a matrix
		void read_data()
		{
			ifstream file;file.open(input_path.c_str());

			// Declare required variables
			int val;
			int nLines; nLines =-1;
			std::string line;

			// Identify number of lines
			while (std::getline(file, line))
			{
				nLines++;
			}
			file.clear();
			file.seekg(0, ios::beg);

			// Define the move set array
			posData.resize(nLines);
			pieceData.resize(nLines);

			// Dimension the Dense Matrices
			for (int i=0;i<nLines;i++)
			{
				posData[i].resize(BSize);
				pieceData[i].resize(BSize);
				for (int j=0;j<BSize;j++)
				{
					file >> val;
					posData[i][j] = val;
				}
			}
		}

		// Print the data of the current move
		void printBoard(int move)
		{
			printf("\n--------------------------------------------");
			// Track what piece moved and update the board before print
			track(move);			

			printf("\nMove number : %d",move);
			printf("\n"); 
			for(int i=Brows-1;i>=0;i--)
			{	
				cout<<'|';
				for(int j=0;j<Bcol;j++)
				{
					cout<<pieceData[move][i*Bcol+j]<<'|';
				}
				cout<<'\n';
			}
			printf("\n--------------------------------------------\n");
		}

		// Track the movement of pieces
		void track(int move)		
		{
			if (move<=0) 
			{ printf("\nThis is the initial position");}
			else
			{ 
				// Search the board for changes
				c1=-1;c2=-1;

				for (int i=0;i<BSize;i++)
				{
					if(posData[move][i]-posData[move-1][i]!=0)
					{
						if(pieceData[move-1][i] == ' '){c2=i;} else {c1=i;}
					}
				}
				reportMove(c1,c2);				// Report

				if (move%2==0) {Player='B';} else {Player='W';}	//Identify who played
				Piece_move(move,c1,c2); 	
			}
		}
		// report the findings
		void reportMove(int c1_,int c2_)
		{
			vector<char> a = SwitchNotation(c1_); 	
			vector<char> b = SwitchNotation(c2_); 	
			cout<<'\n'<<pieces[findPiece(c1_)]->getType() <<a[0]<<a[1]<<"-"<<pieces[findPiece(c1_)]->getType()<<b[0]<<b[1]<<endl;
		}
		// Find what piece is there in a particular version of the code
		int findPiece(int loc_)		
		{
			int found=-1;
			for (int i=0;i<32;i++)
			{
				if(!pieces[i]->getTaken()){if (pieces[i]->getLoc()==loc_){found=i;}}
			}
			return found;	
		}

		// Update board
		void Piece_move(int move_,int c1_,int c2_)
		{
			// Copy old positions
			for (int i=0;i<64;i++){pieceData[move_][i]=pieceData[move_-1][i];}	

			// Moving the piece
			pieceData[move_][c2_]=pieceData[move_-1][c1_];
			pieces[findPiece(c1)]->setLoc(c2);
			pieceData[move_][c1_]=' ';
		}

		// Game start position
		void start_game()
		{
			Player	= 	'W';
			pieces.resize(32);
			pieces[0]  = new Piece('P','W',1,0);
			pieces[1]  = new Piece('P','W',1,1);
			pieces[2]  = new Piece('P','W',1,2);
			pieces[3]  = new Piece('P','W',1,3);
			pieces[4]  = new Piece('P','W',1,4);
			pieces[5]  = new Piece('P','W',1,5);
			pieces[6]  = new Piece('P','W',1,6);
			pieces[7]  = new Piece('P','W',1,7);
			pieces[8]  = new Piece('R','W',0,0);
			pieces[9]  = new Piece('R','W',0,7);
			pieces[10] = new Piece('N','W',0,1);
			pieces[11] = new Piece('N','W',0,6);
			pieces[12] = new Piece('B','W',0,2);
			pieces[13] = new Piece('B','W',0,5);
			pieces[14] = new Piece('Q','W',0,3);
			pieces[15] = new Piece('K','W',0,4);
			pieces[16] = new Piece('p','B',6,0);
			pieces[17] = new Piece('p','B',6,1);
			pieces[18] = new Piece('p','B',6,2);
			pieces[19] = new Piece('p','B',6,3);
			pieces[20] = new Piece('p','B',6,4);
			pieces[21] = new Piece('p','B',6,5);
			pieces[22] = new Piece('p','B',6,6);
			pieces[23] = new Piece('p','B',6,7);
			pieces[24] = new Piece('r','B',7,0);
			pieces[25] = new Piece('r','B',7,7);
			pieces[26] = new Piece('n','B',7,1);
			pieces[27] = new Piece('n','B',7,6);
			pieces[28] = new Piece('b','B',7,2);
			pieces[29] = new Piece('b','B',7,5);
			pieces[30] = new Piece('q','B',7,3);
			pieces[31] = new Piece('k','B',7,4);

			for (int i=0;i<64;i++){pieceData[0][i] = ' ';}
			for (int i=0;i<32;i++){pieceData[0][pieces[i]->getLoc()] = pieces[i]->getType();}
		}

		// Print where all the pieces currently are
		void PrintPieceData(){for(int i=0;i<32;i++) pieces[i]->printPiece();cout<<endl;}

		// Switch notation
		vector<char>  SwitchNotation(int loc_ ) 
		{
			Nloc[0] = char(((loc_+1)%8) + 64);
			Nloc[1] = char(((loc_+1)/8) + 49);
			return Nloc;
		}

	private:
		//std::vector<double> posData;		///< Store the chess board
		vector<vector<int> > posData;
		vector<vector<char> > pieceData;
		vector<char>	Nloc;
		vector<Piece*>	pieces;			///< store piece info in a stack
		std::string	input_path;		///< Location of the input data
		int		BSize;			///< Size of the board (number of squares)
		int 		Brows;			
		int 		Bcol;
		int 		c1,c2;			///<locations of the pices that moved
		char		Player;			///< Black or White to move
};
