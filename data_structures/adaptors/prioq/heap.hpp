#ifndef MAX_HEAP_HPP
#define MAX_HEAP_HPP

#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>

namespace alda {

template <typename T, typename Comparator = std::less<T>>
void max_heapify_to_right( std::vector<T>& arr, 
						   std::size_t index, 
						   Comparator comp_less = std::less<T>() ) {
	int left  = arr.size() - ( 2 * (arr.size() - index - 1) + 1 ) - 1;
	int right = arr.size() - ( 2 * (arr.size() - index - 1) + 2 ) - 1;
	std::size_t largest = index;

	if ( left >= 0 && comp_less( arr[largest], arr[left] ) )
		largest = left;
	if ( right >= 0 && comp_less( arr[largest], arr[right] ) )
		largest = right;

	if ( largest != index ) {
		std::swap( arr[index], arr[largest] );
		max_heapify_to_right( arr, largest );
	}
}

template <typename T, typename Comparator = std::less<T>>
void build_max_heap_to_right( std::vector<T>& arr, Comparator comp_less = std::less<T>() ) {
	for ( int i = arr.size() / 2; i < arr.size(); ++i ) {
		max_heapify_to_right( arr, i, comp_less );
	}
}

};	// alda

#endif	// MAX_HEAP_HPP