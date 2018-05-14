// ==============================
// item.cpp
// 与项类方法实现
// ==============================

#include <algorithm>
#include "item.h"

Item::Item() :
    isUsed(false), variableQuantity(0)
{

}
Item::Item(int variablePara) :
    isUsed(false), variableQuantity(variablePara)
{
    for (int i = 0; i < variablePara; i++)
        variableContain.push_back(-1);
}
Item::Item(int minItem, int variableQuantity) :
    isUsed(false), variableQuantity(variableQuantity)
{
    for (int i = 0; i < variableQuantity; i++)
        variableContain.push_back(-1);
    push_back_minItem(minItem);
    updateVariableContain();
}
Item::Item(std::vector<int> para) :
    isUsed(false)
{
    variableQuantity = para.size();
    //TODO:
}
Item & Item::operator=(const Item &para)
{
    if (variableQuantity != para.variableQuantity)
        return *this;
    isUsed = para.isUsed;
    variableContain = para.variableContain;
    minItemContain = para.minItemContain;
    return *this;
}
bool Item::operator==(const Item &a) const
{
    if (variableQuantity != a.variableQuantity)
        return false;
    if (minItemContain.size() != a.minItemContain.size())
        return false;
    else
    {
        for (int i = 0; i < minItemContain.size(); i++)
        {
            if (!a.isMinItemContained(minItemContain[i]))
                return false;
        }
        return true;
    }
}
void Item::clear()
{
    variableContain.clear();
    variableQuantity = 0;
    minItemContain.clear();
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
std::vector<int> Item::get_variableContain() const
{
    return variableContain;
}
int Item::get_variableContain(int pos) const
{
    return variableContain[pos];
}
std::vector<int> Item::get_minItemContain() const
{
    return minItemContain;
}
bool Item::isMinItemContained(int minItem) const
{
    std::vector<int>::const_iterator pos;
    pos = std::find(minItemContain.begin(), minItemContain.end(), minItem);
    if (pos == minItemContain.end())
        return false;
    else
        return true;
}
void Item::set_variableQuantity(int para)
{
    variableQuantity = para;
    updateVariableContain();
}
void Item::set_isUsed(bool para)
{
    isUsed = para;
}
void Item::set_variableContain(const std::vector<int> &para)
{
    variableContain = para;
    updateMinItemContain();
}
void Item::set_minItemContain(const std::vector<int> &para)
{
    minItemContain = para;
    updateVariableContain();
}
void Item::set_variableContian(int pos, int para)
{
    variableContain[pos] = para;
    updateMinItemContain();
}
void Item::push_back_minItem(int para)
{
    //如果与项中已经包含要加入的最小项，则返回
    if (isMinItemContained(para))
        return;

    minItemContain.push_back(para);

    for (int j = 0; j < variableQuantity; j++)
    {
        if (variableContain[j] == 2)
            continue;
        else if(variableContain[j] == -1)
        {
            int status;
            status = (1 << (variableQuantity - j - 1)) & para;
            if (status)
                variableContain[j] = 1;
            else
                variableContain[j] = 0;
        }
        else
        {
            int status;
            status = (1 << (variableQuantity - j - 1)) & para;
            if (!status && variableContain[j] == 1)
                variableContain[j] = 2;
            else if (status && variableContain[j] == 0)
                variableContain[j] = 2;
            else
                continue;
        }
    }
}
void Item::removeMinItem(int minItem)
{
    std::vector<int>::iterator p;
    p = std::find(minItemContain.begin(), minItemContain.end(), minItem);
    if (p == minItemContain.end())
        return;
    minItemContain.erase(p);
    updateVariableContain();
}
void Item::updateVariableContain()
{
    variableContain.clear();
    for (int i = 0; i < variableQuantity; i++)
        variableContain.push_back(-1);
    for (int i = 0; i < minItemContain.size(); i++)
    {
        for (int j = 0; j < variableQuantity; j++)
        {
            if (variableContain[j] == 2)
                continue;
            else if(variableContain[j] == -1)
            {
                int status;
                status = (1 << (variableQuantity - j - 1)) & minItemContain[i];
                if (status)
                    variableContain[j] = 1;
                else
                    variableContain[j] = 0;
            }
            else
            {
                int status;
                status = (1 << (variableQuantity - j - 1)) & minItemContain[i];
                if (!status && variableContain[j] == 1)
                    variableContain[j] = 2;
                else if (status && variableContain[j] == 0)
                    variableContain[j] = 2;
                else
                    continue;
            }
        }
    }
}
void Item::updateMinItemContain()
{
    //TODO:
}
int Item::numOfPositiveVariables() const
{
    int count = 0;
    for (int i = 0; i < variableContain.size(); i++)
    {
        if (variableContain[i] == 1)
            count++;
    }
    return count;
}
int Item::numOfNegativeVariables() const
{
    int count = 0;
    for (int i = 0; i < variableContain.size(); i++)
    {
        if (variableContain[i] == 0)
            count++;
    }
    return count;
}
bool Item::combine(Item &a, Item &b, Item &result)
{
    if (a.variableQuantity != b.variableQuantity)
        return false;
    result.clear();
    result.variableQuantity = a.variableQuantity;
    result.updateVariableContain();
    std::sort(a.minItemContain.begin(), a.minItemContain.end());
    std::sort(b.minItemContain.begin(), b.minItemContain.end());

    int aPos, bPos;
    bPos = 0;
    for (aPos = 0; aPos < a.minItemContain.size(); aPos++)
    {
        if (bPos >= b.minItemContain.size())
            result.push_back_minItem(a.minItemContain[aPos]);
        else if (a.minItemContain[aPos] < b.minItemContain[bPos])
            result.push_back_minItem(a.minItemContain[aPos]);
        else if (a.minItemContain[aPos] == b.minItemContain[bPos])
        {
            result.push_back_minItem(a.minItemContain[aPos]);
            bPos++;
        }
        else
        {
            while (bPos <= b.minItemContain.size() && a.minItemContain[aPos] >= b.minItemContain[bPos])
            {
                result.push_back_minItem(b.minItemContain[bPos]);
                bPos++;
            }
            result.push_back_minItem(a.minItemContain[bPos]);
        }
    }
    while (bPos <= b.minItemContain.size())
    {
        result.push_back_minItem(b.minItemContain[bPos]);
        bPos++;
    }
    result.updateVariableContain();
    return true;
}
std::string Item::toString() const
{
    std::string result;
    for (int i = 0; i < variableContain.size(); i++)
    {
        switch(variableContain[i])
        {
        case 0:
            result += 'a' + i;
            break;
        case 1:
            result += 'A' + i;
            break;
        default:
            break;
        }
    }
    return result;
}