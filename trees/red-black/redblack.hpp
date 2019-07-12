#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

#include <algorithm>
#include <iostream>
#include <exception>
#include <tuple>


// RBtree class
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
 * Balanced Red-Black tree data structure implementation
 */
class RBtree
{
	using T = Comparable; ///< Alias for convenince
public:

	/**
	 * Default constructor
	 */
	RBtree( ) noexcept
		: root { NIL }
	{
	}

	/**
	 * Copy constructor
	 */
	RBtree( const RBtree& rhs ) : root{ Node::NIL }
	{
		root = clone( rhs.root );
	}

	/**
	 * Move constructor
	 */
	RBtree( RBtree&& rhs ) : root{ rhs.root }
	{
		rhs.root = Node::NIL;
	}

	/**
	 * Destructor
	 */
	~RBtree( ) noexcept
	{
		erase( );
	}

	/**
	 * Copy assignment
	 */
	RBtree& operator = ( const RBtree& rhs )
	{
		RBtree copy { rhs };
		std::swap( *this, copy );

		return *this;
	}

	/**
	 * Move assignment
	 */
	RBtree& operator = ( RBtree&& rhs )
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
		return root == Node::NIL;
	}

	/**
	 * Return minimal item of the tree
	 */
	T find_min( ) const noexcept
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
	T find_max( ) const noexcept
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
		T value;	   ///< Value stored in this node

		Color color;   ///< Red or black color of the node

		Node *parent;  ///< Parent node pointer
		Node *left;    ///< Left subtree pointer
		Node *right;   ///< Right subtree pointer


		Node( const T& value, Color color, Node* parent, Node *left, Node* right)
			: value{ value }, color{ color }, parent{ parent },
			  left{ left }, right{ right } { }

		Node( T&& value, Color color, Node* parent, Node *left, Node* right)
			: value{ std::move(value) }, color{ color }, parent{ parent },
			  left{ left }, right{ right } { }

		/**
		 * Sentinel for NIL (external leaf) support
		 */
		static constexpr Node  NIL_VAL { T{ }, Color::BLACK, nullptr, nullptr, nullptr };
		static constexpr Node* NIL     { &NIL_VAL };
	};
	
// *******************SPECIFIC-TO-RED_BLACK-tree***********************
	/**
	 * Enumeration for coloring red-black tree
	 */
	enum class Color { RED, BLACK };

	/**
	 * Get balancing factor
	 */
	int b_factor( Node* nd ) const noexcept;

	/**
	 * Right single rotation
	 */
	void rr_rotate( Node*& nd ) noexcept;

	/**
	 * Left single rotation
	 */
	void ll_rotate( Node*& nd ) noexcept;

	/**
	 * Keep tree balanced, main feature of an AVL tree
	 */
	void balance( Node*& imb_node ) noexcept;

	/**
	 * Right-left double rotation
	 */
	void rl_rotate( Node*& nd ) noexcept;

	/**
	 * Left-right double rotation
	 */
	void lr_rotate( Node*& nd ) noexcept;

// ***************************************************************

private:

	Node *root; ///< Root node

	/**
	 * Insert item to node, keep it balanced
	 */
	void insert( const T& value, Node*& nd );

	/**
	 * Find and remove value from tree, keep it balanced
	 */
	void remove( const T & value, Node * & nd ) noexcept;

	/**
	 * Remove all elements from tree
	 */
	void erase( Node*& nd ) noexcept;

	/**
	 * Return true if value is in the tree
	 */
	bool contains( const T & value, Node *nd ) const noexcept;
	/**
	 * Return pointer to the node with the minimal item
	 */
	Node* find_min( Node* nd ) const noexcept;

	/**
	 * Return pointer to the node with the maximal item
	 */
	Node* find_max( Node* nd ) const noexcept;

	/**
	 * Return height of the tree
	 */
	size_t height( Node* nd ) const noexcept;

	/**
	 * Return number of items in the tree
	 */
	size_t size( Node*& nd ) const noexcept;

	/**
	 * Call f on each item in this order: Parent-Left-Right
	 */
	template <typename Func>
	void preorder( Func&& f, Node*& nd ) const;

	/**
	 * Call f on each item in this order: Left-Parent-Right
	 */
	template <typename Func>
	void inorder( Func&& f, Node*& nd ) const;

	/**
	 * Call f on each item in this order: Left-Right-Parent
	 */
	template <typename Func>
	void postorder( Func&& f, Node*& nd ) const;

	/**
	 * Return deep copy of a tree pointed by nd
	 */
	Node* clone( Node* nd ) const;

};


};

#endif