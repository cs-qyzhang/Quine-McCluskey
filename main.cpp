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
    int select, variableNum;
    vector<char> variables;
    vector<int> minItemTemp;
    vector<string> variableTemp;
    string stringTemp;
    Item item;
    char yesOrNo;
    char input[300];
    int intTemp;
    bool hadToMinItems = false;

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
            if (hadToMinItems)
                hadToMinItems = false;
            cout << "请先输入变量个数：";
            cin >> variableNum;
            if (cin.fail())
            {
                cin.clear();
                cin.get();
                cout << "错误的输入格式！请输入一个数字！" << endl;
                minItemTemp.clear();
                break;
            }
            cout << "请按照变量顺序依次输入变量名，以空格分隔。" << endl;
            cout << "变量名可由下划线(_)，大写字母(A~Z)，小写字母(a~z)，数字(0~9)组成。" << endl;
            variableTemp.clear();
            for (int i = 0; i < variableNum; i++)
            {
                cin >> stringTemp;
                variableTemp.push_back(stringTemp);
            }
            item.set_variable(variableTemp);
            break;
        case 2:
            if (hadToMinItems)
                hadToMinItems = false;
            if (item.get_variable().empty())
            {
                cout << "请先输入变量名称！" << endl;
                break;
            }
            cout << "表达式中允许的运算符有：或(+), 与(*), 非(!), 异或(^), 同或(@)；" << endl;
            cout << "其中不同变量之间相与可省略\'*\'号；" << endl;
            cout << "在变量名后输入单引号(\')代表该变量以反变量的形式出现。" << endl;
            cout << "请输入表达式：";
            cin >> stringTemp;
            item.expr(stringTemp, variableTemp);
            minItemTemp = item.get_minItem();
            for (int i = 0; i < minItemTemp.size(); i++)
                cout << minItemTemp[i] << ' ';
            cout << endl;
            hadToMinItems = true;
            break;
        case 3:
            if (item.get_variable().empty())
            {
                cout << "请先输入变量名称！" << endl;
                break;
            }
            if (hadToMinItems)
            {
                hadToMinItems = false;
                cout << "是否将第二步得到的最小项化简？(y/n)";
                cin >> yesOrNo;
            }
            else
                yesOrNo = 'n';
            if (yesOrNo != 'y' && yesOrNo != 'Y')
            {
                cout << "请输入最小项，以空格分隔，-1结束输入：";
                minItemTemp.clear();
                while (cin >> intTemp)
                {
                    if (cin.fail())
                    {
                        cin.clear();
                        cin.get();
                        cout << "错误的输入格式！请输入一个数字！" << endl;
                        minItemTemp.clear();
                        break;
                    }
                    if (intTemp == -1)
                        break;
                    minItemTemp.push_back(intTemp);
                }
                item.set_minItem(minItemTemp);
            }
            stringTemp = item.toString();
            cout << "化简后的表达式为：" << endl;
            cout << stringTemp << endl;
            break;
        case 4:
            if (hadToMinItems)
                hadToMinItems = false;
            if (item.get_variable().empty())
            {
                cout << "请先输入变量名称！" << endl;
                break;
            }
            cout << "表达式中允许的运算符有：或(+), 与(*), 非(!), 异或(^), 同或(@)；" << endl;
            cout << "其中不同变量之间相与可省略\'*\'号；" << endl;
            cout << "在变量名后输入单引号(\')代表该变量以反变量的形式出现。" << endl;
            cout << "请输入表达式：";
            cin >> stringTemp;
            item.expr(stringTemp, variableTemp);
            stringTemp = item.toString();
            cout << "化简后的表达式为：" << endl;
            cout << stringTemp << endl;
            break;
        default:
            hadToMinItems = false;
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
    cout << " 1.按顺序输入变量" << endl;
    cout << " 2.将表达式转换为最小项" << endl;
    cout << " 3.将最小项化简表达式" << endl;
    cout << " 4.化简表达式" << endl;
    cout << "-----------------------------" << endl;
    cout << "请输入选项以继续：";
    cin  >> select;
    if (cin.fail())
    {
        cin.clear();
        cin.get();
        cout << "错误的输入格式！请输入一个数字！" << endl;
        return -1;
    }
    return select;
}
