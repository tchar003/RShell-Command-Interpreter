#include "Executor.h"
#include <regex>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <memory>

using namespace std;

void Executor::mirror(std::vector<std::string> parsed) {
	regex connector("\\|\\||&&|;");
	regex command("\\w+.*");
	regex argument(".+");
	regex comment("#.*|#");

	vector<string> mirrored;

	for (unsigned i = 0; i < parsed.size(); ++i) {
		// Push parens to the mirrored vector
		if (parsed.at(i).at(0) == '(' && parsed.at(i).size() > 1) {
			parsed.at(i).erase(0, 1);
			mirrored.push_back("(");
		}

		// Capture [ -f file ] format of test command
		if (parsed.at(i) == "[") {
			++i;
			mirrored.push_back("test");

			// Peek past the next token
			// If the next token is not a flag, add -e as default flag
			if (i < parsed.size() &&
				parsed.at(i + 1) != "]" &&
				parsed.at(i + 1).at(0) != '-') {
				mirrored.push_back("-e");
			}

			while (i < parsed.size() && parsed.at(i) != "]") {
				mirrored.push_back(parsed.at(i));
				++i;
			}

			continue;
		}

		// Whole token that is not in [] format
		if (parsed.at(i).size() > 0 && parsed.at(i) != "]" && parsed.at(i) != "[") {
			std::string token = parsed.at(i);

			// Check for closing parens or ;
			// If found, pop it off the token and push it to the mirrored vector
			if (!token.empty() && (token.back() == ')' || token.back() == ';')) {
				char lastChar = token.back();
				token.pop_back();
				if (!token.empty()) {
					mirrored.push_back(token);
				}
				mirrored.push_back(std::string(1, lastChar));
			} else {
				mirrored.push_back(parsed.at(i));
			}
		}
	}

	for (unsigned i = 0; i < mirrored.size(); ++i) {
		if (mirrored.at(i) == "(") {
			rawExp.push_back(std::make_shared<Paren>("("));
		} else if (mirrored.at(i) == ")") {
			rawExp.push_back(std::make_shared<Paren>(")"));
		} else if (regex_match(mirrored.at(i), comment)) {
			break;
		} else if (regex_match(mirrored.at(i), command)) {
			vector<string> temp;
			temp.push_back(mirrored.at(i)); // The command itself

			// Check for arguments, comments, or connectors
			while (i + 1 < mirrored.size()) {
				++i;
				if (regex_match(mirrored.at(i), comment)) {
					--i;
					break;
				} else if (regex_match(mirrored.at(i), connector) || mirrored.at(i) == ")") {
					--i;
					break;
				}
				temp.push_back(mirrored.at(i));
			}

			rawExp.push_back(std::make_shared<Cmd>(temp));
		}

		if (regex_match(mirrored.at(i), connector)) {
			if (mirrored.at(i) == "||") {
				rawExp.push_back(std::make_shared<Or>());
			} else if (mirrored.at(i) == "&&") {
				rawExp.push_back(std::make_shared<And>());
			} else {
				rawExp.push_back(std::make_shared<Semi>());
			}
		}
	}
}

void Executor::treeBuild() {
	regex parens("\\(|\\)");

	stack<std::shared_ptr<Base>> op_stack;
	queue<std::shared_ptr<Base>> out_queue;

	// Shunting Yard Algorithm
	for (unsigned i = 0; i < rawExp.size(); ++i) {
		// If the token is a command, add it to the output queue
		if (rawExp.at(i)->type() == "Cmd") {
			out_queue.push(rawExp.at(i));
		}

		// If the token is a left paren, push it to the operator stack
		if (rawExp.at(i)->type() == "(") {
			op_stack.push(rawExp.at(i));
		}

		// If the token is an operator
		if (rawExp.at(i)->type() == "Operator") {
			while (!op_stack.empty() && op_stack.top()->type() != "(") {
				std::shared_ptr<Base> temp = op_stack.top();
				op_stack.pop();
				out_queue.push(temp);
			}
			op_stack.push(rawExp.at(i));
		}

		// If the token is a right paren
		if (rawExp.at(i)->type() == ")") {
			while (op_stack.top()->type() != "(") {
				std::shared_ptr<Base> temp = op_stack.top();
				op_stack.pop();
				out_queue.push(temp);
			}
			if (op_stack.top()->type() == "(") {
				op_stack.pop();
			}
		}
	}

	// Pop all the operators from the stack to the output queue
	while (!op_stack.empty()) {
		std::shared_ptr<Base> temp = op_stack.top();
		op_stack.pop();
		out_queue.push(temp);
	}

	// Build the tree from the output queue
	while (!out_queue.empty()) {
		if (out_queue.front()->type() == "Cmd") {
			op_stack.push(out_queue.front());
		} else if (out_queue.front()->type() == "Operator") {
			out_queue.front()->addRight(op_stack.top());
			op_stack.pop();
			if (!op_stack.empty()) {
				out_queue.front()->addLeft(op_stack.top());
				op_stack.pop();
			}
			op_stack.push(out_queue.front());
		}

		if (out_queue.size() == 1) {
			line = out_queue.front();
		}
		out_queue.pop();
	}
}
