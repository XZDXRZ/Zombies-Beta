//后端
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
char ch;//玩家输入
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
        void m_init(int id) {//生成僵尸
            srand((unsigned)time(NULL));//该死的伪随机！！
            a:x=rand()%10;
            y=rand()%10;
            if (_map[x][y]==' ') {
                _map[x][y]='Z';
                dead=false;
            } else
                goto a;//优化僵尸生成机制，确定每局都有僵尸
            Sleep(100);//由于优化僵尸生成机制，所以等待不用了（少等一会儿）
            system("cls");
        }
        void close_attack(int id) {//近身攻击
            if (abs(px-x)<=5 && abs(py-y)<=5) {//判断与玩家的距离
                if (px-x<=0) {//在玩家上
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
                if (py-y>=0) {//在玩家左
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
        void defense() {//保护能源石
            //因为能穿墙（emmmm，其实是因为我懒），所以不用判断下一步是不是空格
            if (stone.x-x<0) {//能源石在它上面
                _map[x][y]=' ';
                x--;
                _map[x][y]='Z';
            }
            if (stone.x-x>0) {//能源石在它下面
                _map[x][y]=' ';
                x++;
                _map[x][y]='Z';
            }
            if (stone.y-y<0) {//能源石在它左面
                _map[x][y]=' ';
                y--;
                _map[x][y]='Z';
            }
            if (stone.y-y>0) {//能源石在它右面
                _map[x][y]=' ';
                y++;
                _map[x][y]='Z';
            }
        }
        void team_attark(int job) {//job参数决定了它在哪打
            if (px>x) {//尝试靠近
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
            if (abs(px-x)==1&&abs(py-y)==1) {//如果距离为1
                if (job==1){//尝试归位，这是上边
                    if (_map[px-1][py]==' ') {
                        _map[x][y]=' ';
                        x=px-1;
                        y=py;
                        _map[x][y]='Z';
                    }
                } else if (job==2) {//左边
                    if (_map[px][py-1]==' ') {
                        _map[x][y]=' ';
                        x=px;
                        y=py-1;
                        _map[x][y]='Z';
                    }
                } else if (job==3) {//下边
                    if (_map[px+1][py]==' ') {
                        _map[x][y]=' ';
                        x=px+1;
                        y=py;
                        _map[x][y]='Z';
                    }
                } else if (job==4) {//右边
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
            //僵尸攻击机制
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
void count_zombies() {//统计僵尸数量
    z_count=0;
    for (int i=0;i<=MAXN;i++) {//遍历地图每一个点
        for (int j=0;j<=MAXN;j++) {
            if (_map[i][j]=='Z')
                z_count++;
        }
    }
}
void move(int lines) {
    //玩家移动
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
    //这块地方是玩家的攻击机制
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
        //打boss
        if (_map[px-1][py]=='O') {
            if (stone.hurt(px,py)) {
                cout << "你损坏了能源石！\n" << endl;
            }
        }
        if (_map[px][py-1]=='O') {
            if (stone.hurt(px,py)) {
                cout << "你损坏了能源石！\n" << endl;
            }
        }
        if (_map[px+1][py]=='O') {
            if (stone.hurt(px,py)) {
                cout << "你损坏了能源石！\n" << endl;
            }
        }
        if (_map[px][py+1]=='O') {
            if (stone.hurt(px,py)) {
                cout << "你损坏了能源石！\n" << endl;
            }
        }
    }
    system("cls");
    for (int i=0;i<=lines;i++)
        puts(_map[i]);
}
void mode1(int lines) {//多线程式（整合）
    HANDLE hConsole=0;
    SetConsoleTextAttribute(hConsole,7);
    int time=0,num=0;
    cout << "地图初始化..." << endl;
    memcpy(_map,cmap,sizeof(cmap));
    Sleep(100);
    system("cls");
    for (int i=0;i<=9;i++) {
        m[i].m_init(i);
        printf("僵尸初始化: %d/10\n",i+1);
    }
    system("cls");
    cout << "能源石初始化中..." << endl;
    stone.init();
    Sleep(100);
    system("cls");
    cout << "玩家初始化..." << endl;
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
    while(true){//游戏主循环
        //成功将华山抡剑的程序移植到此！
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
		printf("生存时间：%d\n",num);
		printf("你的血量: %d\n",health);
		printf("能源石生命：%d\n",stone.durable);
		printf("剩余僵尸数量：%d\n",z_count);
		Sleep(50);
		time++;
		if (health<=0) {
		    system("color c4");
            printf("你失败了！");
            Sleep(2000);
            return;
		}
		if (is_win()) {
            cout << "你胜利了！";
            Sleep(2000);
            return;
		}
		if (stone.durable<=0) {//如果能源石被破坏
		    system("cls");//清屏
		    _map[stone.x][stone.y]=' ';//清除能源石
		    for (int i=0;i<=lines;i++)
                puts(_map[i]);
            cout << "你胜利了！";
            Sleep(2000);
            return;
		}
    }
    return;
}