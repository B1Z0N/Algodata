#include <iostream>
#include <array>
#include <fstream>
#include <vector>


// @Problem
// Given a partially filled 9×9 2D array ‘grid[9][9]’, 
// the goal is to assign digits (from 1 to 9) to the empty 
// cells so that every row, column, and subgrid of size 3×3 
// contains exactly one instance of the digits from 1 to 9.
//
// @Example
// +---+---+---+---+---+---+---+---+---+
// | 3 |   | 6 | 5 |   | 8 | 4 |   |   |
// +---+---+---+---+---+---+---+---+---+
// | 5 | 2 |   |   |   |   |   |   |   |
// +---+---+---+---+---+---+---+---+---+
// |   | 8 | 7 |   |   |   |   | 3 | 1 |
// +---+---+---+---+---+---+---+---+---+
// |   |   | 3 |   | 1 |   |   | 8 |   |
// +---+---+---+---+---+---+---+---+---+
// | 9 |   |   | 8 | 6 | 3 |   |   | 5 |
// +---+---+---+---+---+---+---+---+---+
// |   | 5 |   |   | 9 |   | 6 |   |   |
// +---+---+---+---+---+---+---+---+---+
// | 1 | 3 |   |   |   |   | 2 | 5 |   |
// +---+---+---+---+---+---+---+---+---+
// |   |   |   |   |   |   |   | 7 | 4 |
// +---+---+---+---+---+---+---+---+---+
// |   |   | 5 | 2 |   | 6 | 3 |   |   |
// +---+---+---+---+---+---+---+---+---+
// 
//
// @Input format
// 3 0 6 5 0 8 4 0 0
// 5 2 0 0 0 0 0 0 0
// 0 8 7 0 0 0 0 3 1
// 0 0 3 0 1 0 0 8 0
// 9 0 0 8 6 3 0 0 5
// 0 5 0 0 9 0 6 0 0
// 1 3 0 0 0 0 2 5 0
// 0 0 0 0 0 0 0 7 4
// 0 0 5 2 0 6 3 0 0
//
// @Output format
// 			????


constexpr std::size_t sudoku_size = 9;
constexpr std::size_t sudoku_empty = 0;

using Grid = std::vector<std::vector<std::size_t>>;

std::ostream& operator<<( std::ostream& os, const Grid& gr ) {
	for ( auto i : gr ) {
		for ( auto j : i ) {
			os << j << " ";
		}
		os << '\n';
	}

	return os;
}

std::istream& operator>>( std::istream& is, Grid& gr ) {
	// for ( auto& i : gr ) {
	// 	for ( auto& j : i ) {
	// 		is >> j;
	// 	}
	// }
	std::size_t val;
	gr.clear();

	for ( std::size_t i = 0; i < sudoku_size; ++i ) {
		gr.push_back( { } );
		for ( std::size_t j = 0; j < sudoku_size; ++j ) {
			is >> val;
			gr[i].push_back( val );
		}
	}

	return is;
}

/**
 * Function to indicate if this element do not violates
 * rules of sudoku puzzle
 */
bool is_matching( const Grid& gr, std::size_t i, std::size_t j ) {
	std::size_t elem = gr[i][j];
	if ( gr[i][j] == sudoku_empty ) return true;

	// checking violation of row rule
	for ( std::size_t column = 0; column < sudoku_size; ++column ) {
		if ( elem == gr[i][column] && column != j ) return false;
	}

	// checking violation of column rule
	for ( std::size_t row = 0; row < sudoku_size; ++row ) {
		if ( elem == gr[row][j] && row != i ) return false;
	}

	// checking violation of 3x3 square rule
	// select one of nine subgrids in which our element placed
	std::size_t row_start = i - i % 3, col_start = j - j % 3;
	
	// and check all square that starts at 
	// ( row_start, col_start ) and ends at
	// ( row_start + sudoku_size / 3, col_start + sudoku_size / 3 )
	for ( std::size_t row = row_start; row < row_start + 3; ++row ) {
		for ( std::size_t column = col_start; column < col_start + 3; ++column ) {
			if ( elem == gr[row][column] && row != i && column != j ) return false;
		}
	}

	return true;
}

/** 
 * Function to solve sudoku, the answer is written to `gr`,
 * returns boolean indicating if it could be solved
 */
bool solve_sudoku( Grid& gr, const std::pair<std::size_t, std::size_t>& index ) {
	if ( index.first >= sudoku_size ) return true;
	static auto next_index {
		[ ] ( const std::pair<std::size_t, std::size_t>& index ) -> std::pair<std::size_t, std::size_t> {
			// if it is the last column, increment row

			if( index.second == sudoku_size - 1 ) {
				return { index.first + 1, 0 };
			}
			else {
				return { index.first, index.second + 1 }; 
			};
		}
	};

	int i = index.first, j = index.second;
	auto next_ind = next_index( index );

	if ( gr[i][j] == sudoku_empty ) {
		for ( std::size_t k = 1; k <= sudoku_size; ++k ) {
			gr[i][j] = k;
			if ( is_matching( gr, i, j ) && solve_sudoku( gr, next_ind ) ) {
				return true;
			}
		}
		gr[i][j] = sudoku_empty;
		return false;
	}
	else {
		return solve_sudoku( gr, next_ind );
	}
}

int main( int argc, char** argv ) {
	if( argc < 2 ) return 0;
	std::ifstream ifs { argv[1] };
	Grid gr;
	ifs >> gr;
	solve_sudoku( gr, { 0, 0 } );
	std::cout << gr;
}