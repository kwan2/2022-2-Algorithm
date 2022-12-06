#include <iostream>
#include <vector>
#include <queue>
#include "Map.h"
#include "Objects.h"

using namespace std;

int side, src, dest, midcamp_num, start_x, start_y, end_x, end_y;
int *mid_camp = new int[midcamp_num];

vector<int> x; // 시작 지점부터 도착 지점까지의 x 좌표를 담아두기 위한 벡터
vector<int> y; // 시작 지점부터 도착 지점까지의 y 좌표를 담아두기 위한 벡터

// 탐색 결과 몇번째만에 가는 것이 가장 좋은지 담는 변수
int minCount = 1e9;

void MapRender()
{
    for (int i = 0; i < 50; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            if (map[i][j] == '1')
                cout << "■"
                     << " ";
            else
                cout
                        << " "
                        << " ";
        }
        cout << endl;
    }
}

// 방향
int nx[4] = {1, -1, 0, 0};
int ny[4] = {0, 0, 1, -1};

// 범위를 설정해서 나가면 false 를 반환해줌.
bool checkBoundary(int i, int j, int goalX, int goalY, int x, int y, int bound)
{
    int hx, hy, lx, ly;

    if (i > goalX)
    {
        hx = i;
        lx = goalX;
    }
    else
    {
        hx = goalX;
        lx = i;
    }
    if (j > goalY)
    {
        hy = j;
        ly = goalY;
    }
    else
    {
        hy = goalY;
        ly = j;
    }
    hx += bound;
    lx -= bound;
    hy += bound;
    ly -= bound;

    // 경계 박스가 맵의 크기보다 커지면 49로 설정해서 맵 전체로 만듦.
    if (hx > 49)
        hx = 49;
    if (lx < 0)
        lx = 0;
    if (hy > 49)
        hy = 49;
    if (ly < 0)
        ly = 0;
    if (x < hx && x > lx && y < hy && y > ly)
        return true;
    else
        return false;
}

// ids
void ids(int i, int j, int goalX, int goalY, int bound)
{
    // i : 현재 x좌표 , j : 현재 y좌표 , x1 : 현재 x좌표와 목표 x좌표 중 작은 값
    // -> i: 현재 x 좌표, j : 현재 y좌표 , goalX: 목표 x 좌표, goalY: 목표 y좌표, bound: 범위

    bool visit[50][50]; // 방문했는지 안했는지를 체크
    int start_x = i;    // 시작 지점의 x 좌표
    int start_y = j;    // 시작 지점의 y 좌표

    for (int i = 0; i < 50; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            visit[i][j] = false;
        }
    }

    int cnt = 1;
    queue<pair<int, int>> q; // queue를 생성하여 bfs를 진행.
    visit[i][j] = true;
    bool flag = false; // 만약 다음으로 이동한 지점이 도착 지점이라면 flag를 true로 만들어 while문을 빠져 나옴.
    q.push({i, j});

    while (!q.empty() && !flag)
    {
        int cur_x = q.front().first;  // queue 첫번째 지점의 x 좌표를 현재 좌표로 x 좌표로 설정
        int cur_y = q.front().second; // queue 첫번째 지점의 y 좌표를 현재 좌표의 y 좌표로 설정
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            int next_x = nx[i] + cur_x; // 다음 이동해야할 지점의 x좌표
            int next_y = ny[i] + cur_y; // 다음 이동해야할 지점의 y좌표

            if (!checkBoundary(start_x, start_y, goalX, goalY, next_x, next_y, bound))
                continue; // 경계 박스 내부에 있는 지 체크
            if (visit[next_x][next_y])
                continue; // 방문했다면 넘어감
            if (map[next_x][next_y] == '1')
                continue; // 만약 벽이라면 넘어감.
            else
            {
                visit[next_x][next_y] = true; // 위의 조건을 모두 충족하면 다음 지점을 방문하고 visit = true로 바꿔줌.
                x.push_back(next_x);          // 방문했으니까 벡터에 x 좌표를 넣어줌.
                y.push_back(next_y);          // 방문했으니까 벡터에 y 좌표를 넣어줌.
                if (next_x == goalX && next_y == goalY)
                {
                    // 만약 다음 지점이 목표 지점과 일치하면 flag = true로 바꿔줌.
                    flag = true;
                    if (minCount > cnt)
                    {
                        // 시작지점부터 도착 지점까지 이동한 횟수가 더 적어졌으면 그것으로 바꿔줌.
                        minCount = cnt;
                    }
                    break;
                }
                q.push({next_x, next_y});
                cnt++;
            }
        }
    }
    if (!visit[goalX][goalY])
    {
        // 만약 while문을 빠져나왔는데 목표 지점에 방문하지 않았으면 x,y 벡터를 초기화 해줌.
        x.clear();
        y.clear();
    }
}

