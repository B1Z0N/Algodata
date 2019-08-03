#include <iostream>
#include <array>
#include <fstream>
#include <vector>


// @Problem
// The N Queen is the problem of placing N chess queens 
// on an N×N chessboard so that no two queens attack each other.
//
// @Example
// 4x4
// Answer:
// +---+---+---+---+
// |   |   | q |   |
// +---+---+---+---+
// | q |   |   |   |
// +---+---+---+---+
// |   |   |   | q |
// +---+---+---+---+
// |   | q |   |   |
// +---+---+---+---+
// 
// @Input format
// 4
//
// @Output format
// 0 0 q 0
// q 0 0 0
// 0 0 0 q
// 0 q 0 0 
//


class Board : public std::vector<std::vector<bool>>
{
	using elem_t = std::vector<bool>;
	using parent_t = std::vector<elem_t>;
public:
	Board( std::size_t n, bool val ) 
	: parent_t { n, elem_t ( n, val ) } {}
	Board() : parent_t{} {}
};

std::istream& operator>>( std::istream& is, Board& brd ) {
	int n;
	is >> n;
	brd = Board ( n, false );

	return is;
}

std::ostream& operator<<( std::ostream& os, const Board& brd ) {
	for ( auto row : brd ) {
		for ( auto elem : row ) {
			os << elem << ' ';
		}
		os << '\n';
	}

	return os;
}

/**
 * Function to indicate if this queen can't attack any other
 */
bool is_matching( const Board& brd, std::size_t row, std::size_t column ) {
	/* row was already checked by solve_queen */

	/* check column */
	for ( std::size_t i = 0; i < brd.size(); ++i ) {
		if ( brd[i][column] ) return false;
	}

	/* check upper left diagonal */
	for ( int i = row, j = column; i >= 0 && j >= 0; --i, --j ) {	// int because std::size_t is always positive
		if ( brd[i][j] ) return false;
	}

	/* check upper right diagonal */
	for ( int i = row, j = column; i >= 0 && j < brd.size(); --i, ++j ) {	// int because std::size_t is always positive
		if ( brd[i][j] ) return false;
	}

	return true;
}

/** 
 * Function to solve sudoku, the answer is written to `gr`,
 * returns boolean indicating if it could be solved
 */
bool solve_queen( Board& brd, std::size_t row ) {
	if ( row == brd.size() ) return true;

	for ( std::size_t column = 0; column < brd.size(); ++column ) {
		if ( is_matching( brd, row, column ) ) {
			brd[row][column] = true;
			if ( solve_queen( brd, row + 1 ) ) {
				return true;
			}
			brd[row][column] = false;
		}
	}

	return false;
}


int main( int argc, char** argv ) {
	Board brd;
	std::cin >> brd;
	solve_queen( brd, 0 );
	std::cout << brd;
}