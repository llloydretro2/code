#include "string"
#include "iostream"
#include "stdlib.h"

int getVal(char c)
{
    if ((c >= '0') && (c <= '9')){
        return int(c) - '0';
    }
    else
    {
        return int(c - 'A') + 10;
    }
}

char getBaseVal(int num)
{
    if ((num >= 0) && (num <= 9)){
        return char(num + '0');
    }
    else
    {
        return char(num - 10 + 'A');
    }
}

int toDec(std::string number, int base)
{
    int length = number.size();
    int power = 1;
    int newNum = 0;

    for (int i = 1; i < length+1; ++i) {
        newNum += getVal(number[length-i]) * power;
        power = base * power;
    }

    return newNum;
}

std::string toNewBase(int decimalNum, int base)
{
    int inputNum = decimalNum;
    std::string newNum = "";
    std::string returnNum = "";

    while(inputNum  > 0)
    {
        newNum += getBaseVal(inputNum % base);
        inputNum /= base;
    }

    int length = newNum.size();
    for (int i = 1; i < length+1; ++i) {
        returnNum += newNum[length-i];
    }

    return returnNum;

}

int main()
{
    //Variable
    int originalBase;
    std::string number;
    int newBase;
    int decNum;
    std::string returnNum;
    

    //Get input from user
    std::cout << "Please enter the number's base: ";
    std::cin >> originalBase;
    std::cout << "Please enter the number: ";
    std::cin >> number;
    std::cout << "Please enter the new base: ";
    std::cin >> newBase;

    decNum = toDec(number, originalBase);
    returnNum = toNewBase(decNum, newBase);

    std::cout << number << " base " << originalBase << " is " << returnNum << " base " << newBase;
}