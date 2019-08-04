#include <iostream>
#include <algorithm>
#include <vector>

// commons library
#include "container_printer/container_printer.hpp" 

void counting_sort( std::vector<int>& arr, std::size_t coverage) {
	std::vector<int> temp ( coverage, 0 );
	std::vector<int> sorted;

	for ( std::size_t i = 0; i < arr.size(); ++i ) {
		temp[arr[i] - 1] = i + 1;
	}

	for ( const auto& x : temp ) {
		if ( x != 0 ) {
			sorted.push_back( arr[x - 1] );
		}
	}

	arr = sorted;
}

int main() {
	int in, num;
	std::vector<int> arr;

	std::cin >> num;
	while( num-- ) {
		std::cin >> in;
		arr.push_back( in );
	}

	int minelem = *std::min_element( std::begin( arr ), std::end( arr ) );
	int maxelem = *std::max_element( std::begin( arr ), std::end( arr ) );

	cmns::print_container( std::cout, arr );
	counting_sort( arr, minelem, maxelem );
	cmns::print_container( std::cout, arr );
}