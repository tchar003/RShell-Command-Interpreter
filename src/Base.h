#ifndef __BASE_H__
#define __BASE_H__
#include <sys/wait.h>
#include <unistd.h>
#include <vector>
#include <regex>
#include <iomanip>
#include <string>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <iostream>
class Base {
public:
        Base() {};
        ~Base() {};
        virtual bool execute() = 0;
        virtual std::string print() = 0;
        virtual bool failed() = 0;
	virtual std::string type() = 0;
	
	virtual void addLeft(Base* lhs) = 0;
	virtual void addRight(Base* rhs) = 0;
};


#endif

