#include <iostream>
#include <algorithm>
#include <vector>

// commons library
#include "container_printer/container_printer.hpp" 

template <typename T>
void bubble_sort( std::vector<T>& arr ) {
	for ( std::size_t i = 0; i < arr.size() - 1; i++ ) {
		for ( std::size_t j = 0; j < arr.size() - i - 1; j++ ) {
			if ( arr[j] > arr[j + 1] ) {
				std::swap( arr[j], arr[j + 1] );
			}
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
	bubble_sort( arr );
	cmns::print_container( std::cout, arr );
}