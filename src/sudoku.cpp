#include "sudoku.hpp"

#include <cstddef>
#include <iostream>
#include <sstream>

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

// Add a possibility in all cells of a row
void Sudoku::add_possibility_row(int row, int column, int value) {
	for (int column_ = 0; column_ < 9; column_++) {
		if (column_ == column) {
			continue;
		}
		Tile* tile = this->board.at(row).at(column_);
		tile->add_possibility(value);
	}
}

// Add a possibility in all cells of a column
void Sudoku::add_possibility_column(int row, int column, int value) {
	for (int row_ = 0; row_ < 9; row_++) {
		if (row_ == row) {
			continue;
		}
		Tile* tile = this->board.at(row_).at(column);
		tile->add_possibility(value);
	}
}

// Add a possibility in all cells of a region
void Sudoku::add_possibility_region(int row, int column, int value) {
	// 3 x 3
	int region_row = row / 3;
	int region_column = column / 3;

	int start_row = region_row * 3;
	int end_row = start_row + 3;
	int start_column = region_column * 3;
	int end_column = start_column + 3;

	for (int row_ = start_row; row_ < end_row; row_++) {
		for (int column_ = start_column; column_ < end_column; column_++) {
			if (row_ == row && column_ == column) {
				continue;
			}
			Tile* tile = this->board.at(row_).at(column_);
			tile->add_possibility(value);
		}
	}
}

// Remove a possibility in all cells of a row
void Sudoku::remove_possibility_row(int row, int column, int value) {
	for (int column_ = 0; column_ < 9; column_++) {
		if (column_ == column) {
			continue;
		}
		Tile* tile = this->board.at(row).at(column_);
		tile->remove_possibility(value);
	}
}

// Remove a possibility in all cells of a column
void Sudoku::remove_possibility_column(int row, int column, int value) {
	for (int row_ = 0; row_ < 9; row_++) {
		if (row_ == row) {
			continue;
		}
		Tile* tile = this->board.at(row_).at(column);
		tile->remove_possibility(value);
	}
}

// Remove a possibility in all cells of a region
void Sudoku::remove_possibility_region(int row, int column, int value) {
	// 3 x 3
	int region_row = row / 3;
	int region_column = column / 3;

	int start_row = region_row * 3;
	int end_row = start_row + 3;
	int start_column = region_column * 3;
	int end_column = start_column + 3;

	for (int row_ = start_row; row_ < end_row; row_++) {
		for (int column_ = start_column; column_ < end_column; column_++) {
			if (row_ == row && column_ == column) {
				continue;
			}
			Tile* tile = this->board.at(row_).at(column_);
			tile->remove_possibility(value);
		}
	}
}

void Sudoku::trim_possibilities() {
	for (int row = 0; row < 9; row++) {
		for (int column = 0; column < 9; column++) {
			Tile* tile = this->board.at(row).at(column);
			if (tile->get_value() == 0) {
				continue;
			}
			this->remove_possibility_row(row, column, tile->get_value());
			this->remove_possibility_column(row, column, tile->get_value());
			this->remove_possibility_region(row, column, tile->get_value());
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
				tile->set_possibilities(std::vector<int>());
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
		std::cout << "\033[2J\033[H"; // clear the screen
		std::cout << this->print_board() << std::endl;
	}

	Tile* tile = this->get_tile(row, column);

	if (tile->get_fixed() == true) {
		return (solve_backtracking(row, column + 1, debug));
	}

	// Backtracking time
	// This is a copy because we may edit the vector in the future tiles, but we don't want it to change unless we go back before this tile
	std::vector<int> possibilities = std::vector<int>(tile->get_possibilities());
	for (size_t i = 0; i < possibilities.size(); i++) {
		int value = possibilities.at(i);
		tile->set_value(value);
		auto check_valid = [&]() -> bool {
			return (this->check_valid(row, column));
		};
		bool is_valid = this->profiler.time_function("check_valid", check_valid);
		if (is_valid == false) {
			tile->set_value(0);
			continue;
		}
		
		this->remove_possibility_row(row, column, value);
		this->remove_possibility_column(row, column, value);
		this->remove_possibility_region(row, column, value);
		bool backtracking = solve_backtracking(row, column + 1, debug);

		if (backtracking == true) {
			return (true);
		}

		this->add_possibility_row(row, column, value);
		this->add_possibility_column(row, column, value);
		this->add_possibility_region(row, column, value);
	}

	tile->set_value(0);
	return (false);
}

std::string Sudoku::print_board() const {
	std::stringstream ss;

	ss << "-------------------------------" << std::endl;
	for (int row = 0; row < 9; row++) {
		ss << "|";
		for (int column = 0; column < 9; column++) {
			Tile* tile = this->get_tile(row, column);
			ss << " ";
			if (tile->get_value() == 0) {
				ss << " ";
			}
			else {
				ss << tile->get_value();
			}
			ss << " ";
			if ((column + 1) % 3 == 0) {
				ss << "|";
			}

		}
		ss << std::endl;
		if ((row + 1) % 3 == 0) {
			ss << "-------------------------------" << std::endl;
		}
	}

	return ss.str();
}

std::ostream& operator<< (std::ostream& out, const Sudoku& sudoku) {
	out << sudoku.print_board();

	return (out);
}
