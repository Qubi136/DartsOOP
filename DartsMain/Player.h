#pragma once
#include <iostream>

using namespace std;

class Player {
	string name;
public:
	Player(string name) {
		this->name = name;
	}
	Player() {
		name = "";
	}
	void setName(string& name) {
		this->name = name;
	}
	string getName() const {
		return name;
	}
};