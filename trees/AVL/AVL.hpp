#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <algorithm>
#include <iostream>
#include <exception>
#include <tuple>


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
	AVLtree( ) noexcept
	 : root{ nullptr }
	{
	}

	/**
	 * Copy constructor
	 */
	AVLtree( const AVLtree& rhs )
	 : root{ nullptr }
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
	~AVLtree( ) noexcept
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
	void remove( const T& value ) noexcept
	{
		remove( value, root );
	}

	/**
	 * Remove all elements from tree
	 */
	void erase( ) noexcept
	{
		erase( root );
	}

	/**
	 * Return true if value is in the tree
	 */
	bool contains( const T& value ) const noexcept
	{
		return contains( value, root );
	}

	/**
	 * Return true if it is empty
	 */
	bool empty( ) const noexcept
	{
		return root == nullptr;
	}

	/**
	 * Return minimal item of the tree
	 */
	T find_min( ) const
	{
		if ( empty( ) )
		{
			throw EmptyTreeError { };
		}

		return find_min( root )->value;
	}

	/**
	 * Return maximal item of the tree
	 */
	T find_max( ) const
	{
		if ( empty( ) )
		{
			throw EmptyTreeError { };
		}

		return find_max( root )->value;
	}

	/**
	 * Return height of the tree
	 */
	size_t height( ) const noexcept
	{
		return height( root );
	}

	/**
	 * Return number of items in the tree
	 */
	size_t size( ) const noexcept
	{
		return size( root );
	}

	/**
	 * Call f on each item in this order: Parent-Left-Right
	 */
	template <typename Func>
	void preorder( Func&& f ) const
	{
		if ( empty( ) )
		{
			throw EmptyTreeError { };
		}

		preorder( std::forward<Func>(f), root );
	}

	/**
	 * Call f on each item in this order: Left-Parent-Right
	 */
	template <typename Func>
	void inorder( Func f ) const
	{
		if ( empty( ) )
		{
			throw EmptyTreeError { };
		}

		inorder( std::forward<Func>(f), root );
	}

	/**
	 * Call f on each item in this order: Left-Right-Parent
	 */
	template <typename Func>
	void postorder( Func f ) const
	{
		if ( empty( ) )
		{
			throw EmptyTreeError { };
		}

		postorder( std::forward<Func>(f), root );
	}

	/**
	 * Error class for signalizing that operation
	 * can't be performed if tree is empty
	 */
	class EmptyTreeError : public std::exception { };

