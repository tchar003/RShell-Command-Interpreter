#ifndef __CMD_H__
#define __CMD_H__

#include "Base.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


class Cmd : public Base {
public:
	Cmd() {args = nullptr; argc = 0; exeFailed = false;}
	Cmd(std::vector<std::string> parsed) {
		argc = parsed.size() + 1;
		args = new char*[argc];
		args[parsed.size()] = '\0';
		for (unsigned i = 0; i < parsed.size(); ++i) {
			args[i] = new char[parsed.at(i).size() + 1];
			strcpy(args[i], parsed[i].c_str());
		}
	}
        ~Cmd() {
		for (unsigned i = 0; i < argc; ++i) {
			delete[] args[i];
		}
		delete[] args[argc];
		args = nullptr;
	}
        bool execute();
        std::string print();
        bool failed() {return exeFailed;}
	std::string type(){return "Cmd";}
	
	void addLeft(Base* lhs) {return;}
	void addRight(Base* rhs) {return;}
private:
		char** args;
		int argc;
		bool exeFailed;
};


#endif

