#include "tile.hpp"

#include <unordered_set>

Tile::Tile(int value, bool fixed, std::unordered_set<int> possibilities) {
	this->value = value;
	this->fixed = fixed;
	this->possibilities = possibilities;
	this->times_visited = 0;
}

int Tile::get_value() {
	return (this->value);
}

bool Tile::get_fixed() {
	return (this->fixed);
}

std::unordered_set<int> Tile::get_possibilities() {
	return (std::unordered_set<int>(this->possibilities));
}

void Tile::set_value(int value) {
	this->value = value;
}

void Tile::set_fixed(bool value) {
	this->fixed = value;
}

void Tile::set_possibilities(std::unordered_set<int> possibilities) {
	this->possibilities = std::unordered_set<int>(possibilities);
}

bool Tile::add_possibility(int value) {
	bool result = this->possibilities.insert(value).second;
	return (result);
}

bool Tile::remove_possibility(int value) {
	// # of elements removed (1 or 0)
	int result = this->possibilities.erase(value);

	return (result);
}

bool Tile::visit() {
	this->times_visited++;

	return (this->times_visited <= 1);
}
