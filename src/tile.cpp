#include "tile.hpp"

#include <algorithm>

Tile::Tile(int value, bool fixed, std::vector<int> possibilities) {
	this->value = value;
	this->fixed = fixed;
	this->possibilities = possibilities;
}

int Tile::get_value() {
	return (this->value);
}

bool Tile::get_fixed() {
	return (this->fixed);
}

std::vector<int> Tile::get_possibilities() {
	return (this->possibilities);
}

void Tile::set_value(int value) {
	this->value = value;
}

void Tile::set_fixed(bool value) {
	this->fixed = value;
}

void Tile::set_possibilities(std::vector<int> possibilities) {
	this->possibilities = std::vector<int>(possibilities);
}

bool Tile::add_possibility(int value) {
	auto it = std::find(this->possibilities.begin(), this->possibilities.end(), value);
	if (it != this->possibilities.end()) {
		return (false);
	}

	this->possibilities.push_back(value);
	return (true);
}

bool Tile::remove_possibility(int value) {
	auto it = std::find(this->possibilities.begin(), this->possibilities.end(), value);
	if (it == this->possibilities.end()) {
		return (false);
	}

	this->possibilities.erase(it);
	return (true);
}
