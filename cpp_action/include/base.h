#ifndef BASE_H_

#include <iostream>
#include <chrono>

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

#endif // !BASE_H_
