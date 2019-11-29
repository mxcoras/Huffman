#include "../include/tree.h"
#include "../include/decode.h"

void Decode(std::string fileName, std::string wrtName)
{
    std::ifstream load;
    load.open(fileName);
    if (!load.is_open())
    {
        std::cout << "Error opening file1, exiting..." << std::endl;
        system("PAUSE");
        exit(1);
    }
    char binary;
    int freq;
    std::bitset<8> bits;
    std::string tmpstr, bitstr;
    std::map<char, int> chFreq;
    load >> tmpstr;
    if (tmpstr != "comp$")
    {
        std::cout << "Error format, exiting..." << std::endl;
        system("PAUSE");
        exit(1);
    }
    do
    {
        load >> binary;
        load >> freq;
        auto iter = chFreq.find(binary);
        chFreq.insert(std::map<char, int>::value_type(binary, freq));
        load >> tmpstr;
    } while (tmpstr != "#@$");
    int lastValid;
    load>>lastValid;
    load.read(&binary, 1);
    while (!load.eof()) //读取字符转化为01串
    {
        load.read(&binary, 1);
        bits = binary; //字符赋值给bitset<8>可直接转化为二进制
        bitstr += bits.to_string();
    }
    bitstr=bitstr.substr(0,bitstr.size()-8);
    load.close();
    HuffmanTree EncodeTree(chFreq);
    std::ofstream write;
    write.open(wrtName);
    if (!write.is_open())
    {
        std::cout << "Error opening file2, exiting..." << std::endl;
        system("PAUSE");
        exit(1);
    }
    HuffTreeNode *Node = EncodeTree.getRoot();
    std::string end = bitstr.substr(bitstr.size() - 8, 8); //处理末尾不够八位的情况
    std::bitset<8> loc(end);
    unsigned long add = loc.to_ulong();
    end = end.substr(8 - lastValid, lastValid);
    bitstr.erase(bitstr.size() - 8, bitstr.size());
    bitstr += end;
    for(auto i : bitstr)
    {
        if (i == '0')
            Node = Node->left;
        else if (i == '1')
            Node = Node->right;
        if (Node->left == nullptr && Node->right == nullptr)
        {
            write << Node->key;
            Node = EncodeTree.getRoot();
        }
    }
    write.close();
}