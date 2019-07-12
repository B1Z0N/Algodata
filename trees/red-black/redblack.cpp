#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

#include <algorithm>
#include <iostream>
#include <exception>
#include <tuple>

#include "redblack.hpp"


// RBtree class implementation

/**
 * Namespace for [al]gorithms and [da]ta structures of mine implementation
 */
namespace alda {

// *******************SPECIFIC-TO-RED_BLACK-tree***********************
template <typename T>

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

	Node *root; ///< Root node

	/**
	 * Insert item to node, keep it balanced
	 */
	void insert( const T& value, Node*& nd )
	{
		if ( nd == Node::NIL )
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
	void preorder( Func&& f, Node*& nd ) const
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
	void inorder( Func&& f, Node*& nd ) const
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
	void postorder( Func&& f, Node*& nd ) const
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
		       new Node{ nd->value, clone( nd->left ), clone( nd->right ) };
	}
};


};

#endif