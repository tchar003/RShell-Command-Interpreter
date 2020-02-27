#include "Executor.h"


using namespace std;
/*
void Executor::build(std::vector<std::string> parsed) {
	regex connector("\\|\\||&&|;");
	regex command("\\w+.*");
	regex semicolon(";");
	regex argument(".+");
	regex comment("#.*|#");
	
	bool semi = false;
	
	Base* left = nullptr;
	Base* right = nullptr;
	Base* AND = nullptr;
	Base* ORL = nullptr;
	std::vector<std::string> temp = {"echo","a"};

	left = new Cmd(temp);

	temp.pop_back();
	temp.pop_back();
	temp.push_back("echi");
	temp.push_back("b");
	
	right = new Cmd(temp);

	AND = new And(left, right);
	temp.pop_back();
	temp.pop_back();
	temp.push_back("echo");
	temp.push_back("c");
	
	ORL = new Cmd(temp);

	line = new Or(AND, ORL);
}
*/
void Executor::mirror(std::vector<std::string> parsed) {
	
        regex connector("\\|\\||&&|;");
        regex command("\\w+.*");
        regex argument(".+");
        regex comment("#.*|#");

	
	vector<string> mirrored;
	
	for (unsigned i = 0; i < parsed.size(); ++i) {
	    if (parsed.at(i).at(0) == '(' && parsed.at(i).size() > 1) {
	       parsed.at(i).erase(0, 1);
	       mirrored.push_back("(");
	    }

	    
	    if (parsed.at(i).at(0) == '[') {
		if (parsed.at(i).size() != 0) {
	       		parsed.at(i).erase(0, 1);
	 	}
	       mirrored.push_back("test");
	    }
	    
	    if (parsed.at(i).size() > 0) {
	    	mirrored.push_back(parsed.at(i));	    
	    }

	    if (mirrored.size() > 0 && mirrored.back().back() == ')') {
	        mirrored.back().pop_back();
	        mirrored.push_back(")");
	    }
	
	    if (mirrored.size() > 0 && mirrored.back().back() == ']') {
	        mirrored.back().pop_back();
	    }
	    
	    if (mirrored.size() > 0 && mirrored.back().back() == ';') {
	        mirrored.back().pop_back();
	        mirrored.push_back(";");
	    }
	}
	/*
	std::cout << "_________MIRRORED INPUT__________\n\n";
	for (unsigned i = 0; i < mirrored.size(); ++i) {
		std::cout << mirrored.at(i) << "\n";
	}*/
	
	for (unsigned i = 0; i < mirrored.size(); ++i) {
		if (mirrored.at(i) == "("){
			rawExp.push_back(new Paren(")"));
		}
		else if (mirrored.at(i) == ")") {
			rawExp.push_back(new Paren("("));
		}
		
		else if (regex_match(mirrored.at(i), comment)) {
			break;
		}
		else if (regex_match(mirrored.at(i), command)) {
			vector<string> temp;
			
			temp.push_back(mirrored.at(i));
			
			while (i + 1 < mirrored.size() ) {
			++i;
			if (regex_match(mirrored.at(i), comment)) {
				--i;
				break;
			}
			else if (regex_match(mirrored.at(i), connector) || mirrored.at(i) == ")") {
				--i;
				break;
			}
			temp.push_back(mirrored.at(i));
			}

			rawExp.push_back(new Cmd(temp));
		}
		
		if (regex_match(mirrored.at(i), connector)) {
			if (mirrored.at(i) == "||") {
				rawExp.push_back(new Or() );
			}
			else if (mirrored.at(i) == "&&") {
				rawExp.push_back(new And() );
			}
			else {
				rawExp.push_back(new Semi() );
			}
		}
							
	}	

	reverse(rawExp.begin(), rawExp.end() );
	
	/*
	for (unsigned i = 0; i < rawExp.size(); ++i) {
		 std::cout << "T: " << rawExp.at(i)->type() << endl;
	}
	*/

}

void Executor::treeBuild() {
	
        regex parens("\\(|\\)");

	stack<Base* > op_stack;
	queue<Base* > out_queue;
	
	//std::cout << "_________________SY_________________\n\n";
	
	for (unsigned i = 0; i < rawExp.size(); ++i) {
		//std::cout << rawExp.at(i)->type() << "\n";
		if (rawExp.at(i)->type() == "Cmd") {
			out_queue.push(rawExp.at(i));
		}
		if (rawExp.at(i)->type() == "("){
			//delete[] rawExp.at(i);
			//rawExp.at(i) == nullptr;
			op_stack.push(rawExp.at(i));
		}
		if (rawExp.at(i)->type() == "Operator") {
			op_stack.push(rawExp.at(i));
		}
		if (rawExp.at(i)->type() == ")") {
			while (op_stack.top()->type() != "(") {
				Base* temp = op_stack.top();
				op_stack.pop();
				out_queue.push(temp);
			}
			if (op_stack.top()->type() == "(") {
				op_stack.pop();
			}
		}						
	}
	/*
	for (unsigned i = 0; i < rawExp.size(); ++i) {
		if (regex_match(rawExp.at(i)->type(), parens)) {
			delete rawExp;
			rawExp[i] = nullptr;
		}
	}*/

	while (!op_stack.empty() ) {
		Base* temp = op_stack.top();
		op_stack.pop();
		out_queue.push(temp);
	}
	/*
	stack<Base* > temp;
	while (!out_queue.empty() ) {
		temp.push(out_queue.front() );
		out_queue.pop();
	}*/
	
	//std::cout <<"_____________________ASSIGN CHILDREN__________\n\n";
	while (!out_queue.empty() ){
		//std::cout << "\n" << out_queue.front()->type() << "\n";
               if (out_queue.front()->type() == "Cmd") {
                        op_stack.push(out_queue.front() );
               }
               else if (out_queue.front()->type() == "Operator") {
			out_queue.front()->addLeft(op_stack.top() );
			op_stack.pop();
			out_queue.front()->addRight(op_stack.top() );
			op_stack.pop();			
                        op_stack.push(out_queue.front() );
               }
		if (out_queue.size() == 1) {line = out_queue.front();}
	       out_queue.pop();
	}
		
}

