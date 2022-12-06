#include <iostream>
#include <stdio.h>
//#include <malloc.h>
#include <stdlib.h>
#include <time.h>
//#include <Windows.h>
#include "Objects.h"

#define C_RED  "\033[31m"
#define C_NRML "\033[0m"
#define C_AQUA "\033[36m"

using namespace std;

typedef struct {
    //the coordinate consists of x, y, and the number of iteration
    //for example (2,3,0)
    int c[4];
} coordinate;

typedef struct elmt* address;

typedef struct elmt
{
    coordinate cord;
    address prev;
    address next;
} element;

//create the list
typedef struct
{
    //the list itself hold the first and the last element
    element* first;
    element* tail;
} list;

void createList(list* L) {
    (*L).first = NULL;
    (*L).tail = NULL;
}

void addFirst(list* L, int x, int y, int i) {
    element* node = (element*)malloc(sizeof(element));

    //add the data
    node->cord.c[0] = x;
    node->cord.c[1] = y;
    node->cord.c[2] = i;

    if ((*L).first == NULL) {
        (*L).first = node;
        (*L).tail = node;
        node->next = NULL;
        node->prev = NULL;
    }
    else {
        node->next = (*L).first;
        (*L).first->prev = node;
        (*L).first = node;
        node->prev = NULL;
    }
}

void addLast(list* L, int x, int y, int i) {

    if ((*L).first == NULL) {
        addFirst(L, x, y, i);
    }
    else {
        element* node = (element*)malloc(sizeof(element));

        //add the data
        node->cord.c[0] = x;
        node->cord.c[1] = y;
        node->cord.c[2] = i;

        //add the node element
        (*L).tail->next = node;
        node->prev = (*L).tail;
        (*L).tail = node;
        node->next = NULL;
    }

}

void delNow(list* L, element* now) {
    //if the last element
    if (now == (*L).first && now == (*L).tail) {
        (*L).first = NULL;
        (*L).tail = NULL;
        free(now);
        //if the first element
    }
    else if (now == (*L).first) {
        (*L).first = now->next;
        (*L).first->prev = NULL;
        now->next = NULL;

        free(now);
        //if the tail element
    }
    else if (now == (*L).tail) {
        (*L).tail = now->prev;
        (*L).tail->next = NULL;
        now->prev = NULL;

        free(now);
        //if at the middle
    }
    else {
        now->prev->next = now->next;
        now->next->prev = now->prev;
        now->next = NULL;
        now->prev = NULL;
        free(now);
    }
}


void printElements(list L) {
    element* now = L.first;

    while (now != NULL) {
        printf("x: %d, y: %d, i: %d\n", now->cord.c[0], now->cord.c[1], now->cord.c[2]);
        now = now->next;
    }
}

//this function return 1 if the path is in the list
int checkPathExist(list L, int x, int y) {
    element* now = L.first;
    int exist = 0;

    while (now != NULL && exist == 0) {
        if (now->cord.c[0] == x && now->cord.c[1] == y) {
            exist = 1;
        }
        now = now->next;
    }

    return exist;
}

//return the number of iteration hold by the node
int returnIteration(list L, int x, int y) {
    element* now = L.first;
    int iteration = 0;
    int found = 0;
    while (now != NULL && found == 0) {
        if (now->cord.c[0] == x && now->cord.c[1] == y) {
            found = 1;
            iteration = now->cord.c[2];
        }
        now = now->next;
    }

    return iteration;
}

