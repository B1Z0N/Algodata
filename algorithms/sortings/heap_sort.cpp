#include <iostream>
#include <algorithm>
#include <vector>

// commons library
#include "container_printer/container_printer.hpp" 

template <typename T>
void max_heapify( std::vector<T>& arr, std::size_t length, std::size_t index ) {
	std::size_t left  = 2 * index + 1;
	std::size_t right = 2 * index + 2;
	std::size_t largest = index;

	if ( left < length && arr[largest] < arr[left] )
		largest = left;
	if ( right < length && arr[largest] < arr[right] )
		largest = right;

	if ( largest != index ) {
		std::swap( arr[index], arr[largest] );
		max_heapify( arr, length, largest );
	}
}

template <typename T>
void build_max_heap( std::vector<T>& arr ) {
	for ( int i = arr.size() / 2 - 1; i >= 0; --i ) {
		max_heapify( arr, arr.size(), i );
	}
}

template <typename T>
void heap_sort( std::vector<T>& arr ) {
	build_max_heap( arr );
	for ( std::size_t i = arr.size() - 1; i > 0; --i ) {
		std::swap( arr[i], arr[0] );
		max_heapify( arr, i, 0 );
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
	heap_sort( arr );
	cmns::print_container( std::cout, arr );
}