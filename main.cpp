//ǰ��
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
    cout << "\n\n\n\n\n\n\t\t\t  �밴������Կ�ʼ��Ϸ";
    _getch();
    b:system("cls");
    cout << "1.���߳�ʽ���ܿ���" << endl;
    cout << "2.�غ��ƣ��ڲ��У������ڴ�������ʵ��ûд;-)��" << endl;
    cout << "3.��Ϸ�̳�" << endl;
    cout << "4.�����ڴ�" << endl;
    cout << "5.�˳���Ϸ" << endl;
    cout << "��������ź󰴻س��Կ�ʼ��Ϸ��" << endl;
    SetConsoleTextAttribute(hConsole,27);
    scanf_s("%d",&num);
    SetConsoleTextAttribute(hConsole,7);
    system("cls");
    switch(num) {
        case 1:
            mode1(13);
            break;
        case 2:
            cout << "�����ڴ�";
            Sleep(3000);
            goto b;
            break;
        case 3:
            cout << "1.����WASD�����ƶ�\n2.���ո������������Ҫ��ʬ������һ�����Ч��\n" << endl;
            SetConsoleTextAttribute(hConsole,76);
            cout << "���棺����Դʯ�;�С��3ʱ����ʬ���Դ�ǽ��\n" << endl;
            SetConsoleTextAttribute(hConsole,7);
            system("pause");
            goto b;
            break;
        case 4:
            cout << "�����ڴ�";
            Sleep(3000);
            goto b;
            break;
        case 5:
            cout << "ȷ��Ҫ�˳���Ϸ��(y/n): ";
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