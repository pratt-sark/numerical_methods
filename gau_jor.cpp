//Author : Pratyay Sarkar
//Semester : 5
//Paper : Numerical Methods
//Program : Gauss Jordan Method

#include <iostream>
#include <iomanip>
using namespace std;

//_____Function List_____
void swap(double *a, double *b);

//Class Matrix represents a matrix with some member functions for:
//Addition, Subtraction, Multiplication, Division, Inverse and others.
class Matrix
{
    int row, col; //number of rows and columns of Matrix object
    double **elements; //the double pointer representing the Matrix

public:
    //Parameterized constructor for class Matrix
    Matrix(int x, int y) //allocates memory for elements and intializes data members
    {
        row = x;
        col = y;
        elements = new double *[row];
        int i;
        for (i = 0; i < row; i++)
            elements[i] = new double[col];
        zeroes();
    }

    //____Member Methods____

    //To accept Matrix elements
    void input(); 
    //To display Matrix elements
    void output();
    //To change all Matrix elements to zeroes
    void zeroes();
    //To change the Matrix into an identity matrix of appropriate order
    void identity();
    //To merge two matrices (of same order) side by side
    Matrix merge(Matrix);
    //To extract a matrix from another matrix
    void subMatrix(Matrix, int, int, int, int);
    //To find inverse of a matrix, if it exists
    Matrix inverse();
    //To change a row of matrix depending on some other row's elements
    void changeRow(int, int, double);
    //To add two matrices
    Matrix add(Matrix);
    //To subtract one matrix from another matrix
    Matrix subtract(Matrix);
    //To multiply one matrix with another matrix
    Matrix multiply(Matrix);

};

//Execution starts here
int main()
{
    //________INPUT STARTS_________
    int n; //order of coefficient matrix
    cout << "\nEnter order of COEFFICIENT MATRIX:\n";
    cin >> n; //order accepted from user

    Matrix aug(n, n + 1); //augmented matrix of order (n,n+1) declared
    cout << "\nThe augmented matrix will be of order (" << n << "*" << n + 1 << ").\n";
    cout << "\nEnter " << n * (n + 1) << " elements of the AUGMENTED MATRIX:\n";
    aug.input(); //elements of augmented matrix accepted from user
    //_________INPUT ENDS________

    //________DISPLAYING NECESSARY MATRICES AND VECTORS______
    Matrix coeff(n, n); //coefficient matrix declared of order (n,n)
    coeff.subMatrix(aug, 0, 0, n, n); //coefficient matrix extracted from augmented matrix
    cout << "\nThe Coefficient Matrix:\n";
    coeff.output(); //coefficient matrix displayed

    Matrix const_vect(n, 1); //constant vector declared of order (n,1)
    const_vect.subMatrix(aug, 0, n, n, n + 1); //constant vector extracted from augmented matrix
    cout << "\nThe Constant Vector:\n";
    const_vect.output(); //constant vector displayed
    cout << "\nThe Augmented Matrix:\n";
    aug.output(); //augmented matrix displayed
    //______END OF SECTION________

    //________APPLYING GAUSS JORDAN METHOD___________
    cout << "\nApplying Gauss-Jordan Method to evaluate roots.....\n";
    Matrix inv = coeff.inverse(); //calculating inverse of coefficient matrix
    cout << "Done.\n"; //this line only executes after successful determination of inverse
    Matrix result = inv.multiply(const_vect); //multiplying inverse with constant vector
    cout << "\n\n---SOLUTION----:\n";
    result.output(); //displaying solution
    return 0;
}

//To accept Matrix elements
void Matrix :: input()
{
    int i, j;
    for (i = 0; i < row; i++)
        for (j = 0; j < col; j++)
            cin >> elements[i][j];
}

//To display Matrix elements
void Matrix :: output()
{
    int i, j;
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
            printf("%7.3lf\t", elements[i][j]);
        //cout<<elements[i][j]<<"\t";
        cout << endl;
    }
}

//To change all Matrix elements to zeroes
void Matrix :: zeroes()
{
    int i, j;
    for (i = 0; i < row; i++)
        for (j = 0; j < col; j++)
            elements[i][j] = 0;
}

