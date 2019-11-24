#ifndef __TREE_H__
#define __TREE_H__

#include "macro.h"

//哈夫曼树节点
typedef struct HuffTreeNode
{
    //叶子节点构造函数
    HuffTreeNode(char k, int w) : key(k), weight(w),
                                  left(nullptr),
                                  right(nullptr)
    {
    }
    //非叶子节点构造函数
    HuffTreeNode(int w) : key('\0'), weight(w),
                          left(nullptr),
                          right(nullptr)
    {
    }
    char key;            //该节点的字符
    int weight;          //该节点的权值
    HuffTreeNode *left;  //左节点
    HuffTreeNode *right; //右节点
} HuffTreeNode;

//哈夫曼树
class HuffmanTree
{
private:
    //哈夫曼树的根节点
    HuffTreeNode *root;
    std::map<char, std::string> chCode;

public:
    //哈夫曼树的构造函数
    HuffmanTree(std::map<char, int> chFreq);
    //哈夫曼树的析构函数
    ~HuffmanTree();
    //返回字符集
    std::map<char, std::string> getChcode();
    //返回根节点
    HuffTreeNode *getRoot();
    //由map中各字符和其对应的频率生成哈夫曼树
    void Generate(std::map<char, int> &chFreq);
    //删除哈夫曼树
    void Clear();
    //通过先序遍历，生成哈夫曼编码字符集
    void CharSet();
    //哈夫曼树的先序遍历
    void PreOrder(HuffTreeNode *Node, std::string &tmp, bool isLeft);
};

#endif //__TREE_H__