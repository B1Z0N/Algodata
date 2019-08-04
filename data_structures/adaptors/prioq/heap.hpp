#ifndef MAX_HEAP_HPP
#define MAX_HEAP_HPP

#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>

namespace alda {

template <typename T, typename Comparator = std::less<T>>
void max_heapify( std::vector<T>& arr, std::size_t length, std::size_t index ) {
	static Comparator comp {};
	std::size_t left  = 2 * index + 1;
	std::size_t right = 2 * index + 2;
	std::size_t largest = index;

	if ( left < length && comp( arr[largest], arr[left] ) )
		largest = left;
	if ( right < length && comp( arr[largest], arr[right] ) )
		largest = right;

	if ( largest != index ) {
		std::swap( arr[index], arr[largest] );
		max_heapify<T, Comparator>( arr, length, largest );
	}
}

template <typename T, typename Comparator = std::less<T>>
void build_max_heap( std::vector<T>& arr ) {
	for ( int i = arr.size() / 2 - 1; i >= 0; --i ) {
		max_heapify<T, Comparator>( arr, arr.size(), i );
	}
}

template <typename T, typename Comparator = std::less<T>>
void pop_heap( std::vector<T>& arr ) {
	std::swap( arr.front(), arr.back() );
	max_heapify<T, Comparator>( arr, arr.size() - 1, 0 );
}

template <typename T, typename Comparator = std::less<T>>
void push_heap( std::vector<T>& arr ) {
	std::swap( arr.front(), arr.back() );
	max_heapify<T, Comparator>( arr, arr.size(), 0 );
}

};	// alda

#endif	// MAX_HEAP_HPP
