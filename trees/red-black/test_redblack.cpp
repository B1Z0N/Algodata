#include "redblack.hpp"

#include <iostream>

using namespace std;
using namespace alda;

int main()
{
	cout << "Insert number of nodes: \n";
	int nd_num;
	cin >> nd_num;

	RBtree<int> tr;
	int value;
	while ( nd_num-- )
	{
		cout << "Insert next value: \n";
		cin >> value;
		tr.insert( value );
	}

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
	tr.preorder( [ ]( int val ) { cout << val << " "; } );
	cout << "\n";

}
