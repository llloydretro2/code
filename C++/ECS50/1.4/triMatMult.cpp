#include "string"
#include "iostream"
#include "stdlib.h"
#include "math.h"
#include "fstream"
#include "vector"
#include "algorithm"

void printResult(std::vector<int> matrix)
{
    for (unsigned i = 0; i < matrix.size(); ++i) {
        std::cout << matrix[i];
        if (i != matrix.size()-1)
        {
            std::cout << " ";
        }
        else
        {
            std::cout << std::endl;
        }
    }
}

void printMatrix(std::vector<int> matrix)
{
    for (unsigned i = 0; i < matrix.size(); ++i) {
        std::cout << matrix[i] << std::endl;
    }
}

std::vector<int> fileToMatrix(std::string fileName, int& size)
{
    std::ifstream file;
    std::vector<int> returnMatrix;
    file.open(fileName, std::ios::in);
    int value;
    if (file.is_open())
    {
        file >> value; // get the dimensions
        size = value;
        while(file >> value)
        {
            returnMatrix.push_back(value);
        }
    }
    file.close();

    return returnMatrix;
}

int calBackBlock(int num)
{
    int result = 0;

    for (int i = 0; i <= num; ++i) {
        result += i;
    }
    return result;
}

std::vector<int> matrixMult(std::vector<int> matrix1, std::vector<int> matrix2, int size)
{
    std::vector<int> resultMatrix;
    int temp;
    int index1;
    int index2;

    for (int i = 0; i < size; ++i) {

        for (int j = i; j < size; ++j) {
            temp = 0;
            for (int k = i; k <= j; ++k) {
                index1 = i * size + k - calBackBlock(i);
                index2 = k * size + j - calBackBlock(k);
//                std::cout << i << " " << j << " " << k << " -> " << index1 << " " << index2 <<std::endl;
                temp += matrix1[index1] * matrix2[index2];

            }
            resultMatrix.push_back(temp);
//            std::cout << std::endl;
        }

    }

    return resultMatrix;
}

int main(int argc, char* argv[])
{
    //Get file name from terminal
    std::string file1 = argv[1];
    std::string file2 = argv[2];

    int size = 0;

    //Read files
    std::vector<int> matrix1 = fileToMatrix(file1, size);
    std::vector<int> matrix2 = fileToMatrix(file2, size);

    std::vector<int> resultMatrix = matrixMult(matrix1, matrix2, size);
    printResult(resultMatrix);

}