#include <stdio.h>
#include <stdlib.h>

//type of the matrix 
typedef struct _matrix {
    int rs;
    int re;
    int cs;
    int ce;
    int arr[10][10];
}matrix;

//print the matrix on screen 
void print_matrix(matrix matrix)
{
    int i;
	int j;
    for (i = matrix.rs ; i <= matrix.re ; i++) 
	{
        for (j = matrix.cs ; j <= matrix.ce ; j++) 
		{
            printf("%d\t", matrix.arr[i][j]);
		}
        printf("\n");
    }
    printf("\n");
    return;
}
//fill the matrix with random numbers
matrix matrix_fill (matrix matrix)
{
	srand(time(NULL));
    int i, j;
    for (i=matrix.rs ; i<=matrix.re ; i++) 
	{
        for (j=matrix.cs ; j<=matrix.ce ; j++)    
		{		
             matrix.arr[i][j] = rand() % (9 + 1 - (-9)) + (-9); 
		}
    }
   	return matrix;
}
//normal matrix multiplication
void regular_mult(matrix x, matrix y )
{	
	int i;
	int j;
	int k;
	int total = 0;
	
	matrix result = x;
	for(k = x.rs; k <= x.re ; k++) 
	{
		for (i = x.rs ; i <= x.re ; i++) 
		{
			for (j = y.cs ; j <= y.ce ; j++) 
			{
				total = total + x.arr[k][j]*y.arr[j][i]; 
			}			
			result.arr[k][i] = total;
			total = 0; //initialize for the next dot product
		}
	}
	//display the result of the multiplication
	print_matrix(result);
}

//subtract matrix
matrix subtract(matrix x, matrix y)
{
      
    int x_i;
	int x_j;
    int y_i;
	int y_j;
    int i;
	int j;
    int n = x.re - x.rs;
	matrix result; 
    
    result.rs = result.cs = 0;
    result.re = result.ce = n;

    for (x_i=x.rs, y_i=y.rs, i=0 ; x_i<=x.re ; x_i++, y_i++, i++) 
	{
        for (x_j=x.cs, y_j=y.cs, j=0 ; x_j<=x.ce ; x_j++, y_j++, j++) 
		{
            result.arr[i][j] = x.arr[x_i][x_j] - y.arr[y_i][y_j];
		}
	}
    
    return result;
}
//add matrix
matrix add(matrix x, matrix y)
{
       
    int x_i;
	int x_j;
    int y_i;
	int y_j;
    int i;
	int	j;
    int n = x.re - x.rs;
	matrix result;
    
    result.rs = result.cs = 0;
    result.re = result.ce = n;

    for (x_i=x.rs, y_i=y.rs, i=0 ; x_i<=x.re ; x_i++, y_i++, i++)
	{
        for (x_j=x.cs, y_j=y.cs, j=0 ; x_j<=x.ce ; x_j++, y_j++, j++)
		{
            result.arr[i][j] = x.arr[x_i][x_j] + y.arr[y_i][y_j];
		}
	}

    return result;
}



