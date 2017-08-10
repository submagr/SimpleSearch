#include<iostream>
#include<string>
#include <vector>
#include<map>
using namespace std;
class node
{

public:
	string word;
	node * next;
	node(string _word) :word(_word),next(NULL){}
};


	 


class query
{
	string input;
	bool flag_phrase;
	map<int, node*> root;

public:
	query()
	{

	}
	query(string _input) :input(_input)
	{
		
	}
	void operator =(string _input)
	{
		input = _input;
	}
	void CheckPhrase()
	{

		if (input.front() == '"' && input.back() == '"')//error if not ending or starting 
		{
			flag_phrase = true;
			cout << "Phrase" << endl;

		}
		else
		{
			flag_phrase = false;
		}
		if (!flag_phrase)
		{
			CreateTree();
		}
	}
	vector<string> split(string str){
		string sep = " ";
			char* cstr = const_cast<char*>(str.c_str());
			char* current;
			vector<string> arr;
			current = strtok(cstr, sep.c_str());
			while (current != NULL){
				arr.push_back(current);
				current = strtok(NULL, sep.c_str());
			}
			return arr;
		}
	void CreateTree()
	{
		vector<string> arr;
		arr = split(input);
		/*for (size_t i = 0; i < arr.size(); i++)
		{
			printf("%s\n", arr[i].c_str());
			
		}*/
		bool start = true;
		int child = 0;
		node* CurrentHead = NULL;
		node * temp = NULL;
		for (size_t i = 0; i < arr.size(); i++)
		{
			
			if (arr[i].compare("AND") == 0)
			{

			}
			else if (arr[i].compare("OR") == 0)
			{
				start = true;
				child++;
			}
			else if (start)
			{
				//cout << "child:" << arr[i].c_str() << endl;
				node* first = new node(arr[i].c_str());
				root[child] = first;
				CurrentHead = first;
				start = false;
			}
			
			else
			{
				//cout << "child:" << arr[i].c_str()<<endl;

				temp = new node(arr[i].c_str());
				CurrentHead->next = temp;
				CurrentHead = temp;

			}

		}
	}
	void TraverseTree()
	{
		for (auto it = root.begin(); it != root.end(); ++it)
		{
			int key = it->first;
			node* value = it->second;
			while (value != NULL)
			{
				cout << "key : " << key << " ; " << "word :" << value->word << endl;
				value = value->next;
			}
		}
	}
	
		//split word
		//create node for each wrd in array
		//send tree as output.
	

	void print()
	{
		cout << input<<endl;
	}
	
 
};
//query q=""apple OR orange"";:
int main()
{

	query q;
	q = "hello AND world OR mango AND banana";
	q.CheckPhrase();
	//q.print();
	q.TraverseTree();

}