#include "Graph.h"


Graph::Graph(vector<vector<int>> adj_Listvector, vector<vector<string>> keys, vector<int> imp, vector<int> ctr)
{
	adjList = adj_Listvector;
	N=adjList.size();
	keywords = keys;
	impressions = imp;
	CTR = ctr;
	Pagerank.resize(N);

}


void Graph::set_adjlist(vector<vector<int>> adj)
{
	adjList = adj;
}

void Graph::set_keywordlist(vector<vector<string>> keys)
{
	keywords = keys;
}

void Graph::set_impresssions(vector<int> imp)
{
	impressions = imp;
}

void Graph::set_CTR(vector<int> ctr)
{
	CTR = ctr;
}

void Graph::numpointingnodes()
{
	
	NumberOfPointers.resize(N);
	pointingNodes.resize(N);
	int counter = 0;
	for (int k = 0; k < N; k++)
	{
		counter = 0;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < adjList[i].size(); j++)
			{
				if (adjList[i][j] == k)
				{
					counter++;
					pointingNodes[k].push_back(i);
				}
			}
		}
		NumberOfPointers[k] = counter;
	}
	
}

void Graph::pageranking()
{
	int index = N;

	vector<vector<double>> temp;
	temp.resize(N);

	for (int i = 0; i < N; i++)
	{
		temp[i].resize(5);
		temp[i][0] = 1.0 / N;
	}

	int previous = 0; 
	double sum = 0;
	
	for (int j = 1; j < 5; j++)
	{
		for (int i = 0; i < N; i++)
		{
			sum = 0;
			for (int k = 0; k < pointingNodes[i].size(); k++)
			{
				previous = pointingNodes[i][k];
				sum = sum + ( double (temp[previous][j - 1]) / double (adjList[previous].size()));
				
			}
			temp[i][j] = sum;
		}
	}
	double min = 10000;
	double max = 0;
	for (int i = 0; i < temp.size(); i++)
	{
		if (temp[i][4] < min)
			min = temp[i][4];

		if (temp[i][4] > max)
			max = temp[i][4];
	}
	
	for (int i = 0; i < N; i++)
	{
		Pagerank[i] = double ( double ( (temp[i][4] - min) ) / double ( (max - min) ) );
	}

	
	
}

void Graph::printGraph()
{
	for (int i = 0; i < N; i++)
	{
		cout << i << " --> ";

		for (int v : adjList[i])
			cout << v << "  ";

		cout << endl;
	}
	cout << "---------------------" << endl;
	for (int i = 0; i < N; i++)
	{
		cout << i << " --> ";

		for (string v : keywords[i])
			cout << v << "  ";

		cout << endl;
	}
	cout << "---------------------" << endl;
	for (int i = 0; i < N; i++)
	{
		cout << i << " --> " << impressions[i];
		cout << endl;
	}
}

void Graph::start()
{
	numpointingnodes();
	pageranking();
	pagescoring();

}

void Graph::pagescoring()
{
	PageScore.resize(N);
	double exp = 0.0;
	for (int i = 0; i < N; i++)
	{
		exp = (0.1 * impressions[i]) / ( 1.0 + (0.1 * impressions[i]) );
		PageScore[i] = (0.4 * Pagerank[i]) + ((((1.0 - exp) * Pagerank[i]) + exp * CTR[i]) * 0.6);
	}
	
}

