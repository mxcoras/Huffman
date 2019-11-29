#include "../include/tree.h"
#include "../include/decode.h"

void Decode(std::string fileName, std::string wrtName)
{
    std::ifstream load; //文件流
    load.open(fileName, std::ios::binary);
    if (!load.is_open())
    {
        std::cout << "Error opening file1, exiting..." << std::endl;
        system("PAUSE");
        exit(1);
    }
    char binary;                //一位字符
    int freq;                   //一位字符的频率
    std::bitset<8> bits;        //利用bitset将字符转换为01串
    std::string tmpstr, bitstr; //bitstr:01串
    std::map<char, int> chFreq; //每个字符和对应频率的map
    load >> tmpstr;
    //如果文件头不为comp$，则说明文件格式不支持
    if (tmpstr != "comp$")
    {
        std::cout << "Error format, exiting..." << std::endl;
        system("PAUSE");
        exit(1);
    }
    load >> std::noskipws; //不忽略空格
    //按位读取字符
    do
    {
        load >> std::noskipws;
        load >> binary;
        load >> binary;
        load >> std::skipws; //忽略空格
        load >> freq;
        auto iter = chFreq.find(binary);
        chFreq.insert(std::map<char, int>::value_type(binary, freq));
        load >> tmpstr;
    } while (tmpstr != "#@$");
    int lastValid; //最后8位字符的有效位数
    load >> lastValid;
    load.read(&binary, 1); //读取一位写入时留下的空格
    //读取字符转换为01串
    while (!load.eof())
    {
        load.read(&binary, 1);
        bits = binary; //字符赋值给bitset<8>可直接转化为二进制
        bitstr += bits.to_string();
    }
    bitstr = bitstr.substr(0, bitstr.size() - 8); //删除最后一位换行符
    load.close();
    HuffmanTree EncodeTree(chFreq); //建树
    std::ofstream write;            //文件流
    write.open(wrtName);
    if (!write.is_open())
    {
        std::cout << "Error opening file2, exiting..." << std::endl;
        system("PAUSE");
        exit(1);
    }
    HuffTreeNode *Node = EncodeTree.getRoot();
    //处理末尾不够八位的情况
    if (lastValid != 0)
    {
        std::string endstr = bitstr.substr(bitstr.size() - 8, 8);
        //std::bitset<8> pos(endstr);
        //unsigned long add = pos.to_ulong();
        endstr = endstr.substr(8 - lastValid, lastValid); //删去无效位
        bitstr.erase(bitstr.size() - 8, bitstr.size());
        bitstr += endstr;
    }
    //遍历01串，通过哈夫曼树译出原文件
    for (auto i : bitstr)
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