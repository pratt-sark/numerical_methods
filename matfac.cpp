//Author : Pratyay Sarkar
//Semester : 5
//Paper : Numerical Methods
//Program : Matrix LU Decomposition and finding roots

#include <iostream>
#include "matrix.h"
using namespace std;

int main()
{
    //________INPUT STARTS_________
    int n; //order of coefficient matrix
    cout << "\nEnter order of COEFFICIENT MATRIX:\n";
    cin >> n; //order accepted from user
    Matrix aug(n,n+1);
    Matrix a(n,n);
    Matrix l(n,n);
    Matrix u(n,n);

    cout << "\nThe augmented matrix will be of order (" << n << "*" << n + 1 << ").\n";
    cout << "\nEnter " << n * (n + 1) << " elements of the AUGMENTED MATRIX:\n";
    aug.input(); //elements of augmented matrix accepted from user
    a.subMatrix(aug, 0, 0, n, n); //coefficient matrix extracted from augmented matrix
    //_________INPUT ENDS________

    cout<<"\n\n--------------ITERATIONS----------------\n\n";
    a.factorize(l,u);
    cout<<"\n\n----------------------------------------\n\n";

    cout<<"\n\n----------------OUTPUT------------------\n\n";
    cout << "\nThe Augmented Matrix : \n";
    aug.output();
    cout << "\nThe L Matrix : \n";
    l.output();
    cout << "\nThe U Matrix : \n";
    u.output();
    cout<<"\n\n----------------------------------------\n\n";
    
    cout<<"\nEvaluating Y such that LY=C where C->constant Vector.........\n";
    Matrix Y(n,1);
    double sum=0;
    int i,j;
    for (i = 0; i < n; i++)
    {
        sum = 0;
        for (j = 0; j < i; j++)
            sum += (Y.elements[j][0] * l.elements[i][j]);
        Y.elements[i][0] = (aug.elements[i][n] - sum) / l.elements[i][i];
    }

    cout<<"\nThe Y matrix :\n";
    Y.output();

    cout<<"\nEvaluating X(roots) such that UX=Y.........\n";
    Matrix X(n,1);
    for (i = n-1; i >= 0; i--)
    {
        sum = 0;
        for (j = i+1; j < n; j++)
            sum += (X.elements[j][0] * u.elements[i][j]);
        X.elements[i][0] = (Y.elements[i][0] - sum) / u.elements[i][i];
    }

    cout<<"\n\n----------------------------------------\n\n";
    cout<<"The roots :\n";
    X.output();
    cout<<"\n----------------------------------------\n\n";
    return 0;
}