//Author : Pratyay Sarkar
//Semester : 5
//Paper : Numerical Methods
//Program : Round-off a number (use Odd-Even rule)

//___Header Files___
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//___Function List___
void make_zeros_after(char*, int);
void shift_to_this_index_from_right(char*, int);

//Execution starts here
void main()
{
    //character pointer to implement a character array to store the input number
    char* n = (char *)calloc(1,sizeof(char));

    //___Input from user : the number___
    printf("\n\n____Application to Round-Off a number___\n");
    printf("\nEnter a number: ");
    gets(n);
    //____End of Input___

    //____Finding position of decimal point___
    int position_of_point = 0;
    for (int i=0;i<strlen(n);i++)
        if (n[i]=='.') 
        {
            position_of_point = i;
            break;
        }
    if (position_of_point==0) //a number with no decimal point has a point at its end by default
        position_of_point=strlen(n);
    printf("\n\nPosition of point is after digit number %d.\n",position_of_point);
    //___Decimal point found and displayed___

    //___Input from user : the rounding-off limit___
    printf("\nEnter q (place upto which rounding off is to be done.)\nEg: For nearest 1000s enter 3\n");
    printf("For 3 decimal places enter -3\nFor nearest integer, enter 0:\n\n");
    int q; //the rounding-off limit
    scanf("%d",&q);
    //____End of Input___

    //____Declaring few important flags and counters____
    int count9=0; //counts the number of 9s converted to zeroes during rounding-off
    bool trailing_zeros=false; //true if the rounded-off number requires trailing zeroes to be printed
    bool over_flow = false; //true if the rounded-off number needs a digit more than input number. 
                            //Eg: round(99) -> 100 when q=2
    bool float_rnd = true; //true if the rounding-off is on the right side of the decimal point
    bool point_crossover = false; //true if while rounding-off, digits on both side of the point are changed. 
                                  //Eg: round(23.993) -> 24.0 when q=-1
    //_____End of declaration_____
    
    //_____Setting those variables accordingly______
    if (q>0) //if the rounding-off is on the left side of the decimal point (eg: nearest hundreds -> q=2)
    {
        trailing_zeros = true; //trailing zeroes (on the left of decimal point) are retained
        float_rnd = false; //this is for obvious reasons, false
        q = position_of_point- q-1; //we start counting positional value from right to left (for digits left of point)
                                    //Eg: In 8367, 3 is in position 2, signifying 10^2th position (hundreds).
                                    //q=2 means nearest hundreds, so 8387 will be 8400
    }
    else if (q==0) //for nearest integer
    {
        //Note: We are essentially making the number to an integer by removing the point first,
        //and then removing the insignificant digits by the same rounding-off rules below.
        //Eg: 44.63 becomes 4463, then becomes 4500, and as trailing_zeroes is false by default, becomes 45.
        q = position_of_point-1;
        shift_to_this_index_from_right(n,q+1); //to remove the decimal point
    }
    else //if the rounding-off is on the right side of the decimal point (eg: 2 decimal places -> q=-2)
        q = position_of_point-q; //Note: q is negative, subtarction here is actually adding abs(q)
    //_____End of section______

    //_____ROUNDING-OFF BEGINS HERE____
    if (n[q+1]<'5' && n[q+1]>='0') //checking digit after q-th place to be >=0 and <5
    {   
        round_level: //rounding to level
            make_zeros_after(n,q); //make every digit after q-th place : zero
    }
    else if (n[q+1]>'5' && n[q+1]<='9') //checking digit after q-th place to be >5 and <=9
    {
        round_up: //rounding up
            make_zeros_after(n,q); //make every digit after q-th place : zero
            check9:
                if (n[q]=='9') //check if q-th place is 9
                {
                    count9++; //counter for 9s -> 0s incremented
                    n[q]='0'; //digit 9 made 0
                    q--; //'q' decremented
                    if (n[q]=='.') //if q-th place is now the position of point
                    {
                        q--; //decrement 'q' further
                        point_crossover = true; //this is for obvious reasons, true
                    }
                    goto check9; //check if q-th place is 9, again
                }
            if (q<0) //q is negative: the original number has been rounded to all zeroes, and need a leading '1'
                over_flow=true;
            else //q is positive: the digit in q-th place is NOT '9'
                n[q]=(char)(n[q]+1); //so, increment that digit
    }    
    else //the digit after q-th place is '5'
    {
        /**Note: Odd-Even rounding system have been used. 
        Odd q-th digit stimulates round_up and Even q-th digit stimulates round_level. 
        Eg: For 2 decimal places, 2.835 -> 2.84, whereas 2.865->2.86 */
        if (n[q]%2==0)
            goto round_level;
        else
            goto round_up;
    }
    //_____CALCULATIONS DONE____

    //_____Printing Rounded-off number____
    printf("\nRounded-off number : ");
    char* r; //to store rounded-off number
    if (!trailing_zeros && float_rnd) //if trailing_zeros=false and float_rnd=true
    {
        if (point_crossover) //if point_crossover is true
            q++; //increment 'q'
        q+=count9; //increment 'q' by number of times 9s are converted to zeroes
        r = strncpy(n,n,q); //copy only the part to be displayed. Eg: 42.3400 should be displayed as 42.34
        r[q+1]='\0'; //adding the null character to the end to signify end of character array
    }
    else if(trailing_zeros && !float_rnd) //if trailing_zeros=true and float_rnd=false
    {
        r = strncpy(n,n,position_of_point-1); //copy the part to the left of point only
        r[position_of_point]='\0'; //adding the null character to the end to signify end of character array
    }
    else
        r = n; //this will never execute (I guess). Still, I am keeping it just in case.
    
    if (over_flow) //if the original number has been rounded to all zeroes, print a leading '1'
        printf("1");
    printf("%s\n",r); //print the rounded-off number

}

//makes all characters after index 'x' : zero 
//except for '.' which remains unchanged 
void make_zeros_after(char* n, int x)
{
    for(int i=x+1;i<strlen(n);i++)
    {
        if (n[i]=='.')
            continue;
        n[i]='0';
    }
}

//makes all characters to the right of x shift one place to its left
void shift_to_this_index_from_right(char* n, int x)
{
    int i;
    for(i=x+1;i<strlen(n);i++)
        n[i-1]=n[i];
    n[i-1]='\0';
}

