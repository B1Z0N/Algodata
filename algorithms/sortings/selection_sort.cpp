#include <iostream>
#include <algorithm>
#include <vector>

// commons library
#include "container_printer/container_printer.hpp" 

template <typename T>
void selection_sort( std::vector<T>& arr ) {
	for ( std::size_t i = 0; i < arr.size() - 1; i++ ) {
		std::size_t min = i;
		for ( std::size_t j = i + 1; j < arr.size(); j++ ) {
			if ( arr[min] > arr[j] ) min = j;
		}
		std::swap( arr[min], arr[i] );
	}
}


int main() {
	int in, num;
	std::vector<int> arr;

	std::cin >> num;
	while( num-- ) {
		std::cin >> in;
		arr.push_back( in );
	}

	cmns::print_container( std::cout, arr );
	selection_sort( arr );
	cmns::print_container( std::cout, arr );
}