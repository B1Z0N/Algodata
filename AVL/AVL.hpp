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

};


};

#endif