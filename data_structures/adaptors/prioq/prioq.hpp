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

  	Prioq( const std::initializer_list<value_type>& lst, 
           const Comparator& comp_less = std::less<T> {} )
  	: _arr{ lst }, _comp_less{ comp_less } { build_max_heap_to_right( _arr, _comp_less ); }
    Prioq( const container_type& lst, 
           const Comparator& comp_less = std::less<T> {} )
    : _arr{ lst }, _comp_less{ comp_less } { build_max_heap_to_right( _arr, _comp_less ); }

  	Prioq( ) = default;
  	Prioq( const Prioq& ) = default; 
  	Prioq( Prioq&& ) = default; 
  	Prioq& operator=( const Prioq& ) = default; 
  	Prioq& operator=( Prioq&& ) = default; 

    const_reference top( ) const { return _arr.back(); };
    void push( const_reference elem ) {
        _arr.push_back( elem );
        max_heapify_to_right( _arr, _arr.size() - 1 );
    }
    void pop( ) {
        _arr.pop_back();
        max_heapify_to_right( _arr, _arr.size() - 1 );
    }

    bool empty( ) const { return _arr.empty(); };
    std::size_t size( ) const { return _arr.size(); };

  private:
    std::vector<value_type> _arr;
    Comparator _comp_less;
};

};  // alda

#endif  // PRIOQ_HPP
