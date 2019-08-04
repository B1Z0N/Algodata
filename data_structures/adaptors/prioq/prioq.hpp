#ifndef PRIOQ_HPP
#define PRIOQ_HPP

#include <initializer_list>
#include <vector>
#include <algorithm>
#include <functional>

#include "heap.hpp"

namespace alda {

template <typename T, typename Comparator = std::less<T>>
class Prioq {
  public:
    using container_type = std::vector<T>;
    using value_compare = Comparator;
    using value_type = typename container_type::value_type;
    using size_type = typename container_type::size_type;
    using reference = typename container_type::reference;
    using const_reference = typename container_type::const_reference;

  	Prioq( const std::initializer_list<value_type>& lst )
  	: _arr{ lst } { build_max_heap<T, Comparator>( _arr ); }
    Prioq( const container_type& arr )
    : _arr{ arr } { build_max_heap<T, Comparator>( _arr ); }

  	Prioq( ) = default;
  	Prioq( const Prioq& ) = default; 
  	Prioq( Prioq&& ) = default; 
  	Prioq& operator=( const Prioq& ) = default; 
  	Prioq& operator=( Prioq&& ) = default; 

    const_reference top( ) const { return _arr.front(); };
    void push( const_reference elem ) {
        _arr.push_back( elem );
        push_heap<T, Comparator>( _arr );
    }
    void pop( ) {
        // for ( const auto& x : _arr ) std::cout << x << " ";
        // std::cout << '\n';
        pop_heap<T, Comparator>( _arr );
        _arr.pop_back();
    }

    bool empty( ) const { return _arr.empty(); };
    std::size_t size( ) const { return _arr.size(); };

  private:
    std::vector<value_type> _arr;
};

};  // alda

#endif  // PRIOQ_HPP
