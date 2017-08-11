#include "Files.h"

FileScope::FileScope(string scopeLoc):_scopeLoc(scopeLoc){
	listFiles();
	createFileLocsHash();
};

void FileScope::listFiles(){
	// <TODO: Delegate this to another class>				
	// <XXX: For now, returning a dummy location>
	string mystring("Test/test.txt");
	 _fileLocs.push_back(mystring);
}

void FileScope::createFileLocsHash(){
	// <TODO: Delegate this to listFiles itself; _fileLocs is redundant>
	for (int i = 0; i < _fileLocs.size(); i++) {
		_fileLocsHash[i] = _fileLocs[i];
	}
}

string FileScope::getFileLocFromIndex(int index){
	return	_fileLocsHash[index];
}

int FileScope::getNumberOfFiles(){
	return _fileLocs.size();
}
