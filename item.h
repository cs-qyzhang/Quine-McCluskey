// ==============================
// item.h
// 与项类定义
// ==============================

#ifndef QUINE_MCCLUSKEY_ITEM_H
#define QUINE_MCCLUSKEY_ITEM_H

#include <vector>
#include <string>

class Item
{
private:
    int variableQuantity;               //变量个数
    bool isUsed;                        //在列表化简法里判断该与项是否用过
    std::vector<int> variableContain;   //所有变量在该与项中的包含情况，-1表示不确定(未初始化)，0表示为反变量，1表示为原变量，2表示都含有
    std::vector<int> minItemContain;    //该与项包含的最小项

    void updateVariableContain();       //根据最小项更新变量包含情况
    void updateMinItemContain();        //根据变量更新最小项包含情况

public:
    explicit Item();                            //默认构造函数，将isUsed设置为0
    Item(int variablePara);                     //根据变量个数构造与项
    Item(int minItem, int variableQuantity);    //根据一个最小项和变量个数构造一个最小项的与项
    Item(std::vector<int> variableContain);     //根据变量包含情况构造与项
    ~Item() = default;                          //默认析构函数
    Item & operator=(const Item &);             //赋值运算符
    bool operator==(const Item &) const;        //等于运算符
    void clear();                               //清空与项

    int get_variableQuantity() const;               //返回variableQuantity的值
    bool get_isUsed() const;                        //返回isUsed的值
    std::vector<int> get_variableContain() const;   //返回variableContain的一个拷贝
    std::vector<int> get_minItemContain() const;    //返回minItemContain的一个拷贝
    int get_variableContain(int pos) const;         //返回第pos个变量的包含情况(pos从0开始)
    bool isMinItemContained(int minItem) const;     //返回与项中是否包含有minItem这一最小项

    void set_variableQuantity(int);                     //设置variableQuantity成员
    void set_isUsed(bool);                              //设置isUsed成员
    void set_variableContain(const std::vector<int> &); //设置variableContain成员
    void set_minItemContain(const std::vector<int> &);  //设置minItemContain成员
    void set_variableContian(int pos, int para);        //将variableContain中的第pos个变量的含情况改为para
    void push_back_minItem(int minItem);                //在该与项中增加一个最小项
    void removeMinItem(int);                            //在该与项中去掉一个最小项

    int numOfPositiveVariables() const;                 //计算并返回与项中含有的原变量个数
    int numOfNegativeVariables() const;                 //计算并返回与项中含有的反变量个数
    static bool combine(Item &a, Item &b, Item &result);//将与项a和与项b进行或运算，得到与项result
    std::string toString() const;                       //计算并返回该与项的表达式
};

#endif //QUINE_MCCLUSKEY_ITEM_H