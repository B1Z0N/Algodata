#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <algorithm>
#include <iostream>
#include <exception>


// AVLtree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x ) 	    -> insert x
// void remove( x ) 	    -> remove x
// void erase( ) 		    -> remove all items
// 
// bool contains( x ) 	    -> true if x is in tree
// bool empty( ) 		    -> true if tree is empty
//
// Comparable find_min( )   -> minimal item
// Comparable find_max( )   -> maximal item
//
// size_t height( ) 	    -> height of the tree
// size_t size( ) 		    -> number of nodes in the tree
//
// void preorder( Func f )  ->
// -> call f on each item: Parent-Left-Right
// void inorder( Func f )   ->
// -> call f on each item: Left-Parent-Right
// void postorder( Func f ) ->
// -> call f on each item: Left-Right-Parent
// ********************************************************


/**
 * Namespace for [al]gorithms and [da]ta structures of mine implementation
 */
namespace alda {


template <typename Comparable>
/**
 * Balanced AVL tree data structure implementation
 */
class AVLtree 
{
	using T = Comparable; ///< Alias for convenince
public:
	/**
	 * Default constructor
	 */
	AVLtree( ) : root{ nullptr } 
	{
	}

	/**
	 * Copy constructor
	 */
	AVLtree( const AVLtree& rhs ) : root{ nullptr } 
	{
		root = clone( rhs.root );
	}

	/**
	 * Move constructor
	 */
	AVLtree( AVLtree&& rhs ) : root{ rhs.root }
	{
		rhs.root = nullptr;
	}

	/**
	 * Destructor
	 */
	~AVLtree( )
	{
		erase( );
	}

	/**
	 * Copy assignment
	 */
	AVLtree& operator = ( const AVLtree& rhs )
	{
		AVLtree copy { rhs };
		std::swap( *this, copy );

		return *this;
	}

	/**
	 * Move assignment
	 */
	AVLtree& operator = ( AVLtree&& rhs )
	{
		std::swap( root, rhs.root );
		return *this;
	}

	/**
	 * Insert item to AVL tree, keep it balanced
	 */
	void insert( const T& value )
	{
		insert( value, root );
	}

	/**
	 * Find and remove value from tree, keep it balanced
	 */
	void remove( const T& value )
	{
		remove( value, root );
	}

	/**
	 * Remove all elements from tree
	 */
 	void erase( )
 	{
 		erase( root );
 	}

 	/**
 	 * Return true if value is in the tree
 	 */
 	bool contains( const T& value )
 	{
 		return contains( value, root );
 	}

 	/**
 	 * Return true if it is empty
 	 */
 	bool empty( )
 	{
 		return root == nullptr;
 	}

 	/**
 	 * Return minimal item of the tree
 	 */
	T find_min( )
	{
		if( empty( ) )
		{
			throw EmptyTreeError { };
		}

		return find_min( root )->value;
	}

 	/**
 	 * Return maximal item of the tree
 	 */
	T find_max( )
	{
		if( empty( ) )
		{
			throw EmptyTreeError { };
		}

		return find_max( root )->value;
	}

	/**
	 * Return height of the tree
	 */
	size_t height( )
	{

	}

	/**
	 * Return number of items in the tree
	 */
	size_t size( )
	{

	}

	/**
	 * Call f on each item in this order: Parent-Left-Right
	 */
	template <typename Func>
	void preorder( Func f )
	{
		preorder( f, root );
	}

	/**
	 * Call f on each item in this order: Left-Parent-Right
	 */
	template <typename Func>
	void inorder( Func f )
	{
		inorder( f, root );
	}

	/**
	 * Call f on each item in this order: Left-Right-Parent
	 */
	template <typename Func>
	void postorder( Func f )
	{
		postorder( f, root );
	}

private:	

	/**
	 * Error class for signalizing that operation
	 * can't be performed if tree is empty 
	 */
	class EmptyTreeError : public std::exception { };

