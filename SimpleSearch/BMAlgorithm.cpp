#include "BMAlgorithm.h"

void BMAlgorithm::Run(list<int> filePool, FileScope scope, string keyWord, map<int, int>& counts, bool matchLowerCase){
	for (list<int>::iterator i = filePool.begin(); i != filePool.end(); ++i){
		counts[*i] = search(scope.getFileLocFromIndex(*i), keyWord, matchLowerCase);
	}
}

//int BMAlgorithm::getFileSize(string fileName){
//	// <REF: http://cplusplus.com/references>
//	streampos begin, end;
//	ifstream myfile(fileName, ios::binary);
//	begin = myfile.tellg();
//	myfile.seekg(0, ios::end);
//	end = myfile.tellg();
//	myfile.close();
//	return (int)(end-begin);
//}

void BMAlgorithm::badCharHeuristic(string str, int size, int badchar[NO_OF_CHARS]){
	int i;

	for (i = 0; i < 256 /*<TODO>*/; i++)
		badchar[i] = -1;

	for (i = 0; i < size; i++)
		badchar[(int)str[i]] = i;
}

// A utility function to get maximum of two integers
int BMAlgorithm::myMax(int a, int b){ 
	return (a > b) ? a : b; 
}

int BMAlgorithm::search(string fileName, string pat, bool matchLowerCase)
{
	// Open File for reading
	int m = pat.length();
	// cout << m << " " << n << endl;
	
	// Get contents of file in a string
	ifstream infile(fileName);
	string txt;

	infile.seekg(0, std::ios::end);
	txt.reserve(infile.tellg());
	infile.seekg(0, std::ios::beg);

	txt.assign((std::istreambuf_iterator<char>(infile)),
		std::istreambuf_iterator<char>());
	int n = txt.size();

	if (matchLowerCase){
		std::transform(pat.begin(), pat.end(), pat.begin(), ::tolower);
		std::transform(txt.begin(), txt.end(), txt.begin(), ::tolower);
	}

	int badchar[256/*<TODO>*/];

	badCharHeuristic(pat, m, badchar);

	int s = 0;
	int matches = 0;
	while (s <= (n - m)){
		int j = m - 1;

		while (j >= 0 && pat[j] == txt[s + j])
			j--;

		if (j < 0){
			matches++;
			s += (s + m < n) ? m - badchar[txt[s + m]] : 1;
		}else{
			s += myMax(1, j - badchar[txt[s + j]]);
		}
	}
	infile.close();
	return matches;
}