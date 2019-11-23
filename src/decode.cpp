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
    std::string tmpstr;
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
    while (!load.eof())
    {
        load >> binary;
        if (binary == '\000')
            Node = Node->left;
        else if (binary == '\001')
            Node = Node->right;
        if (Node->left == nullptr && Node->right == nullptr)
        {
            write << Node->key;
            Node = EncodeTree.getRoot();
        }
    }
}