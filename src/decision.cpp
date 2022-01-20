/*
==============================================================================
							Decision problem
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

using namespace std;

int main(){
	vector< vector<int> > mat = {{0,1,1,1,1,0,0},{1,0,1,0,0,1,1},{1,1,0,1,0,1,0},{1,0,1,0,1,1,1},{1,0,0,1,0,1,1},{0,1,1,1,1,0,1},{0,1,0,1,1,1,0}};
	generateDimacsG("file/graph.txt",mat);
	
	size_t nClique = 0;
	while(nClique < 1 || nClique > mat.size()){
		cout<<"Insert a number for k: ";
		cin>>nClique;
	}
	
	reductorCNF("file/graph.txt",nClique);
	
	int isClique = system("picosat file/cnf_file.cnf");
}
