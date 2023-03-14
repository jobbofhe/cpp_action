#ifndef STATIC_STATIC_INIT_TEST_H_
#define STATIC_STATIC_INIT_TEST_H_

#include "base.h"

class StaticInit {
public:
    StaticInit() {};
    int GetNumber() {
        return number_;
    }

    float GetScore() {
        return score_;
    }

private:
    // 除了 int/short 类型的， static const int/short xx 可以被初始化；
    static const int number_ = 0;
    // 其他类型不能初始化
    static const float score_;
};

void StaticInit_Test() {
    StaticInit a;
    std::cout << a.GetNumber() << std::endl;
}

#endif