int Graph::oneWordSearch(string word)
{
	set<double> results;
	vector<int> resultsindex;
	int index=1, choice=1;
	int flag=0;

	set<double> ::reverse_iterator it = results.rbegin();
	
	
	
	while (choice == 1)
	{
		

		flag = 0;
		index = 1; 
		for (int i = 0; i < keywords.size(); i++)
		{
			for (int j = 0; j < keywords[i].size(); j++)
			{
				if (keywords[i][j] == word)
				{
					results.insert(PageScore[i]);
					flag++;
				}
			}
		}

		cout << " Search Results: \n";

		if (flag == 0)
		{
			cout << "There is no results for the entered keywords.\n" << "please choose new search and try new keywords.\n";

			cout << " Would you like to" << endl;
			cout << "1. New Search\n" << "2. Exit\n";

			cout << "Type in your choice here: ";
			cin >> choice;

			while (choice != 1 && choice != 2 )
			{
				cout << "Invalid input!\n";
				cout << " Would you like to" << endl;
				cout << "1. New Search\n" << "2. Exit\n";

				cout << "Type in your choice here: ";
				cin >> choice;
			}
			choice++;
			break;
		}
		else 
		{
			for (it = results.rbegin(); it != results.rend(); it++)
			{
				for (int i = 0; i < PageScore.size(); i++)

					if (PageScore[i] == *it)
					{
						resultsindex.push_back(i);
						cout << index << ". www.test" << i + 1 << ".com" << endl;
						impressions[i]++;
					}
				index++;
			}
	
			ofstream updateIMP;
			updateIMP.open("impressions file.csv");

			if (updateIMP.is_open())
			{

				for (int i = 0; i < impressions.size(); i++)
				{
					updateIMP << impressions[i] << ',';
				}

			}
			updateIMP.close();
			
		}
		


		cout << " Would you like to" << endl;
		cout << "1. Choose a webpage to open.\n" << "2. New Search\n" << "3. Exit\n";

		cout << "Type in your choice here: ";
		cin >> choice;

		while (choice != 1 && choice != 2 && choice != 3)
		{
			cout << "Invalid input!\n";
			cout << " Would you like to\n";
			cout << "1. Choose a webpage to open.\n" << "2. New Search\n" << "3. Exit\n \n";

			cout << "Type in your choice here: ";
			cin >> choice;
		}

		if (choice == 2 || choice == 3)
		{
			return choice;
		}
		else if (choice == 1)
		{
			cout << "choose the webpage number that you want to view.\n";

			cout << "Type in your choice here: ";
			cin >> choice;

			cout << "You are now viewing ";
			cout << "www.test" << resultsindex[choice - 1] + 1 << ".com\n";

			CTR[resultsindex[choice - 1]] ++;

			ofstream updateCTR;
			updateCTR.open("CTR.txt");

			if (updateCTR.is_open())
			{

				for (int i = 0; i < CTR.size(); i++)
				{
					updateCTR << CTR[i] << '\n';
				}

			}
			updateCTR.close();
		}

		pagescoring();
		results.clear();
		resultsindex.clear();


		cout << " Would you like to" << endl;
		cout << "1. Go back to search results.\n" << "2. New Search\n" << "3. Exit \n";

		cout << "\nType in your choice here: ";
		cin >> choice;

		while (choice != 1 && choice != 2 && choice != 3)
		{
			cout << "Invalid input!\n";
			cout << " Would you like to\n";
			cout << "1. Choose a webpage to open.\n" << "2. New Search\n" << "3. Exit\n \n";

			cout << "Type in your choice here: ";
			cin >> choice;
		}
	}

	
	return choice;
}



int Graph::orSearch(string word, string word2)
{
	set<double> results;
	vector<int> resultsindex;
	int index = 1, choice = 1;
	int flag = 0;

	set<double> ::reverse_iterator it = results.rbegin();



	while (choice == 1)
	{


		flag = 0;
		index = 1;
		for (int i = 0; i < keywords.size(); i++)
		{
			for (int j = 0; j < keywords[i].size(); j++)
			{
				if (keywords[i][j] == word || keywords[i][j] == word2)
				{
					results.insert(PageScore[i]);
					flag++;
					break;
				}
			}
		}

		cout << " Search Results: \n";

		if (flag == 0)
		{
			cout << "There is no results for the entered keywords.\n" << "please choose new search and try new keywords.\n";

			cout << " Would you like to" << endl;
			cout << "1. New Search\n" << "2. Exit\n";

			cout << "Type in your choice here: ";
			cin >> choice;

			while (choice != 1 && choice != 2)
			{
				cout << "Invalid input!\n";
				cout << " Would you like to" << endl;
				cout << "1. New Search\n" << "2. Exit\n";

				cout << "Type in your choice here: ";
				cin >> choice;
			}
			choice++;
			break;
		}
		else
		{
			for (it = results.rbegin(); it != results.rend(); it++)
			{
				for (int i = 0; i < PageScore.size(); i++)

					if (PageScore[i] == *it)
					{
						resultsindex.push_back(i);
						cout << index << ". www.test" << i + 1 << ".com" << endl;
						impressions[i]++;
					}
				index++;
			}

			ofstream updateIMP;
			updateIMP.open("impressions file.csv");

			if (updateIMP.is_open())
			{

				for (int i = 0; i < impressions.size(); i++)
				{
					updateIMP << impressions[i] << ',';
				}

			}
			updateIMP.close();
		}



		cout << " Would you like to" << endl;
		cout << "1. Choose a webpage to open.\n" << "2. New Search\n" << "3. Exit\n";

		cout << "Type in your choice here: ";
		cin >> choice;

		while (choice != 1 && choice != 2 && choice != 3)
		{
			cout << "Invalid input!\n";
			cout << " Would you like to\n";
			cout << "1. Choose a webpage to open.\n" << "2. New Search\n" << "3. Exit\n \n";

			cout << "Type in your choice here: ";
			cin >> choice;
		}

		if (choice == 2 || choice == 3)
		{
			return choice;
		}
		else if (choice == 1)
		{
			cout << "choose the webpage number that you want to view.\n";

			cout << "Type in your choice here: ";
			cin >> choice;

			cout << "You are now viewing";
			cout << "www.test" << resultsindex[choice - 1] + 1 << ".com\n";

			CTR[resultsindex[choice - 1]] ++;

			ofstream updateCTR;
			updateCTR.open("CTR.txt");

			if (updateCTR.is_open())
			{

				for (int i = 0; i < CTR.size(); i++)
				{
					updateCTR << CTR[i] << '\n';
				}

			}
			updateCTR.close();
		}

		pagescoring();
		results.clear();
		resultsindex.clear();


		cout << " Would you like to" << endl;
		cout << "1. Go back to search results.\n" << "2. New Search\n" << "3. Exit \n";

		cout << "\nType in your choice here: ";
		cin >> choice;

		while (choice != 1 && choice != 2 && choice != 3)
		{
			cout << "Invalid input!\n";
			cout << " Would you like to\n";
			cout << "1. Choose a webpage to open.\n" << "2. New Search\n" << "3. Exit\n \n";

			cout << "Type in your choice here: ";
			cin >> choice;
		}
	}


	return choice;
}

