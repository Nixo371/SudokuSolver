#include "profiler.hpp"
#include <unordered_map>

void Profiler::reset_function_times() {
	this->function_times.clear();
}

std::unordered_map<std::string, double> Profiler::get_function_times() {
	return (this->function_times);
};
