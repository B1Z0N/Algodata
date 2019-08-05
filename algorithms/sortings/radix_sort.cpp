#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

// commons library
#include "container_printer/container_printer.hpp" 

const std::size_t kSystemBase = 10; 


/**
 * Sorts integral type vector, only nonnegative values accepted.
 */
template <typename IntegralType, typename F>
void counting_sort_from_zero( std::vector<IntegralType>& arr, 
							  std::size_t elements_in_range,
							  const F& transform ) {
	std::vector<std::size_t> temp ( elements_in_range, IntegralType {} );
	std::vector<IntegralType> sorted ( arr.size() );

	for ( std::size_t i = 0; i < arr.size(); ++i ) {
		temp[transform(arr[i])] += 1;
	}

	for ( std::size_t i = 1; i < temp.size(); ++i ) {
		temp[i] = temp[i - 1] + temp[i];
	}

	for ( int i = arr.size() - 1; i >= 0; --i ) {
		auto& found { temp[transform(arr[i])] };
		sorted[--found] = arr[i];

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
		counting_sort_from_zero( arr, kSystemBase, get_digit( i ) );
	}
}

template <typename IntegralType>
void radix_sort( std::vector<IntegralType>& arr ) {
	std::size_t max_digit_num { };
	std::for_each( std::begin( arr ), std::end( arr ),
		// find number of digits 
		[&max_digit_num] ( IntegralType& num ) {
			std::size_t next_digit_num { 1 };
			// finding order of this num
			while ( num /
					static_cast<int>( 
						pow( kSystemBase, next_digit_num ) 
					) 
				  ) ++next_digit_num;

			if ( next_digit_num > max_digit_num ) 
				max_digit_num = next_digit_num;
		}
	);

	radix_sort( arr, max_digit_num );
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
	radix_sort( arr );
	cmns::print_container( std::cout, arr );
}