int Graph::andSearch(string word, string word2)
{
	set<double> results;
	vector<int> resultsindex;
	int index = 1, choice = 1;
	int flag = 0;

	set<double> ::reverse_iterator it = results.rbegin();



	while (choice == 1)
	{


		flag = 0;
		index = 1;
		for (int i = 0; i < keywords.size(); i++)
		{
			for (int j = 0; j < keywords[i].size(); j++)
			{
				if (keywords[i][j] == word || keywords[i][j] == word2)
				{
					if (keywords[i][j] == word)
					{
						for (int j = 0; j < keywords[i].size(); j++)
						{
							if (keywords[i][j] == word2)
							{
								results.insert(PageScore[i]);
								flag++;
							}
						}
					}
					else
					{
						for (int j = 0; j < keywords[i].size(); j++)
						{
							if (keywords[i][j] == word)
							{
								results.insert(PageScore[i]);
								flag++;
							}
						}
					}
					
					
				}
			}
		}

		cout << " Search Results: \n";

		if (flag == 0)
		{
			cout << "There is no results for the entered keywords.\n" << "please choose new search and try new keywords.\n";

			cout << " Would you like to" << endl;
			cout << "1. New Search\n" << "2. Exit\n";

			cout << "Type in your choice here: ";
			cin >> choice;

			while (choice != 1 && choice != 2)
			{
				cout << "Invalid input!\n";
				cout << " Would you like to" << endl;
				cout << "1. New Search\n" << "2. Exit\n";

				cout << "Type in your choice here: ";
				cin >> choice;
			}
			choice++;
			break;
		}
		else
		{
			for (it = results.rbegin(); it != results.rend(); it++)
			{
				for (int i = 0; i < PageScore.size(); i++)

					if (PageScore[i] == *it)
					{
						resultsindex.push_back(i);
						cout << index << ". www.test" << i + 1 << ".com" << endl;
						impressions[i]++;
					}
				index++;
			}
			
			ofstream updateIMP;
			updateIMP.open("impressions file.csv");

			if (updateIMP.is_open())
			{

				for (int i = 0; i < impressions.size(); i++)
				{
					updateIMP << impressions[i] << ',';
				}

			}
			updateIMP.close();
		}



		cout << " Would you like to" << endl;
		cout << "1. Choose a webpage to open.\n" << "2. New Search\n" << "3. Exit\n";

		cout << "Type in your choice here: ";
		cin >> choice;

		while (choice != 1 && choice != 2 && choice != 3)
		{
			cout << "Invalid input!\n";
			cout << " Would you like to\n";
			cout << "1. Choose a webpage to open.\n" << "2. New Search\n" << "3. Exit\n \n";

			cout << "Type in your choice here: ";
			cin >> choice;
		}

		if (choice == 2 || choice == 3)
		{
			return choice;
		}
		else if (choice == 1)
		{
			cout << "choose the webpage number that you want to view.\n";

			cout << "Type in your choice here: ";
			cin >> choice;

			cout << "You are now viewing";
			cout << "www.test" << resultsindex[choice - 1] + 1 << ".com\n";

			CTR[resultsindex[choice - 1]] ++;

			ofstream updateCTR;
			updateCTR.open("CTR.txt");

			if (updateCTR.is_open())
			{

				for (int i = 0; i < CTR.size(); i++)
				{
					updateCTR << CTR[i] << '\n';
				}

			}
			updateCTR.close();
		}

		pagescoring();
		results.clear();
		resultsindex.clear();


		cout << " Would you like to" << endl;
		cout << "1. Go back to search results.\n" << "2. New Search\n" << "3. Exit \n";

		cout << "\nType in your choice here: ";
		cin >> choice;

		while (choice != 1 && choice != 2 && choice != 3)
		{
			cout << "Invalid input!\n";
			cout << " Would you like to\n";
			cout << "1. Choose a webpage to open.\n" << "2. New Search\n" << "3. Exit\n \n";

			cout << "Type in your choice here: ";
			cin >> choice;
		}
	}


	return choice;
}


