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
	string query;
	getline(cin, query);

	cout << "Recieved scope: " << scope << endl << "----------------" << endl;
	cout << "Recieved query: " << endl<< query << endl << "------------------" << endl;

	FileScope myScope(scope);
	Query myQuery(myScope, query);
	// Display the contents of parsed MAP
	myQuery.displayParsedQuery();

	myQuery.resolveQuery();
	myQuery.displayResult();
	//listFiles files(parsedQ.getScope());
	//ProcessQuery pq(files, parsedQ);
	return 0;
}