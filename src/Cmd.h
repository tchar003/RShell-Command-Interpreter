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
#include <vector>
#include <memory>

class Cmd : public Base {
public:
	// Default constructor
	Cmd() {
		args = nullptr;
		argc = 0;
		exeFailed = false;
	}

	// Creates a command object from a vector of strings
	// Execvp requires a null-terminated string
	Cmd(std::vector<std::string> parsed) {
		exeFailed = false;
		argc = parsed.size() + 1;
		args = new char*[argc];

		args[parsed.size()] = nullptr;
		for (unsigned i = 0; i < parsed.size(); ++i) {
			args[i] = new char[parsed.at(i).size() + 1];
			strcpy(args[i], parsed[i].c_str());
		}
	}

	// Destructor
	~Cmd() {
		for (unsigned i = 0; i < argc - 1; ++i) {
			delete[] args[i];
		}
		delete[] args;
	}

	// Executes the command
	bool execute();

	// Prints the command
	std::string print();

	// Checks if execution failed
	bool failed() { return exeFailed; }

	// Returns the type of the object
	std::string type() { return "Cmd"; }

	// No-op for adding left child
	void addLeft(std::shared_ptr<Base> lhs) { return; }

	// No-op for adding right child
	void addRight(std::shared_ptr<Base> rhs) { return; }

private:
	char** args;      // Arguments for the command
	int argc;         // Argument count
	bool exeFailed;   // Flag to indicate if execution failed
};

#endif
