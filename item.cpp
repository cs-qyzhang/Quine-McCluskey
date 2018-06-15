// ==============================
// item.cpp
// 项的类方法实现
// ==============================

#include <algorithm>
#include "item.h"

// ------------------------------
// 函数名称：Item
// 函数功能：默认析构函数，不包含参数
// 函数参数：无
// 函数返回：无
// 函数说明：无
// ------------------------------
Item::Item() :
    isUsed(false), variableQuantity(0)
{

}
// ------------------------------
// 函数名称：Item
// 函数功能：析构函数，根据变量名构造
// 函数参数：const std::vector<std::string>&, 变量名
// 函数返回：无
// 函数说明：无
// ------------------------------
Item::Item(const std::vector<std::string> &variablePara) :
    isUsed(false), variable(variablePara),
    variableQuantity(variablePara.size())
{

}
// ------------------------------
// 函数名称：Item
// 函数功能：析构函数，根据变量名和最小项构造
// 函数参数：const std::vector<std::string>&, 变量名
//         const std::vector<int>&, 最小项
// 函数返回：无
// 函数说明：无
// ------------------------------
Item::Item(const std::vector<std::string> &variablePara,
           const std::vector<int> &para) :
    isUsed(false), variableQuantity(variablePara.size),
    variable(variablePara), minItem(para)
{

}
// ------------------------------
// 函数名称：operator=
// 函数功能：赋值运算
// 函数参数：const Item &para
// 函数返回：Item &
// 函数说明：无
// ------------------------------
Item & Item::operator=(const Item &para)
{
    variableQuantity = para.variableQuantity;
    isUsed = para.isUsed;
    minItem = para.minItem;
    variable = para.variable;
    return *this;
}
// ------------------------------
// 函数名称：operator==
// 函数功能：等于运算
// 函数参数：const Item &
// 函数返回：bool
// 函数说明：不对isUsed项进行比较
// ------------------------------
bool Item::operator==(const Item &a) const
{
    if (variableQuantity != a.variableQuantity)
        return false;
    if (variable != variable)
        return false;
    if (minItem.size() != a.minItem.size())
        return false;
    else
    {
        for (int i = 0; i < minItem.size(); i++)
        {
            if (!a.isMinItemContained(minItem[i]))
                return false;
        }
        return true;
    }
}
// ------------------------------
// 函数名称：clear
// 函数功能：清空项
// 函数参数：无
// 函数返回：无
// 函数说明：无
// ------------------------------
void Item::clear()
{
    variableQuantity = 0;
    variable.clear();
    minItem.clear();
    isUsed = false;
}
int Item::get_variableQuantity() const
{
    return variableQuantity;
}
bool Item::get_isUsed() const
{
    return isUsed;
}
std::vector<int> & Item::get_minItem() const
{
    std::vector<int> result;
    result = minItem;
    return result;
}
std::vector<std::string> & Item::get_variable() const
{
    std::vector<std::string> result;
    result = variable;
    return result;
}
bool Item::isMinItemContained(int para) const
{
    std::vector<int>::const_iterator pos;
    pos = std::find(minItem.begin(), minItem.end(), para);
    if (pos == minItem.end())
        return false;
    else
        return true;
}
void Item::set_variableQuantity(int para)
{
    variableQuantity = para;
}
void Item::set_isUsed(bool para)
{
    isUsed = para;
}
void Item::set_minItem(const std::vector<int> &para)
{
    minItem = para;
}
void Item::set_variable(const std::vector<std::string> &para)
{
    variable = para;
}
void Item::push_back_minItem(int para)
{
    //如果项中已经包含要加入的最小项，则返回
    if (isMinItemContained(para))
        return;

    minItem.push_back(para);
}
void Item::removeMinItem(int para)
{
    std::vector<int>::iterator p;
    p = std::find(minItem.begin(), minItem.end(), para);
    if (p == minItem.end())
        return;
    minItem.erase(p);
}
Item & Item::operator+(const Item &para)
{
    std::vector<int> result;
    std::vector<int> a = minItem;
    std::vector<int> b = para.minItem;

    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());

    std::vector<int>::iterator pa, pb;
    pb = b.begin();
    for (pa = a.begin(); pa != a.end(); pa++)
    {
        if (pb == b.end())
            result.push_back(*pa);
        else if (*pa < *pb)
            result.push_back(*pa);
        else if (*pa == *pb)
        {
            result.push_back(*pa);          //假设a中没有重复元素，b中没有重复元素
            *pb++;
        }
        else
        {
            while (pb != b.end() && *pb > *pa)
            {
                result.push_back(*pb);
                pb++;
            }
            result.push_back(*pa);
        }
    }
    while (pb != b.end())
    {
        result.push_back(*pb);
        pb++;
    }
    minItem = result;
    return *this;
}
Item & Item::operator*(const Item &para)
{
    std::vector<int> result;
    std::vector<int> a = minItem;
    std::vector<int> b = para.minItem;

    result.clear();
    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());

    std::vector<int>::iterator pa, pb;
    pb = b.begin();
    for (pa = a.begin(); pa != a.end(); pa++)
    {
        if (pb == b.end())
            break;
        else
        {
			while (pb != b.end() && *pb < *pa)
            {
                pb++;
        	}
            
        	if(*pb==*pa)
        	{
        		result.push_back(*pb);
        		pb++;
			}
		}
    }

    minItem = result;
    return *this;
}
int Item::numOfPositiveVariables() const
{
    //TODO:
}
int Item::numOfNegativeVariables() const
{
    //TODO:
}
int Item::expr(const std::string &exprPara, const std::vector<std::string> &variablePara)
{
    variable = variablePara;
    variableQuantity = variable.size();
    isUsed = false;
    minItem.clear();

    //第一步：扫描输入是否合法。
    //       合法性包括：
    //       1.运算符操作数都为变量名或表达式。
    //       2.给定的变量名具有确定性，即会产生混淆的与项表达式中要加上*以区分
    //         如若同时存在C,CE,E三种变量的情况下存在CE表达式。
    //       3.表达式中的变量名都在变量名集合内。
    //       4.表达式中的运算符都要包含在运算符集合内。
    //       5.括号能够正确匹配
    int legalState;
    legalState = legalExpr(exprPara);
    if (legalState)
        return legalState;

    //第二步：将表达式中的变量名替换为相应的二位十进制编码，以变量在变量名集合中的下标进行编码。




    //第三步：将表达式中的与项转换成Item并存放在vector中，并按照该项在vector中的下标进行编码，编码为三位十进制。




    //第四步：将第三步得到的中缀表达式转换为后缀表达式。
    //       运算符优先级：
    //       非(!) > 与(*) > 异或(^) = 同或(@) > 或(+)



    //第五步：计算并合并各个与项，最后将所有的与项合并为一个与项。
}
// ------------------------------
// 函数名称：legalExpr
// 函数功能：判断表达式是否合法
// 函数参数：const std::string &
// 函数返回：int, 0：合法，1：不满足条件1,2：不满足条件2,3：不满足条件3
//              4：不满足条件4,5：不满足条件5
// 函数说明：合法性：
//         1.运算符操作数都为变量名或表达式。
//         2.给定的变量名具有确定性，即会产生混淆的与项表达式中要加上*以区分
//           如若同时存在C,CE,E三种变量的情况下存在CE表达式。
//         3.表达式中的变量名都在变量名集合内。
//         4.表达式中的运算符都要包含在运算符集合内。
//         5.括号能够正确匹配
// ------------------------------
int Item::legalExpr(const std::string &para)
{
    //TODO:词法分析学习
    //检查合法性第一步：运算符操作数都为变量名或表达式


    //检查合法性第二步：给定的变量名具有确定性


    //检查合法性第三步：表达式中的变量名都在变量名集合内


    //检查合法性第四步：表达式中的运算符都要包含在运算符集合内


    //检查合法性第五步：括号能够正确匹配
    return 0;
}