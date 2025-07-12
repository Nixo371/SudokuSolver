#include "tile.hpp"
#include "profiler.hpp"

#include <vector>
#include <string>

class Sudoku {
	private:
		std::vector<std::vector<Tile*>> board;

		bool check_row(int row) const;
		bool check_column(int column) const;
		bool check_region(int region_row, int region_column) const;
	
	public:
		Sudoku();
		Sudoku(std::string board);

		Profiler profiler;
		void initialize_board();
		void load_board(std::string board);
		Tile* get_tile(int row, int column) const;

		bool check_valid(int row, int column);

		bool solve_backtracking(int row = 0, int column = 0, bool debug = false);

		void print_board() const;
};

std::ostream& operator<< (std::ostream& out, const Sudoku& sudoku);
