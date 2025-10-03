#include <vector>

class Tile {
	private:
		int value;
		bool fixed;
		std::vector<int> possibilities;
	
	public:
		Tile(int value = 0, bool fixed = false, std::vector<int> possibilities = std::vector<int>({1, 2, 3, 4, 5, 6, 7, 8, 9}));

		int get_value();
		bool get_fixed();
		std::vector<int> get_possibilities();

		void set_value(int value);
		void set_fixed(bool value);
		void set_possibilities(std::vector<int> possibilities);
		bool add_possibility(int value);
		bool remove_possibility(int value);
};
