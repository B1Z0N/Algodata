#include "redblack.hpp"

#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace alda;

template <typename T>
class levels {
	T min;
	std::vector<T> items { };

	int counter { };
	std::vector<int> new_levels { };

public:

	void operator()( T a )
	{
		++counter;
		if ( counter == 1)
		{
			min = a;
		}
		else if( min >= a) 
		{
			min = a;
			new_levels.push_back( counter - 1 ); // 1, 2
		}


		items.push_back( a ); // 20, 10, 30
	}

	void print()
	{
		int size = items.size();
		int count = 0;
		for ( int i = 0; i < items.size(); )
		{
			cout << std::string( size--, ' ');
			while ( i != new_levels[count] && i < items.size() )
			{
				cout << items[i++] << ' ';
			}
			count++;
			cout << "\n";
		}
	}
};

int main() 
{
	// cout << "Insert number of nodes: \n";
	int nd_num;
	// cin >> nd_num;

	RBtree<int> tr { 20, 10, 5, 30, 40 };
	
	int value;
	// while ( nd_num-- )
	// {
	// 	cout << "Insert next value: \n";
	// 	cin >> value;
	// 	tr.insert( value );
	// }

	cout << "Insert number of nodes you'd like to delete: \n";
	cin >> nd_num;

	while ( nd_num-- )
	{
		cout << "Treee is: ";
		tr.preorder( [ ]( int val ) { cout << val << " "; } );
		cout << "\n";

		cout << "Insert next value to remove: \n";
		cin >> value;
		tr.remove( value );
	}

	cout << "Treee is: ";
	tr.levelprint( cout );
	cout << "\n";
	
}
