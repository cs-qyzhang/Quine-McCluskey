#include <iostream>
#include "item.h"

using namespace std;
void CreatItemTable(vector<Item> &items, 
                    vector<vector<Item> > &table);
bool Step(vector<vector<Item> > &tableA,
          vector<vector<Item> > &tableB, vector<Item> &result);
void Select(vector<Item> &items, vector<Item> &result);

int quantity;

int main(void)
{
    vector<Item> items, result;
    vector<vector<Item> > tableA, tableB; 
    int temp;
    cout << "请输入变量个数：" << endl;
    cin >> quantity;
    cout << "请输入最小项，-1结束输入：" << endl;
    cin >> temp;
    while (temp != -1)
    {
        if (temp < 0)
        {
            cout << "请检查输入！" << endl;
            return 0;
        }
        Item item(temp, quantity);
        items.push_back(item);
        cin >> temp;
    }
    CreatItemTable(items, tableA);
    for (int i = 0; i < quantity; i++)
    {
        if (i % 2 == 0)
        {
            if (!Step(tableA, tableB, result))
                break;
        }
        else
        {
            if (!Step(tableB, tableA, result))
                break;
        }
    }
    //Select(items, result);
    for (auto &x : result)
    {
        cout << x.toString() << ' ';
    }
    cout << endl;
    return 0;
}

void CreatItemTable(vector<Item> &items, 
                    vector<vector<Item> > &table)
{
    if (items.empty())
        return ;
    table.clear();
    for (int i = 0; i <= quantity; i++)
    {
        vector<Item> *temp;
        temp = new std::vector<Item>;
        table.push_back(*temp);
    }
    for (auto x : items)
        table[x.numOfOne()].push_back(x);
    return ;
}

bool Step(vector<vector<Item> > &tableA,
          vector<vector<Item> > &tableB, vector<Item> &result)
{
    if (tableA.empty())
        return false;
    tableB.clear();
    for (int i = 0; i <= quantity; i++)
    {
        vector<Item> *temp;
        temp = new std::vector<Item>;
        tableB.push_back(*temp);
    }
    for (int i = 0; i < tableA.size() - 1; i++)
    {
        for (int j = 0; j < tableA[i].size(); j++)
        {
            for (int k = 0; k < tableA[i + 1].size(); k++)
            {
                Item result;
                if (Item::combain(tableA[i][j], tableA[i + 1][k], result))
                {
                    tableB[result.numOfOne()].push_back(result);
                    tableA[i][j].set_isUsed(true);
                    tableA[i + 1][k].set_isUsed(true);
                }
            }
        }
    }
    for (auto &x : tableA)
    {
        for (auto &y : x)
        {
            if (!y.get_isUsed())
                result.push_back(y);
        }
    }
    for (const auto &x : tableB)
    {
        if (!x.empty())
            return true;
    }
    return false;
}

void Select(vector<Item> &items, vector<Item> &result)
{
    vector<vector<int> > flags;
    int rowNum, coloumNum;
    rowNum = result.size() + 1;
    coloumNum = items.size() + 1;
    vector<int> temp;
    for (int i = 0; i < coloumNum; i++)
        temp.push_back(0);
    for (int i = 0; i < rowNum; i++)
        flags.push_back(temp);
    for (int i = 1; i < coloumNum; i++)
        flags[0][i] = items[i - 1].get_itemContain()[0];
    for (int i = 1; i < rowNum; i++)
        flags[i][0] = i - 1;
    for (int i = 1; i < rowNum; i++)
    {

    }
    
}