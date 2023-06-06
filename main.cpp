#include "TextQuery.h"

int main()
{
	ifstream infile("Test.txt");

	TextQuery tq(infile);

	while (true) 
	{
		string s;
		cout << "enter word to look for, or q to quit: ";
		// stop if we hit end-of-file on the input or if a 'q' is entered
		if (!(cin >> s) || s == "q") break;
			print(cout, tq.query(s)) << endl;
	}

	return 0;
}