int main()
{
    // 입력 받을 변수 명 선언

    cout << "------------------------------------------------- 입력 ---------------------------------------------"
         << endl;
    cout << "                                                진영 선택                                            " << endl;
    cout << "                                        1: 블루 진영 2: 레드 진영 > ";
    cin >> side;
    cout << "                                                                                                  "
         << endl;
    cout << "                                            시작 캠프 위치 설정                                        " << endl;
    cout << "                             1. 레드 2. 칼날부리  3. 작은 골렘  4. 블루  5. 늑대 6. 두꺼비                      " << endl;
    cout << "                                            시작 캠프 설정 > ";
    cin >> src;
    cout << endl;
    cout << "                                              갱킹 위치 정보                                          " << endl;
    cout << "                                          1. 탑 2. 미드 3. 바텀" << endl;
    cout << "                                            도착 위치 설정 > ";
    cin >> dest;
    cout << endl;
    cout << "                                     중간에 먹어야 할 아군 정글 캠프" << endl;
    cout << "                                   몇개의 캠프를 먹을 것인지 선택 하시오 > ";
    cin >> midcamp_num;

    cout << "                             1. 레드 2. 칼날부리 3. 작은 골렘  4. 블루  5. 늑대 6. 두꺼비" << endl;
    for (int i = 0; i < midcamp_num; i++)
    {
        cout << "                                           들려야할 캠프 > ";
        cin >> mid_camp[i];
    }
    cout << endl;
    cout << "————————————————————— 초기맵 출력 ———————————————————————" << endl;
    MapRender();
    cout << "————————————————————————————————————————————————" << endl;

    start_x = objArr[side - 1][src - 1].x;
    start_y = objArr[side - 1][src - 1].y;

    end_x = line[side - 1][dest - 1].x;
    end_y = line[side - 1][dest - 1].y;

    int path[midcamp_num][2];

    for (int i = 0; i < midcamp_num; i++)
    {
        path[i][0] = objArr[side - 1][mid_camp[i] - 1].x;
        path[i][1] = objArr[side - 1][mid_camp[i] - 1].y;
    }

    // 첫 시작 지점
    if (midcamp_num == 0)
    {
        for (int bound = 0; bound < 50; bound++)
            ids(start_x, start_y, end_x, end_y, bound);
        for (int i = 0; i < minCount; i++)
            map[x[i]][y[i]] = '0';
        minCount = 1e9;
        x.clear();
        y.clear();
    }
    else
    {
        for (int bound = 0; bound < 50; bound++)
            ids(start_x, start_y, path[0][0], path[0][1], bound);
        for (int i = 0; i < minCount; i++)
            map[x[i]][y[i]] = '0';
        minCount = 1e9;
        x.clear();
        y.clear();
    }

    // 들러야 하는 캠프 사이
    if (midcamp_num != 0)
    {
        for (int i = 0; i < midcamp_num - 1; i++)
        {
            minCount = 1e9;
            x.clear();
            y.clear();
            for (int bound = 0; bound < 50; bound++)
                ids(path[i][0], path[i][1], path[i + 1][0], path[i + 1][1], bound);
            for (int i = 0; i < minCount; i++)
                map[x[i]][y[i]] = '0';
        }

        minCount = 1e9;
        x.clear();
        y.clear();
    }

    // // 마지막 캠프 ~ 도착 지점.
    if (midcamp_num != 0)
    {
        for (int bound = 0; bound < 50; bound++)
            ids(path[midcamp_num - 1][0], path[midcamp_num - 1][1], end_x, end_y, bound);
        for (int i = 0; i < minCount; i++)
            map[x[i]][y[i]] = '0';
    }

    // 맵 출력
    for (int i = 0; i < 50; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            if (map[i][j] == '1')
                cout << "■"
                     << " ";
            else if (map[i][j] == '0')
                cout << "*"
                     << " ";
            else
                cout
                        << " "
                        << " ";
        }
        cout << endl;
    }
}