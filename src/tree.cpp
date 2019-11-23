#include "../include/tree.h"

//作为sort函数的参数排序节点列表
bool cmpWeight(HuffTreeNode *data1, HuffTreeNode *data2)
{
    return data1->weight < data2->weight;
}

HuffmanTree::HuffmanTree(std::map<char, int> chFreq)
{
    Generate(chFreq);
}

HuffmanTree::~HuffmanTree()
{
}

void HuffmanTree::Generate(std::map<char, int> &chFreq)
{
    std::vector<HuffTreeNode *> vecNode;//将待建树的节点存入vector容器中
    for (auto iter : chFreq)
    {
        vecNode.push_back(new HuffTreeNode(iter.first, iter.second));
    }
    /*进行排序并用权值最小的两个节点建立新树，
    *新建的树的权值等于这两个节点之和，
    * 最后将该树的的根节点装回vector容器中
    * 重复该步骤直至容器中剩下一个节点
    * 该节点即为哈夫曼树的根节点*/
    while(vecNode.size()!=1){
        std::sort(vecNode.begin(),vecNode.end(),cmpWeight);
        auto tmp=new HuffTreeNode(vecNode[0]->weight+vecNode[1]->weight);
        auto leftChild=new HuffTreeNode(vecNode[0]->weight);
        auto rightChild=new HuffTreeNode(vecNode[1]->weight);
        tmp->left=leftChild;
        tmp->right=rightChild;
        vecNode.erase(vecNode.begin(),vecNode.begin()+2);
        vecNode.push_back(tmp);
    }
    this->root=vecNode[0];
}

void HuffmanTree::Clear()
{
}

std::map<char, std::string> HuffmanTree::CharSet()
{
    std::map<char, std::string> chCode;
    std::string tmp;//暂存的编码
    PreOrder(root, chCode, tmp, true);
    return chCode;
}

void HuffmanTree::PreOrder(HuffTreeNode *Node, std::map<char, std::string> &chCode, std::string &tmp, bool isLeft)
{
    if (Node == nullptr)
        return;
    //若为左节点，编码加0，右节点加1
    if (isLeft)
        tmp += '0';
    else
        tmp += '1';
    //若为叶子节点，将该字符及其编码以pair形式插入map中，并删除一位编码
    if (Node->left == nullptr && Node->right == nullptr)
    {
        chCode.insert(std::pair<char, std::string>(Node->key, tmp));
        tmp.pop_back();
    }
    PreOrder(Node->left, chCode, tmp, true);
    PreOrder(Node->right, chCode, tmp, false);
}