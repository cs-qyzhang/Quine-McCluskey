// ==============================
// item.cpp
// 项的类方法实现
// ==============================

#include <algorithm>
#include <list>
#include <iostream>
#include <cmath>
#include <stack>
#include "item.h"

// ------------------------------
// 函数名称：Item
// 函数功能：默认析构函数，不包含参数
// 函数参数：无
// 函数返回：无
// 函数说明：无
// ------------------------------
Item::Item() :
    isUsed(false)
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
    isUsed(false), variable(variablePara)
{
    std::sort(variable.begin(), variable.end());
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
    isUsed(false), variable(variablePara), minItem(para)
{
    std::sort(variable.begin(), variable.end());
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
    variable.clear();
    minItem.clear();
    isUsed = false;
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
    std::sort(variable.begin(), variable.end());
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
Item Item::operator+(const Item &para)
{
    Item result;
    result.variable = variable;
    std::vector<int> a = minItem;
    std::vector<int> b = para.minItem;

    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());

    std::vector<int>::iterator pa, pb;
    pb = b.begin();
    for (pa = a.begin(); pa != a.end(); pa++)
    {
        if (pb == b.end())
            result.minItem.push_back(*pa);
        else if (*pa < *pb)
            result.minItem.push_back(*pa);
        else if (*pa == *pb)
        {
            result.minItem.push_back(*pa);          //假设a中没有重复元素，b中没有重复元素
            *pb++;
        }
        else
        {
            while (pb != b.end() && *pb < *pa)
            {
                result.minItem.push_back(*pb);
                pb++;
            }
            if (*pb == *pa)
            {
                result.minItem.push_back(*pb);
                pb++;
            }
            else
                result.minItem.push_back(*pa);
        }
    }
    while (pb != b.end())
    {
        result.minItem.push_back(*pb);
        pb++;
    }
    return result;
}
Item Item::operator*(const Item &para)
{
    Item result;
    result.variable = variable;
    std::vector<int> a = minItem;
    std::vector<int> b = para.minItem;

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
        		result.minItem.push_back(*pb);
        		pb++;
			}
		}
    }

    return result;
}
Item Item::operator!()
{
    Item result;
    result.variable = variable;
    std::vector<int> complement;
    std::vector<int>::iterator p;

    p = minItem.begin();
    for (int i = 0; i < exp2(variable.size()); i++)
    {
        if (p == minItem.end())
            complement.push_back(i);
        else if (i < *p)
            complement.push_back(i);
        else if (i == *p)
            p++;
        else
            ;
    }
    result.minItem = complement;

    return result;
}
int Item::numOfPositiveVariables() const
{
    //TODO:
}
int Item::numOfNegativeVariables() const
{
    //TODO:
}
// ------------------------------
// 函数名称：isOperator
// 函数功能：判断表达式中字符是否为运算符
// 函数参数：char
// 函数返回：bool， true代表该字符为运算符，否则返回false
// 函数说明：无
// ------------------------------
bool Item::isOperator(char para)
{
    if (para == '@' ||
        para == '^' ||
        para == '*' ||
        para == '+' ||
        para == '!' ||
        para == '(' ||
        para == ')')
        return true;
    else
        return false;
}
// ------------------------------
// 函数名称：isVariable
// 函数功能：判断表达式中字符是否为变量
// 函数参数：char
// 函数返回：bool， true代表该字符为变量，否则返回false
// 函数说明：无
// ------------------------------
bool Item::isVariable(char para)
{
    if (para >='a' && para <= 'z')
        return true;
    else if (para >= 'A' && para <= 'Z')
        return true;
    else if (para >= '0' && para <= '9')
        return true;
    else if (para == '_')
        return true;
    else
        return false;
}
// ------------------------------
// 函数名称：vaPosToString
// 函数功能：将int型的变量名所在vector中的下标转换为二位十进制编码并用字符串表示
// 函数参数：int
// 函数返回：std::string，转换后的编码
// 函数说明：无
// ------------------------------
std::string Item::vaPosToString(int para)
{
    std::string result;
    if (para < 10)
    {
        result.push_back('0');
        result.push_back('0' + para);
    }
    else
    {
        result.push_back('0' + para / 10);
        result.push_back('0' + para % 10);
    }
    return result;
}
// ------------------------------
// 函数名称：itemPosToString
// 函数功能：将int型的与项所在vector中的下标转换为三位十进制编码并用字符串表示
// 函数参数：int
// 函数返回：std::string，转换后的编码
// 函数说明：无
// ------------------------------
std::string Item::itemPosToString(int para)
{
    std::string result;
    if (para < 10)
    {
        result.push_back('0');
        result.push_back('0');
        result.push_back('0' + para);
    }
    else if (para >= 10 && para <= 99)
    {
        result.push_back('0');
        result.push_back('0' + para / 10);
        result.push_back('0' + para % 10);
    }
    else
    {
        result.push_back('0' + para / 100);
        result.push_back('0' + (para / 10) % 10);
        result.push_back('0' + para % 10);
    }
    return result;
}
// ------------------------------
// 函数名称：variableEcoding
// 函数功能：将一个与项中的变量转变为相应的二位十进制编码，并用string表示
// 函数参数：std::string，变量名组成的与项
// 函数返回：std::string，转换后的编码
// 函数说明：无
// ------------------------------
std::string Item::variableEcoding(std::string para)
{
    std::string::iterator p1, p2, lastPos;
    p1 = para.begin();
    p2 = p1;
    
    while (p1 != para.end())
    {
        lastPos = p1;
        std::string temp;
        std::vector<std::string>::iterator pos;

        while (p2 != para.end())
        {
            p2++;

            temp = para.substr(p1 - para.begin(), p2 - p1);
            pos = std::find(variable.begin(), variable.end(), temp);
            if (pos != variable.end())
                lastPos = p2;

        }

        temp = para.substr(p1 - para.begin(), lastPos - p1);
        pos = std::find(variable.begin(), variable.end(), temp);
        para.replace(p1, lastPos, vaPosToString(pos - variable.begin()));
        p1 += 2;
        p2 = p1;
    }

    return para;
}
// ------------------------------
// 函数名称：listToInt
// 函数功能：将用链表表示的每个变量的包含情况转换为相应的最小项
// 函数参数：const std::list<int> &flag，用链表表示的每个变量的包含情况
// 函数返回：int，转换后的最小项
// 函数说明：无
// ------------------------------
int Item::listToInt(const std::list<int> &flag)
{
    int result = 0;

    std::list<int>::const_iterator p;
    p = flag.begin();
    for (int i = 0; i < flag.size(); i++)
    {
        result = result << 1;
        result += *p;
        p++;
    }

    return result;
}
// ------------------------------
// 函数名称：stringToMinItems
// 函数功能：将用string表示的与项转换为相应的最小项集合
// 函数参数：std::string，变量名组成的与项
// 函数返回：std::vector<int>，转换后的最小项集合
// 函数说明：无
// ------------------------------
std::vector<int> Item::stringToMinItems(std::string para)
{
    std::vector<int> result;
    std::vector<int> vaContained;

    //建立vaContained
    std::string::iterator p1;
    p1 = para.begin();
    while (p1 != para.end())
    {
        std::string temp;
        temp = para.substr(p1 - para.begin(), 2);
        vaContained.push_back(std::stoi(temp));
        p1 += 2; 
    }
    std::sort(vaContained.begin(), vaContained.end());

    int leftVaNum;
    leftVaNum = variable.size() - vaContained.size();

    std::list<int> min;
    for (int i = 0; i < exp2(leftVaNum); i++)
    {
        int num;
        num = i;

        for (int j = 0; j < leftVaNum; j++)
        {
            min.push_front(num % 2);
            num /= 2;
        }

        for (int j = 0; j < vaContained.size(); j++)
        {
            std::list<int>::iterator p;
            p = min.begin();
            std::advance(p, vaContained[j]);
            min.insert(p, 1);
        }

        result.push_back(listToInt(min));
        min.clear();
    }
    return result;
}
// ------------------------------
// 函数名称：operatorPriority
// 函数功能：得到运算符的优先级
// 函数参数：char，运算符
// 函数返回：int，运算符优先级
// 函数说明：无
// ------------------------------
int Item::operatorPriority(char para)
{
    if (para == '!')
        return 3;
    else if (para == '*')
        return 2;
    else if (para == '^' || para == '@')
        return 1;
    else if (para == '+')
        return 0;
    else
        return -1;
}
// ------------------------------
// 函数名称：InfixToSuffix
// 函数功能：中缀表达式转后缀表达式
// 函数参数：std::string，中缀表达式
// 函数返回：std::string，后缀表达式
// 函数说明：无
// ------------------------------
std::string Item::InfixToSuffix(std::string para)
{
    std::stack<char> operatorStack;
    std::string result;

    std::string::iterator p;
    p = para.begin();
    while (p != para.end())
    {
        if (isOperator(*p))
        {
            if (operatorStack.empty())
                operatorStack.push(*p);
            else if (*p == '(')
                operatorStack.push(*p);
            else if (*p == ')')
            {
                while (operatorStack.top() != '(')
                {
                    result.push_back(operatorStack.top());
                    operatorStack.pop();
                }
                operatorStack.pop();
            }
            else
            {
                while (!operatorStack.empty() &&
                       operatorPriority(operatorStack.top()) >=
                       operatorPriority(*p))
                {
                    result.push_back(operatorStack.top());
                    operatorStack.pop();
                }
                operatorStack.push(*p);
            }
        }
        else
            result.push_back(*p);
        
        p++;
    }
    while (!operatorStack.empty())
    {
        result.push_back(operatorStack.top());
        operatorStack.pop();
    }
    return result;
}
// ------------------------------
// 函数名称：expr
// 函数功能：将一个逻辑表达式字符串转换为一个Item
// 函数参数：const std::string&，逻辑表达式
//          const std::vector<std::string>&，变量名vector
// 函数返回：int，处理结果，包括表达式是否合法，转换是否产生错误。若成功转换则返回0
// 函数说明：无
// ------------------------------
int Item::expr(const std::string &exprPara, const std::vector<std::string> &variablePara)
{
    variable = variablePara;
    std::sort(variable.begin(), variable.end());

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
    std::string expressions = (std::string)exprPara;
    std::string::iterator p1, p2;

    //清除空格
    while (true)
    {
        p1 = std::find(expressions.begin(), expressions.end(), ' ');
        if (p1 != expressions.end())
            expressions.erase(p1);
        else
            break;
    }

    p1 = expressions.begin();
    p2 = expressions.begin();
    const int BEGIN = 0, VARIABLES = 1, OPERATORS = 2;
    int state = BEGIN;

    while (p1 != expressions.end())
    {
        switch (state)
        {
        case BEGIN:
            if (isOperator(*p1))
                state = OPERATORS;
            else if (isVariable(*p1))
                state = VARIABLES;
            else
                return -1;
            break;
        case VARIABLES:
            p2++;
            if (p2 == expressions.end() || !isVariable(*p2))
            {
                if (p2 == expressions.end())
                    ;
                else if (isOperator(*p2))
                    state = OPERATORS;
                else
                    return -1;
                std::string temp;
                temp = variableEcoding(expressions.substr(p1 - expressions.begin(), p2 - p1));
                expressions.replace(p1, p2, temp);
                p1 += temp.size();
                p2 = p1;
            }
            break;
        case OPERATORS:
            p1++;
            p2++;
            if (isVariable(*p1))
                state = VARIABLES;
            else if (isOperator(*p1))
                ;
            else
                return -1;
            break;
        default:
            return -1;
        }
    }



    //第三步：将表达式中的与项转换成Item并存放在vector中，并按照该项在vector中的下标进行编码，编码为三位十进制。
    std::vector<Item> itemTable;

    int index = 0;
    p1 = expressions.begin();
    p2 = p1;
    Item *items;
    bool end;
    end = false;
    while (!end)
    {
        while(isOperator(*p1))
            p1++;
        if (p1 == expressions.end())
            break;

        p2 = p1;
        p2++;

        while (p2 != expressions.end() && !isOperator(*p2))
            p2++;
        
        if (p2 == expressions.end())
            end = true;

        std::string temp;
        temp = expressions.substr(p1 - expressions.begin(), p2 - p1);

        items = new Item(variable);
        items->set_minItem(stringToMinItems(temp));
        itemTable.push_back(*items);

        temp = itemPosToString(index++);
        expressions.replace(p1, p2, temp);

        p1 += 3;
    }


    //第四步：将第三步得到的中缀表达式转换为后缀表达式。
    //       运算符优先级：
    //       非(!) > 与(*) > 异或(^) = 同或(@) > 或(+)
    expressions = InfixToSuffix(expressions);


    //第五步：计算并合并各个与项，最后将所有的与项合并为一个与项。
    std::stack<Item> itemStack;
    p1 = expressions.begin();
    Item temp1, temp2;
    while (p1 != expressions.end())
    {
        if (isOperator(*p1))
        {
            switch(*p1)
            {
            case '!':
                temp1 = itemStack.top();
                itemStack.pop();
                temp1 = !temp1;
                itemStack.push(temp1);
                break;
            case '*':
                temp1 = itemStack.top();
                itemStack.pop();
                temp2 = itemStack.top();
                itemStack.pop();
                temp1 = temp1 * temp2;
                itemStack.push(temp1);
                break;
            case '^':
                temp1 = itemStack.top();
                itemStack.pop();
                temp2 = itemStack.top();
                itemStack.pop();
                temp1 = (temp1 * (!temp2)) + ((!temp1) * temp2);
                itemStack.push(temp1);
                break;
            case '@':
                temp1 = itemStack.top();
                itemStack.pop();
                temp2 = itemStack.top();
                itemStack.pop();
                temp1 = (temp1 * temp2) + ((!temp1) * (!temp2));
                itemStack.push(temp1);
                break;
            case '+':
                temp1 = itemStack.top();
                itemStack.pop();
                temp2 = itemStack.top();
                itemStack.pop();
                temp1 = temp1 + temp2;
                itemStack.push(temp1);
                break;
            }
            p1++;
        }
        else
        {
            std::string temp;
            temp = expressions.substr(p1 - expressions.begin(), 3);
            itemStack.push(itemTable[std::stoi(temp)]);
            p1 += 3;
        }
    }
    temp1 = itemStack.top();
    minItem = temp1.minItem;
    return 0;
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