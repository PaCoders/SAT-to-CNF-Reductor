/*
==============================================================================
					Search and Optimisation problem
						Francisco Chanivet Sanchez
==============================================================================
*/
#include <iostream>
#include <list>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <string.h>
#include <algorithm>

#include "reduction.h"
#include "graphs.h"
#include "translator.h"

using namespace std;

//Optimisation problem
void optimisationProblem(){
	vector< vector<int> > mat;
	translator("file/graph.txt",mat);
	size_t nClique = mat.size() + 1;
	int isClique = 0;
	while(nClique > 0 && isClique != 2560){
		--nClique;
		reductorCNF("file/graph.txt",nClique);
		isClique = system("picosat file/cnf_file.cnf > /dev/null");
		if(isClique != 2560){
			cout<<"There is not a solution for k = "<<nClique<<endl;
		}
	}
	
	if(isClique == 2560){
		cout<<"There is a solution for k = "<<nClique<<"!"<<endl;
	}
}

//Search problem
void searchProblem(){
	vector< vector<int> > mat;
	translator("file/graph.txt",mat);
	
	list<unsigned int> set;
	list<unsigned int> vertex;
	for(unsigned int i = 0; i < mat.size(); i++){
		vertex.push_back(i);
	}
	string file = "file/subgraph.txt";
	int isClique = 0;
	size_t nClique = 0;
	while(nClique < 1 || nClique > mat.size()){
		cout<<"Insert a clique number: ";
		cin>>nClique;
	}
	
	cout<<"Searching the combination...."<<endl;
	while(next_permutation(vertex.begin(),vertex.end()) && isClique != 2560){
		set = vertex;
		set.resize(nClique);
		generateDimacsSG(file,set,mat);
		
		//We execute the reductor here
		reductorCNF(file,nClique);
		
		isClique = system("picosat file/cnf_file.cnf > /dev/null");
		
	}
	
	cout<<"The nodes that make a "<<nClique<<"-clique are: "<<endl;
	list<unsigned int>::iterator it = set.begin();
	while(it != set.end()){ 
		cout<<(*it) + 1<<", ";
		++it;
	}
	cout<<endl;
}

int main(){
	//We create the DIMACS file
	vector< vector<int> > mat = {{0,1,1,1,1,0,0},{1,0,1,0,0,1,1},{1,1,0,1,0,1,0},{1,0,1,0,1,1,1},{1,0,0,1,0,1,1},{0,1,1,1,1,0,1},{0,1,0,1,1,1,0}};
	generateDimacsG("file/graph.txt",mat);
	
	int opt = 10;
	
	while(opt > 0){
		cout<<"\n============================================================="<<endl;
		cout<<"What type of problem do you want to execute? "<<endl;
		cout<<"\t 1. Optimisation problem"<<endl;
		cout<<"\t 2. Search problem"<<endl;
		cout<<"------ Introduce 0 if you want to exit. ------";
		cout<<"\n============================================================="<<endl;
		
		cout<<"Option: ";
		cin>>opt;
		cout<<endl;
		if(opt == 1){
			optimisationProblem();
			cout<<endl;
		}
		if(opt == 2){
			searchProblem();
			cout<<endl;
		}
	}
	

}
