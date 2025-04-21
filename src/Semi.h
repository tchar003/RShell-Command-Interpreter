#ifndef __SEMI_H__
#define __SEMI_H__

#include "Base.h"

class Semi : public Base {
public:
	Semi() {
		left = nullptr;
		right = nullptr;
	}

	~Semi() {
		left = nullptr;
		right = nullptr;
	}

	// Executes the left command and then the right command
	bool execute() {
		if (!right) {
			return left->execute();
		} else {
			left->execute();
			return right->execute();
		}
	}

	// Prints the representation of the Semi operator
	std::string print() {
		if (!left || !right) {
			return ";";
		}
		return left->print() + ";" + right->print();
	}

	// Checks if the left command failed
	bool failed() {
		return left->failed();
	}

	// Returns the type of the operator
	std::string type() {
		return "Operator";
	}

	// Adds a left operand
	void addLeft(std::shared_ptr<Base> lhs) {
		left = lhs;
	}

	// Adds a right operand
	void addRight(std::shared_ptr<Base> rhs) {
		right = rhs;
	}

private:
	std::shared_ptr<Base> left;
	std::shared_ptr<Base> right;
};

#endif
