#ifndef __EXECUTOR_H__
#define __EXECUTOR_H__

#include <regex>
#include <stack>
#include <queue>



#include "Base.h"
#include "Cmd.h"
#include "Or.h"
#include "And.h"
#include "Semi.h"
#include "Paren.h"

class Executor: public Base {
public:
	
        ~Executor() {
		delete line;
	}
	void mirror(std::vector<std::string> parsed);
	void treeBuild();
       	bool execute() {
		if (!line) {return false;}
		line->execute();
	}
        std::string print() {
		if (!line) {return "No root node";}
		return line->print();
	}
        bool failed(){
		return false;
	}
	std::string type() { return "what are you calling me for?";}


	void addLeft(Base* lhs) {return;}
        void addRight(Base* rhs) {return;}


private:
	Base* line;
	std::vector<Base* > rawExp;
};


#endif
