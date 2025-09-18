#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <chrono>
#include <ios>
#include <sstream>
#include <string>

#include "Graph.h"
#include "LinkedList.h"
#include "Euler.h"

using namespace std::chrono;


int main() {

    Graph g;
    g.getVertexAmount();
    g.buildGraph();

    Euler e = Euler(&g);

    int efficiency;
	std::cin >> efficiency; // 1 = efficient, 2 = non-efficient
	if (efficiency != 1 && efficiency != 2) {
		std::cout << "Invalid input." << std::endl;
		return 0;
	}

    int showTime;
    std::cin >> showTime; // 1 = show runtime, 0 = don't show
	if (showTime != 0 && showTime != 1) {
		std::cout << "Invalid input." << std::endl;
		return 0;
	}
	bool isEulerian = g.checkEulerian();

	if (!isEulerian) {
		std::cout << "Graph is not Eulerian.";
		return 0;
	}

	auto start = high_resolution_clock::now();
    ListNode* res = e.FindEulerCycle();
    auto stop = high_resolution_clock::now();

    e.PrintCycle();

    if (showTime == 1) {
        auto duration = duration_cast<microseconds>(stop - start);
        //std::cout << duration.count() << std::endl; // print only the number
    }

    return 0;

	/*Graph g;
	g.getVertexAmount();
	g.buildGraph();
	Euler e = Euler(&g);
	ListNode* res = e.FindEulerCycle();
	e.PrintCycle();*/
	
		//Euler e = g.cycle->FindEulerCycle();
		//e.PrintCycle();
		//return 0;
}




