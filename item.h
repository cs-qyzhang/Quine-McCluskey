// ==============================
// item.h
// 项的类定义
// ==============================

#ifndef QUINE_MCCLUSKEY_ITEM_H
#define QUINE_MCCLUSKEY_ITEM_H

#include <vector>
#include <string>

// ------------------------------
// 类名：Item
// 说明：该类描述了一个 包含若干最小项 的项
// ------------------------------
class Item
{
private:
    int variableQuantity;                       //变量个数
    bool isUsed;                                //在列表化简法里判断该项是否用过
    std::vector<int> minItem;                   //该项包含的最小项

    int numOfPositiveVariables() const;         //计算并返回项中含有的原变量个数
    int numOfNegativeVariables() const;         //计算并返回项中含有的反变量个数

public:
    explicit Item();                            //默认构造函数，将isUsed,variableQuantity设置为0
    Item(int variableQuantity);                 //根据变量个数构造项
    Item(const std::vector<int> &minItemPara);  //根据变量包含情况构造项
    ~Item() = default;                          //默认析构函数
    Item & operator=(const Item &);             //赋值运算符
    bool operator==(const Item &) const;        //等于运算符
    Item & operator+(const Item &);             //或运算
    Item & operator*(const Item &);             //运算
    void clear();                               //清空项

    int get_variableQuantity() const;           //返回variableQuantity的值
    bool get_isUsed() const;                    //返回isUsed的值
    std::vector<int> & get_minItem() const;     //返回minItemContain的一个拷贝
    bool isMinItemContained(int minItem) const; //返回项中是否包含有minItem这一最小项

    void set_variableQuantity(int);             //设置variableQuantity成员
    void set_isUsed(bool);                      //设置isUsed成员
    void set_minItem(const std::vector<int> &); //设置minItemContain成员
    void push_back_minItem(int minItem);        //在该项中增加一个最小项
    void removeMinItem(int);                    //在该项中去掉一个最小项

    std::string toString() const;               //列表化简法计算并返回该项的最简表达式
};

#endif //QUINE_MCCLUSKEY_ITEM_H