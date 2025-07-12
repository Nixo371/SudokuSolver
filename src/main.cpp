#include "sudoku.hpp"

#include <iostream>
#include <fstream>
#include <ostream>
#include <string>

int main(int argc, char *argv[]) {
	std::ifstream file;
	std::ofstream out_file;
	if (argc < 2) {
		std::cerr << "Incorrect Usage!" << std::endl;
		std::cerr << "./sudoku {file} [file...] [...]" << std::endl;

		return (1);
	}

	Profiler profiler;

	for (int i = 1; i < argc; i++) {
		file.open(argv[i]);
		std::string line;
		std::cout << "Solving '" << argv[1] << "'..." << std::endl;

		int total_puzzles = 0;
		while (std::getline(file, line)) {
			total_puzzles++;
		}
		// Reset to start of file
		file.clear();
		file.seekg(0);

		out_file.open(std::string(argv[i]).append("_out"));
		out_file << "total_time, check_valid" << std::endl;

		int count = 0;

		Timer timer;
		Timer puzzle_timer;
		while (std::getline(file, line)) {
			Sudoku sudoku = Sudoku(line);
			sudoku.profiler.reset_function_times();
			std::cout << sudoku << std::endl;
			std::cout << "Solving puzzle #" << count + 1 << "/" << total_puzzles << std::endl;

			puzzle_timer.reset();
			sudoku.solve_backtracking(0, 0, false);
			double puzzle_time = puzzle_timer.elapsed();
			std::string puzzle_time_str = std::to_string(puzzle_time);

			std::cout << sudoku << std::endl;
			count++;

			out_file << puzzle_time_str << ", " << sudoku.profiler.get_function_times()["check_valid"] << std::endl;
		}
		double time = timer.elapsed();
		std::cout << "Puzzle Count: " << count << std::endl;
		std::cout << "Total Time: " << time << "s" << std::endl;
		std::cout << "Time/Puzzle: " << time / count << "s" << std::endl;
		file.close();
		out_file.close();
	}
}
