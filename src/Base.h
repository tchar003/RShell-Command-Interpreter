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
        // Constructor and Destructor
        Base() {}

        // Virtual Destructor
        // Allows for proper cleanup of derived classes
        // when a pointer to the base class is deleted.
        // This is important for memory management
        // and prevents memory leaks.
        virtual ~Base() {}

        // Pure virtual functions

        // Runs Command or logical operator
        virtual bool execute() = 0;

        // Returns string representing node
        virtual std::string print() = 0;

        // Reports execution result (affects control flow: &&, ||)
        virtual bool failed() = 0;

        // Returns string identifier (e.g., cmd, operator, &&, ||)
        virtual std::string type() = 0;

        // Binary Tree in postfix
        virtual void addLeft(std::shared_ptr<Base> lhs) = 0;
        virtual void addRight(std::shared_ptr<Base> rhs) = 0;
};

#endif
