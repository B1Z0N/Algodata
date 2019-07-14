#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

#include <algorithm>
#include <iostream>
#include <exception>
#include <tuple>
#include <memory>

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
		: root { Node::NIL }
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
// ******************Internal-members-and-classes**********************
	/**
	 * Enumeration for coloring red-black tree
	 */
	enum class Color { RED, BLACK };

	/**
	 * Binary tree node class
	 */
	struct Node
	{
		T value;	       ///< Value stored in this node

		Color color;       ///< Red or black color of the node

		Node *parent;      ///< Parent node pointer
		Node *left;        ///< Left subtree pointer
		Node *right;   	   ///< Right subtree pointer

		static Node* NIL;  ///<Sentinel for NIL (external leaf) support

		Node( const Node& ) = default;
		Node( Node&& ) = default;

		Node& operator = ( const Node& ) = default;
		Node& operator = ( Node&& ) = default;

		Node( const T& value, Color color, Node* parent, Node *left, Node* right)
			: value{ value }, color{ color }, parent{ parent },
			  left{ left }, right{ right } { }

		Node( T&& value, Color color, Node* parent, Node *left, Node* right)
			: value{ std::move(value) }, color{ color }, parent{ parent },
			  left{ left }, right{ right } { }

		~Node() { delete NIL; }
	};

	// std::unique_ptr<Node> Node::NIL { reinterpret_cast<T>(0), Color::BLACK, nullptr, nullptr, nullptr };

	Node *root; ///< Root node


private:

// *******************SPECIFIC-TO-RED_BLACK-tree***********************

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
	 * Recolor the tree
	 */
	void insert_fixup( Node* nd )
	{
		while( nd->color == Color::RED )
		{
			if( nd->parent == nd->parent->parent->left )
			{
				Node* pright = nd->parent->parent->right;

				if( pright->color == Color::RED )
				{
					nd->parent->color = Color::BLACK;
					pright->color = Color::BALCK;

					nd = nd->parent->parent;
					nd->color = Color::RED;
				}
				else if( nd->parent->right == nd )
				{
					nd = nd->parent;
					ll_rotate( nd );
				}
				else
				{
					nd->parent->color = Color::BLACK;
					nd->parent->parent->color = Color::RED;
					rr_rotate( nd->parent->parent );
				}
			}
			else 	// symmetric, left replaced by right, and vice versa
			{
				Node* pleft = nd->parent->parent->left;

				if( pleft->color == Color::RED )
				{
					nd->parent->color = Color::BLACK;
					pleft->color = Color::BALCK;

					nd = nd->parent->parent;
					nd->color = Color::RED;
				}
				else if( nd->parent->left == nd )
				{
					nd = nd->parent;
					rr_rotate( nd );
				}
				else
				{
					nd->parent->color = Color::BLACK;
					nd->parent->parent->color = Color::RED;
					ll_rotate( nd->parent->parent );
				}
			}
		}

		// root color, appropriate setup
		for( ; nd->parent != Node::NIL; nd = nd->parent ) { }
		nd->color = Color::BLACK;
	}

// ***************************************************************

private:


	/**
	 * Insert item to node, keep it balanced
	 */
	void insert( const T& value, Node*& nd )
	{
		Node* temp = nd;
		Node* prev = Node::NIL;

		while ( temp != Node::NIL )
		{
			prev = temp;
			if ( value > temp->value )
				temp = temp->right;
			else
				temp = temp->left ;
		}

		temp = new Node { value, Color::RED, prev, Node::NIL, Node::NIL };

		if( prev == Node::NIL ) 
			nd = temp;
		else if ( value > prev->value )
			prev->right = temp;
		else
			prev->left  = temp;

		insert_fixup( nd );
	}

	/**
	 * Find and remove value from tree, keep it balanced
	 */
	void remove( const T & value, Node * & nd ) noexcept
	{
		if ( nd == Node::NIL )
			return;   // Item not found; do nothing

		if ( value < nd->value )
		{
			remove( value, nd->left );
		}
		else if ( nd->value < value )
		{
			remove( value, nd->right );
		}
		else if ( nd->left != Node::NIL && nd->right != Node::NIL ) // Two children
		{
			nd->value = find_min( nd->right )->value;
			remove( nd->value, nd->right );
		}
		else
		{
			Node *oldnode = nd;
			nd = ( nd->left != Node::NIL ) ? nd->left : nd->right;
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
		if ( nd != Node::NIL )
		{
			erase( nd->left );
			erase( nd->right );
			delete nd;
		}

		nd = Node::NIL;
	}

	/**
	 * Return true if value is in the tree
	 */
	bool contains( const T & value, Node *nd ) const noexcept
	{
		while ( nd != Node::NIL )
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
		while ( nd->left != Node::NIL )
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
		while ( nd->right != Node::NIL )
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
		if ( nd == Node::NIL ) return 0;

		return std::max( height( nd->left  ),
		                 height( nd->right ) ) + 1;
	}

	/**
	 * Return number of items in the tree
	 */
	size_t size( Node*& nd ) const noexcept
	{
		if ( nd == Node::NIL ) return 0;

		return size( nd->left ) + size( nd->right ) + 1;
	}

	/**
	 * Call f on each item in this order: Parent-Left-Right
	 */
	template <typename Func>
	void preorder( Func&& f, Node* nd ) const
	{
		if ( nd == Node::NIL ) return;

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
		if ( nd == Node::NIL ) return;

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
		if ( nd == Node::NIL ) return;

		postorder( std::forward<Func>( f ), nd->left );
		postorder( std::forward<Func>( f ), nd->right );
		f( nd->value );
	}

	/**
	 * Return deep copy of a tree pointed by nd
	 */
	Node* clone( Node* nd ) const
	{
		return nd == Node::NIL ?
		       Node::NIL  	   :
		       new Node{ nd->value, nd->color, nd->parent,
		                 clone( nd->left ), clone( nd->right ) };
	}
};


template <typename T>
typename RBtree<T>::Node* RBtree<T>::Node::NIL =
    new RBtree<T>::Node { reinterpret_cast<T>(0), Color::BLACK, nullptr, nullptr, nullptr };


};


#endif