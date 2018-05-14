// ==============================
// main.cpp
// 主函数所在源文件
// ==============================

#include <iostream>
#include "item.h"

using namespace std;

int ShowMenu(void);

int main(void)
{
    int select;
    vector<char> variables;

    while (true)
    {
        select = ShowMenu();
        switch (select)
        {
        case 0:
            return 0;
            break;
        case 1:
            break;
        default:
            break;
        }
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
    //TODO:
}