private:

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
	void insert( const T& value, Node*& nd )
	{
		if ( nd == nullptr )
			nd = new Node{ value, nullptr, nullptr };
		else if ( value < nd->value )
		{
			insert( value, nd->left );
			balance( nd );
		}
		else if ( nd->value < value )
		{
			insert( value, nd->right );
			balance( nd );
		}
		else
			;  // Duplicate; do nothing
	}

	/**
	 * Find and remove value from tree, keep it balanced
	 */
	void remove( const T & value, Node * & nd ) noexcept
	{
		if ( nd == nullptr )
			return;   // Item not found; do nothing

		if ( value < nd->value )
		{
			remove( value, nd->left );
		}
		else if ( nd->value < value )
		{
			remove( value, nd->right );
		}
		else if ( nd->left != nullptr && nd->right != nullptr ) // Two children
		{
			nd->value = find_min( nd->right )->value;
			remove( nd->value, nd->right );
		}
		else
		{
			Node *oldnode = nd;
			nd = ( nd->left != nullptr ) ? nd->left : nd->right;
			delete oldnode; 
			return;
		}

		balance( nd );
	}

	/**
	 * Remove all elements from tree
	 */
	void erase( Node*& nd ) noexcept
	{
		if ( nd )
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
	bool contains( const T & value, Node *nd ) const noexcept
	{
		while ( nd != nullptr )
			if ( value < nd->value )
				nd = nd->left;
			else if ( nd->value < value )
				nd = nd->right;
			else
				return true;    // Match

		return false;   // No match
	}

	/**
	 * Return pointer to the node with the minimal item
	 */
	Node* find_min( Node* nd ) const noexcept
	{
		while ( nd->left )
		{
			nd = nd->left;
		}

		return nd;
	}

	/**
	 * Return pointer to the node with the maximal item
	 */
	Node* find_max( Node* nd ) const noexcept
	{
		while ( nd->right )
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
		if ( !nd ) return 0;

		return std::max( height( nd->left  ),
		                 height( nd->right ) ) + 1;
	}

	/**
	 * Return number of items in the tree
	 */
	size_t size( Node*& nd ) const noexcept
	{
		if ( !nd ) return 0;

		return size( nd->left ) + size( nd->right ) + 1;
	}

	/**
	 * Call f on each item in this order: Parent-Left-Right
	 */
	template <typename Func>
	void preorder( Func&& f, Node* nd ) const
	{
		if ( !nd ) return;

		f( nd->value );
		preorder( std::forward<Func>( f ), nd->left );
		preorder( std::forward<Func>( f ), nd->right );
	}

	/**
	 * Call f on each item in this order: Left-Parent-Right
	 */
	template <typename Func>
	void inorder( Func&& f, Node* nd ) const
	{
		if ( !nd ) return;

		inorder( std::forward<Func>( f ), nd->left );
		f( nd->value );
		inorder( std::forward<Func>( f ), nd->right );
	}

	/**
	 * Call f on each item in this order: Left-Right-Parent
	 */
	template <typename Func>
	void postorder( Func&& f, Node* nd ) const
	{
		if ( !nd ) return;

		postorder( std::forward<Func>( f ), nd->left );
		postorder( std::forward<Func>( f ), nd->right );
		f( nd->value );
	}

	/**
	 * Return deep copy of a tree pointed by nd
	 */
	Node* clone( Node* nd ) const
	{
		return nd == nullptr ?
		       nullptr  	 :
		       new Node{ nd->value, clone( nd->left ), clone( nd->right ) };
	}

// *******************SPECIFIC-TO-AVL-tree***********************

	/**
	 * Keep tree balanced, main feature of an AVL tree
	 */
	void balance( Node*& imb_node ) noexcept
	{
		int factor { b_factor( imb_node ) };

		static auto right_is_higher { [ ] ( int fact ) {
			return fact < -1;
		}};

		static auto left_is_higher { [ ] ( int fact ) {
			return fact > 1;
		}};

		if ( left_is_higher( factor ) )
		{
			int lfactor = b_factor( imb_node->left );

			if ( right_is_higher( lfactor ) )
			{
				lr_rotate( imb_node );
			}
			else
			{
				rr_rotate( imb_node );
			}
		}
		else if ( right_is_higher( factor ) )
		{
			int rfactor = b_factor( imb_node->right );

			if ( left_is_higher( rfactor ) )
			{
				rl_rotate( imb_node );
			}
			else
			{
				ll_rotate( imb_node );
			}
		}
	}

	/**
	 * Get balancing factor
	 */
	int b_factor( Node* nd ) const noexcept
	{
		return height( nd->left ) - height( nd->right );
	}

	/**
	 * Right single rotation
	 */
	void rr_rotate( Node*& nd ) noexcept
	{
		Node* new_right = nd;
		nd = nd->left;
		new_right->left = nd->right;
		nd->right = new_right;
	}

	/**
	 * Left single rotation
	 */
	void ll_rotate( Node*& nd ) noexcept
	{
		Node* new_left = nd;
		nd = nd->right;
		new_left->right = nd->left;
		nd->left = new_left;

	}

	/**
	 * Right-left double rotation
	 */
	void rl_rotate( Node*& nd ) noexcept
	{
		rr_rotate( nd->right );
		ll_rotate( nd );
	}

	/**
	 * Left-right double rotation
	 */
	void lr_rotate( Node*& nd ) noexcept
	{
		ll_rotate( nd->left );
		rr_rotate( nd );
	}

// ***************************************************************



};


};

#endif