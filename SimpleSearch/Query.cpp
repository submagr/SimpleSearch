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

void Query::displayParsedQuery(){
	typedef map<int, list<SubQuery *>>::const_iterator MapIterator;
	for (MapIterator iter = root.begin(); iter != root.end(); iter++)
	{
		cout << "Key: " << iter->first << endl << "Values:" << endl;
		list<SubQuery *> columnList = (iter->second);
		for (list<SubQuery *>::iterator i = columnList.begin(); i != columnList.end(); ++i)
			(*i)->displaySubQuery();
	}
}

Query QueryParser::parse(string scope, string query){
	Query q;
	q.setParams(scope, query);
	CheckPhrase(q);
	return q;
}

void QueryParser::CheckPhrase(Query &q)
{
	string input = q.getKeyword();
	CreateTree(q);
}

vector<string> QueryParser::split(string sentence){
	istringstream iss(sentence);
	vector<string> arr;
	copy(istream_iterator<string>(iss),
		istream_iterator<string>(),
		back_inserter(arr));
	return arr;
}


void QueryParser::CreateTree(Query &q)
{
	string input = q.getKeyword();
	vector<string> arr;
	arr = split(input); 
	// <XXX: There is an issue with the algorithm of split (Hint: What happens when subquery of type exact match contains spaces ?)>
	bool start = true; // Represents that map[child] is not created yet
	int child = 0; // Denotes the OR branch (column)
	for (size_t i = 0; i < arr.size(); i++)
	{
		if (arr[i].compare("AND") == 0)
		{
			continue;
		}
		else if (arr[i].compare("OR") == 0) // <XXX: what happens if first word was OR>
		{
			start = true;
			child++;
			continue;
		}
		else if (start)
		{
			SubQuery * first = SubQueryFactory::CreateSubQuery(arr[i], start);
			q.root[child].push_back(first);
			start = false;
		}
		else
		{
			SubQuery *temp = SubQueryFactory::CreateSubQuery(arr[i], start);
			q.root[child].push_back(temp);
		}
	}
}

ProcessQuery::ProcessQuery(listFiles files, Query query) :_files(files), _query(query){
	for (int i = 0; i<(int)(files._fileLocs.size()); i++){
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

	for (i = 0; i < 256 /*<TODO>*/; i++)
		badchar[i] = -1;

	for (i = 0; i < size; i++)
		badchar[(int)str[i]] = i;
}

// A utility function to get maximum of two integers
int ProcessQuery::myMax(int a, int b){ 
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

	int badchar[256/*<TODO>*/];

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
			s += myMax(1, j - badchar[txt[s + j]]);
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

