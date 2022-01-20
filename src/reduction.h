/* ========================================================================
					Reducing to CNF
					Francisco Chanivet Sánchez
   ========================================================================
*/


#ifndef _REDUCTION_H
#define _REDUCTION_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string.h>
#include <cstdlib>
#include "translator.h"

using namespace std;

int enumerate(vector< vector<int> >& x, size_t numVert, size_t nClique){
	// xir = "vertex i in G is vertex r in a k-clique of G"
	int numV = 1;
	
	for(size_t i = 0; i < numVert; i++){
		for(size_t r = 0; r < nClique; r++){
			x[i][r] = numV;
			++numV;
		}
	}
	
	return numV; //We obtain the number of variables
}

void editClause(size_t nVar, size_t numC){
	ifstream temporal("file/temp.cnf");
	ofstream cnf("file/cnf_file.cnf");
	string line;
	while(getline(temporal,line)){
		if(line[0] == 'p'){
			cnf<<"p cnf "<<nVar-1<<" "<<numC<<endl;
		}
		else{
			cnf<<line<<endl;
		}
	}
	cnf.close();
	temporal.close();
	remove("file/temp.cnf");
}

void reductorCNF(string file_name,size_t k){ //k is the size of clique

	vector< vector<int> > g;
	translator(file_name, g);

	ofstream file("file/temp.cnf"); //We create the file with the CNF Sat
	file<<"c Reduction to CNF\n";
	file<<"c\n";
	file<<"c\n";
	
	//At first, we need to define the number of clauses and variables that we have
	
	vector< vector<int> > num(g.size(), vector<int>(k,0));
	int nVar = enumerate(num,g.size(),k);
	size_t nCla = 0;
	
	file<<"p"<<endl; //We modify this later

	// 1st clause
	for(size_t r = 0; r < k; r++){
		for(size_t i = 0; i < g.size(); i++){
			file<<num[i][r]<<" ";
		}
		file<<"0\n";
		++nCla;
	}

	// 2nd clause 
	for(size_t i = 0; i < g.size(); i++){
		for(size_t s = 1; s < k; s++){
			for(size_t r = 0; r < s; r++){
				file<<num[i][r]*(-1)<<" "<<num[i][s]*(-1)<<" 0"<<endl;
				++nCla;
			}
		}
	}
		
	// 3rd clause
	size_t r = 0, s = 0;
	size_t i, j;
	while(r < k){
		s = 0;
		while(s < k){
			if(r != s){
				j = 1;
				while(j < g.size()){
					i = 0;
					while(i < j){
						if(g[i][j] == 0){
							file<<num[i][r]*(-1)<<" "<<num[j][s]*(-1)<<" 0"<<endl;
							++nCla;
						}
						i++;
					}
					j++;
				}
					
			}
			s++;
		}
		r++;
	}
		
	file.close();
	editClause(nVar,nCla);
}


#endif
