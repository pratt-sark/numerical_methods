//Author : Pratyay Sarkar
//Semester : 5
//Paper : Numerical Methods
//Program : Solve a system of 'n' linear equations having 'n' unknowns (Gaussian elimination)

//___Header Files___
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//___Function List___
void input(int **a,int n);
void display(int **a,int n);
int** allocatemem(int n);
void process_matrix(int **mat, int n);

bool *col_zero;

//Execution starts here
void main()
{
    int **a; //matrix of n*(n+1)
    int n; //number of equations and/or number of unknowns
    col_zero = (bool *)calloc(n,sizeof(bool));
    printf("\n\n-----Gaussian Elimination Method-------");
    printf("\n\n(Program to accept Augmented Matrix (n*(n+1)) and display the value of unknowns)\n");
    printf("\nEnter the value of n:\n");
    scanf("%d",&n);
    a = allocatemem(n); //allocate memory for a matrix of size (n*(n+1))
    printf("\nEnter %d elements of augmented matrix:\n",n*(n+1));
    input(a,n);
    printf("\n\nThe augmented matrix (%d*%d):\n",n,n+1);
    display(a,n);
    process_matrix(a,n);
}

int ** allocatemem(int x)
{
    int **a = (int **)calloc(x,sizeof(int *));
    int i;
    for (i=0;i<x;i++)
        a[i] = (int *)calloc(x+1,sizeof(int));
    return a;
}

void input(int **a, int x)
{
    int i,j;
    for (i=0;i<x;i++)
        for (j=0;j<=x;j++)
            scanf("%d",&a[i][j]);
}

void display(int **a, int x)
{
    int i,j;
    for (i=0;i<x;i++)
    {
        for (j=0;j<=x;j++)
            printf("%d\t",a[i][j]);
        printf("\n");
    }
}

//to swap two numbers
void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

//solve the upper triangular matrix
void solve(int **a,int n)
{
    int i,j;
    double ans=0,x[n],c;
    printf("\n\n-----SOLUTION-------\n");
    for (i=n-1;i>=0;i--)
    {
        if (col_zero[i]) //i-th unknown does not exist in input
            continue; 
        ans = 0;
        c = a[i][i];
        for(j=i+1;j<n;j++)
            ans+=(a[i][j]*x[j]);
        ans = (a[i][n]-ans)/c;
        x[i] = ans;
    }
    for(i=0;i<n;i++)
        printf("\nx%d = %f",i+1,x[i]);
    printf("\n");
}

//check for finite, infinite or no solution
bool check(int **a,int n)
{
    int i,j;
    int flag,z=0;
    for (i=0;i<n;i++)
    {
        flag=0;
        for(j=0;j<=n;j++)
        {
            if (a[i][j]!=0)
                flag++;
        }
        if (flag==0)
            z=1;
        else if (flag==1 && a[i][n]!=0)
            z=2;
    }
    if (z==1)
    {
        printf("\nInfinitely Many Solutions.\n");
        return false;
    }
    else if (z==2)
    {
        printf("\nNo Solutions.\n");
        return false;
    }
    return true;
}

//Function to convert the passed matrix into an upper triangular matrix
void process_matrix(int **mat, int n)
{
	int i,num1, num2, index; //Initialize values

	// temporary array for storing row of pivot element
	int temp[n+1];

	// loop for traversing the diagonal elements
	for (i=0;i<n;i++) 
	{
		index = i; // initialize the index

		// finding the index which has non zero value (pivot element)
		while (index<n && mat[index][i] == 0) 
			index++;
		if (index == n) // if there is no non zero element
		{
            col_zero[i] = true; //indicates that column-i is a zero vector
            continue;
        }
		if (index != i) 
		{
			// loop for swaping the diagonal element row and index row
			for (int j=0; j<=n; j++)
				swap(&mat[index][j], &mat[i][j]);
		}
		// storing the values of pivot elements' row
		for (int j=0; j<=n; j++)
			temp[j] = mat[i][j];

		// traversing every row below the pivot element
		for (int j = i+1; j<n; j++) 
		{
			num1 = temp[i]; // value of diagonal element
			num2 = mat[j][i]; // value of next row element

			// traversing the each element of j-th row
			for (int k=0; k<=n; k++) 
			{
				// multiplying to make the diagonal element and next row element equal
                // and then subtracting 
				mat[j][k] = (num1 * mat[j][k]) - (num2 * temp[k]);
			}
		}
	}
    printf("\nMatrix after processing: \n");
    display(mat,n);
    if (check(mat,n))
        solve(mat,n);
}