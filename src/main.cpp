#include "Base.h"
#include "Or.h"
#include "Cmd.h"
#include "And.h"
#include "Executor.h"
#include "Semi.h"

using namespace std;

int main() {
	while (1) {
		string input;
		string s;
		vector<string> parsed;

		// Prompt for user input
		cout << "$ ";
		getline(cin, input);

		// Parse the input into a vector of strings
		istringstream sin(input);
		while (sin >> quoted(s)) {
			parsed.push_back(s);
		}

		// Create an Executor object and process the input
		Executor exeLine;
		exeLine.mirror(parsed);
		exeLine.treeBuild();

		// Execute the command tree
		exeLine.execute();
	}

	return 0;
}
