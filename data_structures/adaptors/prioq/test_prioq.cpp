#include "prioq.hpp"

#include <iostream>
#include <vector>
#include <queue>
#include <functional>

int main( ) {
	alda::Prioq<int> pq { 100, -1, 2, -3, 4, -5, 6, -7, 8, -20};

	while ( !pq.empty() ) {
		std::cout << pq.top() << " ";
		pq.pop();
	}

	std::cout << '\n';
}