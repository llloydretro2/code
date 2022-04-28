#include "iostream"
#include "fstream"
#include "string"
#include "vector"
#include "stack"
#include "cstring"
using namespace std;

//vector<std::string> a;
//vector<vector<std::string>> a;
//if a.size() < 20 or not
//vector.push(), pop()
//pointer: mem on heap
//length:
//capacity:

int main(int argc, char **argv)
{

    if (argc < 2)
    {
        std::cout << "Too few command-line arguments." << std::endl;
        return 1;
    }
    if (argc > 2)
    {
        std::cout << "Too many command-line arguments." << std::endl;
        return 1;
    }

    ifstream ifile;
    ifile.open(argv[1]);
    if (!ifile)
    {
        std::cout << "Failed to open file: nonexistent_file." << std::endl;
        return 1;
    }

    int totalLine = 0;
    string content[50] ;
    string temp;
    unsigned maxStringLen = 0;
    while(getline(ifile, temp, '\n'))
    {
        content[totalLine+1] = temp;
        while (content[totalLine+1].length() < 20)
        {
            content[totalLine+1] += " ";
        }
        totalLine++;
        if (temp.length() > maxStringLen)
        {
            maxStringLen = temp.length();
        }
    }
    if (totalLine > 30)
    {
        std::cout << "File " << argv[1] << " has too many lines." << std::endl;
        return 2;
    }
    if (maxStringLen > 20)
    {
        std::cout << "File " << argv[1] << " has at least one too long line." << std::endl;
        return 2;
    }
//    content vector<std::string>

    vector<std::string> formatContent;
    stack<vector<std::string>> historyOp;
    stack<vector<std::string>> recoverOp;
    int rowNum = 1;
    int printEdge = 10;
    int lineNum = 1;
    bool saveStatus = false;
    string command = "";
    string previousCommand = "";
    while (command != "q")
    {

        //default printing method
        std::cout << "     ";
        for (int i = 1; i < lineNum; ++i) {
            std::cout << " ";
        }
        std::cout << "*" << std::endl;
        std::cout << "     12345678901234567890" << std::endl;
        for (int i = printEdge - 9; i <= printEdge; ++i) {
            if (i == rowNum)
            {
                std::cout << "*";
            }
            else
            {
                std::cout << " ";
            }

            if (i < 10)
            {
                if (i <= totalLine)
                {
                    std::cout << "  " << i << "|" << content[i] << std::endl;
                } else
                {
                    std::cout << "  " << i << std::endl;
                }
            }
            else
            {
                if (i <= totalLine)
                {
                    std::cout << " " << i << "|" << content[i] << std::endl;
                } else
                {
                    std::cout << " " << i << std::endl;
                }
            }


        }
        std::cout << "     12345678901234567890" << std::endl;
        std::cout << "Enter command: " << std::endl;
        //default printing method

        previousCommand = command;
        getline(cin, command);

        formatContent.clear();
        for (int i = 0; i < 31; ++i)
        {
            formatContent.push_back(content[i]);
        }

        if (command == "")
        {
            if (previousCommand != "")
            {
                command = previousCommand;
            }
            else
            {
                std::cout << "No previous command." << std::endl;
            }
        }

        if (strstr(command.c_str(), "save"))
        {
            string saveFile = command.substr(5, command.length()-4);
            ofstream outfile(saveFile, ios::trunc);
            for (int i = 1; i < totalLine+1; ++i) {
                outfile << content[i] << "\n";
            }
            outfile.close();
            saveStatus = true;
            continue;
        }

        if (command == "d")
        {
            if (lineNum < 20)
            {
                lineNum++;
            }
            continue;
        }
        if (command == "a")
        {
            if (lineNum > 1)
            {
                lineNum--;
            }
            continue;
        }
        if (command == "s")
        {
            if (rowNum < totalLine)
            {
                rowNum++;
                if (rowNum > printEdge)
                {
                    printEdge++;
                }
            }
            else
            {
                if (printEdge < (totalLine + 9))
                {
                    printEdge++;
                }
            }
            continue;
        }
        if (command == "w")
        {
            if (rowNum > 1)
            {
                rowNum--;
                if (printEdge > 10 && printEdge > (rowNum+9))
                {
                    printEdge--;
                }
            }
            continue;
        }

        if (command.at(0) == 'd')
        {
            int steps = std::stoi(command.substr(2, command.length()-2));
            for (int i = 0; i < steps; ++i) {
                if (lineNum < 20)
                {
                    lineNum++;
                }
            }
        }
        if (command.at(0) == 'a')
        {
            int steps = std::stoi(command.substr(2, command.length()-2));
            for (int i = 0; i < steps; ++i) {
                if (lineNum > 1)
                {
                    lineNum--;
                }
            }
        }
        if (command.at(0) == 's')
        {
            int steps = std::stoi(command.substr(2, command.length()-2));
            for (int i = 0; i < steps; ++i) {
                if (rowNum < totalLine)
                {
                    rowNum++;
                    if (rowNum > printEdge)
                    {
                        printEdge++;
                    }
                }
                else
                {
                    if (printEdge < (totalLine + 9))
                    {
                        printEdge++;
                    }
                }
                continue;
            }
        }
        if (command.at(0) == 'w')
        {
            int steps = std::stoi(command.substr(2, command.length()-2));
            for (int i = 0; i < steps; ++i) {
                if (rowNum > 1)
                {
                    rowNum--;
                    if (printEdge > 10 && printEdge > (rowNum+9))
                    {
                        printEdge--;
                    }
                }
                continue;
            }
        }

        if (strstr(command.c_str(), "i"))
        {
            historyOp.push(formatContent);
            int originalLineNum = lineNum;
            int originalRowNum = rowNum;
            string insertWord = command.substr(2, command.length()-2);
//            length = 20
            for (unsigned i = 0; i < insertWord.length(); ++i)
            {

                if (lineNum<= 20)
                {
                    content[rowNum][lineNum - 1] = insertWord[i];
                }
                else
                {
                    lineNum = 1;
                    rowNum ++;
                    totalLine = rowNum;
                    content[rowNum] = "                    ";
                    content[rowNum][lineNum-1] = insertWord[i];
                }
                lineNum++;
            }
            lineNum = originalLineNum;
            rowNum = originalRowNum;
        }

        if (command == "u")
        {
            if (historyOp.size() > 0)
            {
                formatContent.clear();
                for (int i = 0; i < 31; ++i)
                {
                    formatContent.push_back(content[i]);
                }
                recoverOp.push(formatContent);

                for (int i = 0; i < 31; ++i)
                {
                    content[i] = historyOp.top()[i];
                    continue;
                }
                historyOp.pop();
            }
            else
            {
                std::cout << "Cannot undo.\n" << std::endl;
            }
        }

        if (command == "r")
        {
            if (recoverOp.size() > 0 && (previousCommand == "u" || previousCommand == "r"))
            {
                formatContent.clear();
                for (int i = 0; i < 31; ++i)
                {
                    formatContent.push_back(content[i]);
                }
                historyOp.push(formatContent);
                for (int i = 0; i < 31; ++i)
                {
                    content[i] = recoverOp.top()[i];
                    continue;
                }
                recoverOp.pop();
            }
            else
            {
                std::cout << "Cannot redo.\n" << std::endl;
            }
        }


        if (command == "q")
        {
            if (historyOp.size() == 0)
            {
                continue;
            }
            string discardStatus = "";
            if (saveStatus == false)
            {
                std::cout << "You have unsaved changes.\n"
                             "Are you sure you want to quit (y or n)?" << std::endl;
                cin >> discardStatus;
                std::cout << std::endl;
                if (discardStatus == "y")
                {
                    continue;
                }
                else
                {
                    command = " ";
                }

            }
        }
    }

    std::cout << "Goodbye!" << std::endl;
    return 0;
}