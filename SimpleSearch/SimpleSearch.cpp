# include <fstream>
# include <iostream>
# include <string>
# include <vector>
# include <algorithm>

# include "Query.h"
# include "Result.h"
# include "Files.h"
using namespace std;

int main(int argc, char *argv[])
{
	QueryParser qparser;
	Query parsedQ = qparser.parse(argc, argv);
	listFiles files(parsedQ.getScope());
	ProcessQuery pq(files, parsedQ);
	return 0;
}
