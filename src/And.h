#ifndef __AND_H__
#define __AND_H__

#include "Base.h"

class And : public Base {
public:
	And() : left(nullptr), right(nullptr) {}

	~And() {
		left = nullptr;
		right = nullptr;
	}

	bool execute() {
		if (left && right) {
			bool temp = left->execute();
			if (temp) {
				return temp;
			} else {
				return right->execute();
			}
		} else {
			return true;
		}
	}

	std::string print() {
		if (!left || !right) {
			return "&&";
		}
		return left->print() + "&& " + right->print();
	}

	bool failed() {
		return left->failed();
	}

	std::string type() {
		return "Operator";
	}

	void addLeft(std::shared_ptr<Base> lhs) {
		left = lhs;
	}

	void addRight(std::shared_ptr<Base> rhs) {
		right = rhs;
	}

private:
	std::shared_ptr<Base> left;
	std::shared_ptr<Base> right;
};

#endif
