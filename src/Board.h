// Class to perform all operations related to the chess board
#include <vector>
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
			BSize 	   = 9;
			Brows	   = 3;
			Bcol	   = 3;
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

			// Dimension the Dense Matrices
			for (int i=0;i<nLines;i++)
			{
			posData[i].resize(BSize);
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
			printf("\nMove number : %d",move);
			printf("\n--------------------------------------------");
			printf("\n"); 
			for(int i=0;i<Brows;i++)
			{
				for(int j=0;j<Bcol;j++)
				{
					cout<<posData[move][i*Bcol+j]<<'\t';
				}
				cout<<'\n';
			}
			printf("\n--------------------------------------------\n");
			
		}

	private:
		//std::vector<double> posData;		///< Store the chess board
		vector<vector<int> > posData;
		std::string	input_path;		///< Location of the input data
		int		BSize;			///< Size of the board (number of squares)
		int 		Brows;			
		int 		Bcol;
};
