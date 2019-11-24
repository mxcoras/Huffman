#include "../include/tree.h"
#include "../include/encode.h"

void Encode(std::string fileName, std::string wrtName)
{
    std::ifstream load;
    load.open(fileName, std::ios::in);
    if (!load.is_open())
    {
        std::cout << "Error opening file1, exiting..." << std::endl;
        system("PAUSE");
        exit(1);
    }
    char binary;
    std::map<char, int> chFreq;
    while (!load.eof())
    {
        load >> binary;
        auto iter = chFreq.find(binary);
        if (iter != chFreq.end())
        {
            iter->second++;
        }
        else
        {
            chFreq.insert(std::map<char, int>::value_type(binary, 1));
        }
    }
    load.close();
    HuffmanTree EncodeTree(chFreq);
    std::ofstream write;
    write.open(wrtName);
    load.open(fileName);
    if (!write.is_open() || !load.is_open())
    {
        std::cout << "Error opening file2, exiting..." << std::endl;
        system("PAUSE");
        exit(1);
    }
    write << "comp$ ";
    auto iter = chFreq.begin();
    while (iter != chFreq.end())
    {
        write << iter->first << " " << iter->second << " ";
        iter++;
        if (iter != chFreq.end())
        {
            write << "$ ";
        }
        else
        {
            write << "#@$ ";
        }
    }
    write.close();
    write.open(wrtName,std::ios::app);
    while (!load.eof())
    {
        load >> binary;
        auto iter = EncodeTree.getChcode().find(binary);
        write << iter->second;
    }
}