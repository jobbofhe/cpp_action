#ifndef MOVE_H_
#define MOVE_H_

#include "base.h"

void MoveRight() {
    int num = 100;
    num = num >> 1;
    std::cout << "result num >> 1: " << num << std::endl;
    // result num >> 1: 50
}

void TestMoveBit() {
    MoveRight();
}

#endif