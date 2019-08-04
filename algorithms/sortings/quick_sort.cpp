#include <iostream>
#include <algorithm>
#include <vector>

// commons library
#include "container_printer/container_printer.hpp" 

template <typename T>
std::size_t partition( std::vector<T>& arr, std::size_t start, std::size_t end ) {
	std::size_t mid = start;
	for ( std::size_t i = start + 1; i < end; i++ ) {
		if ( arr[i] < arr[mid] ) {
			std::swap( arr[i], arr[mid] );
		}

		mid++
	}

	return mid;
}

template <typename T>
void __quick_sort( std::vector<T>& arr, std::size_t start, std::size_t end ) {
	if ( start < end ) {
		std::size_t mid = partition( arr, start, end );

		__quick_sort( arr, start, mid   );
		__quick_sort( arr, mid + 1, end );
	}
}

template <typename T>
void quick_sort( std::vector<T>& arr ) {
	__quick_sort( arr, 0, arr.size() );
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
	quick_sort( arr );
	cmns::print_container( std::cout, arr );
}