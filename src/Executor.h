#ifndef __EXECUTOR_H__
#define __EXECUTOR_H__

#include <regex>
#include <stack>
#include <queue>
#include <memory>


#include "Base.h"
#include "Cmd.h"
#include "Or.h"
#include "And.h"
#include "Semi.h"
#include "Paren.h"

class Executor: public Base {
public:
	
        ~Executor() {
		/*
		for (unsigned i = 0; i < rawExp.size(); ++i) {
			delete rawExp[i];
			rawExp[i] = nullptr;
		}
		rawExp.clear();
		line = nullptr;*/
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


	void addLeft(std::shared_ptr<Base> lhs) {return;}
        void addRight(std::shared_ptr<Base> rhs) {return;}


private:
	std::shared_ptr<Base> line;
	std::vector<std::shared_ptr<Base> > rawExp;
};


#endif
