/*
==========================================================================
					Dimacs generator
					Francisco Chanivet Sanchez
==========================================================================
*/

#ifndef GRAPHS_H
#define GRAPHS_H

#include <fstream>
#include <list>
#include <vector>
#include <string.h>

using namespace std;

//Function that generates a DIMACS file for a graph
void generateDimacsG(string file_name, const vector< vector<int> >& v){
	ofstream graph(file_name);
	graph<<"c Graph of this problem"<<endl;
	graph<<"c"<<endl;
	graph<<"p edge "<<v.size()<<" "<<v.size()<<endl;
	for(size_t i = 0; i < v.size(); i++){
		for(size_t j = 0; j < v.size(); j++){
			if(v[i][j] == 1){
				graph<<"e "<<i+1<<" "<<j+1<<endl;
			}
		}
	}
	
	graph.close();
	
}

//Function that generates a DIMACS file for a subgraph of a graph
void generateDimacsSG(string file_name,list<unsigned int>& vertex, const vector< vector<int> >& v){
	ofstream graph(file_name);
	graph<<"c Subgraph of this problem"<<endl;
	graph<<"c"<<endl;
	graph<<"p edge "<<v.size()<<" "<<v.size()<<endl;
	vertex.sort();
	list<unsigned int>::iterator it = vertex.begin();
	while(it != vertex.end()){
		list<unsigned int>::iterator it2 = vertex.begin();
		while(it2 != vertex.end()){
			if(v[*it][*it2] == 1){
				graph<<"e "<<(*it) + 1<<" "<<(*it2) + 1<<endl;
			}	
			++it2;
		}
		++it;
	}
		
	graph.close();
	
}

#endif
