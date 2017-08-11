#include "Files.h"

bool FileScope::DirectoryExists(string dirName, vector<string> &files) {
	DWORD ftyp = GetFileAttributesA(dirName.c_str());

	if (ftyp == INVALID_FILE_ATTRIBUTES)
		return false;  //something is wrong with your path!

	if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
		return true;   // this is a directory!
	files.push_back(dirName);
	return false;    // this is not a directory!

}


void FileScope::getdir(string dir, vector<string> &files)
{
	DIR *dp;
	struct dirent *dirp;
	if ((dp = opendir(dir.c_str())) == NULL) {
		cout << "Error(" << errno << ") opening " << dir << endl;
		
	}

	string dirRec = dir;

	while ((dirp = readdir(dp)) != NULL) {
		dirRec = dir;
		dirRec.append("\\");
		//cout << dirp->d_name << endl;
		dirRec.append(dirp->d_name);
		if (string(dirp->d_name).compare(".") == 0)
		{
			continue;
		}
		if (string(dirp->d_name).compare("..") == 0)
		{
			continue;
		}

		if (DirectoryExists(dirRec, files))
		{

			getdir(dirRec, files);
		}

		//files.push_back(dirRec);
	}
	closedir(dp);
}


FileScope::FileScope(string scopeLoc):_scopeLoc(scopeLoc){
	listFiles();
	createFileLocsHash();
};

void FileScope::listFiles(){
	// <TODO: Delegate this to another class>				
	// <XXX: For now, returning a dummy location>

	 // string dir = string("C:\\Users\\bbansal\\Documents\\CBLectures");
	 string dir = _scopeLoc;
	 //_fileLocs = vector<string>();

	 getdir(dir, _fileLocs);
	 cout << _fileLocs.size() << endl;
	 for (unsigned int i = 0; i < _fileLocs.size(); i++) {
		 // cout << _fileLocs[i] << endl;
	 }
	//string mystring("Test/test.txt");
	// _fileLocs.push_back(mystring);
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
