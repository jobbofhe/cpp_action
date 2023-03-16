#ifndef DESIGN_PATTERN_DCLP_H_
#define DESIGN_PATTERN_DCLP_H_

#include "base.h"

class DclpSingleton {
public:
	static DclpSingleton* GetInstance() {
        if (!instance_) {
            std::lock_guard<std::mutex> _(mtx_);
            if (!instance_) {
                instance_ = new DclpSingleton;
            }
        }
        std::cout << "instance_: " << instance_ << std::endl;
		return instance_;
	}
    DclpSingleton() {}
    DclpSingleton(DclpSingleton&) = delete;
	DclpSingleton& operator=(const DclpSingleton&) = delete;
    
private:
    static DclpSingleton* instance_;
    static std::mutex mtx_;
};

DclpSingleton* DclpSingleton::instance_ = nullptr;
std::mutex DclpSingleton::mtx_;

void ThreadFunc() {
    DclpSingleton* instance = DclpSingleton::GetInstance();
}

void DclpSingletonTest() {
    const int loop = 100;

    std::vector<std::thread> vec_tds;
    for (size_t i = 0; i < loop; ++i) {
        vec_tds.push_back(std::thread(ThreadFunc));
    }

    for (size_t i = 0; i < loop; ++i) {
        vec_tds[i].join();
    }
}

void DclpSingletonTest2() {
    DclpSingleton* instance = DclpSingleton::GetInstance();
    std::cout << "instance: " << instance << std::endl;
}

#endif // DESIGN_PATTERN_DCLP_H_