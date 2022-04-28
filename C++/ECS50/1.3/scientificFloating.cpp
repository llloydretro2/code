#include "string"
#include "iostream"

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

std::string toBinary2sComplement(int decimalNum)
{
    bool sign = false;
    int base = 2;
    int inputNum;
    bool addStatus;
    if (decimalNum < 0)
    {
        sign = true;
        inputNum = -decimalNum;
    } else
    {
        inputNum = decimalNum;
    }

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

    if (sign)
    {
        for (unsigned i = 0; i < returnNum.size(); ++i) {

            if (returnNum[i] == '1') {
                returnNum[i] = '0';
            } else if (returnNum[i] == '0') {
                returnNum[i] = '1';
            }
        }

        addStatus = true;
        for (int i = returnNum.size()-1; i >= 0; --i) {
            if (addStatus)
            {
                if (returnNum[i] == '0')
                {
                    returnNum[i] = '1';
                    addStatus = false;
                }
                else if (returnNum[i] == '1')
                {
                    returnNum[i] = '0';
                }
            }
        }
        returnNum = "1" + returnNum;
    }

    return returnNum;
}



int main()
{
    float num;
    std::cout << "Please enter a float: ";
    std::cin >> num;

    unsigned int float_int = *((unsigned int*)&num);
    int sign = float_int >> 31;
    int exponent = (float_int << 1 >> 24) - 127;
    int matissa = float_int << 9 >> 9;

    std::string binary = toBinary2sComplement(matissa);

    if (binary.size() < 23)
    {
        unsigned size = binary.size();
        for (unsigned i = 0; i < (23-size); ++i) {
            binary = "0" + binary;
        }
    }

    int formatShift = 0;
    for (unsigned i = 0; i < binary.size(); ++i) {
        if (binary[i] == '1')
        {
            formatShift = i;
        }
    }
    std::string formatBinary = binary.substr(0, formatShift+1);
    if (sign == 1)
    {
        std::cout << "-";
    }
    if (num == 0)
    {
        std::cout << "0E0" << std::endl;
    } else
    {
        std::cout << "1." << formatBinary << "E" << exponent << std::endl;
    }

}