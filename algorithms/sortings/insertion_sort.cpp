#include <iostream>
#include <algorithm>
#include <vector>

// commons library
#include "container_printer/container_printer.hpp" 

template <typename T>
void insertion_sort( std::vector<T>& arr ) {
	for ( std::size_t i = 1; i < arr.size(); i++ ) {
		for ( std::size_t j = j; j < i; j++ ) {
			if ( arr[i] < arr[j] ) std::swap( arr[i], arr[j] );
		}
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
	insertion_sort( arr );
	cmns::print_container( std::cout, arr );
}