#ifndef UNTITLED_OBJECTS_H
#define UNTITLED_OBJECTS_H
#include <iostream>

typedef struct object {
    int x;
    int y;
} Object;

Object b_golem = {43, 28};
Object b_blue = {23, 13};
Object b_red = {37, 25};
Object b_wolf = {29, 11};
Object b_raptor = {31, 21};
Object b_toad = {22, 4};

Object r_golem = {6, 21};
Object r_blue = {26, 36};
Object r_red = {12, 24};
Object r_wolf = {20, 38};
Object r_raptor = {18, 28};
Object r_toad = {27, 45};

Object b_top = { 1, 9 };
Object r_top = { 9, 1 };
Object b_bottom = { 38, 48 };
Object mid ={25,25};
Object r_bottom = { 48, 38 };
Object objArr[2][6]={
        {b_red,b_raptor,b_golem,b_blue,b_wolf,b_toad},
        {r_red,r_raptor,r_golem,r_blue,r_wolf,r_toad}
};

Object line[2][3] = {{b_top,mid,b_bottom},{r_top,mid,r_bottom}};

#endif //UNTITLED_OBJECTS_H