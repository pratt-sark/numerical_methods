//Author : Pratyay Sarkar
//Semester : 5
//Paper : Numerical Methods
//Program : q-th root of a number Newton-Raphson Method

#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include "functionmod2.h"
using namespace std;

const double tolerance = pow(10,-5);
const int ITER_MAX = pow(10,4);

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

double startFind(Function f,Function diff)
{
    double x=1,y,y0=f.getValue(0);
    int count=0;
    while(true)
    {
        y = f.getValue(x);
        if (y == 0)
            return x;
        else if (y*y0 < 0)
            return findRoot(f,diff,x-1,x);             
        x++;
        y0 = y;

        count++;
        if(count>ITER_MAX)
        {
            cout<<"\n\nNo positive roots found.\n";
            break;
        }
    }
}

int main()
{
    string s;
    double n;
    int q;
    cout<<"\n\n_______TO FIND q-th ROOT OF A NUMBER_________\n\n";
    cout<<"Enter a number:\n";
    cin>>n;
    cout<<"Enter the value of q:\n";
    cin>>q;
    s = "+x^"+to_string(q)+" -"+to_string(n);
    cout<<"\n\nThe polynomial function f(x) = "<<s<<endl;
    Function f(s); //x^3 -8x -4

    string diff = getDiff(f.func);
    cout<<"\nAfter differentiating,i.e. f'(x) = "<<diff<<endl;
    Function d(diff);
    
    cout<<"\n\nDo you want to specify boundaries of roots?\nEnter y for yes, otherwise enter any other character:\n";
    char c; cin>>c;

    if (c=='y'||c=='Y')
    {
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
    else
    {
        double root = startFind(f,diff);
        cout<<"-------------------------------------------------------------------------------------\n";
        cout<<"\n\n--------SOLUTION---------\n";
        printf("\nRoot ----> %10.4lf\n\n",root);
    }
}