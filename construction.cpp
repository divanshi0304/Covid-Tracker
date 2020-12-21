#include <bits/stdc++.h>
#include <sqlite3.h>
#include <unordered_map>
#include <list>
#include <iterator>
#include <fstream>

using namespace std;

class Graph
{
	unordered_map<string, list<pair<string, long double>>> l;

	public:
		void addEdge(string x, string y, long double wt)
		{
			l[x].push_back(make_pair(y, wt));
			l[y].push_back(make_pair(x, wt));
			return;
		}
    unordered_map<string, list<pair<string, long double>>> :: iterator it=l.begin();
    void Displaygraph()
    {
      // iterator it::l.begin();
      for(auto p:l)
      {
        string src=p.first;
        list<pair<string, long double>> nbrs=p.second;
        cout<<src<<": ";
        for(auto nbr:nbrs)
        {
          string dest=nbr.first;
          long double dist=nbr.second;
          // cout<<dest<<" "<<dist<<", ";
        }
        cout<<endl;
      }
			return;
		}
		string shortestPath(string landmark)
		{
			unordered_map<string,long double> dist;
			if(landmark.at(0)=='C')
			{
				// cout<<landmark<<"is the nearest Covid Centre to you"<<endl;
				return landmark;
			}
			//Set all distances to max
			for(auto entry:l)
				dist[entry.first]=INT_MAX;

			//make set to find node with minimum distance from landmark
			set<pair<long double,string>> s;
			dist[landmark]=0;
			s.insert(make_pair(0,landmark));
			while(!s.empty())
			{
				//find dist, node name of starting node for each iteration
				auto p=*(s.begin());
				string node=p.second;
				long double nodeDist=p.first;
				s.erase(s.begin());

				//iterate over ngbrs of current node
				for(auto ngbrs:l[node])
				{
					if(nodeDist+ngbrs.second<dist[ngbrs.first])
					{
						string dest=ngbrs.first;
						auto f=s.find(make_pair(dist[dest],dest));
						if(f!=s.end())
							s.erase(f);
						dist[dest]=nodeDist+ngbrs.second;
						s.insert(make_pair(dist[dest],dest));
					}
				}
			}

			string closestCentre;
			long double minDist=INT_MAX;
			for(auto d:dist)
			{
				string centre=d.first;
				long double dist=d.second;
				char ch=centre.at(0);
				if(ch=='C' && dist<minDist)
				{
					minDist=dist;
					closestCentre=centre;
				}
				// cout<<d.first<<" is located at distance of  "<<d.second<<endl;
			}
			// cout<<"Minimun "

			cout<<"Nearest covid center is located at a distance of  "<<minDist<<" KM"<<endl;
			return (closestCentre);
		}

}centre;

// Graph centre;

// This is the callback function to display the select data in the table
static int callback(void *NotUsed, int argc, char **argv, char **szColName)
{

	std::size_t temp = 20;
    string x=argv[0];
    string y=argv[1];
		string z (argv[2]);
		long double a1=stold(z, &temp);

  centre.addEdge(x, y, a1);

  // std::cout << "\n";

  return 0;
}

int main()
{
  sqlite3 *db;
  char *szErrMsg = 0;

  // open database
  // int rc = sqlite3_open("Sqlite_Test.db", &db);
  int rc = sqlite3_open("graph.sqlite", &db);

  // if(rc)
  // {
  //   std::cout << "Can't open database\n";
  // } else {
  //   std::cout << "Open database successfully\n";
  // }

  // prepare our sql statements
  const char *pSQL[6];
  pSQL[0] = "CREATE TABLE Employee(Firstname varchar(30), Lastname varchar(30), Age smallint)";
  pSQL[1] = "SELECT * FROM Dist_LL";
  pSQL[2] = "SELECT * FROM Dist_CL";
  pSQL[3] = "SELECT * FROM Dist_CC";



  // execute sql
  for(int i = 1; i < 4; i++)
  {
    rc = sqlite3_exec(db, pSQL[i], callback, 0, &szErrMsg);
    if(rc != SQLITE_OK)
    {
      std::cout << "SQL Error: " << szErrMsg << std::endl;
      sqlite3_free(szErrMsg);
      break;
    }
  }

  // close database
  if(db)
  {
    sqlite3_close(db);
  }
  // centre.Displaygraph();
  cout<<endl;

	string value;
  ifstream myfile ("value.txt");
  if (myfile.is_open())
  {

		getline (myfile,value);
		// cout<<value;
    myfile.close();
  }

	string mycenter= centre.shortestPath(value);
	// cout<<endl<<mycenter<<endl;
	ofstream myfile1 ("mycenter.txt");
if (myfile1.is_open())
{
	myfile1 << mycenter;
	// myfile << "This is another line.\n";
	myfile1.close();
}
else cout << "Unable to open file";
  return 0;
}
