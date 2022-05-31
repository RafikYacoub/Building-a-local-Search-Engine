#include "Graph.h"


vector<vector<int>> readGraphFile (string file_name);
vector<vector<string>> readKeywordFile (string file_name);
vector<int> readImpressionsFile (string file_name);
vector<int> readCTRFile(string file_name);

int newSearch(Graph network);

int main()
{
	vector<vector<int>> adj = readGraphFile("Web Graph File.csv");
	vector<vector<string>> keys = readKeywordFile("Keyword file.csv");
	vector <int> imp = readImpressionsFile("impressions file.csv");
	vector<int> CTR = readCTRFile("CTR.txt"); 
	Graph network(adj, keys, imp, CTR);
	network.start();


	int choice;

	cout << "Welcome!" << endl << "What would you like to do? " << endl << "1. New Search " << endl << "2. Exit " << endl;
	cout << endl << "Type in your choice here: ";
	cin >> choice;

	while (choice != 1 && choice != 2)
	{
		cout << "Invalid input!\n";
		cout << "What would you like to do? " << endl << "1. New Search " << endl << "2. Exit " << endl;
		cout << endl << "Type in your choice here: ";
		cin >> choice;
	}


	while (choice == 1)
	{
		 choice = newSearch(network);
		 CTR = readCTRFile("CTR.txt");
		 imp = readImpressionsFile("impressions file.csv");
		 network.set_CTR(CTR);
		 network.set_impresssions(imp);

	}

	
	if (choice == 2)
	{
		cout << "I hope you enjoyed searching using our search engine :) bye!";
		return 0;
	}
	
	
	
	return 0;
}



int newSearch(Graph network)
{
	int choice = 0;
	string word;
	vector <string> input;
	input.resize(4);

	cout << "Please Enter you search keywords, 2 keywords at most. \nYou may use words like AND, OR, and Quotation marks (\"\") "
		<< "between if needed to used between 2 keywords. \nYour search keywords: ";

	cin.ignore();

	getline(cin, input[0],'\n'); //to divide the string into separate substrings  
	
	int i = 1;
	
	for (auto x : input[0])
	{
		if (x == ' ')
		{
			
			//cout << word << endl;
			word = "";
			i++;
		}
		else {
			word = word + x;
			input[i] = word;
		}
	}
	
	if (input[2].empty() && input[3].empty()) //user entered one word
	{
		choice = network.oneWordSearch(input[1]);
		choice--;
	}
	else if (input[1][0] == '"')
	{ 
		string word;
		word = input[1].substr(1, input[1].size() - 1);
		word = word + " " + input[2].substr(0, input[2].size() - 1);
		choice = network.oneWordSearch(word);
		choice--;
	}
	else
	{
		if (input[2] == "and" || input[2] == "AND")
		{
			choice = network.andSearch(input[1], input[3]);
			choice--;
		}
		else if (input[2] == "or" || input[2] == "OR")
		{
			choice = network.orSearch(input[1], input[3]);
			choice--;
		}
		else if ((input[3].length() == 0) && input[1][0] != '\"')
		{
			choice = network.orSearch(input[1], input[2]);
			choice--;
		}
	}

	
	while (choice != 1 && choice != 2)
	{
		cout << "Invalid input!\n";
		cout << "What would you like to do? " << endl << "1. New Search " << endl << "2. Exit " << endl;
		cout << endl << "Type in your choice here: ";
		cin >> choice;
	}

	return choice;
}


vector<vector<int>> readGraphFile(string file_name)
{
	vector<vector<int>> adj_list;
	adj_list.resize(10);

	string source, destination;
	int src, dest;

	ifstream Web_Graph_File;
	Web_Graph_File.open(file_name);

	if (Web_Graph_File.is_open())
	{
		while (Web_Graph_File.good())
		{
			getline(Web_Graph_File, source, ',');
			getline(Web_Graph_File, destination, '\n');

			if (source[8] == '1' && source[9] == '0')
			{
				src = 10;
			}
			else
			{
				src = atoi(&source[8]);
			}

			if (destination[8] == '1' && destination[9] == '0')
			{
				dest = 10;
			}
			else
			{
				dest = atoi(&destination[8]);
			}

			//cout << src - 1 << "  " << dest - 1 << endl;
			adj_list[src - 1].push_back(dest - 1);
			
		}
	}

	Web_Graph_File.close();

	return adj_list;
}

vector<vector<string>> readKeywordFile(string file_name)
{
	vector<vector<string>> keyword_list;
	keyword_list.resize(10);

	string site, word1, word2, word3, word4, word5;
	int src;

	ifstream keyword_File;
	keyword_File.open(file_name);

	if (keyword_File.is_open()) {
		while (keyword_File.good())
		{
			getline(keyword_File, site, ',');
			getline(keyword_File, word1, ',');
			getline(keyword_File, word2, ',');
			getline(keyword_File, word3, ',');
			getline(keyword_File, word4, ',');
			getline(keyword_File, word5, '\n');


			if (site[8] == '1' && site[9] == '0')
			{
				src = 10;
			}
			else
			{
				src = atoi(&site[8]);
			}


			keyword_list[src - 1].push_back(word1);
			keyword_list[src - 1].push_back(word2);
			keyword_list[src - 1].push_back(word3);
			keyword_list[src - 1].push_back(word4);
			keyword_list[src - 1].push_back(word5);
		}
	}

	keyword_File.close();

	return keyword_list;
}

vector<int> readImpressionsFile(string file_name)
{
	vector<int> impressions_list;
	impressions_list.resize(10);

	string  number;
	int  n = 0, i=0;

	ifstream Impressions_File;
	Impressions_File.open(file_name);

	if (Impressions_File.is_open())
	{
		while (Impressions_File.good())
		{
			getline(Impressions_File, number, ',');
			if (!number.empty())
			{
				n = stoi(number);
				impressions_list[i] = n;
			}		
			i++;
		}
	}
	Impressions_File.close();

	return impressions_list;
}

vector<int> readCTRFile(string file_name)
{
	vector<int> CTR;
	CTR.resize(10);

	ifstream CTR_File;
	CTR_File.open(file_name);

	if (CTR_File.is_open())
	{
		CTR_File >> CTR[0] >> CTR[1] >> CTR[2] >> CTR[3] >> CTR[4] >> CTR[5] >> CTR[6] >> CTR[7] >> CTR[8] >> CTR[9];
	}
	CTR_File.close();

	return CTR;
}

