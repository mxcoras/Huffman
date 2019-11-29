#include "../include/tree.h"
#include "../include/encode.h"

void Encode(std::string fileName, std::string wrtName)
{
    std::ifstream load; //文件流
    load.open(fileName, std::ios::in);
    if (!load.is_open())
    {
        std::cout << "Error opening file1, exiting..." << std::endl;
        system("PAUSE");
        exit(1);
    }
    char binary;                //一位字符
    std::map<char, int> chFreq; //每个字符和对应频率的map
    //按位读取字符，统计频率
    load >> std::noskipws;
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
    HuffmanTree EncodeTree(chFreq); //哈夫曼树
    std::ofstream write;            //文件流
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
    //将字符和相应频率信息写入文件
    while (iter != chFreq.end())
    {
        write << iter->first << " " << iter->second << " ";
        iter++;
        if (iter != chFreq.end())
        {
            write << "$ "; //分隔字符
        }
        else
        {
            write << "#@$ "; //结束标记
        }
    }
    std::string bitstr; //01串
    while (!load.eof())
    {
        load >> binary;
        if (load.eof())
            break;
        auto iter = EncodeTree.chCode.find(binary);
        bitstr += iter->second;
    }
    //最后8位字符的有效位数
    int lastValid = bitstr.size() % 8;
    write << lastValid << " ";
    //每8位01转成一个字符写入文件中
    while (bitstr.size() >= 8)
    {
        std::bitset<8> bits(bitstr, 0, 8);
        bitstr.erase(0, 8);
        write << static_cast<char>(bits.to_ulong());
    }
    //处理末位不够8位的情况，不够8位补0
    if (!bitstr.empty())
    {
        unsigned long loc = bitstr.size();
        std::bitset<8> endbits(bitstr, 0, loc);
        std::cout << static_cast<char>(endbits.to_ulong());
        write << static_cast<char>(endbits.to_ulong());
        //    write << static_cast<char>(loc);
    }
    write.close();
}