//To change the Matrix into an identity matrix of appropriate order
void Matrix :: identity()
{
    if (row!=col)
    {
        cout << "\nMatrix cannot be converted to an Identity Matrix.\n";
        exit(0);
    }

    zeroes();
    int i;
    for (i = 0; i < row; i++)
        elements[i][i] = 1;
}

//To merge two matrices (of same order) side by side
Matrix Matrix :: merge(Matrix b)
{
    if (row!=b.row || col!=b.col)
    {
        cout << "\nMatrices cannot be merged.\n";
        exit(0);
    }

    Matrix c(row, col * 2);
    int i, j;
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
            c.elements[i][j] = elements[i][j];
        for (j = col; j < col * 2; j++)
            c.elements[i][j] = b.elements[i][j - col];
    }
    return c;
}

//To extract a matrix from another matrix
void Matrix :: subMatrix(Matrix b, int x1, int y1, int x, int y)
{
    int i, j, rj = 0, cj = 0;
    for (i = x1; i < x; i++)
    {
        for (j = y1; j < y; j++)
        {
            elements[rj][cj] = b.elements[i][j];
            cj++;
        }
        rj++;
        cj = 0;
    }
}

//To find inverse of a Matrix
Matrix Matrix :: inverse()
{
    Matrix I(row, col); //declare an identity matrix of same order
    I.identity(); //define it

    Matrix A = this->merge(I); //matrix formed by merging current matrix and I (same order)
    cout << "\nThe Merged Matrix:\n";
    A.output();

    int i, j, index;
    for (i = 0; i < row; i++)
    {
        //_______CHECK FOR DIAGONAL ELEMENT_______
        index = i;
        //finding the index which has non zero value (pivot element)
        while (index < row && A.elements[index][i] == 0)
            index++;
        if (index == row) //if there is no non zero element
        {
            cout << "\nNo inverse exists.\n";
            exit(0);
        }
        if (index != i)
        {
            //loop for swapping the diagonal element row and index row
            for (j = 0; j <= A.col; j++)
                swap(&A.elements[index][j], &A.elements[i][j]);
        }
        //______NOW DIAGONAL ELEMENT IS NON-ZERO___________

        //_______CHANGING THE ROWS NOW_________
        double piv = A.elements[i][i]; //pivot element
        for (j = i; j <= A.col; j++) //dividing the current row elements by pivot
            A.elements[i][j] = (A.elements[i][j] / piv);
        
        for (j = 0; j < row; j++) //changing rows above and below pivot element appropriately
        {
            if (j == i) //no need to change current row
                continue;
            //change other rows as-> R(j) = R(j) - A(j,i)*R(i)
                A.changeRow(j, i, A.elements[j][i]);
        }
        //_______ROWS CHANGED_______

        cout << "\nAfter row " << i << "\n";
        A.output();
    }
    //cout<<"\nCheck:\n";
    //A.output();
    Matrix inv(row, col);
    inv.subMatrix(A, 0, col, row, 2 * col);
    //inv.output();
    return inv;
}

//To change a row of matrix depending on some other row's elements
void Matrix :: changeRow(int a, int b, double x)
{
    int j;
    for (j = 0; j < col; j++)
        elements[a][j] = elements[a][j] - (x * elements[b][j]);
}

//To multiply two matrices
Matrix Matrix :: multiply(Matrix b)
{
    Matrix c(row, b.col);
    int i, j, k;
    for (i = 0; i < row; i++)
        for (j = 0; j < b.col; j++)
            for (k = 0; k < col; k++)
                c.elements[i][j] = c.elements[i][j] + (elements[i][k] * b.elements[k][j]);
    return c;
}

//To add two matrices
Matrix Matrix :: add(Matrix b)
{
    Matrix c(row, col);
    int i, j;
    for (i = 0; i < row; i++)
        for (j = 0; j < col; j++)
            c.elements[i][j] = c.elements[i][j] + (elements[i][j] + b.elements[i][j]);
    return c;
}

//To subtract two matrices
Matrix Matrix :: subtract(Matrix b)
{
    Matrix c(row, col);
    int i, j;
    for (i = 0; i < row; i++)
        for (j = 0; j < col; j++)
            c.elements[i][j] = c.elements[i][j] + (elements[i][j] - b.elements[i][j]);
    return c;
}

//To swap two numbers
void swap(double *a, double *b)
{
    double t = *a;
    *a = *b;
    *b = t;
}