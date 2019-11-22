#ifndef __TREE_H__
#define __TREE_H__

#include "macro.h"

//哈夫曼树节点
struct HuffTreeNode
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
};

//哈夫曼树
class HuffmanTree
{
private:
    //哈夫曼树的根节点
    HuffTreeNode *root;

public:
    HuffmanTree(std::map<char, int> chFreq);
    ~HuffmanTree();
    //由map中各字符和其对应的频率生成哈夫曼树
    void Generate(std::map<char, int> chFreq);
    //删除哈夫曼树
    void Clear();
};

#endif //__TREE_H__