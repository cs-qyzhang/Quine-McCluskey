// ==============================
// item.cpp
// 项的类方法实现
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

}
Item::Item(const std::vector<int> &para) :
    isUsed(false)
{
    variableQuantity = para.size();
    minItem = para;
}
Item & Item::operator=(const Item &para)
{
    variableQuantity = para.variableQuantity;
    isUsed = para.isUsed;
    minItem = para.minItem;
    return *this;
}
bool Item::operator==(const Item &a) const
{
    if (variableQuantity != a.variableQuantity)
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
void Item::clear()
{
    variableQuantity = 0;
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
    //TODO:
}
Item & Item::operator*(const Item &para)
{
    //TODO:
}
int Item::numOfPositiveVariables() const
{
    //TODO:
}
int Item::numOfNegativeVariables() const
{
    //TODO:
}