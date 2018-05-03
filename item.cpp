#include "item.h"
#include <algorithm>

Item::Item() :
    isUsed(false)
{

}
Item::Item(int numbering, int quantity) :
    isUsed(false)
{
    itemContain.push_back(numbering);
    if (numbering == 0)
    {
        for (int i = 0; i < quantity; i++)
            binaryCode.push_back(0);
        return;
    }
    while (numbering != 0)
    {
        binaryCode.push_back(numbering % 2);
        numbering = numbering / 2;
    }
    while (binaryCode.size() < quantity)
        binaryCode.push_back(0);
    std::reverse(binaryCode.begin(), binaryCode.end());
}
Item & Item::operator=(const Item &para)
{
    isUsed = para.isUsed;
    binaryCode = para.binaryCode;
    itemContain = para.itemContain;
    return *this;
}
bool Item::get_isUsed()
{
    return isUsed;
}
std::vector<int> Item::get_binaryCode()
{
    return binaryCode;
}
std::vector<int> Item::get_itemContain()
{
    return itemContain;
}
void Item::set_isUsed(bool para)
{
    isUsed = para;
}
void Item::set_binaryCode(const std::vector<int> &para)
{
    binaryCode = para;
}
void Item::set_itemContain(const std::vector<int> &para)
{
    itemContain = para;
}
bool Item::isItemContain(int item)
{
    std::vector<int>::iterator pos;
    pos = std::find(itemContain.begin(), itemContain.end(), item);
    if (pos == itemContain.end())
        return false;
    else
        return true;
}
int Item::numOfOne()
{
    int count = 0;
    for (int i = 0; i < binaryCode.size(); i++)
    {
        if (binaryCode[i] == 1)
            count++;
    }
    return count;
}
bool Item::combain(const Item &a, const Item &b, Item &result)
{
    int hasDiff = 0;
    for (int i = 0; i < a.binaryCode.size(); i++)
    {
        if (a.binaryCode[i] == b.binaryCode[i])
            continue;
        else if (a.binaryCode[i] + b.binaryCode[i] == 1)
        {
            if (hasDiff)
                return false;
            else
                hasDiff = i + 1;
        }
        else if (a.binaryCode[i] == -1 || b.binaryCode[i] == -1)
            return false;
    }
    if (hasDiff)
    {
        result = a;
        result.binaryCode[hasDiff - 1] = -1;
        for (auto &x : b.itemContain)
        {
            std::vector<int>::iterator pos;
            pos = std::find(result.itemContain.begin(), 
                            result.itemContain.end(), x);
            if (pos == result.itemContain.end())
                result.itemContain.push_back(x);
        }
        return true;
    }
    else
        return false;
}
std::string Item::toString()
{
    std::string result;
    for (int i = 0; i < binaryCode.size(); i++)
    {
        switch(binaryCode[i])
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