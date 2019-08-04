#include <iostream>
#include <algorithm>
#include <vector>

// commons library
#include "container_printer/container_printer.hpp" 

/**
 * Sorts integral type vector, only nonnegative values accepted.
 * elements_in_range >= min - max + 1
 */
template <typename IntegralType>
void counting_sort( std::vector<IntegralType>& arr, std::size_t elements_in_range ) {
	std::vector<IntegralType> temp ( elements_in_range + 1, IntegralType {} );
	std::vector<IntegralType> sorted;

	for ( std::size_t i = 0; i < arr.size(); ++i ) {
		temp[arr[i]] = i + 1;
	}

	for ( const auto& x : temp ) {
		if ( x != 0 ) {
			sorted.push_back( arr[x - 1] );
		}
	}

	arr = std::move( sorted );
}

template <typename IntegralType>
void counting_sort_with_negatives( std::vector<IntegralType>& arr, IntegralType min, IntegralType max ) {
	bool neg = min < 0;
	static auto array_addition {
		[] ( std::vector<IntegralType>& arr, IntegralType add ) {
			for ( auto& x : arr ) {
				x += add;
			}
		}
	};
	
	if ( neg ) array_addition( arr, -min );
	counting_sort( arr, max - min + 1 );
	if ( neg ) array_addition( arr,  min );
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
	counting_sort_with_negatives( arr, minelem, maxelem );
	cmns::print_container( std::cout, arr );
}