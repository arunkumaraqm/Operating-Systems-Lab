#include <iostream>
#include <set>
#include <cassert>
#include <vector>

using namespace std;
bool EndsWith(const std::string& data, const std::string& suffix)
{
    return data.find(suffix, data.size() - suffix.size()) != string::npos;
}
int main()
{
	string fname, dname, command;
	set<string> files, dirs;
	dirs.insert(".");

	while(true)
	{
		cout << ">> ";
		cin >> command;
		if (command == "create" or command == "insert" or command == "touch")
		{
			cin >> fname;
			auto it = fname.begin();
			for (it = fname.begin(); it != fname.end(); ++it)
			{
				if (*it == '/')
				{
					break;
				}

			}
			if (it == fname.end())
			{
				dname = ".";
				fname = "./" + fname;
			}
			else
			{
				dname = string(fname.begin(), it);
			}
			assert(fname.length() != dname.length() + 1); // assert file name not empty

			if (dirs.find(dname) == dirs.end())
			{
				cerr << "Directory doesn't exist" << endl;
				continue;
			}

			auto it2 = files.find(fname);
			if (it2 != files.end())
			{
				cerr << "File already exists."<<endl;
			}
			else
			{
				files.insert(fname);
			}
		}
		else if (command == "display" or command == "show" or command == "ls")
		{
			for (auto file: files)
			{
				cout << file << endl;
			}
		}
		else if (command == "delete" or command == "remove" or command == "rm")
		{
			cin >> fname;
			
			auto it = fname.begin();
			for (it = fname.begin(); it != fname.end(); ++it)
			{
				if (*it == '/')
				{
					break;
				}
			}
			if (it == fname.end())
			{
				fname = "./" + fname;
			}
			
			auto it2 = files.find(fname);
			if (it2 != files.end())
			{
				files.erase(it2);
			}
			else
			{
				cerr << "File not found." << endl;
			}
		}
		else if (command == "mkdir")
		{
			cin >> dname;
			if (dirs.find(dname) == dirs.end())
			{
				dirs.insert(dname);
			}
			else
			{
				cerr << "Directory already exists."<<endl;
			}
		}
		else if (command == "find" or command == "search")
		{
			cin >> fname;
			bool flag = 0;
			for (auto file: files)
			{
				if (EndsWith(file, fname))
				{
					cout << file << endl;
					flag = 1;
				}
			}
			if (not flag) cerr << "No matches found." << endl;
			
		}
		else if (command == "exit" or command == "quit" or command == "q")
		{
			break;
		}
		else
		{
			cerr << "Invalid command." << endl;
		}
	}
}