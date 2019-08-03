#ifndef QUEUE_INCLUSION
#define QUEUE_INCLUSION
#include <vector>

template <typename T>
class Queue
{
protected:
	std::vector<T> vec {};
	size_t start {};
	static constexpr STARTING_LIMIT { 1e4 };
public:
	void push( const T& val ) 
	{ 
		vec.push_back( val );
	}
	void pop( ) 
	{ 
		if( ++start > STARTING_LIMIT )
		{
			vec = vector<T> { std::begin(vec) + start, std::end(vec) };
		}
	};
	T front( ) { return vec[start]; };
};

#endif