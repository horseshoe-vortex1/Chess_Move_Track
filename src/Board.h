// Class to perform all operations related to the chess board
#include <vector>
#include "Piece.h"
#include <iostream>
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
			//cout<<'\n'<<"Number of lines counted "<<nLines<<endl;

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
			// Track what piece moved and update the board before print
			track(move);			

			printf("\n--------------------------------------------");
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
			{ printf("This is the initial position");}
			else
			{ 
				// Search the board for changes
				c1=0;c2=0;
				for (int i=0;i<BSize;i++)
				{
					if(posData[move][i]-posData[move-1][i]!=0)
					{
						if (c1==0)
						{c1=i;} 
						else 
						{c2=i;}
					}
				}
				if (move%2==0) {Player='B';} else {Player='W';}	//Identify who played
			 	checkPiece(move-1,c1,c2);
				Piece_move(move,c1,c2); 	
				// report the findings
				//cout<<"A piece was moved from "<<<<" to "<<char((c2+1)/8+65)<<(c2+1)%8<<" or the other way round"<<endl;
			}
		}

		
		// Check piece
		char checkPiece(int move_,int &c1_,int &c2_)
		{
			if (pieceData[move_][c1_]==' ') {
			int temp = c1_;
			c1_=c2_;
			c2_=c1_;
			}
		}

		// Update board
		void Piece_move(int move_,int c1_,int c2_)
		{
			cout<<'\n'<<Player<<" moves "<<c1_<<" to "<<c2_<<endl;
			for (int i=0;i<64;i++){pieceData[move_][i]=pieceData[move_-1][i];}	// Copy old positions

			// Moving the piece
			pieceData[move_][c2_]=pieceData[move_-1][c1_];
			pieceData[move_][c1_]=' ';
		}

		// Game start position
		void start_game()
		{
			Player	= 	'W';
			for (int i=0;i<64;i++){pieceData[0][i] = ' ';}
			Piece P1('P','W',1,0);pieceData[0][P1.loc] = P1.type;
			Piece P2('P','W',1,1);pieceData[0][P2.loc] = P2.type;
			Piece P3('P','W',1,2);pieceData[0][P3.loc] = P3.type;
			Piece P4('P','W',1,3);pieceData[0][P4.loc] = P4.type;
			Piece P5('P','W',1,4);pieceData[0][P5.loc] = P5.type;
			Piece P6('P','W',1,5);pieceData[0][P6.loc] = P6.type;
			Piece P7('P','W',1,6);pieceData[0][P7.loc] = P7.type;
			Piece P8('P','W',1,7);pieceData[0][P8.loc] = P8.type;
			Piece R1('R','W',0,0);pieceData[0][R1.loc] = R1.type;
			Piece R2('R','W',0,7);pieceData[0][R2.loc] = R2.type;
			Piece N1('N','W',0,1);pieceData[0][N1.loc] = N1.type;
			Piece N2('N','W',0,6);pieceData[0][N2.loc] = N2.type;
			Piece B1('B','W',0,2);pieceData[0][B1.loc] = B1.type;
			Piece B2('B','W',0,5);pieceData[0][B2.loc] = B2.type;
			Piece Q ('Q','W',0,3);pieceData[0][Q.loc ] =  Q.type;
			Piece K ('K','W',0,4);pieceData[0][K.loc ] =  K.type;
			Piece p1('p','B',6,0);pieceData[0][p1.loc] = p1.type;
			Piece p2('p','B',6,1);pieceData[0][p2.loc] = p2.type;
			Piece p3('p','B',6,2);pieceData[0][p3.loc] = p3.type;
			Piece p4('p','B',6,3);pieceData[0][p4.loc] = p4.type;
			Piece p5('p','B',6,4);pieceData[0][p5.loc] = p5.type;
			Piece p6('p','B',6,5);pieceData[0][p6.loc] = p6.type;
			Piece p7('p','B',6,6);pieceData[0][p7.loc] = p7.type;
			Piece p8('p','B',6,7);pieceData[0][p8.loc] = p8.type;
			Piece r1('r','B',7,0);pieceData[0][r1.loc] = r1.type;
			Piece r2('r','B',7,7);pieceData[0][r2.loc] = r2.type;
			Piece n1('n','B',7,1);pieceData[0][n1.loc] = n1.type;
			Piece n2('n','B',7,6);pieceData[0][n2.loc] = n2.type;
			Piece b1('b','B',7,2);pieceData[0][b1.loc] = b1.type;
			Piece b2('b','B',7,5);pieceData[0][b2.loc] = b2.type;
			Piece q ('q','B',7,3);pieceData[0][q.loc ] =  q.type;
			Piece k ('k','B',7,4);pieceData[0][k.loc ] =  k.type;
		
	
		}

	private:
		//std::vector<double> posData;		///< Store the chess board
		vector<vector<int> > posData;
		vector<vector<char> > pieceData;
		std::string	input_path;		///< Location of the input data
		int		BSize;			///< Size of the board (number of squares)
		int 		Brows;			
		int 		Bcol;
		int 		c1,c2;			///<locations of the pices that moved
		char		Player;			///< Black or White to move
};
