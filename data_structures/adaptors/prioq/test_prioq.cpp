#include "prioq.hpp"

#include <iostream>
#include <vector>
#include <queue>

int main( ) {
	alda::Prioq<int> pq { 4, 3, 2, -50, 50, -39 };

	while ( !pq.empty() ) {
		std::cout << pq.top() << " ";
		pq.pop();
	}

	std::cout << '\n';
}