#ifndef __OR_H__
#define __OR_H__

#include "Base.h"

class Or : public Base {
public:
        Or() {}
	~Or() {
		delete[] left;
		left = nullptr;
		delete[] right;
		right = nullptr;
	}
        bool execute() {
		bool temp;
		if (temp = left->execute() ) {
			return right->execute();
		}
		else {return temp;}
	}
        std::string print() {
		if (!left || !right) {return "||";}
		else {
			return left->print() + "|| " + right->print();
		}
	}
        bool failed() {return left->failed();}
	std::string type() {return "Operator";}
	void addLeft(Base* lhs) {left = lhs;}
        void addRight(Base* rhs) {right = rhs;}

private:
	Base* left = nullptr;
	Base* right = nullptr;
};


#endif

