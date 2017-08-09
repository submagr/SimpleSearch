#include "Query.h"

void Query::setParams(string scope, string keyword){
	_scope = scope;
	_keyword = keyword;
}

string Query::getScope(){
	return _scope;
}

string Query::getKeyword(){
	return _keyword;
}

Query QueryParser::parse(int argc, char *argv[]){
	if (argc != 3) {
		cout << "Usage: " << argv[0] << " <scope>" << " search keyword" << endl;
		throw;
	} else {
		Query q;
		q.setParams(argv[1], argv[2]);
		return q;
		//ifstream the_file(argv[1]);
		//if (!the_file.is_open())
		//	cout << "Could not open file\n";
		//else {
		//	char x;
		//	while (the_file.get(x))
		//		cout << x;
		//}
	}
}

ProcessQuery::ProcessQuery(listFiles files, Query query) :_files(files), _query(query){
	for (int i = 0; i<files._fileLocs.size(); i++){
		ProcessFile(i);
	}
	_results.display();
}

int ProcessQuery::getFileSize(string fileName){
	// <REF: http://cplusplus.com/references>
	streampos begin, end;
	ifstream myfile(fileName, ios::binary);
	begin = myfile.tellg();
	myfile.seekg(0, ios::end);
	end = myfile.tellg();
	myfile.close();
	cout << "size is: " << (end - begin) << " bytes.\n";
	return (int)(end-begin);
}

void ProcessQuery::badCharHeuristic(string str, int size, int badchar[NO_OF_CHARS]){
	int i;

	for (i = 0; i < NO_OF_CHARS; i++)
		badchar[i] = -1;

	for (i = 0; i < size; i++)
		badchar[(int)str[i]] = i;
}

// A utility function to get maximum of two integers
int ProcessQuery::max(int a, int b) { 
	return (a > b) ? a : b; 
}

Result ProcessQuery::search(string fileName, string pat)
{
	// Open File for reading
	int m = pat.length();
	int n = getFileSize(fileName);
	cout << m << " " << n << endl;
	
	// Get contents of file in a string
	ifstream infile;
	infile.open(fileName);
	string txt;
	infile >> txt;
	// std::transform(data.begin(), data.end(), data.begin(), ::tolower);

	int badchar[NO_OF_CHARS];

	badCharHeuristic(pat, m, badchar);

	int s = 0;
	Result result(fileName);
	while (s <= (n - m)){
		int j = m - 1;

		while (j >= 0 && pat[j] == txt[s + j])
			j--;

		if (j < 0){
			result.addMatch(s);
			s += (s + m < n) ? m - badchar[txt[s + m]] : 1;
		}else{
			s += max(1, j - badchar[txt[s + j]]);
		}
	}
	infile.close();
	return result;
}

void ProcessQuery::ProcessFile(int i){
	string fileLoc = _files._fileLocs[i];
	Result result = search(fileLoc, _query.getKeyword());
	_results.addResult(result);
}
