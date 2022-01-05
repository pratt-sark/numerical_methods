//Author : Pratyay Sarkar
//Semester : 5
//Paper : Numerical Methods
//Program : Tabular Method

#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include "functionmod.h"
using namespace std;

const double tolerance = pow(10,-5);
const int ITER_MAX=500;

class FunctionRoot
{
    public: 
    vector<double> roots;

    void getPosRoots(Function f, int n, vector<pair<double,double>> boundary)
    {
        double x=1,y,y0=f.getValue(0);
        int k=0, zeroes=0,count=0;
        cout<<"\n\n---------INITIAL TABULATION TO IDENTIFY ROOT BOUNDARIES---------\n\n";
        cout<<"-----------------------------\n";
        cout<<"    x       \t      f(x)    \n";
        cout<<"-----------------------------\n";
        printf("%7.6lf\t%12.6lf\n",0,y0);
        if (y0 == 0)
        {   
            roots.push_back(0);
            k++; zeroes++;
            if (n==0) //if there is no positive root, this is the only root (x=0)
            {
                displayRoots();
                exit(0);
            }
        }
        while(true)
        {   
            y = f.getValue(x);
            if (y0 == 0 && validBounds(f,x-1,x)) //if x is a root, as well as a boundary
            {
                boundary.push_back(make_pair(x-1,x));   
                k++; 
            }
            if (y == 0) //x is a root, so do stuff accordingly
            {
                zeroes++; k++;
                roots.push_back(x);
            }
            else if (y*y0 < 0)
            {
                boundary.push_back(make_pair(x-1,x));   
                k++;            
            }    
            printf("%7.6lf\t%12.6lf\n",x,y);
            x++;
            y0 = y;
            if (k==n || zeroes==n)
                break;
            
            count++;
            if(count>ITER_MAX)
            {
                cout<<"\n\nThere are only "<<k<<" positive real roots.\n";
                break;
            }
        }
        cout<<"-----------------------------\n\n";
        if (!boundary.empty())
        {
            cout<<"The Boundary Pairs in which the roots lie: \n\n";
            display(boundary);
            cout<<"\n___________________________________________________________";
            cout<<"\n----------TABULATING ROOT BOUNDARIES TO FIND ROOTS---------";
            cout<<"\n___________________________________________________________";
            getRoots(f,boundary);
        }
    }

    void display(vector<pair<double,double>> boundary)
    {
        for (int i=0;i<boundary.size();i++)
            cout<<boundary[i].first<<" , "<<boundary[i].second<<endl;
    }

    bool validBounds(Function f, double a, double b)
    {
        double h = (b-a)/10;
        double i,y,y0=f.getValue(a);
        for (i=a+h;i<=b;i+=h)
        {
            y = f.getValue(i);
            if (y*y0 < 0)
                return true;
            y0 = y;
        }
        return false;
    }

    double rootfinder(Function f, double a, double b)
    {
        double h = (b-a)/10;
        double i,y,y0=f.getValue(a);
        cout<<"\n\n********* TABLE FOR "<<a<<"<root<"<<b<<" **********\n\n";
        cout<<"-----------------------------\n";
        cout<<"    x       \t      f(x)    \n";
        cout<<"-----------------------------\n";
        printf("%7.6lf\t%12.6lf\n",a,y0);
        for (i=a+h;i<=b;i+=h)
        {
            y = f.getValue(i);
            printf("%7.6lf\t%12.6lf\n",i,y);
            if (y*y0 < 0)
            {
                cout<<"-----------------------------\n\n";
                if (h<tolerance)
                    return i;
                else
                    return (1*rootfinder(f,i-h,i));
            }
            y0 = y;
        }
    }

    void getRoots(Function f, vector<pair<double,double>> boundary)
    {
        int i; double root;
        for (i=0;i<boundary.size();i++)
        {
            root = rootfinder(f,boundary[i].first,boundary[i].second);
            roots.push_back(root);
            cout<<"\n_________________________\n";
            cout<<"------ROOT FOUND!!-------\n_________________________\n\n";
            //printf("\nRoot %d ---->  %7.4lf",i+1,root);
        }
    }

    void displayRoots()
    {
        for (int i=0;i<roots.size();i++)
            printf("\nRoot %d ---->  %7.4lf",i+1,roots[i]);
    }
};

int getDegree(string s)
{
    int i,len=s.length(),max=0;
    char c;
    string t="";
    int x_pos = s.find("x");
    if (x_pos>=0 && x_pos<len && (s.find("^")<0 || s.find("^")>=len))
        return 1;
    for (i=s.find("^")+1;i<len;i++)
    {
        c = s[i];
        if (c!=' ')
            t+=c;
        else
        {
            //cout<<"\nt = "<<t<<", i = "<<i<<endl;
            if(max<(int)(stof(t)))
                max = (int)(stof(t));
            t=(s.substr(i+1)); //cout<<"\nt = "<<t<<endl;
            if (t.find("^")<0 || t.find("^")>t.length())
                return max;
            i=t.find("^")+i+1;//cout<<"\ni = "<<i<<endl;
            t="";
        }
    }
    return max;
}

int getSign(vector<pair<int,char>> s)
{
    int i,k=0,len=s.size(); 
    char sign=s[0].second;
    //cout<<"\nlen = "<<len<<endl;
    //cout<<"\nsign = "<<sign<<endl;
    for(i=1;i<len;i++)
    {
        if (s[i].second != sign)
            k++;
        sign = s[i].second;
    }
    return k;
}

int main()
{
    string s;
    cout<<"\n\n_______TABULAR METHOD TO FIND +VE ROOTS OF A POLYNOMIAL FUNCTION_________\n\n";
    cout<<"Enter a polynomial function f(x):\n";
    getline(cin,s);
    cout<<"\n\nThe polynomial function f(x) = "<<s<<endl;
    int d = getDegree(s);
    cout<<"\nDegree of f(x) = "<<d<<endl;
    Function f(s);
    double y = f.getValue(0);
    int r_pos = getSign(f.signarr);
    cout<<"\nNumber of positive roots = "<<r_pos<<endl;
    cout<<"\nThe above number maybe less than "<<r_pos<<", but is always odd.\n";
    //x^4 -5x^3 -12x^2 +76x -79
    //x^2 -2.5x +1.5
    vector<pair<double,double>> boundary;
    FunctionRoot ob;
    ob.getPosRoots(f, r_pos, boundary);
    cout<<"\n\n-------SOLUTION--------\n";
    ob.displayRoots();
    cout<<"\n\n-----------------------\n\n";
    return 0;
}