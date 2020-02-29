#ifndef __Semi_H__
#define __Semi_H__

#include "Base.h"

class Semi : public Base {
public:
        Semi() {left = nullptr; right = nullptr;}
	~Semi() {left = nullptr; right = nullptr;}
        bool execute() {
			
		if (!right){return left->execute();}
		else {left->execute(); return right->execute();}
	}
        std::string print() {
		if (!left || !right) {return ";";}
		return left->print() + ";" + right->print();
	}
        bool failed() {return left->failed();}
	std::string type() {return "Operator";}


	
        void addLeft(std::shared_ptr<Base> lhs) { left = lhs;}
        void addRight(std::shared_ptr<Base> rhs) {right = rhs;}


private:
		std::shared_ptr<Base> left;
		std::shared_ptr<Base>  right;
};


#endif
