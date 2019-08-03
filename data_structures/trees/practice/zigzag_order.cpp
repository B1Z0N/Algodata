// C++ program to print zigzag
// traversal of a binary tree
// using Recursion

#include<bits/stdc++.h>
using namespace std;

// Binary tree Node
struct Node
{
	struct Node* left;
	struct Node* right;
	int data;
};

// Function to create a new
// Binary Tree Node
struct Node* newNode( int data )
{
	struct Node* temp = new Node;

	temp->data = data;
	temp->left = NULL;
	temp->right = NULL;

	return temp;
}

void erase( Node* root )
{
	if( root )
	{
		erase( root->left  );
		erase( root->right );

		delete root;
	}
}

/**
 * Function to print zig zag traversal of a Tree
 * starting from root Node
 */
void printZigZag( Node* root )
{
	std::deque<Node*> q; // double ended queue
	q.push_front( root );

	int this_level { 1 }; // count of nodes to be printed on this level
	int next_level { 0 }; // count of nodes to be printed on the next level
	bool left_to_right { false }; // direction
	Node* nd; // helper variable

	while ( !q.empty( ) )
	// proceed while q is not empty
	// ( while there still are nodes to print ) 
	{
		if ( left_to_right )
		{
			nd = q.back();
			q.pop_back();


			if ( nd->right )
			{
				q.push_front( nd->right );
				next_level++;
			}
			if ( nd->left )
			{
				q.push_front( nd->left );
				next_level++;
			}
		}
		else
		{
			nd = q.front();
			q.pop_front();

			if ( nd->left )
			{
				q.push_back( nd->left );
				next_level++;
			}
			if ( nd->right )
			{
				q.push_back( nd->right );
				next_level++;
			}
		}

		cout << nd->data << " ";

		if ( --this_level == 0 )
		// if there are no nodes left on this level
		{
			left_to_right = !left_to_right;
			// change direction
			this_level = next_level;
			// got to next_level
			next_level = 0;
			// empty number of nodes on the next level
		}
	}

	cout << '\n';
}

// Driver code
int main( )
{
	struct Node* root = newNode( 7 );
	root->left = newNode( 6	 );
	root->left->left = newNode( 5 );
	root->left->left->left = newNode( 3 );
	root->left->left->left->right = newNode( 4 );

	root->right = newNode( 10 );
	root->right->right = newNode( 11 );
	root->right->right->right = newNode( 15 );
	root->right->right->right->left = newNode( 13 );
	root->right->right->right->left->left = newNode( 12 );

	printZigZag( root ); // 7 | 10 6 | 5 11 | 15 3 | 4 13 | 12 |
	erase( root );

	root = newNode( 8 );
	root->left = newNode( 3 );
	root->left->left = newNode( 0 );
	root->left->right = newNode( 7 );
	root->left->right->left = newNode( 5 );

	root->right = newNode( 9 );
	root->right->right = newNode( 11 );
	root->right->right->right = newNode( 12 );
	root->right->right->left = newNode( 10 );

	printZigZag( root ); // 8 | 9 3 | 0 7 11 | 12 10 5 | 
	// '|' means new level

	return 0;
}
