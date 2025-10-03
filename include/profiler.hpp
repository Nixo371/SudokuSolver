#include "timer.hpp"

#include <string>
#include <unordered_map>

class Profiler {
	private:
		std::unordered_map<std::string, double> function_times;

	public:
		template <typename F>
		auto time_function(std::string key, F function) {
			Timer timer;
			timer.reset();

			auto result = function();

			double time = timer.elapsed();

			if (this->function_times.count(key) == 0) {
				this->function_times[key] = 0.0;
			}
			this->function_times[key] += time;

			return (result);
		};

		/*
		template <typename F>
		void time_function(std::string key, F function){
			Timer timer;
			timer.reset();

			function();

			double time = timer.elapsed();

			if (this->function_times.count(key) == 0) {
				this->function_times[key] = 0.0;
			}
			this->function_times[key] += time;
		};
		*/

		void reset_function_times();
		std::unordered_map<std::string, double> get_function_times();
};
