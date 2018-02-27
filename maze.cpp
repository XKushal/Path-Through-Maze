#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
				
using namespace std;

//global variables 
char space = ' ';  //any space inside the maze represents a character
char path = '|';   //this character is printed in the path followed
const int row_size=22;  //maximum size of the rows
const int col_size=76;  //maximum size of the column
typedef char maze[row_size][col_size];  //type defination of the array

//function prototype 
//this function finds the path through the maze
void find_paths( maze myMaze, int r, int c, int read_row, int read_column);
//precondition: the size of the maze should be less than or equal to 22 by 76
//the starting point of the maze should always be at the second posiiton i,e (1,2)
//Postcondition: For each path thorugh the maze, the maze and that path should be 
//printed in the terminal and the path is represented by the unique character
//main
int main()
{  
	int read_row, read_column;  //integer variable to read row and column
	char asterisk;   //it reads the character inside the maze
	maze myMaze;     //the new object for the maze
	
	//reading the maze from the file
	ifstream infile;
	const int NAMESIZE=20;  //size of the input file
	char input_filename[NAMESIZE+1];
	cout<<"Enter the name of the input file: ";
	cin>>input_filename;
	infile.open(input_filename);  //opens the input file
	//incase the file cannot be read
	if(!infile)
	{
		cout<<"Cannot open the input file.\n";
		return 0;
	}
	
	//reads the row and column of the maze(size)
	infile>>read_row>>read_column;
	infile.get(asterisk);   //take one character at a time
	//Reads whole size of the maze
	for(int i=0; i<read_row; ++i)
	{
		for(int j = 0; j<read_column; ++j)
		{ 			infile.get(myMaze[i][j]); 
		}
		infile.get(asterisk); 
	}

	//Prints the input file which contains maze
	cout << "The maze of size "<<read_row<<" by "<<read_column<<" before finding the path is: \n";
	for(int i=0; i<read_row; ++i)
	{
		for(int j=0; j<read_column; ++j)
		{
			cout<<myMaze[i][j];
		}
		cout<<endl;
	}
	cout<<endl;
	//Prints the maze after finding the path through the maze 
	cout<<"The maze of size "<<read_row<<" by "<<read_column<<" after finding the path through the maze: \n";
    myMaze[0][1] = path; //by default starting point of the maze
   find_paths ( myMaze, 0, 1, read_row, read_column );

	return 0;
}

//the function finds the path through the maze
void find_paths ( maze myMaze, int r, int c, int read_row, int read_column )
{
	//base case: when the r reaches to maximum row that it cannot move further
	//steps down so it prints the path its been through
  if ( r == read_row-1 )
 	for(int i=0; i<read_row; ++i)
	{
		for(int j=0; j<read_column; ++j)
		{
			cout<<myMaze[i][j];
		}
		cout<<endl;
	}
  else
  {
  	//moves upward if it finds the space from that position
    if ( r > 0 && myMaze[r-1][c] == space ) 
    {
      myMaze[r-1][c] = path;
      find_paths(myMaze,r-1,c,read_row,read_column);//recursive call
      myMaze[r-1][c] = space;
    }
   	//moves downward if it finds the sapce from that  very position
    if ( myMaze[r+1][c] == space )
    {
      myMaze[r+1][c] = path;
      find_paths(myMaze,r+1,c,read_row,read_column);
      myMaze[r+1][c] = space;
    }
   	//moves left if it finds the sapce from that same position
    if ( myMaze[r][c-1] == space ) 
    {
      myMaze[r][c-1] = path;
      find_paths(myMaze,r,c-1,read_row,read_column);
      myMaze[r][c-1] = space;
    }
   	//moves right if it finds the sapce from that same position
    if ( myMaze[r][c+1] == space ) 
    {
      myMaze[r][c+1] = path;
      find_paths(myMaze,r,c+1,read_row,read_column);
      myMaze[r][c+1] = space;
    }
  }
}
