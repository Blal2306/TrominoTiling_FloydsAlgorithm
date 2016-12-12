#include <stdio.h>
#include <stdlib.h>

int board[30][30];
int SIZE;
int number; //id for each domino

int MyPow(int a,int b)
{
	int out = a;
	while(b != 0)
	{
		out = out*a;
		b--;
	}
	return out;
}
void init(int size, int x, int y)
{
	//make the size power of two
	int total_size = 1;
	while(total_size < size)
	{
		total_size*=2;
	}
	SIZE = total_size;
	number = 1;
	
	//initialize the board with zero values
	for(int i = 0; i < total_size; i++)
	{
		for(int j = 0; j < total_size; j++)
		{
			board[i][j] = 0;
		}
	}
	//mark the hole
	board[x][y] = -1;
}
void start_tromino()
{
	tile(SIZE,0,0);
}
void tile(int size, int begin_x, int begin_y)
{
	//BASE CASE - just need to put one tromino
	if(size == 2)
	{
		for(int i = 0; i < size; i++)
		{
			for(int j = 0; j < size; j++)
			{
				if(board[begin_x+i][begin_y+j] == 0)
				{
					board[begin_x+i][begin_y+j] = number;
				}
			}
		}
		number++;
	}
	//RECURSIVE CASE - for tiling
	else
	{
		int loc_x = begin_x;
		int loc_y = begin_y;
		
		for(int x = begin_x; x < begin_x + size; x++)
		{
			for(int y = begin_y; y < begin_y+size; y++)
			{
				if(board[x][y] != 0)
				{
					loc_x = x;
					loc_y = y;
				}
			}
		}
		
		//HOLE IN THE FIRST QUADRANT
		if(loc_x < begin_x + size/2 && loc_y < begin_y + size/2)
		{
			//UPPER LEFT CORNER
			tile(size/2, begin_x, begin_y);
			
			//put the tromino in the middle
			board[begin_x+size/2][begin_y+size/2-1] = number;
			board[begin_x+size/2][begin_y+size/2] = number;
			board[begin_x+size/2-1][begin_y+size/2] = number;
			
			//ID for the next tromino
			number++;
			
			tile(size/2, begin_x, begin_y+size/2);
			tile(size/2, begin_x+size/2, begin_y);
			tile(size/2, begin_x+size/2, begin_y+size/2);
		}
		
		//QUADRANT NUMBER TWO
		else if(loc_x < begin_x + size/2 && loc_y >= begin_y + size/2)
		{
			//recursively tile upper right quadrant
			tile(size/2, begin_x, begin_y+size/2);
			
			//put tromino in the middle
			board[begin_x+size/2][begin_y+size/2-1] = number;
			board[begin_x+size/2][begin_y+size/2] = number;
			board[begin_x+size/2-1][begin_y+size/2-1] = number;
			
			//id for the next tromino
			number++;
			
			tile(size/2, begin_x, begin_y);
			tile(size/2, begin_x+size/2, begin_y);
			tile(size/2, begin_x+size/2, begin_y+size/2);
		}
		
		//QUADRANT THREE
		else if(loc_x >= begin_x + size/2 && loc_y < begin_y + size/2)
		{
			tile(size/2,begin_x+size/2, begin_y);
			
			board[begin_x+size/2-1][begin_y+size/2] = number;
			board[begin_x+size/2][begin_y+size/2] = number;
			board[begin_x+size/2-1][begin_y+size/2-1] = number;
			
			//id for the tromino
			number++;
			
			tile(size/2, begin_x, begin_y);
			tile(size/2, begin_x, begin_y+size/2);
			tile(size/2, begin_x+ size/2, begin_y+size/2);
			
		}
		//FOURTH QUADRANT
		else
		{
			tile(size/2,begin_x+size/2, begin_y+size/2);
			board[begin_x+size/2-1][begin_y+size/2] = number;
			board[begin_x+size/2][begin_y+size/2-1] = number;
			board[begin_x+size/2-1][begin_y+size/2-1] = number;
			
			//id for the next tromino
			number++;
			
			tile(size/2, begin_x+size/2, begin_y);
			tile(size/2, begin_x, begin_y+size/2);
			tile(size/2, begin_x, begin_y);
		}
	}
}
void print_board()
{
	for(int i = 0; i < SIZE; i++)
	{
		for(int j = 0; j < SIZE; j++)
		{
			if(board[i][j] == -1)
				printf("X\t");
			else
				printf("%d\t",board[i][j]);
		}
		printf("\n");
	}
}
int main(int argc, char *argv[])
{
	int k = atoi(argv[1]);
	k--;
	int size = MyPow(2, k);
	//random number for the holes
	srand(time(NULL));
	int x = rand() % ((size-1)+ 1 - (0)) + (0);
	int y = rand() % ((size-1)+ 1 - (0)) + (0);
	
	init(size, x, y);
	start_tromino();
	print_board();
	return 0;
}
