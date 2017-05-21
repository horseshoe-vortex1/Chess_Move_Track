//Class to store information about the piece
#include <vector>
#include <iostream>
using namespace std;

class Piece
{
	public:	
		


		// Initialization
		Piece(char type_,char owner_,int row_,int col_)
		{
			type  = type_;
			owner = owner_;
			row   = row_;
			col   = col_;		
			taken = false;
			loc   = row_*8+col_; 
		}



		//	Pawn	P 
		//	Rook	R
		//	Queen	Q
		// 	Bishop	B
		//	Knight	N
		//	King	K

		char	type;	
		char	owner;
		int	row;
		int 	col;
		bool	taken;
		int	loc;	///< location on the board vector
		
};
