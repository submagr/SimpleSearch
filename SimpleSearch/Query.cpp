#include "Query.h"

Query::Query(FileScope scope, string keyword) :_scope(scope), _keyword(keyword)
{
	QueryParser::parse(*this);
}

Query::~Query(){
	//<TOOD: Uncomment> 
	//delete _fileOccurances;
}
void Query::setParams(string scope, string keyword){
	_scope = scope;
	_keyword = keyword;
}

FileScope Query::getScope(){
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

void Query::resolveQuery(){
	_resultSize = _scope.getNumberOfFiles();
	_result = new int[_resultSize]; // <TODO: delete>
	for (int i = 0; i < _resultSize; i++){
		_result[i] = 0;
	}

	for (int i = 0; i < root.size(); i++){
		int * fileOccurances = new int[_resultSize]; 
		for (int i = 0; i < _resultSize; i++){
			fileOccurances[i] = 0;
		}

		std::list<SubQuery *>::const_iterator iterator;
		for (iterator = root[i].begin(); iterator != root[i].end(); ++iterator) {
			(*iterator)->handleQuery(fileOccurances, _resultSize);
		}

		for (int i = 0; i < _resultSize; i++){
			_result[i] += fileOccurances[i];
		}
		delete[] fileOccurances; // <TODO: will this be executed in every loop ?>
	}
}

void Query::displayResult(){
	cout << "Results for Query: {" << _keyword << "} are: " << endl;
	for (int i = 0; i < _resultSize; i++){
		if (_result[i]!=0){
			cout << "\t" << _scope.getFileLocFromIndex(i) << " : " << _result[i] << endl;
		}
	}
}

void QueryParser::parse(Query &q){
	CheckPhrase(q);
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
			SubQuery * first = SubQueryFactory::CreateSubQuery(arr[i], start, q.getScope());
			q.root[child].push_back(first);
			start = false;
		}
		else
		{
			SubQuery *temp = SubQueryFactory::CreateSubQuery(arr[i], start, q.getScope());
			q.root[child].push_back(temp);
		}
	}
}

