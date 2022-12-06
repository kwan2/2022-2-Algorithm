#include <iostream>
#include <queue>
#include <vector>
#include "Map.h"
#include "Objects.h"
using namespace std;

typedef struct Pos{
    int x;
    int y;
    int f; // g+h
    int g; // 출발지에서부터의 거리
    int h; // 도착지까지의 휴리스틱
} pos;

int heuristic(Pos a, Pos b){ // Manhattan distance로 휴리스틱 계산
    return abs(a.x-b.x)+abs(a.y-b.y);
}

struct compare{ // 우선순위 큐 f값으로 정렬해주기 위한 compare 비교자
    bool operator()(const Pos& p1, const Pos& p2){// bool 값으로 f값을 비교
        if(p1.f != p2.f) return p1.f>p2.f;
        return p1.f > p2.f;
    }
};

int main(){
    int deltaX[4] = {-1, 0, 1, 0};
    int deltaY[4] = {0, -1, 0, 1}; // 상,좌,하,우 탐색용

    int side, src, dest, midcamp_num;
    int *mid_camp = new int[midcamp_num];
    cout << "------------------------------------------------- 입력 ---------------------------------------------"<< endl;
    cout << "                                                진영 선택                                            " << endl;
    cout << "                                        1: 블루 진영 2: 레드 진영 > ";
    cin >> side;
    cout << "                                                                                                  "<< endl;
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
    for (int i = 0; i < midcamp_num; i++) {
        cout << "                                           들려야할 캠프 > ";
        cin >> mid_camp[i];
    }
    cout <<endl<<"————————————————————— 초기맵 출력 ———————————————————————" << endl;
    for(int i=0; i<50; i++){
        for(int j=0; j<50; j++){
            if(map[i][j] == '1') cout<<"■ ";
            else if(map[i][j] == '*') cout<<"* ";
            else cout<<"  ";
        }
        cout<<endl;
    }

    Pos start; // 스타트 위치 지정
    if(side==1){
        if(src==1){ start.x = 37; start.y = 25;}
        else if(src==2){ start.x = 31; start.y = 21;}
        else if(src==3){ start.x = 43; start.y = 28;}
        else if(src==4){ start.x = 23; start.y = 13;}
        else if(src==5){ start.x = 29; start.y = 11;}
        else if(src==6){ start.x = 22; start.y = 4;}
    } else if(side==2){
        if(src==1){ start.x = 12; start.y = 24;}
        else if(src==2){ start.x = 18; start.y = 28;}
        else if(src==3){ start.x = 6; start.y = 21;}
        else if(src==4){ start.x = 26; start.y = 36;}
        else if(src==5){ start.x = 20; start.y = 38;}
        else if(src==6){ start.x = 27; start.y = 45;}
    }

    Pos end; // 도착 위지 지정
    if(dest==1){ end.x = 2; end.y = 2;}
    else if(dest==2){ end.x = 24; end.y = 24;}
    else if(dest==3){ end.x=46; end.y = 46;}

    int trial = 0; // 반복 횟수 출력용!

    // 반복!!
    for(int i=0; i<=midcamp_num; i++){
        Pos from, internalDest;
        if(trial == 0) from = start;
        trial++;
        from.g = 0; // 출발지 g 초기화
        if(trial==midcamp_num+1) internalDest = end; // 마지막은 마지막 정글 캠프에서 도착 라인까지
        else{
            if(side==1){
                if(mid_camp[i] == 1){ internalDest.x = 37; internalDest.y = 25;}
                else if(mid_camp[i]==2){ internalDest.x = 31; internalDest.y = 21;}
                else if(mid_camp[i]==3){ internalDest.x = 43; internalDest.y = 28;}
                else if(mid_camp[i]==4){ internalDest.x = 23; internalDest.y = 13;}
                else if(mid_camp[i]==5){ internalDest.x = 29; internalDest.y = 11;}
                else if(mid_camp[i]==6){ internalDest.x = 22; internalDest.y = 4;}
            } else if(mid_camp[i]==2){
                if(mid_camp[i]==1){ internalDest.x = 12; internalDest.y = 24;}
                else if(mid_camp[i]==2){ internalDest.x = 18; internalDest.y = 28;}
                else if(mid_camp[i]==3){ internalDest.x = 6; internalDest.y = 21;}
                else if(mid_camp[i]==4){ internalDest.x = 26; internalDest.y = 36;}
                else if(mid_camp[i]==5){ internalDest.x = 20; internalDest.y = 38;}
                else if(mid_camp[i]==6){ internalDest.x = 27; internalDest.y = 45;}
            }
        }

        priority_queue<Pos, vector<Pos>, compare> pq; // 우선순위 큐 사용
        int isVisited[50][50] = {false,}; // 방문 체크 배열 초기화
        int parentX[50][50] = {0, };
        int parentY[50][50] = {0, }; // 부모 정보 담는 배열 초기화

        pq.push(from); // 시작위치 우선순위 큐에 삽입

        while(!pq.empty()){ // 우선순위 큐 비기 전까지(도착)
            Pos now = pq.top(); // 우선순위 큐 맨 앞 위치 pop 하고 now 객체에 담아줌.
            pq.pop();

            if(isVisited[now.x][now.y]) continue; // 이미 방문 했던 곳이라면 다음 탐색
            isVisited[now.x][now.y] = true; // 현재 방문 위치 방문했다 표기

            if(now.x == internalDest.x && now.y == internalDest.y){ // 도착하면 break
                break;
            }

            for(int i=0; i<4; i++){ // 4방향 탐색
                Pos next;
                next.x=now.x+deltaX[i]; next.y=now.y+deltaY[i]; // next 객체 초기화
                next.g = now.g + 1;
                next.h = heuristic(next, internalDest); // 휴리스틱 값 계산
                next.f = next.g + next.h;

                if((!isVisited[next.x][next.y]) && map[next.x][next.y] != '1'){ // 방문하지 않았고, 벽이 아니라면
                    parentX[next.x][next.y] = now.x; parentY[next.x][next.y] = now.y; // 부모 정보 담아주기
                    pq.push(next); // 우선순위 큐에 삽입
                }
            }
        }

        // 이제 부모 정보 따라서 backtracking
        vector<pair<int, int>> v; // vector에 pair로 담아서 관리
        int ex = internalDest.x, ey = internalDest.y;
        v.push_back(make_pair(ex,ey)); // 벡터에 도착지 담음.

        map[internalDest.x][internalDest.y] = '*'; // 경로 표시
        while(true){ // backtracking하며 경로 넣어주기
            int px = parentX[v[0].first][v[0].second], py = parentY[v[0].first][v[0].second]; // 부모 정보 가져와서
            map[px][py] = '*'; // 경로 표시
            if(px == from.x && py == from.y) break; // 출발지 까지 오면 종료
            else{
                v.clear(); // 벡터 초기화
                v.push_back(make_pair(px, py)); // 부모 위치 벡터에 담아줌
            }
        }
        cout<<"start"<<endl; // 맵 출력하기
        for(int i=0; i<50; i++){
            for(int j=0; j<50; j++){
                if(map[i][j] == '1') cout<<"■ ";
                else if(map[i][j] == '*') cout<<"* ";
                else cout<<"  ";
            }
            cout<<endl;
        }

        from = internalDest; // 출발지를 현재 목적지로 바꿔주기
    }
}