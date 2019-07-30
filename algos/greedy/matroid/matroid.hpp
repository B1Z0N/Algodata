#include <iostream>
#include <set>
#include <vector>
#include <list>
#include <tuple>
#include <functional>


class Matroid
{
	using size_t = std::size_t;

	std::set<std::set<size_t>> I;						// set of all subsets ( it's indexes )
	std::vector<std::pair<size_t, size_t>> w; 			// weight-index table

	mutable std::set<size_t> optimal_indices {}; 		// indexes of optimal solution

	mutable bool calculated { false };
public:

	Matroid( const std::set<std::set<size_t>>& I, 
			 const std::vector<size_t>& weights )
		: I{ I }, w{}
	{ 
		std::transform( std::begin( weights ), std::end( weights ),
			std::back_inserter( w ),
			[ index = 0 ] ( size_t weight ) -> std::pair<size_t, size_t>
			{ 
				return { index, weight };
			}
		);

		std::sort( std::begin( w ), std::end( w ), 
			[ ] ( const std::pair<size_t, size_t>& fst, const std::pair<size_t, size_t>& snd )
			{
				return fst.first < snd.first;	// weight1 < weight2
			}
		);
	}

	std::set<size_t> optimal_subset( ) const
	{
		if( !calculated )
		{
			__optimal_subset( );
			calculated = true;
		}

		return optimal_indices;
	}



private:

	void __optimal_subset( ) const
	{
		for( auto& x : w )
		{
			auto it_bool = optimal_indices.insert( x.second );
			if( !I.contains( optimal_indices ) )
				optimal_indices.erase( it_bool.first );
		}
	}

};

template <typename T, typename C, typename BinaryOperation>
T optimal_solution( const Matroid& matr, const C& container, BinaryOperation bop, T init = T {} )
{
	std::set<std::size_t> indices { matr.optimal_subset( ) };
	return std::accumulate( std::begin( indices ), std::end( indices ), init, 
							[ ] ( std::size_t i, std::size_t j )
							{
								return bop( container[ i ], container[ j ] );
							}
			);
}

template <typename T, typename C>
T optimal_solution( const Matroid& matr, const C& container, T init = T {} )
{
	std::set<std::size_t> indices { matr.optimal_subset( ) };
	return std::accumulate( std::begin( indices ), std::end( indices ), init, 
							[ ] ( std::size_t i, std::size_t j )
							{
								return container[ i ] + container[ j ];
							}
			);
}