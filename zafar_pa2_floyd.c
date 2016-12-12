#include <stdio.h>
#include <stdlib.h>

FILE *fr;
//MAIN DATA STRUCTURES
int matrix[30][30];
int p_matrix[30][30];
int size = 0;
int matrix_it = 1;

//HELPER METHODS
void init_matrix()
{
	for(int i = 1; i < size; i++)
	{
		for(int j = 1; j < size; j++)
		{
			if(i == j)
			{
				matrix[i][j] = 0;
				p_matrix[i][j] = 0;
			}	
			else
			{
				matrix[i][j] = 499;
				p_matrix[i][j] = 0;
			}	
		}
	}
	

}
void print_matrix()
{
	printf("D - MATRIX\n\n");
	for(int i = 1; i < size; i++)
	{
		for(int j = 1; j < size; j++)
		{
			printf("%d\t",matrix[i][j]);
		}
		printf("\n");
	}
	printf("\nP - MATRIX\n\n");
	for(int i = 1; i < size; i++)
	{
		for(int j = 1; j < size; j++)
		{
			printf("%d\t",p_matrix[i][j]);
		}
		printf("\n");
	}
	
}
void path(int x, int y)
{
	if(p_matrix[x][y] != 0)
	{
		path(x,p_matrix[x][y]);
		printf(", v%d",p_matrix[x][y]);
		path(p_matrix[x][y],y);
	}
	else
		return;
}
void path_init(int x, int y)
{
	printf("From v%d to v%d : ",x,y);
	printf("v%d",x);
	path(x,y);
	printf(", v%d\n",y);
}
int main(int argc, char *argv[])
{
	// *** START OF FILE READING *** //
	int n;
	char line[80];

	fr = fopen (argv[1], "rt");
	
	//GET THE DIMENSIONS OF THE MATRIX
	fgets(line,30,fr);
	char temp[30] = ""; //FIRST LINE STORED HERE
	char* pch;
	pch = strtok(line,",");
	while(pch != NULL)
	{
		strcat(temp,pch);
		strcat(temp," ");
		pch = strtok(NULL,",");
		size++;
	}
	size++;
	
	int row = 1;
	int column = 1;
	//parse the first line
	pch = strtok(temp," ");
	while(pch != NULL)
	{
		matrix[row][column] = atoi(pch);
		pch = strtok(NULL," ");
		column++;
	}
	
	//read all the files	
	while(fgets(line, 10, fr) != NULL)
	{
		row++;
		char* pch;
		pch = strtok(line,",");
		column = 1;
		while(pch != NULL)
		{
			matrix[row][column] = atoi(pch);
			pch = strtok(NULL,",");
			column++;
		}
	}
	fclose(fr);
	// *** END OF FILE READING *** //
	
	// *** START OF THE DISTANCE MATRIX CALCULATION *** //
	for(int k = 1; k < size; k++)
	{
		for(int i = 1; i < size; i++)
		{
			for(int j = 1; j < size; j++)
			{
				if(matrix[i][j] > (matrix[i][k] + matrix[k][j]))
				{
					matrix[i][j] = matrix[i][k] + matrix[k][j];
					p_matrix[i][j] = k;
				}
			}
		}
	}
	
	print_matrix();
	
	printf("\nShortest path for each pair of node :\n\n");
	for(int i = 1; i < size; i++)
	{
		for(int j = 1; j < size; j++)
		{
			path_init(i, j);
		}
	}
	
	return 0;
}


