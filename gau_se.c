//Author : Pratyay Sarkar
//Semester : 5
//Paper : Numerical Methods
//Program : Solve a system of 'n' linear equations having 'n' unknowns
//(Gauss-Seidel Iterative Method)

//___Header Files___
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

//___Function List___
void input(int **a,int n);
void display(int **a,int n);
void display1d(double *a, int n);
void swap(int *a, int *b);
int** allocatemem(int n);
bool check_diag(int **a, int n);
void gauSeidel(int **a, int n, double *x);

bool changed_to_diag_dom;

//Execution starts here
void main()
{
    int **a; //matrix of n*(n+1)
    int n; //number of equations and/or number of unknowns
    printf("\n\n-----Gauss-Seidel Iterative Method-------");
    printf("\n\n(Program to accept Augmented Matrix (n*(n+1)) and display the value of unknowns)\n");
    printf("\nEnter the value of n:\n");
    scanf("%d",&n);
    a = allocatemem(n); //allocate memory for a matrix of size (n*(n+1))
    double *result = (double *)calloc(n,sizeof(double));
    printf("\nEnter %d elements of augmented matrix:\n",n*(n+1));
    input(a,n);
    printf("\n\nThe augmented matrix (%d*%d):\n",n,n+1);
    display(a,n);
    if(!check_diag(a,n))
        exit(1);
    
    if (changed_to_diag_dom)
    {
        printf("\n\nAfter making the augmented matrix (%d*%d) diagonally dominant:\n",n,n+1);
        display(a,n);
    }
    printf("\n\n-----SOLUTION-------\n");
    gauSeidel(a,n,result);
}

int get_maxIndex(int **a, int n, int i)
{
    int j,max_index=0;
    for(j=1;j<n;j++)
        if (a[i][j]>a[i][max_index])
            max_index = j;
    return max_index;
} 

bool diag_dom(int **a, int n, int row)
{
    int j,sum=0;
    for(j=0;j<n;j++)
    {
        if (row!=j)
            sum+=abs(a[row][j]);
    }
    return (abs(a[row][row])>sum);
}

bool check_diag(int **a, int n)
{
    int i,j,sum=0,count_okays;
    bool is_okay[n]; 

    check1:
    count_okays=0;
    for(i=0;i<n;i++)
    {
        if (diag_dom(a,n,i))
        {
            //printf("\nRow %d is diag.dom.\n",i);
            is_okay[i] = true;
            count_okays++;
        }
    }   
    if (count_okays==n)
        return true;
    else if (count_okays==n-1)
    {
        printf("\nCannot be made strictly diagonally dominant.\nUnsuitable for Gauss-Seidel Method.\n");
        return false;
    }
    else
    {
        //attempt to make diagonally dominant
        for(i=0;i<n;i++)
        {
            if (!is_okay[i])
            {
                int max_index = get_maxIndex(a,n,i);
                //printf("\nIndex %d is not okay, max = %d\n",i,max_index);
                if (!(is_okay[max_index]) && max_index!=i)
                {
                    for (j=0;j<=n;j++)
                        swap(&a[max_index][j],&a[i][j]);
                }
                /*else
                {
                    printf("\nCannot be made strictly diagonally dominant.\nUnsuitable for Gauss-Seidel Method.\n");
                    return false;
                }*/
                if(diag_dom(a,n,i) && diag_dom(a,n,max_index))
                {
                    is_okay[i] = true;
                    is_okay[max_index] = true;
                }
            }
        }
        changed_to_diag_dom = true;
    }
    goto check1;
    //return true;
}

//to find solution vector using Gauss-Seidel Method
void gauSeidel(int **a, int n, double *x)
{
    int i,j,k=1;
    //initial values of solution vector [all zeroes]
    double *x_in = (double *)calloc(n,sizeof(double));;
    while (true)
    {
        for(i=0;i<n;i++)
        {
            //upper triangular part uses previous values of x (x_in[])
            for(j=i+1;j<n;j++)
                x[i] = x[i] + (-1.0*a[i][j]*x_in[j]);
            //lower triangular part uses current values of x (x[])
            for(j=0;j<i;j++)
                x[i] = x[i] + (-1.0*a[i][j]*x[j]);            

            //adding the constant_vector element and dividing by diagonal element
            x[i] = (x[i] + a[i][n])/a[i][i];
        }
        
        //printf("\n");
        //______end______
        for(i=0;i<n;i++)
        {
            //setting condition for breaking out of loop: 3 decimal places
            if(fabs(x[i]-x_in[i])>0.001)
                break;
        }
        //if a sufficiently precise solution is reached, break
        if (i==n)
            break;
        k++; //increment number of iterations
        //change the values of (solution vector) to zeroes and initial values to current values
        for(i=0;i<n;i++)
        {
            x_in[i] = x[i];
            x[i] = 0;
        }
    }
    display1d(x,n);
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

void display1d(double *a, int n)
{
    int i;
    for(i=0;i<n;i++)
        printf("x%d = %lf\n",i+1,a[i]);
}

//to swap two numbers
void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}