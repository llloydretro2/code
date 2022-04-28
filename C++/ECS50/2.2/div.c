#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    //Get two dividend and divisor
    unsigned dividend = atoi(argv[1]);
    unsigned printDivisor = atoi(argv[2]);
    unsigned divisor = printDivisor;

    //Set @remainder to be dividend at beginning
    unsigned remainder = dividend;
    //Set @quotient to be 0 at beginning
    unsigned quotient = 0;
    //Variable @count is used for loop
    unsigned count = 1;

    //Bitshifting @divisor to be the biggest possible number less than d@ividend
    for (unsigned i = 0; i < 32; i++)
    {
        //If @divisor less than @dividend
        if (divisor < dividend)
        {
            //left shift @divisor one position
            divisor = divisor << 1;
            //increase @count by 1
            count++;
        }
        
        //If divisor greater then dividend
        if (divisor > dividend)
        {
            //Right shift @divisor one position
            divisor = divisor >> 1;
            //Decrease @count by 1
            count--;
        }
    }

    //Subtracting @divisor from @dividend, get @remainder
    for (unsigned i = 0; i < count; i++)
    {
        //Subtract if @remainder greater than @divisor
        if (remainder >= divisor)
        {
            remainder = remainder - divisor;
            //Update @quotient at the position to 1
            quotient = (quotient << 1) | 0b1;
            //Right shift @divisor
            divisor = divisor >> 1;
        }
        //Update @quotient and @divisor otherwise
        else
        {
            //Update @quotient at the position to 0
            quotient = quotient << 1;
            //Right shift @divisor
            divisor = divisor >> 1;
        }
    }

    //Print
    printf("%d / %d = %d R %d", dividend, printDivisor, quotient, remainder);
    
    return 0;
}