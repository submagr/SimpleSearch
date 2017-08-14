# include <fstream>
# include <iostream>
# include <string>
# include <vector>
# include <algorithm>
# include <map>

# include "Query.h"
# include "Files.h"


using namespace std;


int main(){
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

		myQuery.resolveQuery();
		myQuery.displayResult();
		cout << "-------------" << endl;
	}
	return 0;
}