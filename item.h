// ==============================
// item.h
// 项的类定义
// ==============================

#ifndef QUINE_MCCLUSKEY_ITEM_H
#define QUINE_MCCLUSKEY_ITEM_H

#include <vector>
#include <string>
#include <list>

// ------------------------------
// 类名：Item
// 说明：该类描述了一个 包含若干最小项 的项
// ------------------------------
class Item
{
private:
    std::vector<std::string> variable;              //变量名称
    bool isUsed;                                    //在列表化简法里判断该项是否用过
    std::vector<int> minItem;                       //该项包含的最小项
    std::vector<std::vector<int>> binaryCode;       //最小项的二进制码，0代表反变量，1代表原变量，-1代表二者皆有

    int numOfPositiveVariables(std::vector<int>);   //计算并返回项中含有的原变量个数
    int numOfNegativeVariables(std::vector<int>);   //计算并返回项中含有的反变量个数

    int operatorPriority(char);                     //得到运算符的优先级
    std::string InfixToSuffix(std::string);         //将前缀表达式字符串变为后缀表达式字符串
    int legalExpr(const std::string &);             //判断表达式是否合法
    bool isOperator(char);                          //判断字符是否属于运算符
    bool isVariable(char);                          //判断字符是否属于变量
    std::string variableEcoding(std::string);       //将变量变为以变量名所在vector下标的二位十进制编码字符串
    std::string vaPosToString(int);                 //将变量名在vector的下标转换为二位十进制对应的字符串
    std::string itemPosToString(int);               //将与项在vector的下标转换为三位十进制对应的字符串
    std::vector<int> stringToMinItems(std::string); //将与项对应字符串转换为该与项对应的最小项
    int listToInt(const std::list<int> &flag);      //将用链表表示的每个变量的包含情况转换为相应的最小项

    void Step1();
    void Step2();
    void Step3(std::vector<int> &unNecessaryPos,
               std::vector<int> &needMinItemPos,
               std::vector<int> &necessaryPos,
               std::vector<std::vector<int>> flag);
    void Step4(std::vector<int> &unNecessaryPos,
               std::vector<int> &needMinItemPos,
               std::vector<int> &necessaryPos,
               std::vector<std::vector<int>> flag);

    bool canCombain(std::vector<int>,
                    std::vector<int>);              //判断两个二进制码表示的最小项集能否合并
    std::vector<int> combain(std::vector<int>,
                             std::vector<int>);     //合并两个二进制码表示的最小项集合

    bool contain(std::vector<int>, int);            //判断一个二进制码表示的项是否包含一个最小项
    bool rowContain(std::vector<int>, int a, int b,
            std::vector<std::vector<int>> flag);
    bool rowEqual(std::vector<int>, int a, int b,
            std::vector<std::vector<int>> flag);
    bool coloumContain(std::vector<int>, int a, int b,
            std::vector<std::vector<int>> flag);

public:
    explicit Item();                                //默认构造函数，将isUsed,variableQuantity设置为0
    Item(const std::vector<std::string> &);         //根据变量名构造项
    Item(const std::vector<std::string> &,
         const std::vector<int> &minItemPara);      //根据最小项数组构造项
    Item(std::string, std::vector<std::string>);    //根据逻辑表达式构造最小项
    ~Item() = default;                              //默认析构函数
    Item & operator=(const Item &);                 //赋值运算符
    bool operator==(const Item &) const;            //等于运算符
    Item operator+(const Item &);                   //或运算
    Item operator*(const Item &);                   //与运算
    Item operator!();                               //非运算
    void clear();                                   //清空项

    bool get_isUsed() const;                        //返回isUsed的值
    std::vector<int> get_minItem() const;           //返回minItemContain的一个拷贝
    std::vector<std::string> & get_variable() const;//返回变量名称

    bool isMinItemContained(int minItem) const;     //返回项中是否包含有minItem这一最小项

    void set_isUsed(bool);                          //设置isUsed成员
    void set_minItem(const std::vector<int> &);     //设置minItemContain成员
    void set_variable(const 
                      std::vector<std::string> &);  //设置变量名称
    
    void push_back_minItem(int minItem);            //在该项中增加一个最小项
    void removeMinItem(int);                        //在该项中去掉一个最小项
    int expr(const std::string &,
             const std::vector<std::string> &);     //根据逻辑表达式重新为项赋值

    std::string toString();                   //列表化简法计算并返回该项的最简表达式

    
};

// ------------------------------
// 结构名：VaContain
// 说明： 该结构用于在将表达式转为最小项时保存
//       一个变量在变量数组中的位置以及是
//       以原变量出现还是反变量出现
// ------------------------------
struct VaContain
{
    int vaPos;          //变量在variable中的位置
    bool isPositive;    //变量是否为原变量
};

bool VaContainComp(VaContain a, VaContain b);       //比较VaContain结构a和的vaPos是否小于b的vaPos

#endif //QUINE_MCCLUSKEY_ITEM_H