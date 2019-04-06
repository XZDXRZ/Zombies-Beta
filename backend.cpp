//���
#include <iostream>
#include <cstdio>
#include <conio.h>
#include <cstdlib>
#include <time.h>
#include <windows.h>
#include <cstring>
#include <cmath>
#include "map.hpp"
using namespace std;
char ch;//�������
int px,py,health;
int z_count;
extern char _map[MAXN][MAXN];
class Stone {
    public:
        int x,y;
        bool destruction;
        int durable;
        void init() {
            srand((int)time(NULL));
            c:x=rand()%15;
            y=rand()%15;
            if (_map[x][y]==' ') {
                _map[x][y]='O';
                destruction=false;
                durable=10;
            } else
                goto c;
        }
        bool hurt(int p,int q) {
            if (_map[x-1][y]=='I') {
                durable--;
                return true;
            }
            if (_map[x+1][y]=='I') {
                durable--;
                return true;
            }
            if (_map[x][y-1]=='I') {
                durable--;
                return true;
            }
            if (_map[x][y+1]=='I') {
                durable--;
                return true;
            }
            return false;
        }
}stone;
class Zombie {
    public:
        int id,x,y;
        bool dead;
        void m_init(int id) {//���ɽ�ʬ
            srand((unsigned)time(NULL));//������α�������
            a:x=rand()%10;
            y=rand()%10;
            if (_map[x][y]==' ') {
                _map[x][y]='Z';
                dead=false;
            } else
                goto a;//�Ż���ʬ���ɻ��ƣ�ȷ��ÿ�ֶ��н�ʬ
            Sleep(100);//�����Ż���ʬ���ɻ��ƣ����Եȴ������ˣ��ٵ�һ�����
            system("cls");
        }
        void close_attack(int id) {//������
            if (abs(px-x)<=5 && abs(py-y)<=5) {//�ж�����ҵľ���
                if (px-x<=0) {//�������
                    if (_map[x-1][y]==' ') {
                        _map[x][y]=' ';
                        x--;
                        _map[x][y]='Z';
                    }
                } else {
                    if (_map[x+1][y]==' ') {
                        _map[x][y]=' ';
                        x++;
                        _map[x][y]='Z';
                    }
                }
                if (py-y>=0) {//�������
                    if (_map[x][y+1]==' ') {
                        _map[x][y]=' ';
                        y++;
                        _map[x][y]='Z';
                    }
                } else {
                    if (_map[x][y-1]==' ') {
                        _map[x][y]=' ';
                        y--;
                        _map[x][y]='Z';
                    }
                }
            }
        }
        void defense() {//������Դʯ
            //��Ϊ�ܴ�ǽ��emmmm����ʵ����Ϊ�����������Բ����ж���һ���ǲ��ǿո�
            if (stone.x-x<0) {//��Դʯ��������
                _map[x][y]=' ';
                x--;
                _map[x][y]='Z';
            }
            if (stone.x-x>0) {//��Դʯ��������
                _map[x][y]=' ';
                x++;
                _map[x][y]='Z';
            }
            if (stone.y-y<0) {//��Դʯ��������
                _map[x][y]=' ';
                y--;
                _map[x][y]='Z';
            }
            if (stone.y-y>0) {//��Դʯ��������
                _map[x][y]=' ';
                y++;
                _map[x][y]='Z';
            }
        }
        void team_attark(int job) {//job���������������Ĵ�
            if (px>x) {//���Կ���
                if (_map[x-1][y]==' ') {
                    _map[x][y]=' ';
                    x--;
                    _map[x][y]='Z';
                }
            } else if (px<x) {
                if (_map[x+1][y]==' ') {
                    _map[x][y]=' ';
                    x++;
                    _map[x][y]='Z';
                }
            }
            if (py>y) {
                if (_map[x][y+1]==' ') {
                    _map[x][y]=' ';
                    y++;
                    _map[x][y]='Z';
                }
            } else if (py<y) {
                if (_map[x][y-1]==' ') {
                    _map[x][y]=' ';
                    y--;
                    _map[x][y]='Z';
                }
            }
            if (abs(px-x)==1&&abs(py-y)==1) {//�������Ϊ1
                if (job==1){//���Թ�λ�������ϱ�
                    if (_map[px-1][py]==' ') {
                        _map[x][y]=' ';
                        x=px-1;
                        y=py;
                        _map[x][y]='Z';
                    }
                } else if (job==2) {//���
                    if (_map[px][py-1]==' ') {
                        _map[x][y]=' ';
                        x=px;
                        y=py-1;
                        _map[x][y]='Z';
                    }
                } else if (job==3) {//�±�
                    if (_map[px+1][py]==' ') {
                        _map[x][y]=' ';
                        x=px+1;
                        y=py;
                        _map[x][y]='Z';
                    }
                } else if (job==4) {//�ұ�
                    if (_map[px][py+1]==' ') {
                        _map[x][y]=' ';
                        x=px;
                        y=py+1;
                        _map[x][y]='Z';
                    }
                }
            }
        }
        void m_move(int id) {
            int tx,ty;
            //��ʬ��������
            if (_map[x+1][y]=='I')
                health--;
            if (_map[x-1][y]=='I')
                health--;
            if (_map[x][y+1]=='I')
                health--;
            if (_map[x][y-1]=='I')
                health--;
            srand((short)time(NULL));
            tx=rand()%2;
            ty=rand()%2;
            if (_map[x+tx][y+ty]!=' ') {
                tx*=-1;
                ty*=-1;
            }
            if (_map[x+tx][y+ty]==' ') {
                _map[x][y]=' ';
                x+=tx;
                y+=ty;
                _map[x][y]='Z';
                return;
            }
        }
}m[10];
bool is_win() {
    for (int i=0;i<=100;i++)
        for (int j=0;j<=100;j++)
            if (_map[i][j]=='Z')
                return false;
    return true;
}
void is_dead(int tx,int ty) {
    for (int i=0;i<=9;i++)
        if (m[i].x==tx+1 || m[i].x==tx-1 || m[i].y==ty-1 || m[i].y==ty-1)
            m[i].dead=true;
}
void count_zombies() {//ͳ�ƽ�ʬ����
    z_count=0;
    for (int i=0;i<=MAXN;i++) {//������ͼÿһ����
        for (int j=0;j<=MAXN;j++) {
            if (_map[i][j]=='Z')
                z_count++;
        }
    }
}
void move(int lines) {
    //����ƶ�
    ch = _getch();
    if (ch=='w'||ch=='W') {
        if (_map[px-1][py]==' ') {
            _map[px][py]=' ';
            px--;
            _map[px][py]='I';
        }
    }
    if (ch=='a'||ch=='A') {
        if (_map[px][py-1]==' ') {
            _map[px][py]=' ';
            py--;
            _map[px][py]='I';
        }
    }
    if (ch=='s'||ch=='S') {
        if (_map[px+1][py]==' ') {
            _map[px][py]=' ';
            px++;
            _map[px][py]='I';
        }
    }
    if (ch=='d'||ch=='D') {
        if (_map[px][py+1]==' ') {
            _map[px][py]=' ';
            py++;
            _map[px][py]='I';
        }
    }
    //���ط�����ҵĹ�������
    if (ch==' ') {
        if (_map[px-1][py]=='Z') {
            _map[px-1][py]=' ';
            is_dead(px,py);
        }
        if (_map[px][py-1]=='Z') {
            _map[px][py-1]=' ';
            is_dead(px,py);
        }
        if (_map[px+1][py]=='Z') {
            _map[px+1][py]=' ';
            is_dead(px,py);
        }
        if (_map[px][py+1]=='Z') {
            _map[px][py+1]=' ';
            is_dead(px,py);
        }
        //��boss
        if (_map[px-1][py]=='O') {
            if (stone.hurt(px,py)) {
                cout << "��������Դʯ��\n" << endl;
            }
        }
        if (_map[px][py-1]=='O') {
            if (stone.hurt(px,py)) {
                cout << "��������Դʯ��\n" << endl;
            }
        }
        if (_map[px+1][py]=='O') {
            if (stone.hurt(px,py)) {
                cout << "��������Դʯ��\n" << endl;
            }
        }
        if (_map[px][py+1]=='O') {
            if (stone.hurt(px,py)) {
                cout << "��������Դʯ��\n" << endl;
            }
        }
    }
    system("cls");
    for (int i=0;i<=lines;i++)
        puts(_map[i]);
}
void mode1(int lines) {//���߳�ʽ�����ϣ�
    HANDLE hConsole=0;
    SetConsoleTextAttribute(hConsole,7);
    int time=0,num=0;
    cout << "��ͼ��ʼ��..." << endl;
    memcpy(_map,cmap,sizeof(cmap));
    Sleep(100);
    system("cls");
    for (int i=0;i<=9;i++) {
        m[i].m_init(i);
        printf("��ʬ��ʼ��: %d/10\n",i+1);
    }
    system("cls");
    cout << "��Դʯ��ʼ����..." << endl;
    stone.init();
    Sleep(100);
    system("cls");
    cout << "��ҳ�ʼ��..." << endl;
    health=20;
    px=3;py=9;
    Sleep(100);
    system("cls");
    cout << "Ready?" << endl;
    Sleep(2000);
    cout << "Go!" << endl;
    Sleep(100);
    system("cls");
    for (int i=0;i<=lines;i++)
        puts(_map[i]);
    while(true){//��Ϸ��ѭ��
        //�ɹ�����ɽ�ս��ĳ�����ֲ���ˣ�
        if(_kbhit())
			move(13);
        for (int j=0;j<=9;j++)
            if (!m[j].dead && _map[m[j].x][m[j].y]=='Z') {
                m[j].m_move(j);
                m[j].close_attack(j);
            }
        for (int i=0;i<=3;i++)
            if (!m[i].dead && _map[m[i].x][m[i].y]=='Z')
                    m[i].team_attark(i);
        int j=4;
        for (int i=0;i<=3;i++)
            if (!m[j].dead && _map[m[j].x][m[j].y]=='Z')
                    m[j].team_attark(i);
            j++;
        if (stone.durable<=3)
            for (int j=0;j<=9;j++)
                if (!m[j].dead && _map[m[j].x][m[j].y]=='Z')
                    m[j].defense();
		if(time>=10)
		{
			time=0;
			num++;
		}
		system("cls");
		for (int i=0;i<=lines;i++)
            puts(_map[i]);
        count_zombies();
		printf("����ʱ�䣺%d\n",num);
		printf("���Ѫ��: %d\n",health);
		printf("��Դʯ������%d\n",stone.durable);
		printf("ʣ�ཀྵʬ������%d\n",z_count);
		Sleep(50);
		time++;
		if (health<=0) {
		    system("color c4");
            printf("��ʧ���ˣ�");
            Sleep(2000);
            return;
		}
		if (is_win()) {
            cout << "��ʤ���ˣ�";
            Sleep(2000);
            return;
		}
		if (stone.durable<=0) {//�����Դʯ���ƻ�
		    system("cls");//����
		    _map[stone.x][stone.y]=' ';//�����Դʯ
		    for (int i=0;i<=lines;i++)
                puts(_map[i]);
            cout << "��ʤ���ˣ�";
            Sleep(2000);
            return;
		}
    }
    return;
}