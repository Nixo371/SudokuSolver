#include <unordered_set>

class Tile {
	private:
		int value;
		bool fixed;
		std::unordered_set<int> possibilities;

		int times_visited;
	
	public:
		Tile(int value = 0, bool fixed = false, std::unordered_set<int> possibilities = std::unordered_set<int>({1, 2, 3, 4, 5, 6, 7, 8, 9}));

		int get_value();
		bool get_fixed();
		std::unordered_set<int> get_possibilities();

		void set_value(int value);
		void set_fixed(bool value);
		void set_possibilities(std::unordered_set<int> possibilities);
		bool add_possibility(int value);
		bool remove_possibility(int value);
		bool visit();
};
