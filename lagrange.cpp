//Author : Pratyay Sarkar
//Semester : 5
//Paper : Numerical Methods
//Program : Lagrange's Interpolation

#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

class InputSet
{
    public:
    vector<pair<double,double>> list;
    vector<double> Dr;
    double w,y;

    InputSet()
    {
        w=1; y=0;
    }

    void input(double x, double y)
    {
        list.push_back(make_pair(x,y));
    }

    void output()
    {
        for (int i=0;i<list.size();i++)
            cout<<list[i].first<<"\t"<<list[i].second<<endl;
    }

    void display(vector<double> t)
    {
        for (int i=0;i<t.size();i++)
            cout<<t[i]<<"\t";
        cout<<endl;
    }

    void set_w(double x)
    {
        int i;
        for (i=0;i<list.size();i++)
            w=w*(x-list[i].first);
    }

    void set_Dr(double x)
    {
        int i,j;
        double temp=1;
        for (i=0;i<list.size();i++)
        {
            for (j=0;j<list.size();j++)
            {
                if (i==j)
                    temp=temp*(x-list[i].first);
                else
                    temp=temp*(list[i].first-list[j].first);
            }
            Dr.push_back(temp);
            temp=1;
        }
    }

    void solve(double x,int n)
    {
        set_Dr(x);
        int i; double temp;
        for (i=0;i<list.size();i++)
        {
            temp = Dr[i];
            y=y+(list[i].second/temp);
        } 
        cout<<"r=0 to "<<n-1<<" [Sum(Yr/Dr)] = "<<y<<endl;  
        y=y*w;
    }
};

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

    inp.solve(x,n);
    cout<<"\n\n-----SOLUTION--------\n\nf("<<x<<") = "<<inp.y<<"\n\n---------------------\n";
    return 0;
}