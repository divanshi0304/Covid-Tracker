//project tracker

#include <iostream>
#include <unordered_map>
#include <list>
#include <string>
using namespace std;

class Graph
{
	unordered_map<string,bool,list<pair<string,int,bool>>> n;
	public:
		void addEdge(string loc1, string loc2, int dist, bool covidCentre)
		{
			n[loc1]push_back(make_pair(loc2,dist,covidCentre));
			n[loc2]push_back(make_pair(loc1,dist,covidCentre));
		}
		
		void shortestPath(string landmark)
		{
			unordered_map<string,int,bool> dist;
			if([n[0].second]==true)
			{
				cout<<landmark<<"is the nearest Covid Centre to you"<<endl; 
				return;
			}
			//Set all distances to max
			for(auto entry:n)
				dist[entry.first]=INT_MAX;
				
			//make set to find node with minimum distance from landmark
			set<pair<int,string>> s;
			dist[landmark]=0;
			s.insert(make_pair(0,landmark));
			while(!s.empty())
			{
				//find dist, node name of starting node for each iteration
				auto p=*(s.begin());
				string node=p.second;
				int nodeDist=p.first;
				s.erase(s.begin());
				
				//iterate over ngbrs of current node
				for(auto ngbrs:n[node,false])
				{
					if(nodeDist+ngbrs.second<dist[ngbrs.first])
					{
						string dest=ngbrs.first;
						auto f=s.find(make_pair(dist[dest],dest))
						if(f!=s.end())
							s.erase(f);
						dist[dest]=nodeDist+ngbrs.second;
						s.insert(make_pair(dist[dest],dest));
					}
				}
			}
			
		}
}
