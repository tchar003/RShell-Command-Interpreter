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

		cout << "$ ";
		getline(cin, input);

		istringstream sin(input);
		while (sin >> quoted(s)) {
			parsed.push_back(s);
		}

		Executor exeLine;
		exeLine.mirror(parsed);
		exeLine.treeBuild();
		//cout << exeLine.print() << endl;

		exeLine.execute();
		
	}
	
	return 0;
}