int main() {
    //intialize the map

    //0 = free
    //1 = wall
    //2 = start
    //3 = end
    int arr[50][50] = {
            {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
            {'1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1'},
            {'1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1'},
            {'1', ' ', ' ', ' ', ' ', '1', '1', ' ', ' ', '1', '1', '1', '1', '1', '1', ' ', ' ', '1', '1', '1', '1', '1', '1', '1', ' ', ' ', '1', '1', '1', '1', '1', '1', ' ', ' ', '1', '1', ' ', ' ', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1'},
            {'1', ' ', ' ', ' ', ' ', ' ', '1', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1', '1', '1', '1', '1', '1', ' ', ' ', '1', '1', '1', ' ', ' ', ' ', ' ', '3', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1'},
            {'1', ' ', ' ', '1', ' ', ' ', ' ', '1', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1', '1', '1', '1', ' ', ' ', '1', '1', '1', '1', ' ', ' ', ' ', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1'},
            {'1', ' ', ' ', '1', '1', ' ', ' ', ' ', '1', '1', ' ', ' ', '1', '1', '1', '1', '1', '1', '1', '1', '1', ' ', ' ', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1', '1', '1', ' ', ' ', ' ', ' ', ' ', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1'},
            {'1', ' ', ' ', '1', '1', '1', ' ', ' ', ' ', '1', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1', '1', '1', '1', '1', '1', '1', '1', ' ', ' ', ' ', '0', ' ', ' ', ' ', '1', '1', ' ', ' ', ' ', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1'},
            {'1', ' ', ' ', '1', '1', '1', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1', ' ', ' ', ' ', ' ', ' ', '1', '1', '1', ' ', ' ', ' ', '1', ' ', '3', ' ', ' ', ' ', '1'},
            {'1', ' ', ' ', '1', ' ', '2', '1', '1', ' ', ' ', ' ', ' ', '1', '1', '1', '1', '1', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1', '1', '1', '1', ' ', ' ', ' ', '1', '1', '1', '1', ' ', ' ', ' ', ' ', ' ', '1', ' ', ' ', ' ', ' ', '1'},
            {'1', ' ', ' ', '1', ' ', ' ', ' ', '1', '1', ' ', ' ', ' ', '1', '1', ' ', ' ', ' ', '1', '2', '0', ' ', '1', '1', '1', '1', ' ', ' ', ' ', ' ', '1', '1', '1', ' ', ' ', '1', '1', '1', '1', ' ', ' ', ' ', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1'},
            {'1', ' ', ' ', ' ', ' ', '1', ' ', ' ', '1', '1', ' ', ' ', ' ', '1', ' ', ' ', ' ', '1', ' ', ' ', ' ', '1', '1', '1', ' ', ' ', ' ', ' ', ' ', '1', '1', '1', ' ', ' ', '1', '1', '1', ' ', ' ', ' ', '1', '1', '1', ' ', ' ', ' ', '1', ' ', ' ', '1'},
            {'1', ' ', ' ', ' ', ' ', ' ', '1', ' ', ' ', ' ', '1', ' ', ' ', ' ', ' ', ' ', ' ', '1', '1', ' ', ' ', '1', '1', '1', ' ', ' ', '1', ' ', ' ', '1', '1', '1', ' ', ' ', '1', '1', ' ', ' ', ' ', '1', '1', '1', '1', ' ', ' ', ' ', ' ', ' ', ' ', '1'},
            {'1', ' ', ' ', '1', ' ', ' ', '1', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1', '1', '1', '1', ' ', ' ', ' ', '1', '1', '1', '1', '1', ' ', ' ', '1', '1', ' ', ' ', ' ', '1', ' ', ' ', ' ', '1', '1', '1', '1', '1', ' ', ' ', '1', ' ', ' ', ' ', '1'},
            {'1', ' ', ' ', '1', ' ', ' ', '1', '1', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1', '1', '1', '1', ' ', ' ', '1', '1', '1', '1', '1', ' ', ' ', ' ', ' ', ' ', ' ', '1', ' ', ' ', ' ', '1', '1', '1', '1', '1', '1', '2', ' ', '1', '1', ' ', ' ', '1'},
            {'1', ' ', ' ', '1', ' ', ' ', '1', '1', '1', ' ', ' ', ' ', '1', '1', ' ', ' ', ' ', '1', '1', '1', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1', ' ', ' ', ' ', ' ', ' ', '1', '1', '1', '1', '1', '1', '1', '1', ' ', '1', '1', ' ', ' ', '1'},
            {'1', ' ', ' ', '1', ' ', ' ', '1', '1', '1', ' ', ' ', ' ', '1', '1', '1', ' ', ' ', ' ', '1', '1', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1', '1', '1', '1', ' ', ' ', ' ', '1', '1', '1', ' ', ' ', ' ', '1', '1', '1', ' ', '1', '1', ' ', ' ', '1'},
            {'1', ' ', ' ', '1', ' ', ' ', '1', '1', '1', ' ', '0', ' ', '1', '1', '1', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1', '1', ' ', ' ', ' ', '1', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '0', ' ', '1', '1', ' ', '1', '1', ' ', ' ', '1'},
            {'1', ' ', ' ', '1', ' ', ' ', '1', '1', '1', ' ', ' ', '1', '1', '1', '1', '1', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1', '1', ' ', ' ', '1', ' ', ' ', ' ', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1', ' ', '1', '1', ' ', ' ', '1'},
            {'1', ' ', ' ', '1', ' ', ' ', '1', '1', '1', ' ', ' ', '1', '1', '1', '1', '1', ' ', ' ', ' ', ' ', ' ', '1', '1', ' ', ' ', ' ', '1', '1', '1', ' ', ' ', ' ', '1', '1', '1', ' ', ' ', '1', ' ', ' ', ' ', ' ', ' ', '1', ' ', '1', '1', ' ', ' ', '1'},
            {'1', ' ', ' ', '1', ' ', ' ', ' ', '1', '1', ' ', ' ', ' ', '1', '1', '1', '1', ' ', ' ', ' ', ' ', ' ', ' ', '1', '1', ' ', ' ', ' ', '1', ' ', ' ', ' ', '1', '1', '1', '1', ' ', ' ', '1', ' ', ' ', '1', ' ', ' ', '1', ' ', '1', '1', ' ', ' ', '1'},
            {'1', ' ', ' ', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1', ' ', ' ', '1', '1', '1', ' ', ' ', ' ', '1', '1', ' ', ' ', ' ', ' ', ' ', '1', '1', '1', '1', ' ', ' ', ' ', '1', '1', '1', '1', ' ', ' ', '1', ' ', '1', '1', ' ', ' ', '1'},
            {'1', ' ', ' ', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1', ' ', ' ', ' ', ' ', '1', '1', ' ', ' ', ' ', '1', '1', ' ', ' ', ' ', '1', '1', '1', '1', '1', ' ', ' ', ' ', '1', '1', '1', '1', ' ', ' ', ' ', ' ', '1', '1', ' ', ' ', '1'},
            {'1', ' ', ' ', '1', '1', '1', ' ', ' ', ' ', '1', '1', '1', ' ', ' ', '1', ' ', ' ', ' ', ' ', ' ', '1', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1', '1', '1', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1', '1', ' ', ' ', '1'},
            {'1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1', '1', '1', '1', '1', '2', ' ', ' ', '1', ' ', ' ', ' ', '1', '1', ' ', ' ', ' ', ' ', '1', '1', ' ', ' ', '1', '1', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1'},
            {'1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1', '1', '1', ' ', ' ', '1', '1', ' ', ' ', ' ', ' ', '1', '1', ' ', ' ', ' ', '1', ' ', ' ', '2', '1', '1', '1', '1', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1'},
            {'1', ' ', ' ', '1', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1', '1', '1', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1', '1', ' ', ' ', ' ', ' ', ' ', '1', ' ', ' ', '1', '1', '1', ' ', ' ', ' ', '1', '1', '1', ' ', ' ', '1'},
            {'1', ' ', ' ', '1', '1', ' ', ' ', ' ', ' ', '1', '1', '1', '1', ' ', ' ', ' ', '1', '1', '1', '1', '1', ' ', ' ', ' ', '1', '1', ' ', ' ', ' ', '1', '1', ' ', ' ', ' ', ' ', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1', ' ', ' ', '1'},
            {'1', ' ', ' ', '1', '1', ' ', '1', ' ', ' ', '1', '1', '1', '1', ' ', ' ', ' ', '1', '1', '1', '1', ' ', ' ', ' ', ' ', ' ', '1', '1', ' ', ' ', ' ', '1', '1', '1', ' ', ' ', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1', ' ', ' ', '1'},
            {'1', ' ', ' ', '1', '1', ' ', '1', ' ', ' ', '1', ' ', ' ', '1', ' ', ' ', '1', '1', '1', '1', ' ', ' ', ' ', '1', ' ', ' ', ' ', '1', '1', ' ', ' ', ' ', ' ', ' ', ' ', '1', '1', '1', '1', ' ', ' ', ' ', '1', '1', ' ', ' ', ' ', '1', ' ', ' ', '1'},
            {'1', ' ', ' ', '1', '1', ' ', '1', ' ', ' ', ' ', ' ', ' ', '1', ' ', ' ', '1', '1', '1', ' ', ' ', ' ', '1', '1', '1', ' ', ' ', ' ', '1', '1', ' ', ' ', ' ', ' ', ' ', '1', '1', '1', '1', '1', ' ', ' ', '1', '1', '1', ' ', ' ', '1', ' ', ' ', '1'},
            {'1', ' ', ' ', '1', '1', ' ', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1', ' ', ' ', ' ', '1', ' ', ' ', '1', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1', '1', '1', '1', '1', '1', ' ', ' ', '1', '1', '1', ' ', ' ', '1', ' ', ' ', '1'},
            {'1', ' ', ' ', '1', '1', ' ', '1', '1', ' ', '0', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1', '1', ' ', ' ', ' ', '1', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1', '1', '1', '1', ' ', '0', ' ', '1', '1', '1', ' ', ' ', '1', ' ', ' ', '1'},
            {'1', ' ', ' ', '1', '1', ' ', '1', '1', '1', ' ', ' ', ' ', '1', '1', '1', ' ', ' ', ' ', '1', '1', '1', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1', '1', '1', ' ', ' ', ' ', '1', '1', '1', ' ', ' ', ' ', '1', '1', '1', ' ', ' ', '1', ' ', ' ', '1'},
            {'1', ' ', ' ', '1', '1', ' ', '1', '1', '1', '1', '1', '1', '1', '1', ' ', ' ', ' ', ' ', ' ', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1', '1', '1', '1', ' ', ' ', ' ', '1', '1', ' ', ' ', ' ', '1', '1', '1', ' ', ' ', '1', ' ', ' ', '1'},
            {'1', ' ', ' ', '1', '1', ' ', '2', '1', '1', '1', '1', '1', '1', ' ', ' ', ' ', '1', ' ', ' ', ' ', ' ', ' ', ' ', '1', '1', '1', '1', '1', ' ', ' ', '1', '1', '1', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1', '1', '1', ' ', ' ', '1', ' ', ' ', '1'},
            {'1', ' ', ' ', '1', '1', ' ', ' ', '1', '1', '1', '1', '1', ' ', ' ', ' ', '1', ' ', ' ', ' ', '1', '1', ' ', ' ', '1', '1', '1', '1', '1', ' ', ' ', ' ', '1', '1', '1', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1', '1', ' ', ' ', '1', ' ', ' ', '1'},
            {'1', ' ', ' ', ' ', ' ', ' ', ' ', '1', '1', '1', '1', ' ', ' ', ' ', '1', '1', ' ', ' ', '1', '1', '1', ' ', ' ', '1', ' ', ' ', '1', '1', '1', ' ', ' ', '1', '1', ' ', ' ', ' ', ' ', ' ', ' ', '1', ' ', ' ', ' ', '1', ' ', ' ', ' ', ' ', ' ', '1'},
            {'1', ' ', ' ', '1', ' ', ' ', ' ', '1', '1', '1', ' ', ' ', ' ', '1', '1', '1', ' ', ' ', '1', '1', '1', ' ', ' ', ' ', ' ', ' ', '1', '1', '1', ' ', ' ', ' ', '1', ' ', ' ', ' ', '1', ' ', ' ', ' ', '1', '1', ' ', ' ', '1', ' ', ' ', ' ', ' ', '1'},
            {'1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1', ' ', ' ', ' ', '1', '1', '1', '1', ' ', ' ', '1', '1', '1', ' ', ' ', ' ', ' ', '1', '1', '1', '1', ' ', '0', '2', '1', ' ', ' ', ' ', '1', '1', ' ', ' ', ' ', '1', '1', ' ', ' ', ' ', '1', ' ', ' ', '1'},
            {'1', ' ', ' ', ' ', ' ', '1', ' ', ' ', ' ', ' ', ' ', '1', '1', '1', '1', ' ', ' ', ' ', '1', '1', '1', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1', '1', '1', '1', '1', '1', ' ', ' ', ' ', ' ', '1', '1', '2', ' ', '1', ' ', ' ', '1'},
            {'1', ' ', ' ', ' ', '3', ' ', '1', ' ', ' ', ' ', '1', '1', '1', ' ', ' ', ' ', ' ', ' ', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1', '1', '1', '1', ' ', ' ', '1'},
            {'1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1', ' ', ' ', ' ', '1', '1', ' ', ' ', ' ', '0', ' ', ' ', ' ', '1', '1', '1', '1', '1', '1', '1', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1', '1', ' ', ' ', ' ', '1', '1', '1', ' ', ' ', '1'},
            {'1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1', ' ', ' ', ' ', ' ', ' ', '1', '1', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1', ' ', ' ', '1', '1', '1', '1', '1', '1', '1', '1', '1', ' ', ' ', '1', '1', ' ', ' ', ' ', '1', '1', ' ', ' ', '1'},
            {'1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1', ' ', ' ', ' ', '1', '1', '1', '1', ' ', ' ', '1', '1', '1', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1', '1', ' ', ' ', ' ', '1', ' ', ' ', '1'},
            {'1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '3', ' ', ' ', ' ', ' ', '1', '1', '1', ' ', ' ', '1', '1', '1', '1', '1', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1', '1', ' ', ' ', ' ', ' ', ' ', '1'},
            {'1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1', ' ', ' ', '1', '1', ' ', ' ', '1', '1', '1', '1', '1', '1', ' ', ' ', '1', '1', '1', '1', '1', '1', '1', ' ', ' ', '1', '1', '1', '1', '1', '1', ' ', ' ', '1', '1', ' ', ' ', ' ', ' ', '1'},
            {'1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1'},
            {'1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1'},
            {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'} };

    int side, src, dest, midcamp_num;
    cout << "------------------------------------------------- 입력 ---------------------------------------------" << endl;
    cout << "                                                진영 선택                                            " << endl;
    cout << "                                        1: 블루 진영 2: 레드 진영 > "; cin >> side;
    cout << "                                                                                                  " << endl;
    cout << "                                            시작 캠프 위치 설정                                        " << endl;
    cout << "                             1. 레드 2. 칼날부리  3. 작은 골렘  4. 블루  5. 늑대 6. 두꺼비                      " << endl;
    cout << "                                            시작 캠프 설정 > "; cin >> src; cout << endl;
    cout << "                                              갱킹 위치 정보                                          " << endl;
    cout << "                                          1. 탑 2. 미드 3. 바텀" << endl;
    cout << "                                            도착 위치 설정 > "; cin >> dest; cout << endl;
    cout << "                                     중간에 먹어야 할 아군 정글 캠프" << endl;
    cout << "                                   몇개의 캠프를 먹을 것인지 선택 하시오 > "; cin >> midcamp_num;
    int* mid_camp = new int[midcamp_num];
    cout << "                             1. 레드 2. 칼날부리 3. 작은 골렘  4. 블루  5. 늑대 6. 두꺼비" << endl;
    for (int i = 0; i < midcamp_num; i++) {
        cout << "                                           들려야할 캠프 > "; cin >> mid_camp[i];
    }
    cout << endl;
    cout << "————————————————————— 초기맵 출력 ———————————————————————" << endl;
    int map[50][50];
    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 50; j++) {
            if (arr[i][j] == 49) {
                arr[i][j] = 1;
                map[i][j] = 1;
            }
            else {
                arr[i][j] = 0;
                map[i][j] = 0;
            }
        }
    }

    cout << "————————————————————————————————————————————————" << endl;
    int* arr_x = new int[midcamp_num + 2];
    int* arr_y = new int[midcamp_num + 2];

    arr_x[0] = objArr[side - 1][src - 1].y;
    arr_y[0] = objArr[side - 1][src - 1].x;

    for (int i = 1; i < midcamp_num + 1; i++) {
        arr_x[i] = objArr[side - 1][mid_camp[i - 1] - 1].y;
        arr_y[i] = objArr[side - 1][mid_camp[i - 1] - 1].x;
    }
    arr_x[midcamp_num + 1] = line[side-1][dest - 1].y;
    arr_y[midcamp_num + 1] = line[side-1][dest - 1].x;

    map[arr_y[0]][arr_x[0]] = 2;
    map[arr_y[midcamp_num + 1]][arr_x[midcamp_num + 1]] = 3;
    for (int iter = 0; iter < midcamp_num + 1; iter++) {
        list L;
        //initialize the list for the path
        createList(&L);
        //start
        int xstart = arr_x[iter];
        int ystart = arr_y[iter];

        //end
        int xend = arr_x[iter + 1];
        int yend = arr_y[iter + 1];

        //using arr[y][x] because arr[row][column]
        //set the start
        arr[ystart][xstart] = 2;
        //set the end
        arr[yend][xend] = 3;

        int i, j;
        //start from the end

        //add the first element to the list, the end
        //of the path
        addFirst(&L, xend, yend, 0);

        int found = 0;
        int cx = xend;
        int cy = yend;
        int ci = 0;

        element* now = L.first;

        //do the iteration until the first node found
        while (found == 0 && now != NULL) {
            //check the adjacent of four direction not wall
            int nowx = now->cord.c[0];
            int nowy = now->cord.c[1];
            int nowi = now->cord.c[2];

            //check the up
            if (nowx == xstart && nowy - 1 == ystart) {
                found = 1;
                addLast(&L, nowx, nowy - 1, nowi + 1);
            }
            if (found == 0) {
                if (nowy - 1 >= 0) {
                    if (checkPathExist(L, nowx, nowy - 1) == 0) {
                        if (arr[nowy - 1][nowx] != 1) {
                            addLast(&L, nowx, nowy - 1, nowi + 1);
                        }
                    }
                }
            }

            //check the down
            if (nowx == xstart && nowy + 1 == ystart) {
                found = 1;
                addLast(&L, nowx, nowy + 1, nowi + 1);
            }
            if (found == 0) {
                //in here check to 9 because the maximum of the map is 9
                if (nowy + 1 <= 50) {
                    if (checkPathExist(L, nowx, nowy + 1) == 0) {
                        if (arr[nowy + 1][nowx] != 1) {
                            addLast(&L, nowx, nowy + 1, nowi + 1);
                        }
                    }
                }
            }

            //check the left
            if (nowx - 1 == xstart && nowy == ystart) {
                found = 1;
                addLast(&L, nowx - 1, nowy, nowi + 1);
            }
            if (found == 0) {
                if (nowx - 1 >= 0) {
                    if (checkPathExist(L, nowx - 1, nowy) == 0) {
                        if (arr[nowy][nowx - 1] != 1) {
                            addLast(&L, nowx - 1, nowy, nowi + 1);
                        }
                    }
                }
            }

            //check the right
            if (nowx + 1 == xstart && nowy == ystart) {
                found = 1;
                addLast(&L, nowx + 1, nowy, nowi + 1);
            }
            if (found == 0) {
                if (nowx + 1 <= 50) {
                    if (checkPathExist(L, nowx + 1, nowy) == 0) {
                        if (arr[nowy][nowx + 1] != 1) {
                            addLast(&L, nowx + 1, nowy, nowi + 1);
                        }
                    }
                }
            }

            now = now->next;
        }

        //do the next step if there was a solution
        if (found == 1) {
            /*********** FROM START TO END ***********/
            found = 0;

            //create the list that hold the track
            list L2;
            createList(&L2);

            addFirst(&L2, L.tail->cord.c[0], L.tail->cord.c[1], L.tail->cord.c[2]);

            //check from the start to the end to find the short path
            //from the built path and also remove the unnecessary path

            now = L.tail;

            int backX = L.tail->cord.c[0];
            int backY = L.tail->cord.c[1];
            int backI = L.tail->cord.c[2];

            while (found == 0) {
                //the holder of the candidate for the
                int candidateX;
                int candidateY;
                int candidateI;

                //check the adjacent from the last one

                //check the adjacent of four direction not wall and check it's the shortest iteration one

                //check up
                //check whether it's in the list
                if (backY - 1 >= 0) {
                    if (checkPathExist(L, backX, backY - 1) == 1) {

                        if (returnIteration(L, backX, backY - 1) < backI) {
                            candidateX = backX;
                            candidateY = backY - 1;
                            candidateI = returnIteration(L, backX, backY - 1);
                        }

                    }
                }

                //check down
                if (backY + 1 <= 50) {
                    if (checkPathExist(L, backX, backY + 1) == 1) {
                        if (returnIteration(L, backX, backY + 1) < backI) {
                            candidateX = backX;
                            candidateY = backY + 1;
                            candidateI = returnIteration(L, backX, backY + 1);
                        }
                    }
                }

                //check left
                if (backX - 1 >= 0) {
                    if (checkPathExist(L, backX - 1, backY) == 1) {
                        if (returnIteration(L, backX - 1, backY) < backI) {
                            candidateX = backX - 1;
                            candidateY = backY;
                            candidateI = returnIteration(L, backX - 1, backY);
                        }
                    }
                }

                //check right
                if (backX + 1 <= 50) {
                    if (checkPathExist(L, backX + 1, backY) == 1) {
                        if (returnIteration(L, backX + 1, backY) < backI) {
                            candidateX = backX + 1;
                            candidateY = backY;
                            candidateI = returnIteration(L, backX + 1, backY);

                        }
                    }
                }

                addLast(&L2, candidateX, candidateY, candidateI);

                backX = candidateX;
                backY = candidateY;
                backI = candidateI;

                //stop it when reach the end path
                if (backX == xend && backY == yend) {
                    found = 1;
                }

            }
            //draw the path to the map

            element* draw = L2.first;

            while (draw != NULL) {
                if (draw != L2.first && draw != L2.tail) {
                    map[draw->cord.c[1]][draw->cord.c[0]] = 9;
                }

                draw = draw->next;
            }


        }
        else {
            printf("There is no solution\n");
        }
        arr[ystart][xstart] = 1;
        //set the end
        arr[yend][xend] = 1;
    }

    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 50; j++) {
            if (map[i][j] == 9) {
                printf("%s* ", C_RED);
                printf("%s", C_NRML);
            }
            else if (map[i][j] == 0) {
                printf("  ");
            }
            else if (map[i][j] == 2) {
                printf("%sS ", C_AQUA);
                printf("%s", C_NRML);
            }
            else if (map[i][j] == 3) {
                printf("%sF ", C_AQUA);
                printf("%s", C_NRML);
            }
            else {
                printf("%d ", map[i][j]);
            }

        }
        printf("\n");
    }
    return 0;
}