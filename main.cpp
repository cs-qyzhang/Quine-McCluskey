// ==============================
// main.cpp
// 主函数所在源文件
// ==============================

#include <iostream>
#include "item.h"

using namespace std;

int ShowMenu(void);
void test(void);

int main(void)
{
    int select;
    vector<char> variables;

    test();

    while (true)
    {
        select = ShowMenu();
        switch (select)
        {
        case -1:
            break;
        case 0:
            return 0;
            break;
        case 1:
            break;
        case 2:
            break;
        default:
            cout << "错误的输入！请检查输入！" << endl;
            break;
        }
        cout << "按任意键继续：";
        cin.get();
        cin.get();
    }
}

// ----------------------------------------
// 函数名称：ShowMenu
// 函数功能：显示功能选择菜单，并返回用户选择
// 函数参数：无
// 函数返回：int, 用户选择
// ----------------------------------------
int ShowMenu()
{
    int select;

    cout << "-----------------------------" << endl;
    cout << " 0.退出程序" << endl;
    cout << " 1.输入" << endl;
    cout << " 2.Solve the simplest expression of minimum items" << endl;
    cout << "-----------------------------" << endl;
    cout << "Please input a number to continue:";
    cin  >> select;
    if (cin.fail())
    {
        cin.clear();
        cin.get();
        cout << "Wrong input! Please check the format of input!" << endl;
        return -1;
    }
    return select;
}

void test(void)
{
    Item a;
    vector<string> variable;
    variable.push_back("A");
    variable.push_back("B");
    variable.push_back("CD");
    variable.push_back("EF");
    string result;
    result = a.expr("AB+!CD+A^EF", variable);
}