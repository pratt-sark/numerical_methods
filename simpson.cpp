//Author : Pratyay Sarkar
//Semester : 5
//Paper : Numerical Methods
//Program : Simpson's 1/3rd Rule for Numerical Integration

#include <iostream>
#include <iomanip>
#include <vector>
#include <math.h>

using namespace std;

#define f(x) 1.0/pow((1+x),2)
#define func_representation "y = 1/((1+x)^2)"

void solve(double a, double b, double h, int n)
{
    double x=a,temp,Y0=0,Y1=0,Y2=0;
    vector<double> y;
    cout<<("\n---------------------------------");
    printf("\n   Xi\t\t\t    Yi");
    cout<<("\n---------------------------------");
    while (x<=b)
    {
        temp = f(x); printf("\n%lf\t\t%lf\n",x,temp);
        y.push_back(temp);
        x+=h;
    }

    Y0 = Y0 + y[0] + y[n];
    for (int i=1;i<n;i++)
    {
        if (i%2==1)
            Y1 = Y1 + y[i];
        else
            Y2 = Y2 + y[i]; 
    }

    cout<<("\n---------------------------------\n");
    double result = (h/3)*(Y0 + 4*Y1 + 2*Y2);
    cout<<"\nh = "<<h<<endl;
    cout<<"\nY0 = "<<Y0<<endl;
    cout<<"\nY1 = "<<Y1<<endl;
    cout<<"\nY2 = "<<Y2<<endl;
    cout<<"\n"<<func_representation<<" integrated from "<<a<<" to "<<b<<" = "<<result<<endl;
    cout<<"\nANSWER --> "<<result<<endl;
}

int main()
{
    double a,b,h;
    int n;
    cout<<"\n\n_______Simpson's 1/3rd Rule for Numerical Integration_________\n\n";
    cout<<"The function in use--> "<<func_representation<<"\n\n";
    cout<<"Enter lower limit (a) = ";
    cin>>a;
    cout<<"\nEnter upper limit (b) = ";
    cin>>b;
    cout<<"\n\nEnter number of equal intervals (n) = ";
    cin>>n;

    h = (b-a)/n;
    cout<<"\n----------------------------------------------------\n"<<endl;
    solve(a,b,h,n);
    cout<<"\n----------------------------------------------------\n\n";
    return 0;
}