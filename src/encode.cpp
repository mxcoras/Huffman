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
        if (load.eof())
            break;
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
    write.open(wrtName, std::ios::binary);
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
    std::string bitstr;
    while (!load.eof())
    {
        load >> binary;
        if (load.eof())
            break;
        auto iter = EncodeTree.chCode.find(binary);
        bitstr += iter->second;
    }
    while (bitstr.size() >= 8)
    {
        std::bitset<8> bits(bitstr, 0, 8);
        bitstr.erase(0, 8);
        write << static_cast<char>(bits.to_ulong());
    }
    if (!bitstr.empty())
    {
        unsigned long loc = bitstr.size();
        std::bitset<8> endbits(bitstr,0,loc);
        write << static_cast<char>(endbits.to_ulong());
        write << static_cast<char>(loc);
    }
    write.close();
}