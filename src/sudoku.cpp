#include "sudoku.hpp"

#include <iostream>

bool Sudoku::check_row(int row) const {
	std::vector<bool> found = std::vector<bool>(9, false);

	for (int column = 0; column < 9; column++) {
		int value = this->get_tile(row, column)->get_value();
		if (value == 0)
			continue;

		if (found[value - 1] == true) {
			// Already in the same row
			return (false);
		}
		found[value - 1] = true;
	}

	return (true);
}

bool Sudoku::check_column(int column) const {
	std::vector<bool> found = std::vector<bool>(9, false);

	for (int row = 0; row < 9; row++) {
		
		int value = this->get_tile(row, column)->get_value();
		if (value == 0)
			continue;

		if (found[value - 1] == true) {
			// Already in the same column
			return (false);
		}
		found[value - 1] = true;
	}

	return (true);
}

bool Sudoku::check_region(int region_row, int region_column) const {
	std::vector<bool> found = std::vector<bool>(9, false);

	for (int row = 0; row < 3; row++) {
		for (int column = 0; column < 3; column++) {
			Tile* tile = this->get_tile((region_row * 3) + row, (region_column * 3) + column);
			
			int value = tile->get_value();
			if (value == 0)
				continue;

			if (found[value - 1] == true) {
				// Already in the same column
				return (false);
			}
			found[value - 1] = true;
		}
	}

	return (true);
}

Sudoku::Sudoku() {
	this->initialize_board();
}

Sudoku::Sudoku(std::string board) {
	this->initialize_board();
	this->load_board(board);
}

void Sudoku::initialize_board() {
	this->board = std::vector<std::vector<Tile*>>(9);
	for (int row = 0; row < 9; row++) {
		this->board.at(row) = std::vector<Tile*>(9);
		for (int column = 0; column < 9; column++) {
			this->board.at(row).at(column) = new Tile();
		}
	}
}

void Sudoku::load_board(std::string board) {
	size_t i = 0;

	for (int row = 0; row < 9; row++) {
		for (int column = 0; column < 9; column++) {
			Tile* tile = this->board.at(row).at(column);
			char c = board.at(i);
			if (c != '.') {
				tile->set_value(c - '0');
				tile->set_fixed(true);
				tile->set_possibilities(std::unordered_set<int>());
			}
			i++;
		}
	}
}

Tile* Sudoku::get_tile(int row, int column) const {
	return (this->board.at(row).at(column));
}

bool Sudoku::check_valid(int row, int column) {
	// Check row
	if (this->check_row(row) == false) {
		return (false);
	}

	// Check column
	if (this->check_column(column) == false) {
		return (false);
	}

	// Check region
	int region_row = row / 3;
	int region_column = column / 3;
	if (this->check_region(region_row, region_column) == false) {
		return (false);
	}

	return (true);
}

bool Sudoku::solve_backtracking(int row, int column, bool debug) {
	while (column >= 9) {
		column -= 9;
		row++;
	}

	if (row >= 9) {
		return (true);
	}
	
	if (debug) {
		this->print_board();
	}

	Tile* tile = this->get_tile(row, column);

	if (tile->get_fixed() == true) {
		return (solve_backtracking(row, column + 1, debug));
	}

	// Backtracking time
	for (int value = 1; value <= 9; value++) {
		tile->set_value(value);
		auto check_valid = [&]() -> bool {
			return (this->check_valid(row, column));
		};
		bool is_valid = this->profiler.time_function("check_valid", check_valid);
		if (is_valid == false) {
			tile->set_value(0);
			continue;
		}

		bool backtracking = solve_backtracking(row, column + 1, debug);

		if (backtracking == true) {
			return (true);
		}
	}

	tile->set_value(0);
	return (false);
}

void Sudoku::print_board() const {
	std::cout << "\033[2J\033[H";
	std::cout << "-------------------------------" << std::endl;
	for (int row = 0; row < 9; row++) {
		std::cout << "|";
		for (int column = 0; column < 9; column++) {
			Tile* tile = this->get_tile(row, column);
			std::cout << " ";
			if (tile->get_value() == 0) {
				std::cout << " ";
			}
			else {
				std::cout << tile->get_value();
			}
			std::cout << " ";
			if ((column + 1) % 3 == 0) {
				std::cout << "|";
			}

		}
		std::cout << std::endl;
		if ((row + 1) % 3 == 0) {
			std::cout << "-------------------------------" << std::endl;
		}
	}
}

std::ostream& operator<< (std::ostream& out, const Sudoku& sudoku) {
	sudoku.print_board();

	return (out);
}
