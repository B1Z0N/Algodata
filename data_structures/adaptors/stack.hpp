#ifndef STACK_INCLUSION
#define STACK_INCLUSION
#include <vector>

template <typename T>
class Stack
{
protected:
	std::vector<T> vec {};
public:
	void push( const T& val ) { vec.push_back( val ); }
	void pop( ) { vec.pop_back(); };
	T top( ) { return vec.back(); };
};

#endif