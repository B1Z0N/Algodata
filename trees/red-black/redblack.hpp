#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

#include <algorithm>
#include <iostream>
#include <exception>
#include <tuple>
#include <queue>

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
// void levelorder( Func f) ->
// -> call f on each item level by level, left-to-right
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
	{
	}

	/**
	 * Copy constructor
	 */
	RBtree( const RBtree& rhs )
	{
		root = clone( rhs.root );
	}

	/**
	 * Move constructor
	 */
	RBtree( RBtree&& rhs ) : root{ rhs.root }
	{
		rhs.root = NIL;
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
		return root == NIL;
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
	 * Call f on each item level-by-level, left-to-right
	 */
	template <typename Func>
	void levelorder( Func&& f ) const
	{
		if ( empty( ) )
		{
			throw EmptyTreeError { };
		}

		levelorder( std::forward<Func>(f), root );
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
	};

	/**
	 * nullptr sentinel value
	 */
	Node __NIL_VAL { reinterpret_cast<T>(0), Color::BLACK, nullptr, nullptr, nullptr };

	Node* NIL { &__NIL_VAL }; ///< nullptr sentinel
	Node *root { NIL }; ///< Root node

private:

// *******************SPECIFIC-TO-RED_BLACK-tree***********************

	/**
	 * Right single rotation
	 */
	void rr_rotate( Node*& pt ) noexcept
	{
		Node *pt_left = pt->left;

		pt->left = pt_left->right;

		if (pt->left != NIL)
			pt->left->parent = pt;

		pt_left->parent = pt->parent;

		if (pt->parent == NIL)
			root = pt_left;

		else if (pt == pt->parent->left)
			pt->parent->left = pt_left;

		else
			pt->parent->right = pt_left;

		pt_left->right = pt;
		pt->parent = pt_left;
	}

	/**
	 * Left single rotation
	 */
	void ll_rotate(Node *&pt)
	{
		Node *pt_right = pt->right;

		pt->right = pt_right->left;

		if (pt->right != NIL)
			pt->right->parent = pt;

		pt_right->parent = pt->parent;

		if (pt->parent == NIL)
			root = pt_right;

		else if (pt == pt->parent->left)
			pt->parent->left = pt_right;

		else
			pt->parent->right = pt_right;

		pt_right->left = pt;
		pt->parent = pt_right;
	}

	/**
	 * Recolor the tree
	 */
	void insert_fixup( Node* nd )
	{
		static auto basic_case {
			[ ] ( Node*& nd ) {
				nd->parent->color = Color::BLACK;

				nd = nd->parent->parent;
				nd->color = Color::RED;
			}
		};

		static auto left_left {
			[this] ( Node*& nd ) {
				basic_case( nd );
				rr_rotate( nd );
			}
		};

		static auto right_right {
			[this] ( Node*& nd ) {
				basic_case( nd );
				ll_rotate( nd );
			}
		};

		while ( nd->parent->color == Color::RED )
		{
			if ( nd->parent == nd->parent->parent->left )
			{
				Node* pright = nd->parent->parent->right;

				if ( pright->color == Color::RED )
					// just recoloring
				{
					nd->parent->color = Color::BLACK;
					pright->color = Color::BLACK;

					nd = nd->parent->parent;
					nd->color = Color::RED;
				}
				else if ( nd->parent->left == nd)
				{
					left_left( nd );
				}
				else
				{
					ll_rotate( nd->parent );
					left_left( nd );
				}
			}
			else 	// symmetric, left replaced with right, and vice versa
			{
				Node* pleft = nd->parent->parent->left;

				if ( pleft->color == Color::RED )
				{
					nd->parent->color = Color::BLACK;
					pleft->color = Color::BLACK;

					nd = nd->parent->parent;
					nd->color = Color::RED;
				}
				else if ( nd->parent->right == nd)
				{
					right_right( nd );
				}
				else
				{
					rr_rotate( nd->parent );
					right_right( nd );
				}
			}
		}

		// root color appropriate setup
		root->color = Color::BLACK;
	}

	/**
	 * Tranplant node "from" to node "to"
	 */
	void RBtransplant( Node* to, Node* from )
	{
		if ( to->parent == NIL )
			root = from;
		else if ( to == to->parent->left )
			to->parent->left  = from;
		else
			to->parent->right = from;

		from->parent = to->parent;
	}

	/**
	 * Remove node from tree, keeping it Red-Black
	 */
	void RBremove( Node* nd )
	{
		Node* replacement = nd;
		Color orginal = replacement->color;
		Node *broken;
		if ( nd->left == NIL )
			// if only right child is present
		{
			RBtransplant( nd, nd->right);
			// set nd->right instead of nd
			broken = nd->right;
			// but now it's color's is broken
		}
		else if ( nd->right == NIL )
			// if only left child is present
		{
			RBtransplant( nd, nd->left );
			// set nd->right instead of nd
			broken = nd->left;
			// but now it's color's is broken
		}
		else
			// in case it has two notnull nodes
		{
			replacement = find_min( nd->right );
			// replace it with  minimal node of right subtree
			original = replacement->color;
			// but keep it's original color
			broken = replacement->right;

			if ( replacement->parent == nd )
				// if minimal of right subtree is child of nd
				broken->parent = replacement;
			// replacement will move up to it's parent
			// which is nd, so eventually it will point to nd
			else
				// if minimal of right subtree is not child of nd
			{
				RBtransplant( replacement, replacement->right );
				// move replacement->right in place of replacement
				replacement->right = nd->right;
				replacement->right->parent = replacement;
				// and set replacement in placement of deleted node
			}

			RBtransplant( nd, replacement );
			// move replacement to nd

			replacement->left = nd->left;
			replacement->left->parent = replacement;
			replacement->color = nd->color;
			// and change it's data to nd's data
		}

		delete nd;
		// now we may delete nd
		// as it is replaced
		if ( original == Color::BLACK )
			// if original color is black, than there might be some
			// violations of red-black properties
			remove_fixup( broken );
	}

	/**
	 * Fix color properties of red-black tree
	 */
	remove_fixup( Node* broken )
	{

	}

// ***************************************************************

private:

	/**
	 * Insert item to node, keep it balanced
	 */
	void insert( const T & value, Node*& nd )
	{
		Node* temp = nd;
		Node* prev = NIL;

		while ( temp != NIL )
		{
			prev = temp;
			if ( value > temp->value )
				temp = temp->right;
			else
				temp = temp->left ;
		}

		temp = new Node { value, Color::RED, prev, NIL, NIL };

		if ( prev == NIL )
			nd = temp;
		else if ( value > prev->value )
			prev->right = temp;
		else
			prev->left  = temp;

		insert_fixup( temp );
	}

	/**
	 * Find and remove value from tree, keep it balanced
	 */
	void remove( const T & value, Node * & nd ) noexcept
	{
		if ( nd == NIL )
			return;   // Item not found; do nothing

		if ( value < nd->value )
		{
			remove( value, nd->left );
		}
		else if ( nd->value < value )
		{
			remove( value, nd->right );
		}
		else if ( nd->left != NIL && nd->right != NIL ) // Two children
		{
			nd->value = find_min( nd->right )->value;
			remove( nd->value, nd->right );
		}
		else
		{
			Node *oldnode = nd;
			nd = ( nd->left != NIL ) ? nd->left : nd->right;
			delete oldnode;
			return;
		}
	}

	/**
	 * Remove all elements from tree
	 */
	void erase( Node*& nd ) noexcept
	{
		if ( nd != NIL )
		{
			erase( nd->left );
			erase( nd->right );
			delete nd;
		}

		nd = NIL;
	}

	/**
	 * Return true if value is in the tree
	 */
	bool contains( const T & value, Node * nd ) const noexcept
	{
		while ( nd != NIL )
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
	Node* find_min( Node * nd ) const noexcept
	{
		while ( nd->left != NIL )
		{
			nd = nd->left;
		}

		return nd;
	}

	/**
	 * Return pointer to the node with the maximal item
	 */
	Node* find_max( Node * nd ) const noexcept
	{
		while ( nd->right != NIL )
		{
			nd = nd->right;
		}

		return nd;
	}

	/**
	 * Return height of the tree
	 */
	size_t height( Node * nd ) const noexcept
	{
		if ( nd == NIL ) return 0;

		return std::max( height( nd->left  ),
		                 height( nd->right ) ) + 1;
	}

	/**
	 * Return number of items in the tree
	 */
	size_t size( Node*& nd ) const noexcept
	{
		if ( nd == NIL ) return 0;

		return size( nd->left ) + size( nd->right ) + 1;
	}

	/**
	 * Call f on each item in this order: Parent-Left-Right
	 */
	template <typename Func>
	void preorder( Func && f, Node * nd ) const
	{
		if ( nd == NIL ) return;

		f( nd->value );
		preorder( std::forward<Func>( f ), nd->left );
		preorder( std::forward<Func>( f ), nd->right );
	}

	/**
	 * Call f on each item in this order: Left-Parent-Right
	 */
	template <typename Func>
	void inorder( Func && f, Node * nd ) const
	{
		if ( nd == NIL ) return;

		inorder( std::forward<Func>( f ), nd->left );
		f( nd->value );
		inorder( std::forward<Func>( f ), nd->right );
	}

	/**
	 * Call f on each item in this order: Left-Right-Parent
	 */
	template <typename Func>
	void postorder( Func && f, Node * nd ) const
	{
		if ( nd == NIL ) return;

		postorder( std::forward<Func>( f ), nd->left );
		postorder( std::forward<Func>( f ), nd->right );
		f( nd->value );
	}

	/**
	 * Call f on each item level by level, left-to-right
	 */
	template <typename Func>
	void levelorder( Func && f, Node * nd ) const
	{
		if ( nd == NIL ) return;

		std::queue<Node *> q;
		q.push( nd );

		while ( !q.empty() )
		{
			nd = q.front();
			q.pop();

			if ( nd->left !=  NIL )
				q.push( nd->left  );
			if ( nd->right != NIL )
				q.push( nd->right );

			f( nd->value );
		}
	}

	/**
	 * Return deep copy of a tree pointed by nd
	 */
	Node* clone( Node * nd ) const
	{
		return nd == NIL ?
		       NIL  	   :
		       new Node{ nd->value, nd->color, nd->parent,
		                 clone( nd->left ), clone( nd->right ) };
	}
};


};


#endif