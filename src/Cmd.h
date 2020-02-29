#ifndef __CMD_H__
#define __CMD_H__

#include "Base.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <algorithm>
#include <functional>
#include <iterator>

class Cmd : public Base {
public:
	Cmd() {args = nullptr; argc = 0; exeFailed = false;}
	Cmd(std::vector<std::string> parsed) {
		exeFailed = false;
		argc = parsed.size() + 1;
		args = new char*[argc];
		//args[parsed.size()] = new char[1];
		args[parsed.size()] = new char[1];
		args[parsed.size()] = '\0';
		for (unsigned i = 0; i < parsed.size(); ++i) {
			args[i] = new char[parsed.at(i).size() + 1];
			strcpy(args[i], parsed[i].c_str() );
		}
		

	}
        ~Cmd() {
		for (unsigned i = 0; i < starts.size(); ++i) {
			delete[] args[i];
		}
		delete[] args;
	}
        bool execute();
        std::string print();
        bool failed() {return exeFailed;}
	std::string type(){return "Cmd";}
	
	void addLeft(std::shared_ptr<Base> lhs) {return;}
	void addRight(std::shared_ptr<Base> rhs) {return;}
private:
		std::vector<char*> starts;
		char** args;
		int argc;
		bool exeFailed;
};


#endif

