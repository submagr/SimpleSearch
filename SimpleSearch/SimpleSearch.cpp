# include <fstream>
# include <iostream>
# include <string>
# include <vector>
# include <algorithm>
# include <map>

# include "Query.h"
# include "Result.h"
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

	QueryParser qparser;
	Query parsedQ = qparser.parse(scope, query); // <TODO: Structure of input is changed, update this>
	// Display the contents of parsed MAP
	parsedQ.displayParsedQuery();
		
	listFiles files(parsedQ.getScope());
	ProcessQuery pq(files, parsedQ);
	return 0;
}