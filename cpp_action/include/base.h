#ifndef INCLUDE_BASE_H_
#define INCLUDE_BASE_H_

#include <iostream>
#include <chrono>
#include <vector>
#include <string>

class TimeDuration {
public:
	//TimeDuration(std::string &task_name) {
	//	start_time_ = std::chrono::system_clock::now();
	//	task_ = task_name;
	//}

	TimeDuration(const char*task_name) {
		start_time_ = std::chrono::system_clock::now();
		task_ = task_name;
	}

	~TimeDuration() {
		end_time_ = std::chrono::system_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time_ - start_time_).count();
		std::cout << "[Task]:" << task_ << "  [Time cost]: " << duration << "/ms" << std::endl;
	}
private:
	//std::string task_;
	const char* task_;
	std::chrono::system_clock::time_point start_time_;
	std::chrono::system_clock::time_point end_time_;
};

class StartEndLine {
public:
	StartEndLine(const char*task_name) {
		task_ = task_name;
		std::cout << "\n-------------------[" << task_ << "]-------------------(Start)" << std::endl;
	}

	~StartEndLine() {
		std::cout << "-------------------[" << task_ << "]-------------------(End)\n" << std::endl;
	}
private:
	const char* task_;
};



#endif // !INCLUDE_BASE_H_
