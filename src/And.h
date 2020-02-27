#ifndef __AND_H__
#define __AND_H__

#include "Base.h"

class And : public Base {
public:
        And(){}
	~And() {
		delete[] left;
		left = nullptr;
		delete[] right; 
		right = nullptr;
	}
        bool execute() {
		bool temp;
		if (temp = left->execute()) {
			return temp;
		}
		else {return right->execute();}
		
	}
        std::string print() {
			if (!left || !right) { return "&&"; }
			return left->print() + "&& " + right->print();
	}
        bool failed() {return left->failed();}
	std::string type() {return "Operator";}

	
        void addLeft(Base* lhs) {left = lhs;}
        void addRight(Base* rhs) {right = rhs;}


private:
	Base* left;
	Base* right;
};


#endif

