//Author : Pratyay Sarkar
//Semester : 5
//Paper : Numerical Methods
//Program : Lagrange's Method of Numerical Differentiation

//___Header Files___
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

//Class to represent the input set of values
class InputSet
{
    public:
    //vector of (x,y) pairs
    vector<pair<double,double> > list;
    double w; //w in lagrange's method
    double wd; //w' in lagrange's method (unused var)
    double y; //result of f'(x)

    InputSet() //default constructor to initialize values
    {
        w=1; wd=1; y=0;
    }

    //push an (x,y) pair in the vector
    void input(double x, double y)
    {
        list.push_back(make_pair(x,y));
    }

    //print the (x,y) pairs
    void output()
    {
        for (int i=0;i<list.size();i++)
            cout<<list[i].first<<"\t"<<list[i].second<<endl;
    }

    //to display a vector of double values (unused func)
    void display(vector<double> t)
    {
        for (int i=0;i<t.size();i++)
            cout<<t[i]<<"\t";
        cout<<endl;
    }

    //to get the k-th value of w'(x) term
    double get_ith_wd(double x, int k)
    {
        int i; double d=1;
        for (i=0;i<list.size();i++)
        {
            if (i!=k)
                d=d*(x-list[i].first);
        }
        //For debugging
        //cout<<"\nx = "<<x<<", k = "<<k<<", d = "<<d<<endl;
        return d;
    }

    //returns the value of w'(x)
    double get_wd(double x)
    {
        int i;
        double s=0;
        for (i=0;i<list.size();i++)
            s+=get_ith_wd(x,i);
        return s;
    }

    //finds and sets the value of w(x)
    void set_w(double x)
    {
        int i;
        for (i=0;i<list.size();i++)
            w=w*(x-list[i].first);
    }

    //returns -1 if x is not a tabular point
    //otherwise returns the index of x in vector
    int isTabularPoint(double x)
    {
        int i;
        for (i=0;i<list.size();i++)
            if (x==list[i].first)
                break;
        return (i==list.size())?-1:i;
    }

    //finds f'(x) for non-tabular points
    void solve(double x,int n)
    {
        wd = get_wd(x); 
        cout<<"\n\nw'(x) = "<<wd<<endl;
        double t1=0,t2=0;
        int i;
        for (i=0;i<list.size();i++)
        {
            double xi = list[i].first;
            double yi = list[i].second;
            double wdi = get_wd(xi);
            t1+=( yi/((x-xi)*wdi) );
            t2+=( yi/((x-xi)*(x-xi)*wdi) );
        }
        y = wd*t1 - w*t2; //final result of f'(x)
    }

    //finds f'(x) for tabular points
    void solve_tab(double x,int n,int r)
    {
        wd = get_wd(x);
        cout<<"\n\nw'(x) = "<<wd<<endl;
        double t1=0,t2=0;
        int i;
        for (i=0;i<list.size();i++)
        {
            if (i==r)
                continue;
            double xi = list[i].first;
            double yi = list[i].second;
            double wdi = get_wd(xi);
            t1+=( yi/((x-xi)*wdi) );
            t2+=( 1/(x-xi) );
        }
        y = wd*t1 + (list[r].second)*t2; //final result of f'(x)
    }
};

//Execution begins here
int main()
{
    cout<<"\n\n-----------Lagrange's Interpolation-----------\n\n";
    cout<<"How many (x,f(x)) pairs are known?\n";
    int n; cin>>n;
    InputSet inp;
    int i; double x,y;
    cout<<"\nEnter the (x,f(x)) pairs:\n";
    for (i=0;i<n;i++)
    {
        cin>>x>>y;
        inp.input(x,y);
    } 
    cout<<"\n\nThe input looks like this:\n";
    cout<<"----------------\nx\tf(x)\n----------------\n";
    inp.output();
    cout<<"----------------\n\n";

    cout<<"\n\nEnter the value of x:\n";
    cin>>x;
    inp.set_w(x);
    cout<<"\nw = "<<inp.w<<endl;
    
    int r = inp.isTabularPoint(x);
    if (r>=0)
        inp.solve_tab(x,n,r);
    else
        inp.solve(x,n);
    cout<<"\n\n-----SOLUTION--------\n\nf'("<<x<<") = "<<inp.y<<"\n\n---------------------\n";
    return 0;
}