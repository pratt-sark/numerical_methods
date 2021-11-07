//Author : Pratyay Sarkar
//Semester : 5
//Paper : Numerical Methods
//Program : Accept a number 'n' and divide it into 'p' random parts

//___Header Files___
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <time.h>
#include <stdbool.h>

//___Function List___
void check_for_zeroes(double *array, int p);
void display_sum(double *array, int p);
void display(double *array, int p);
bool dupli(double *array, int p);

//Execution starts here
void main()
{
    int p; //number of parts
    double n; //the number to be split

    printf("\n\n----------Program to accept a number and split it into 'p' parts------\n");

    //______INPUT 'n' and 'p'_____
    printf("\nEnter a number : ");
    scanf("%lf",&n);
    printf("\nEnter the value 'p' : ");
    scanf("%d",&p);
    //______End of input______

    //Declaring an array of size 'p' to store the 'p' parts
    double *a = (double *)(calloc(p,sizeof(double)));

    //Setting the seed for rand() to generate random numbers
    srand(time(NULL)*1000);

    //_____Declaration of important variables_______
    double ran=0; //to store a random part (value cahnges in every iteration of loop) 
    int i; //control variable of loop
    double temp=0; //to temporarily store a random part which is finally stored in 'ran'
    double n_copy = n; //copy of n
    //______________________________________________
    
    //Initial log (for end-user clarity)
    printf("\nThe number = %lf\n",n);
    printf("\nWorking on the number.....\nFinding splits...\nSearching for Duplicates....\n\n");
    
    //Actual work starts here
    for (i=1;i<p;i++)
    {
        compute: temp = ((double)(rand())/(double)(RAND_MAX)) * (n/(p-i));
        //printf("\nim here bruh Iteration %d - %lf\n",i,temp);        
        if (temp==0)
            goto compute;
        ran = temp; //the random part, if not zero, is stored in 'ran'
        a[i-1]=ran; //storing the random part in the array
        if (dupli(a,i))
        {
            a[i-1]=0; goto compute;
        }
        n -= ran; //n decremented by 'ran'
    }
    a[i-1]=n; //the last part stored in the array

    //______Debuggers log______
    printf("\nDuplicates removed and replaced sucessfully. \nPrinting values.....\n\n");
    //_________________________
    printf("\nThe %d parts are: \n",p);
    display(a,p); //display the parts
    display_sum(a,p); //the sum of the parts is calculated and displayed for correctness
    check_for_zeroes(a,p); //to check for any zeroes are present in the array (which is undesirable)
    free(a);
}

//Displays the 'p'parts
void display(double *arr, int p)
{
    int i;
    for (i=0;i<p;i++)
        printf("\nPart %3d:\t%0.25lf",i+1,arr[i]);
    
}

//Displays the sum of all the numbers in the array
void display_sum(double *array, int p)
{
    int i; double sum=0;
    for (i=0;i<p;i++)
        sum+=array[i];
    printf("\n__________\n\nSum of these %d numbers = %lf\n_________\n",p,sum);
}

//Checks if any zeroes are present in the array
void check_for_zeroes(double *array,int p)
{
    int i,count=0;
    for(i=0;i<p;i++)
        if (array[i]==0)
        {
            count++;
            printf("\nZero detected - Part %d\n",i+1);
        }
    if (count==0)
        printf("\nOutput OK (No zeroes found)\n\n");
    else
        printf("\nUnsuccessful split (One or multiple zeroes found)\n\n");
}

//to check for duplicates in generated numbers
bool dupli(double *array, int p)
{
    int i,j;
    for (i=0;i<p;i++)
    {
        for (j=i+1;j<p;j++)
            if (array[i]==array[j])
                goto out;
    }
    out:
        if (i!=p)
        {
            printf("\nDuplicates exist at %d, %d\n",i+1,j+1);
            return true;
        }  
    return false;  
}