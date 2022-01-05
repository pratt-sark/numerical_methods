#include <iostream>
#include <iomanip>
using namespace std;

class Matrix
{
    public:
    int row,col;
    double **elements;
    Matrix(int x,int y)
    {
        row=x; col=y;
        elements = new double*[row];
        int i;
        for (i=0;i<row;i++)
            elements[i] = new double[col];
        zeroes();
    }
    void input()
    {
        int i,j;
        for (i=0;i<row;i++)
            for (j=0;j<col;j++)
                cin>>elements[i][j];
    }
    void output()
    {
        int i,j;
        for (i=0;i<row;i++)
        {
            for (j=0;j<col;j++)
                printf("%7.3lf\t",elements[i][j]);
                //cout<<elements[i][j]<<"\t";
            cout<<endl;
        }
    }
    void zeroes()
    {
        int i,j;
        for (i=0;i<row;i++)
            for (j=0;j<col;j++)
                elements[i][j]=0;
    }
    void identity()
    {
        zeroes();
        int i;
        for (i=0;i<row;i++)
            elements[i][i]=1;
    }

    void initAll(double k)
    {
        int i,j;
        for (i=0;i<row;i++)
            for (j=0;j<col;j++)
                elements[i][j]=k;
    }

    void subMatrix(Matrix b, int x1, int y1, int x, int y)
    {
        int i,j,rj=0,cj=0;
        for(i=x1;i<x;i++)
        {
            for (j=y1;j<y;j++)
            {
                elements[rj][cj]=b.elements[i][j];
                cj++;
            }
            rj++;cj=0;
        }
    }

    //LU Decomposition using Crout's Method
    void factorize(Matrix l, Matrix u)
    {
        int i,j,k;
        for (i = 0; i < col; i++) 
        {
            //Finding i-th column of L
            for (j = 0; j < row; j++) 
            {
                if (j < i)
                    l.elements[j][i] = 0;
                else 
                {
                    l.elements[j][i] = elements[j][i];
                    for (k = 0; k < i; k++)
                        l.elements[j][i] = l.elements[j][i] - l.elements[j][k] * u.elements[k][i];
                }
            }

            //Finding i-th row of U
            for (j = 0; j < col; j++) 
            {
                if (j < i)
                    u.elements[i][j] = 0;
                else if (j == i)
                    u.elements[i][j] = 1;
                else 
                {
                    u.elements[i][j] = elements[i][j] / l.elements[i][i];
                    for (k = 0; k < i; k++)
                        u.elements[i][j] = u.elements[i][j] - ((l.elements[i][k] * u.elements[k][j]) / l.elements[i][i]);
                }
            }

            //printing the iterations
            cout<<"\nAfter iteration "<<i<<":"<<endl;
            cout<<"\nL -->\n";
            l.output();
            cout<<"\nU -->\n";
            u.output();
        }
    }
    
    Matrix multiply(Matrix b)
    {
        Matrix c(row,b.col);
        int i,j,k;
	    for (i=0;i<row;i++)
		    for (j=0;j<b.col;j++)
			    for (k=0;k<col;k++)
			        c.elements[i][j] = c.elements[i][j] + (elements[i][k]*b.elements[k][j]);
        return c;
    }
    
    Matrix add(Matrix b)
    {
        Matrix c(row,col);
        int i,j;
	    for (i=0;i<row;i++)
		    for (j=0;j<col;j++)
			    c.elements[i][j] = c.elements[i][j] + (elements[i][j]+b.elements[i][j]);
        return c;
    }

    Matrix subtract(Matrix b)
    {
        Matrix c(row,col);
        int i,j;
	    for (i=0;i<row;i++)
		    for (j=0;j<col;j++)
			    c.elements[i][j] = c.elements[i][j] + (elements[i][j]-b.elements[i][j]);
        return c;
    }
};