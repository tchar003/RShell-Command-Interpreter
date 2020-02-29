#ifndef __PAREN_H__
#define __PAREN_H__

#include "Base.h"

class Paren : public Base {
public:
	Paren(std::string lr) {str = lr;}
	~Paren() {}
	bool execute(){return true;}
	std::string print() {return str;}
	bool failed() {return true;}
	std::string type() {return str;}

	
        void addLeft(std::shared_ptr<Base> lhs) {return;}
        void addRight(std::shared_ptr<Base> rhs) {return;}


private:
	std::string str;
};

#endif
