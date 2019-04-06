//前端
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
#include <Windows.h>
using namespace std;
extern void mode1(int);
int main() {
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int num=0;
	system("TITLE Zombies");
    logo_page:system("color 07");
    system("cls");
    SetConsoleTextAttribute(hConsole,10);
    cout << "\n\n\n\n\t\t\t\tZombies\n";
    SetConsoleTextAttribute(hConsole,7);
    cout << "\n\n\n\n\n\n\t\t\t  请按任意键以开始游戏";
    _getch();
    b:system("cls");
    cout << "1.多线程式（很卡）" << endl;
    cout << "2.回合制（内测中，敬请期待）（其实还没写;-)）" << endl;
    cout << "3.游戏教程" << endl;
    cout << "4.敬请期待" << endl;
    cout << "5.退出游戏" << endl;
    cout << "（输入序号后按回车以开始游戏）" << endl;
    SetConsoleTextAttribute(hConsole,27);
    scanf_s("%d",&num);
    SetConsoleTextAttribute(hConsole,7);
    system("cls");
    switch(num) {
        case 1:
            mode1(13);
            break;
        case 2:
            cout << "敬请期待";
            Sleep(3000);
            goto b;
            break;
        case 3:
            cout << "1.按“WASD”键移动\n2.按空格键攻击（必须要僵尸距离你一格才有效）\n" << endl;
            SetConsoleTextAttribute(hConsole,76);
            cout << "警告：当能源石耐久小于3时，僵尸可以穿墙！\n" << endl;
            SetConsoleTextAttribute(hConsole,7);
            system("pause");
            goto b;
            break;
        case 4:
            cout << "敬请期待";
            Sleep(3000);
            goto b;
            break;
        case 5:
            cout << "确定要退出游戏吗？(y/n): ";
            SetConsoleTextAttribute(hConsole,27);
            char yn;
            cin >> yn;
            if (yn=='y' || yn=='Y')
                return 0;
            else if (yn=='n' || yn=='N') {
                SetConsoleTextAttribute(hConsole,7);
                goto b;
            }
    }
    goto logo_page;
    return 0;
}