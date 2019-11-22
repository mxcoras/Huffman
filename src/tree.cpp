#include"../include/tree.h"

bool cmpWeight(HuffTreeNode *data1,HuffTreeNode *data2)
{
    return data1 -> weight < data2 -> weight;
}

HuffmanTree::HuffmanTree(std::map<char,int> chFreq)
{
}

HuffmanTree::~HuffmanTree()
{
}

void HuffmanTree::Generate(std::map<char,int> chFreq){
    
}

void HuffmanTree::Clear(){
    
}