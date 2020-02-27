#ifndef __Semi_H__
#define __Semi_H__

#include "Base.h"

class Semi : public Base {
public:
        Semi() {}
	~Semi() {left = nullptr; right = nullptr;}
        bool execute() {
			left->execute();
			return right->execute();
		}
        std::string print() {
		if (!left || !right) {return ";";}
		return left->print() + ";" + right->print();
	}
        bool failed() {return left->failed();}
	std::string type() {return "Operator";}


	
        void addLeft(Base* lhs) { left = lhs;}
        void addRight(Base* rhs) {right = rhs;}


private:
		Base* left;
		Base*  right;
};


#endif
