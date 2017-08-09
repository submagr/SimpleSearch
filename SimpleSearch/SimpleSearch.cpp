# include <fstream>
# include <iostream>
# include <string>
# include <vector>
# include <algorithm>
using namespace std;

# define NO_OF_CHARS 256

/*  This is a factory class
	Will take input string and return the query object
*/
class listFiles{
public:
	vector<string> _fileLocs; // <TODO: Make this private and provide a function that returns iterator>
	listFiles(string scope)
	{
		// <TODO: Delegate this to another class>				
		// <XXX: For now, returning a dummy location>
		string mystring("Test/test.txt");
		 _fileLocs.push_back(mystring);
	}
};

class Query{
	string _scope; 
	string _keyword;
public:
	void setParams(string scope, string keyword){
		_scope = scope;
		_keyword = keyword;
	}
	string getScope(){
		return _scope;
	}
	string getKeyword(){
		return _keyword;
	}
};

class QueryParser{
public:
	Query parse(int argc, char *argv[]){
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
};

class Result{
public:
	string _fileLocation;
	vector<int> _matchLocations;
	Result(string fileLoc):_fileLocation(fileLoc){
	}
	void display(){
		cout << "Total Matches for " << _fileLocation << " : " << _matchLocations.size() << endl;
		for (int i = 0; i < _matchLocations.size(); i++){
			cout << "\t" << i+1 << ". Shift = " << _matchLocations[i] << endl;
		}
	}
	void addMatch(int matchLocation){
		_matchLocations.push_back(matchLocation);
	}
};

class Results{
public:
	vector<Result> _results;
	void addResult(Result result){
		_results.push_back(result);
	}
	void display(){
		for (int i = 0; i < _results.size(); i++){
			_results[i].display();
		}
	}
};

class ProcessQuery{
public:		
	listFiles _files;
	Query _query;
	Results _results;
	ProcessQuery(listFiles files, Query query) :_files(files), _query(query){
		for (int i = 0; i<files._fileLocs.size(); i++){
			ProcessFile(i);
		}
		_results.display();
	}

	int getFileSize(string fileName){
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

	void badCharHeuristic(string str, int size, int badchar[NO_OF_CHARS]){
		int i;

		for (i = 0; i < NO_OF_CHARS; i++)
			badchar[i] = -1;

		for (i = 0; i < size; i++)
			badchar[(int)str[i]] = i;
	}

	Result search(string fileName, string pat)
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

	void ProcessFile(int i){
		string fileLoc = _files._fileLocs[i];
		Result result = search(fileLoc, _query.getKeyword());
		_results.addResult(result);
	}
};



int main(int argc, char *argv[])
{
	QueryParser qparser;
	Query parsedQ = qparser.parse(argc, argv);
	listFiles files(parsedQ.getScope());
	ProcessQuery pq(files, parsedQ);
	return 0;
}
