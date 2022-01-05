//Author : Pratyay Sarkar
//Semester : 5
//Paper : Numerical Methods
//Program : Newton's Backward Interpolation

#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

class InputSet
{
    public:
    vector<pair<double,double>> list;
    vector<double> fwd;
    double h;
    double u;
    double xn;
    double temp;
    double y;

    InputSet()
    {
        h=0; temp=0; u=0; xn=0; y=0;
    }

    void set_u(double x)
    {
        xn = list.back().first;
        cout<<"\nxn = "<<xn<<endl<<"x = "<<x<<endl;
        u = (x-xn)/h;
    }
    
    void input(double x, double y)
    {
        list.push_back(make_pair(x,y));
        if (list.size()>1)
            h = x-temp;
        temp = x;
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
    }

    bool check_resolved(vector<double> t)
    {
        if(t.size()==1)
            return true; 
        double a = t[0];
        int i;
        for (i=1;i<t.size();i++)
            if (t[i]!=a)
                break;
        return (i==t.size());
    }

    int fact(int x)
    {
        if (x==0)
            return 1;
        else 
        return x*fact(x-1);
    }

    double get_ith_term(int i)
    {
        double uu=1,yy=fwd[i];
        int k=0;
        while(k<i)
        {
            uu=uu*(u+k);
            k++;
        }
        double result = uu*(yy/fact(i));
        return result;
    }

    void solve()
    {
        int i,k=0;
        vector<double> emptyvec; //empty vector
        vector<double> temp_list; //initially contains list of known f(x)
        vector<double> deltas; //list of Del f(x) in each iteration

        fwd.push_back(list.back().second);
        for (i=0;i<list.size();i++)
            temp_list.push_back(list[i].second);
        cout<<"\nf(x):\t\t"; display(temp_list); cout<<endl;

        re_iterate:
        for (i=1;i<temp_list.size();i++)
            deltas.push_back(temp_list[i] - temp_list[i-1]);
        
        k++; cout<<"\n/_\\"<<k<<"f(x):\t"; display(deltas); cout<<endl;
        fwd.push_back(deltas.back());
        if (!check_resolved(deltas))
        {
            temp_list = deltas;
            deltas = emptyvec;
            goto re_iterate;
        }
        
        //cout<<"\n\nNumber of backward differences taken = "<<k<<endl;
        cout<<"\n\nThe Delta Vector = ";
        display(fwd); cout<<endl;

        for (i=0;i<fwd.size();i++)
            y= y+get_ith_term(i);
    }
};

int main()
{
    cout<<"\n\n-----------Newton's Backward Interpolation for Equal Intervals--------\n\n";
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
    inp.set_u(x);
    cout<<"h = "<<inp.h<<endl;
    cout<<"u = "<<inp.u<<endl;

    inp.solve();
    cout<<"\n\n-----SOLUTION--------\n\nf("<<x<<") = "<<inp.y<<"\n\n---------------------\n";
    return 0;
}