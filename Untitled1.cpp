//project tracker
#include<bits/stdc++.h>
#include <iostream>
#include <unordered_map>
#include <list>
#include <string>
using namespace std;

template<typename T>
class Graph
{
	unordered_map<T,list<pair<T,int>>> n;
	public:
		void addEdge(T loc1, T loc2, int dist)
		{
			n[loc1].push_back(make_pair(loc2,dist));
			n[loc2].push_back(make_pair(loc1,dist));
		}
		
		void shortestPath(T landmark)
		{
			unordered_map<T,int> dist;
			if(landmark.at(0)=='C')
			{
				cout<<landmark<<"is the nearest Covid Centre to you"<<endl; 
				return;
			}
			//Set all distances to max
			for(auto entry:n)
				dist[entry.first]=INT_MAX;
				
			//make set to find node with minimum distance from landmark
			set<pair<int,T>> s;
			dist[landmark]=0;
			s.insert(make_pair(0,landmark));
			while(!s.empty())
			{
				//find dist, node name of starting node for each iteration
				auto p=*(s.begin());
				T node=p.second;
				int nodeDist=p.first;
				s.erase(s.begin());
				
				//iterate over ngbrs of current node
				for(auto ngbrs:n[node])
				{
					if(nodeDist+ngbrs.second<dist[ngbrs.first])
					{
						T dest=ngbrs.first;
						auto f=s.find(make_pair(dist[dest],dest));
						if(f!=s.end())
							s.erase(f);
						dist[dest]=nodeDist+ngbrs.second;
						s.insert(make_pair(dist[dest],dest));
					}
				}
			}
			
			T closestCentre;
			int minDist=INT_MAX;
			for(auto d:dist)
			{
				T centre=d.first;
				int dist=d.second;
				char ch=centre.at(0);
				if(ch=='C' && dist<minDist)
				{
					minDist=dist;
					closestCentre=centre;
				}
				cout<<d.first<<" is located at distance of  "<<d.second<<endl;
			}
			cout<<closestCentre<<" is located at distance of  "<<minDist<<endl;
		}
};
int main()
{
    Graph<string> india;
    india.addEdge("Amritsar","Delhi",1);
    india.addEdge("Amritsar","Jaipur",4);
    india.addEdge("Jaipur","Delhi",2);
    india.addEdge("Jaipur","Mumbai",8);
    india.addEdge("Bhopal","Agra",2);
    india.addEdge("Mumbai","Bhopal",3);
    india.addEdge("Agra","Delhi",1);
    //india.printAdj();
    india.shortestPath("Amritsar");


 return 0;
}


