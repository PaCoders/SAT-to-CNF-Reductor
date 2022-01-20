/* ========================================================================
				TRANSLATOR FROM DIMACS TO A GRAPH
					Francisco Chanivet Sánchez
   ========================================================================
*/

#ifndef _TRANSLATOR_H
#define _TRANSLATOR_H

#include <vector>
#include <fstream>
#include <regex>
#include <sstream>
#include <string.h>

//Precondition: -
//Postcondition: Return with a vector two numbers of string
//We extract the numbers of text file with regular expressions
void transInt(std::string str, int *v,std::regex exp){ 
	std::sregex_iterator currentMatch(str.begin(), str.end(), exp);
	std::sregex_iterator lastMatch;
	int cont = 0;
	while(currentMatch != lastMatch && cont < 2){
		std::smatch match= *currentMatch;
		std::stringstream s1(match.str());
		s1>>*(v + cont);
		currentMatch++;
		cont++;
	}
}

//Precondition: -
//Postcondition: We fill the adjacency matrix with the values of txt
void translator(std::string file_name,std::vector< std::vector<int> >& v){

	using namespace std;
	
	string line;
	ifstream file(file_name);
	regex expression("((?:[0-9])+?)+");
	int values[2];
	while(getline(file,line)){
		if(line[0] != 'c'){
			transInt(line,values,expression);
			if(line[0] == 'p'){
				vector< vector<int> > aux(values[0], vector<int>(values[1],0));
				v = aux;
			}
			else{
				v[values[0]-1][values[1]-1] = 1;
			}
		}
	}
	
	file.close();	
}

#endif
