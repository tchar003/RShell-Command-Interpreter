#ifndef __OR_H__
#define __OR_H__

#include "Base.h"

class Or : public Base {
public:
        Or() {left = nullptr; right = nullptr;}
	~Or() {
		//delete[] left;
		left = nullptr;
		//delete[] right;
		right = nullptr;
	}
        bool execute() {
		bool temp = 0;
		if (temp = left->execute() ) {
			std::cout << "LEFT FAILED"  << temp << "\n";
			temp = right->execute();
			std::cout << "Returned right: " << temp << "\n";
			return temp;
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
	void addLeft(std::shared_ptr<Base> lhs) {left = lhs;}
        void addRight(std::shared_ptr<Base> rhs) {right = rhs;}

private:
	std::shared_ptr<Base> left = nullptr;
	std::shared_ptr<Base> right = nullptr;
};


#endif

