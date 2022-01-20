# ===================================================================
#					MAKEFILE FOR ASSIGNMENT 3
#					Francisco Chanivet Sanchez
# ===================================================================

CXX = g++
CXXFLAGS = -std=c++11 -Wall -O3
OBJS = SearchOptV.o decision.o
EXES = resolution decision

all: decision resolution

resolution: SearchOptV.o
	$(CXX) -o resolution $(CXXFLAGS) SearchOptV.o

SearchOptV.o: SearchOptV.cpp reduction.h translator.h graphs.h
	$(CXX) -c $(CXXFLAGS) SearchOptV.cpp

decision: decision.o
	$(CXX) -o decision $(CXXFLAGS) decision.o

decision.o: SearchOptV.cpp translator.h reduction.h graphs.h
	$(CXX) -c $(CXXFLAGS) decision.cpp	
	
clean:
	${RM} ${OBJS} ${EXES} core *~
