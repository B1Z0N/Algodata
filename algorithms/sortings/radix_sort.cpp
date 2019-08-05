#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

// commons library
#include "container_printer/container_printer.hpp" 

const std::size_t kSystemBase = 10; 


/**
 * Sorts integral type vector, only nonnegative values accepted.
 * elements_in_range >= min - max + 1
 */
template <typename IntegralType, typename F>
void counting_sort_from_zero( std::vector<IntegralType>& arr, 
							  std::size_t elements_in_range,
							  const F& transform ) {
	std::vector<IntegralType> temp ( elements_in_range + 1, IntegralType {} );
	std::vector<IntegralType> sorted;

	for ( std::size_t i = 0; i < arr.size(); ++i ) {
		temp[transform(arr[i])] += 1;
	}

	for ( std::size_t i = 0; i < temp.size(); ++i ) {
		while ( temp[i] ) {
			sorted.push_back( i ); 
			--temp[i];
		}
	}

	arr = std::move( sorted );
}

template <typename IntegralType>
void radix_sort( std::vector<IntegralType>& arr, std::size_t max_digit_num ) {
	// lambda that generates lambda that takes ith digit from a number
	static auto get_digit {
		[] ( std::size_t i ) {
			return [i] ( IntegralType num ) {

				IntegralType current_radix = pow( kSystemBase,   i  );
				IntegralType res = 
					(( num % (current_radix * kSystemBase) ) - 
					( num % current_radix )) / current_radix;

				return res;
			};
		}
	};

	for ( int i = 0; i < max_digit_num; ++i ) {
		counting_sort( arr, kSystemBase, get_digit( i ) );
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

	int minelem = *std::min_element( std::begin( arr ), std::end( arr ) );
	int maxelem = *std::max_element( std::begin( arr ), std::end( arr ) );

	cmns::print_container( std::cout, arr );
	radix_sort( arr, 3 );
	cmns::print_container( std::cout, arr );
}