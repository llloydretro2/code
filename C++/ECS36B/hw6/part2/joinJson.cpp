#include <json/json.h>
#include <json/reader.h>
#include <json/writer.h>
#include <json/value.h>
#include <string>

#include <iostream>
#include <stdio.h>

#include <time.h>
using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        return -1;
    }
    
    FILE *f1 = fopen(argv[0], "r");
    if (f1 == NULL)
    {
        return -1;
    }

    FILE *f2 = fopen(argv[1], "r");
    if (f2 == NULL)
    {
        return -1;
    }
    
    long lSize1;
    long lSize2;
    size_t lResult1;
    size_t lResult2;
    
    fseek(f1, 0, SEEK_END);
    lSize1 = ftell(f1);
    char *f1_ptr = (char *) malloc(sizeof(char)*lSize1);
    lResult1 = fread(f1_ptr, 1, lSize1, f1);
    if (lSize1 != lResult1)
    {
        fputs("Reading error to json 1", stderr);
        exit(-3);
    }
    
    fseek(f2, 0, SEEK_END);
    lSize2 = ftell(f2);
    char *f2_ptr = (char *) malloc(sizeof(char)*lSize2);
    lResult2 = fread(f2_ptr, 1, lSize2, f2);
    if (lSize2 != lResult2)
    {
        fputs("Reading error to json 2", stderr);
        exit(-3);
    }

    Json::Value myv_message;
    Json::CharReaderBuilder builder;
    Json::CharReader* reader = builder.newCharReader();
    std::string errors;

    try
    {
        bool parsingSuccessful = reader->parse(f1_ptr, f1_ptr+lSize1, &myv_message, &errors);
        parsingSuccessful = reader->parse(f2_ptr, f2_ptr+lSize2, &myv_message, &errors);
        delete reader;

        if(!parsingSuccessful)
        {
            std::cout << "Failed to parse the content JSON, errors:" << std::endl;
            std::cout << errors << std::endl;
        }
    }
    catch(...)
    {
        std::cout << "here\n";
    }

    std::cout << myv_message.toStyledString() << std::endl;
    return 0;
    
}