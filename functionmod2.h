#include <iostream>
#include <string>
#include <cmath>
#include <utility>
#include <vector>
#include <algorithm>
#include "functionmod.h"
using namespace std;

string trim(string s)
{
    int i;
    for (i=0;i<s.length();i++)
        if(s[i]!=' ')
            break;
    s = s.substr(i);
    for (i=s.length()-1;i>=0;i--)
        if(s[i]!=' ')
            break;
    s = s.substr(0,i+1);
    return s;
}

string hasTrig(string s)
{
    const string list[] = {"sin", "cos", "tan", "cot", "sec", "cosec"};
    int i,len = s.length();
    for (i=0;i<6;i++)
    {
        int pos = s.find(list[i]);
        if (pos>=0 && pos<len)
            return list[i];
    }
    return "";
}

const string list[] = {"sin", "cos"};
const string dlist[] = {"cos", "-sin"};

string getTrigDiff(string s)
{
    string t = hasTrig(s);
    int pos_trig = s.find(t);
    int pos_x = s.find("x");
    char sign=s[0];
    if (sign!='-' && sign!='+')
        sign='+';

    string c;
    if (pos_trig==0)
        c="1";
    else
    {
        c = s.substr(1,pos_trig-1);
        if (c.length()==0)
            c="1";
    }

    string coeff;
    if (pos_trig==0)
        coeff="1";
    else
    {
        if (pos_x-pos_trig==3)
            coeff="1";
        else
            coeff = s.substr(pos_trig+3,pos_x-1);
    }

    if (sign=='+' && t[2]=='s')
        sign='-';
    else if (sign=='-' && t[2]=='s')
        sign='+';

    t = (t[2]=='s')?"sin":"cos"; //cout<<"\ncoeff="<<coeff<<"\nc="<<c<<"\nsign="<<sign<<endl;
    string res = (sign+to_string(stof(coeff)*stof(c))+t+coeff+"x");
    cout<<"\nres="<<res<<endl;
    return res;
}

string getDiffTerm(string s)
{
    if(hasTrig(s).length()!=0)
        return trim(getTrigDiff(s));

    int len = s.length();
    int pos_x = s.find("x");//cout<<"\npos_x = "<<pos_x<<endl;
    if (pos_x<0 || pos_x>=len)
        return "";
    
    string c;
    if (pos_x==0)
        c="1";
    else
    {
        c = s.substr(1,pos_x-1);
        if (c.length()==0)
            c="1";
    }

    string i;
    if (pos_x==len-1)
        i="1";
    else
        i = s.substr(pos_x+2);
    //cout<<"\nposx="<<pos_x<<"\tc="<<c<<"\ti="<<i<<endl;
    double coeff = stof(c);
    double index = stof(i);
    coeff = coeff*index;
    index--;
    string res;
    if(s[0]=='+' || s[0]=='-')
        res = s[0]+to_string(coeff)+"x^"+to_string(index);
    else
        res = to_string(coeff)+"x^"+to_string(index);
    return trim(res);
}

string getDiff(string f)
{
    string s;
    int len = f.length();
    //cout<<"\nfunc: "<<func<<"\tx = "<<x<<"\tlen: "<<len<<endl;
    f[len] = ' '; len++;
    int i; char c; 
    string t=""; double num=0;
    for (i=0;i<len;i++)
    {
        c = f[i];
        if (c!=' ')
            t+=c;
        else
        {
            string temp = getDiffTerm(t); 
            //cout<<"\nterm="<<temp<<"\nlen="<<temp.length()<<endl;
            
            if (temp.length()!=0)
                s+= temp;
            if (i!=len-1 && temp.length()!=0)
                s+=" ";
            t="";
        }
    }
    if (s.length()==0)
        return "0";
    return trim(s);
    //return s.substr(0,s.length()-2);
}

/*
int main()
{
    string s;
    cout<<"Enter a polynomial function f(x):\n";
    getline(cin,s);
    cout<<"\n\nThe polynomial function f(x) = "<<s<<endl;
    Function f(s);
    string diff = getDiff(f.func);
    //diff = diff.substr(0,diff.length()-2);
    cout<<"\nAfter differentiating,i.e. f'(x) = "<<diff<<endl;
    //cout<<"\nlen = "<<diff.length()<<endl;
    Function d(diff);
    cout<<"\nf(1) = "<<d.getValue(1)<<endl;
    return 0;
}*/