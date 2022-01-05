//Author : Pratyay Sarkar
//Semester : 5
//Paper : Numerical Methods
//Program : Bisection Method

#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include "functionmod.h"
using namespace std;

const double tolerance = pow(10,-5);

double findRoot(Function f, double An, double Bn)
{
    int n=0; double Xn_1 = 0,y = 0, Xn=0;
    if (f.getValue(An)>0 || f.getValue(Bn)<0) //always ensure f(An) is negative
    {
        An = An+Bn;
        Bn = An-Bn;
        An = An-Bn;
    }
    cout<<"\n___________________TABLE FOR ROOTS BETWEEN "<<An<<" and "<<Bn<<"____________________\n";
    cout<<"----------------------------------------------------------------------\n";
    cout<<"     n\t     A(n)     \t     B(n)\t    X(n+1)\t  f(X(n+1))\n";
    cout<<"----------------------------------------------------------------------\n";
    while(true)
    {
        Xn_1 = (An+Bn)/2;
        y = f.getValue(Xn_1);
        printf("%6d\t%10.6lf\t%10.6lf\t%10.6lf\t%10.6lf\n",n,An,Bn,Xn_1,y);
        if (y<0)
            An = Xn_1;
        else if (y>0)
            Bn = Xn_1;
        else 
            return Xn_1; 
        
        if (abs(Xn_1-Xn) < tolerance)
            return Xn_1;
        n++;
        Xn = Xn_1;
    }
}

int main()
{
    string s;
    cout<<"\n\n_______BISECTION METHOD TO FIND ROOTS OF A POLYNOMIAL FUNCTION_________\n\n";
    cout<<"Enter a polynomial function f(x):\n";
    getline(cin,s);
    cout<<"\n\nThe polynomial function f(x) = "<<s<<endl;
    
    Function f(s); double a,b;
    cout<<"\nEnter the integer boundaries of the root: ";
    cin>>a>>b;
    double fAn = f.getValue(a);
    double fBn = f.getValue(b);
    
    cout<<"\n\n------Values at boundary points--------"<<endl;
    cout<<"      f("<<a<<") = "<<fAn<<endl;
    cout<<"      f("<<b<<") = "<<fBn<<endl;
    cout<<"---------------------------------------\n\n";

    if (fAn*fBn>0)
        cout<<"No roots are in the interval ("<<a<<", "<<b<<").\n";
    else if(fAn*fBn==0)
    {
        if (fAn==0)
            cout<<"\nThe Boundary value "<<a<<" is a root.\n\n";
        if (fBn==0)
            cout<<"\nThe Boundary value "<<b<<" is a root.\n\n";
    }
    else
    {
        double root = findRoot(f,a,b);
        cout<<"\n\n--------SOLUTION---------\n";
        printf("\nRoot ----> %10.4lf\n\n",root);
    }
}