	/**
	 * Binary tree node class
	 */
	struct Node
	{
		T value;	 ///< Value stored in this node
		Node *left;  ///< Left subtree pointer
		Node *right; ///< Right subtree pointer

		Node( const T& value, Node *left, Node* right )
			: value{ value }, left{ left }, right{ right } { }

		Node( T&& value, Node* left, Node* right )
			: value( std::move( value ) ), left{ left }, right{ right } { }
	};

	Node *root; ///< Root node 

	/**
	 * Insert item to node, keep it balanced
	 */
	void insert( const T& value, Node* nd )
	{
		Node *head {nd};
		
		while( nd )
		{
			prev = nd;
			if( nd->value < value )
			{
				nd = nd->right;
			}
			else if( nd->value > value )
			{
				nd = nd->left;
			}
			else
				;	// Duplicate
		}

		nd = new Node { value, nullptr, nullptr };

		balance( head );
	}

	/**
	 * Find and remove value from tree, keep it balanced
	 */
	void remove( const T& value, Node*& nd ) noexcept
	{

	}

	/**
	 * Remove all elements from tree
	 */
 	void erase( Node*& nd ) noexcept
 	{
 		if( nd )
 		{
 			erase( nd->left );
 			erase( nd->right );
 			delete nd;
 		}

 		nd = nullptr;
 	}

 	/**
 	 * Return true if value is in the tree
 	 */
 	bool contains( const T& value, Node*& nd ) const noexcept
 	{
 		if( !nd ) 
 		{
 			return false;
 		}
 		else if( value > nd->value )
 		{
 			return contains( value, nd->right );
 		}
 		else if( value < nd->value )
 		{
 			return contains( value, nd ->left );
 		}
 		else 
 		{
 			return true;
 		}
 	}

 	/**
 	 * Return pointer to the node with the minimal item
 	 */
	Node* find_min( Node*& nd ) const noexcept
	{
		while( nd->left )
		{
			nd = nd->left;
		}

		return nd;
	}

 	/**
 	 * Return pointer to the node with the maximal item
 	 */
	Node* find_max( Node*& nd ) const noexcept
	{
		while( nd->right )
		{
			nd = nd->right;
		}

		return nd;
	}

	/**
	 * Return height of the tree
	 */
	size_t height( Node* nd ) const noexcept
	{
		if( !nd ) return 0;

		return std::max( height( nd->left  ), 
						 height( nd->right ) ) + 1;
	}

	/**
	 * Return number of items in the tree
	 */
	size_t size( Node*& nd ) const noexcept
	{
		if( !nd ) return 0;

		return size( nd->left ) + size( nd->right ) + 1;
	}

	/**
	 * Call f on each item in this order: Parent-Left-Right
	 */
	template <typename Func>
	void preorder( Func&& f, Node*& nd ) const
	{
		if( !nd ) return;

		f( nd->value );
		preorder( std::forward<Func>( f ), nd->left );
		preorder( std::forward<Func>( f ), nd->right );
	}

	/**
	 * Call f on each item in this order: Left-Parent-Right
	 */
	template <typename Func>
	void inorder( Func&& f, Node*& nd ) const
	{
		if( !nd ) return;

		inorder( std::forward<Func>( f ), nd->left );
		f( nd->value );
		inorder( std::forward<Func>( f ), nd->right );
	}

	/**
	 * Call f on each item in this order: Left-Right-Parent
	 */
	template <typename Func>
	void postorder( Func&& f, Node*& nd ) const
	{
		if( !nd ) return;

		postorder( std::forward<Func>( f ), nd->left );
		postorder( std::forward<Func>( f ), nd->right );
		f( nd->value );
	}

	/**
	 * Keep tree balanced, main feature of an AVL tree
	 */
	void balance( Node*& nd )
	{

	}

	/**
	 * Return deep copy of a tree pointed by nd
	 */ 
	Node* clone( Node* nd ) const
	{

	}
};


};

#endif