# include <fstream>
# include <iostream>
# include <string>
# include <vector>
# include <algorithm>
# include <map>

# include "Query.h"
# include "Files.h"
# include "Dictionary.h"


using namespace std;


int main(){
	cout << "Loading Dictionary, this may take a few minutes..." << endl;
	// Dictionary();
	string scope;
	cin >> scope;
	cin.ignore();
	cout << "Recieved scope: " << scope << endl;
	FileScope myScope(scope);

	int numQueries;
	cin >> numQueries;
	cin.ignore();
	cout << "Recieved num of queries = " << numQueries << endl << "----------" << endl;


	for (int i = 0; i < numQueries; i++){
		string query;
		getline(cin, query);
		cout << i+1 << ". Recieved query: " << endl << query << endl;
		Query myQuery(myScope, query);
		// myQuery.displayParsedQuery();
		myQuery.resolveQuery();
		myQuery.displayResult();
		cout << "-------------" << endl;
	}
	return 0;
}
