#include <iostream>	// cin, cout
#include <ios>		// streamsize
#include <vector>	// vector
#include <fstream>	// ifstream
#include <limits>	// numeric_limits<streamsize>::max

template <typename __Istream>
std::string __input( __Istream&);

std::string input( const char* fname = nullptr );

template <typename __Ostream>
void __output( __Ostream&, const std::string& );

void output( const std::string&, const char* fname = nullptr );


//------------------------------------------------------------------
// @Problem
// Encode and decode information with Huffman encoding
//
// You are given an array of elements with attributes
// freq ( x.freq ) and val ( x.val )
//
// @Example
// 1. You are given a text, so you capture letter's frequencies
// and push it to the table
//
// 2. Buiding binary tree
// +------+-----+-----+-----+-----+
// | val  | 'a' | 'b' | 'c' | 'd' |
// +------+-----+-----+-----+-----+
// | freq |  14 |  5  |  9  |  7  |
// +------+-----+-----+-----+-----+
//
// so lets build code tree:
// * Find two vals with minimal frequencies and push it to the tree,
//   root of this two nodes added to the table
//   ( 0 is the least of two vals and 1 is another)
//
//  			 ''(12)
//				 /	 \
//			   0/	  \1
//	 	  'b'(5)	  'd'(7)
//
// * Repeat previous step with new data
//
// 				 ''(21)
// 				 /	 \
// 			   0/	  \1
// 			'c'(9)  ''(12)
// 					 /	 \
// 				   0/	  \1
// 			   'b'(5)	  'd'(7)
//
// * And again
//
//		    	   ''(35)
//		    	   /  \
//		    	 0/	   \1
//		     'a'(14) ''(21)
//		    		 /	 \
//		    	   0/	  \1
//		    	'c'(9)  ''(12)
//		    			 /	 \
//		    		   0/	  \1
//		    	   'b'(5)	  'd'(7)
//
// the solution is binary ( not search ) tree mentioned above,
// so, for example, code for 'a' is 0 and code for 'b' is 110
// code of 'cabad' is 10 0 110 0 111
//					   c a  b  a  d
//
// P. S. we should've been encoding our initial text, but it is to
// cumbersome to show it as an example, just use the same algorithm
// to encode and decode( in 3rd item ) initial text
//
// 3. Decoding
//
// let us decode this, we are given tree above and
// a code mentioned above ( cabad )
//
// we have code 1001100111
// * take 1, go right in the tree, take 0 go left and stop,
// because there are no way further, so we get 'c' as a first letter
//
// * in the same way we get 'a', 'b', 'a', and 'd', we can't have any
// ambiguity in letters, cause this is the property of a Huffman encoding
//
// @Input format
// cabad
//
// @Output
// 1001100111
//-----------------------------------------------------------------------------


/**
 * Structure to represent tree node
 */
struct Node
{
	uNodeptr left;
	std::unqiue_ptr<Node> right;

	char val;
	int freq;
};

using uNodeptr = std::unique_ptr<Node>;

struct uNodeptr_greater
{
	bool operator()( const uNodeptr& fst, const uNodeptr& snd )
	{ 
		return fst->freq > snd->freq 
	}
};

using prioque = std::priority_queue <
                uNodeptr,
                std::vector<uNodeptr>,
                uNodeptr_greater
                >;


void Huffman_table_from_tree( uNodeptr& root, std::map<char, std::string>& table, std::string prev )
{
	if ( root->left == nullptr )
		// if it is a leaf
	{
		table[ root->val ] = prev;
		return;
	}

	Huffman_table_from_tree( root->left , table, prev + '0' );
	Huffman_table_from_tree( root->right, table, prev + '1' );
}


prioque frequentify( const std::string& text )
{
	prioque pq;
	std::map<char, int> freqs;
	for ( auto c : text )
	{
		if ( freqs.find( c ) != std::end( freqs ) )
			freqs[ c ] += 1;
		else
			freqs[ c ] = 1;
	}
	for ( auto& nd : freqs )
		pq.push( std::make_unique<Node>( nullptr, nullptr, nd.first, nd.second ) );

	return pq;
}


std::map<char, std::string>
Huffman_build_encoding( prioque pq )
{
	uNodeptr root;
	while ( true )
	{
		auto left  = pq.top(); pq.pop();
		auto right = pq.top(); pq.pop();

		root->left = left;
		root->right = right;
		root->freq = left->freq + right->freq;

		if( pq.empty() ) break;

		pq.push( root );
	}

	std::map<char, std::string> table;
	Huffman_table_from_tree( root, table, "" );

	return table;
}


/**
 * Solution function ( encoding )
 */
std::string Huffman_encode( const std::string & text )
{
	auto table { Huffman_build_encoding( frequentify( text ) ) };
	std::string encoded {};

	for ( auto c : text )
		encoded += table[ c ];

	return encoded;
}


int main()
{
	std::string text { input() };
	std::string encoded { Huffman_encode( text ) };
	output( encoded );

	return 0;
}


template <typename __Istream>
std::string __input( __Istream & in )
{
	std::string costs;
	// in.ignore( std::numeric_limits<std::streamsize>::max, '\n' );

	in >> costs;

	return costs;
}


std::string input( const char* fname )
{
	if ( !fname )
	{
		return __input( std::cin );
	}
	else
	{
		std::ifstream ifs { fname, std::ofstream::in };
		std::string text { __input( ifs ) };
		ifs.close();

		return text;
	}
}


template <typename __Ostream>
void __output( __Ostream & os, const std::string & encoded )
{
	os << encoded;
}


void output( const std::string & encoded, const char* fname )
{
	if ( !fname )
	{
		__output( std::cout, encoded );
	}
	else
	{
		std::ofstream ofs { fname };
		__output( ofs, encoded );
		ofs.close();
	}
}