//multiply the matrix 
matrix multiply(matrix x, matrix y)
{
    matrix A, B, C, D, E, F, G, H;
    matrix M1, M2, M3, M4, M5, M6, M7;
    matrix Q1, Q2, Q3, Q4;
    matrix result;
    int x_i, x_j;
    int i, j;
    int n = x.re - x.rs + 1;

	//if the size of the matrix is two
    if (n <= 2) 
	{
        int a, b, c, d, e, f, g, h;
        matrix m3 = x;
        
        a = x.arr[x.rs][x.cs];
        b = x.arr[x.rs][x.cs+1];
        c = x.arr[x.rs+1][x.cs];
        d = x.arr[x.rs+1][x.cs+1];
        e = y.arr[y.rs][y.cs];
        f = y.arr[y.rs][y.cs+1];
        g = y.arr[y.rs+1][y.cs];
        h = y.arr[y.rs+1][y.cs+1];

        m3.arr[m3.rs][m3.cs]      = a*e + b*g;
        m3.arr[m3.rs][m3.cs+1]    = a*f + b*h;
        m3.arr[m3.rs+1][m3.cs]    = c*e + d*g;
        m3.arr[m3.rs+1][m3.cs+1]  = c*f + d*h;

        return m3;
    }

	//solve the matrix using recursion
    result.rs = result.cs = 0;
    result.ce = result.re = n - 1;

    A = B = C = D = x;
    E = F = G = H = y;
    
    A.rs = x.rs;
    A.re = x.re/2;
    A.cs = x.cs;
    A.ce = x.ce/2;
    
    B.rs = x.rs;
    B.re = x.re/2;
    B.cs = x.ce/2 + 1;
    B.ce = x.ce;

    C.rs = x.re/2 + 1;
    C.re = x.re;
    C.cs = x.cs;
    C.ce = x.ce/2;
    
    D.rs = x.re/2 + 1;
    D.re = x.re;
    D.cs = x.ce/2 + 1;
    D.ce = x.ce;

    E.rs = y.rs;
    E.re = y.re/2;
    E.cs = y.cs;
    E.ce = y.ce/2;
    
    F.rs = y.rs;
    F.re = y.re/2;
    F.cs = y.ce/2 + 1;
    F.ce = y.ce;

    G.rs = y.re/2 + 1;
    G.re = y.re;
    G.cs = y.cs;
    G.ce = y.ce/2;
    
    H.rs = y.re/2 + 1;
    H.re = y.re;
    H.cs = y.ce/2 + 1;
    H.ce = y.ce;

    M1 = multiply(A, subtract(F, H));
    M2 = multiply(add(A, B), H);
    M3 = multiply(add(C, D), E);
    M4 = multiply(D, subtract(G, E));
    M5 = multiply(add(A, D), add(E, H));
    M6 = multiply(subtract(B, D), add(G, H));
    M7 = multiply(subtract(A, C), add(E, F));

    Q1 = add(subtract(add(M5, M4), M2), M6);
    Q2 = add(M1, M2);
    Q3 = add(M3, M4);
    Q4 = subtract(subtract(add(M1, M5), M3), M7);

    for (x_i=Q1.rs, i=0 ; x_i<=Q1.re ; x_i++, i++)
	{
        for (x_j=Q1.cs, j=0 ; x_j<=Q1.ce ; x_j++, j++)
		{
            result.arr[i][j] = Q1.arr[x_i][x_j];
		}
	}

    for (x_i=Q2.rs, i=0 ; x_i<=Q2.re ; x_i++, i++)
	{
        for (x_j=Q2.cs, j=n/2 ; x_j<=Q2.ce ; x_j++, j++)
		{
            result.arr[i][j] = Q2.arr[x_i][x_j];
		}
	}

    for (x_i=Q3.rs, i=n/2 ; x_i<=Q3.re ; x_i++, i++)
	{
        for (x_j=Q3.cs, j=0 ; x_j<=Q3.ce ; x_j++, j++)
		{
            result.arr[i][j] = Q3.arr[x_i][x_j];
		}
	}

    for (x_i=Q4.rs, i=n/2 ; x_i<=Q4.re ; x_i++, i++)
	{
        for (x_j=Q4.cs, j=n/2 ; x_j<=Q4.ce ; x_j++, j++)
		{
            result.arr[i][j] = Q4.arr[x_i][x_j];
		}
	}
    
    return result;
}
int main(int argc, char *argv[]) 
{
	int i;

	if (argc != 2)   {
		printf("number of arguments not correct .....\n");
		exit(1);
	}

	int total_size = 1;
	int a = atoi(argv[1]); 
	
	//convert the input given to the power of 2
	for ( i=0; i < a  ; i++ )
		total_size = total_size*2 ;

	matrix matrix1;
	matrix matrix2;
	
	matrix1.rs=0;
 	matrix1.re=total_size-1;
 	matrix1.cs=0;
 	matrix1.ce=total_size-1;
 	matrix2 =matrix1; 

	//fill both matrices with random numbers
	matrix1 = matrix_fill(matrix1);
	matrix2 = matrix_fill(matrix2);
	printf("MATRIX A : \n");
	print_matrix((matrix1)); 
	
	printf("\nMATRIX B : \n");
    print_matrix((matrix2));
    
    printf("\nREGULAR MULTIPLICATION\n");
    regular_mult(matrix1, matrix2);	
    
	printf("\nSTRASSEN'S MATRIX MULTIPLICATION\n");
    print_matrix(multiply(matrix1, matrix2));

    return 0;
}


