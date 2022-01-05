//Author : Pratyay Sarkar
//Semester : 5
//Paper : Numerical Methods
//Program : Newton-Raphson Method

#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include "functionmod2.h"
using namespace std;

const double tolerance = pow(10,-5);

double findRoot(Function f, Function diff, double Xn, double En)
{
    int n=0; double Xn_1 = 0, fXn, fDn, h;
    
    cout<<"\n___________________TABLE FOR ROOTS BETWEEN "<<Xn<<" and "<<En<<"____________________\n";
    cout<<"-------------------------------------------------------------------------------------\n";
    cout<<"     n\t   X(n)\t            f(X(n))\t    f'(X(n))\t    h(n)\t    X(n+1)\n";
    cout<<"-------------------------------------------------------------------------------------\n";
    while(true)
    {
        fXn = f.getValue(Xn);
        fDn = diff.getValue(Xn);
        h = -fXn/fDn;
        Xn_1 = Xn+h;
        printf("%6d\t%10.6lf\t%10.6lf\t%10.6lf\t%10.6lf\t%10.6lf\n",n,Xn,fXn,fDn,h,Xn_1); 
        
        if (abs(Xn_1-Xn) < tolerance)
            return Xn_1;
        n++;
        Xn = Xn_1;
    }
}

int main()
{
    string s;
    cout<<"\n\n_______NEWTON-RAPHSON METHOD TO FIND ROOTS OF A FUNCTION_________\n\n";
    cout<<"Enter a polynomial function f(x):\n";
    getline(cin,s);
    cout<<"\n\nThe polynomial function f(x) = "<<s<<endl;
    Function f(s); //x^3 -8x -4

    string diff = getDiff(f.func);
    cout<<"\nAfter differentiating,i.e. f'(x) = "<<diff<<endl;
    Function d(diff);
    
    double a,b;
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
        double root = findRoot(f,diff,a,b);
        cout<<"-------------------------------------------------------------------------------------\n";
        cout<<"\n\n--------SOLUTION---------\n";
        printf("\nRoot ----> %10.4lf\n\n",root);
    }
}