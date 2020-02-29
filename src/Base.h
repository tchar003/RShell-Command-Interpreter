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
#include <memory>
class Base {
public:
        Base() {};
        virtual ~Base() {};
        virtual bool execute() = 0;
        virtual std::string print() = 0;
        virtual bool failed() = 0;
	virtual std::string type() = 0;
	
	virtual void addLeft(std::shared_ptr<Base> lhs) = 0;
	virtual void addRight(std::shared_ptr<Base> rhs) = 0;
};


#endif

