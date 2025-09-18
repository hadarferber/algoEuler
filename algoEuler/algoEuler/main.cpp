#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "node.h"
#include <chrono>
#include <ios>
#include "graph.h"
#include "node.h"
#include "edge.h"
#include "euler.h"
#include <sstream>
#include <string>

using namespace std;

int main() {
	int n;
	cin >> n;
	if (n <= 0) {
		cout << "invalid input" << endl;
		return 1;
	}
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear newline

	Graph newGraph(n);

	string edgeLine;
	getline(cin, edgeLine); // read the line with edges

	istringstream edgeStream(edgeLine);
	int firstVertex, secondVertex;   // <--- declare here
	while (edgeStream >> firstVertex >> secondVertex) {
		if (firstVertex < 1 || firstVertex > n ||
			secondVertex < 1 || secondVertex > n ||
			firstVertex == secondVertex) {
			cout << "invalid input" << endl;
			return 1;
		}
		newGraph.addEdge(firstVertex - 1, secondVertex - 1);
	}
	
	//Creating the euler object 
	Euler euler(newGraph);
	int efficientOrNotChoice, runTimeChoice;
	//getting the choice to decide if efficient or not 
	cin >> efficientOrNotChoice;
	/*if (efficientOrNotChoice != 1 || efficientOrNotChoice != 2) {
		cout << "invalid input" << endl;
		exit(1);
	}*/

	bool isEulerian = euler.checkEulerian();
	if (!isEulerian) {
		cout << "no euler cycle" << endl;
		return 0;
	}

	//getting the choice to see run time or not
	cin >> runTimeChoice;
	if (runTimeChoice == 0) {
		//no runtime
		if (efficientOrNotChoice == 1) {
			euler.runEfficientAlgorithm();
		}
		else if (efficientOrNotChoice == 2) {
			euler.runInefficientAlgorithm();
		}
	}
	else if (runTimeChoice == 1) {
		//yes runtime
		auto start = chrono::high_resolution_clock::now();
		//running the program
		if (efficientOrNotChoice == 1) {
			euler.runEfficientAlgorithm();
		}
		else if (efficientOrNotChoice == 2) {
			//run not efficient
		}

		//printing runtime measurement
		auto end = chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start); std::cout << "Function took " << duration.count() << "microseconds." << std::endl;
		
	}
	else {
		cout << "invalid input" << endl;
		exit(1);
	}


	return 0;

}