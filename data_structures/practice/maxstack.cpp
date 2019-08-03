#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stack>

using namespace std;

template <typename T>
class MaxStack
{
    using istack = stack<T>;

    istack mainst { };
    istack maxst  { };

public:

    void push( const T& val ) 
    { 
        mainst.push( val );

        if( mainst.size() == 1 )
        {
            maxst.push( val );
            return;
        }

        if( val > maxst.top() )
            maxst.push( val );
        else
            maxst.push( maxst.top() );
    }

    void pop( ) 
    { 
        mainst.pop();
        maxst.pop();
    }

    T top( ) 
    { 
        return mainst.top(); 
    }

    T max_element( )
    {
        return maxst.top();
    }
};

using istack = MaxStack<int>;

int main() {
    int N, query, elem;

    cin >> N;
    istack st;

    while(N--)
    {
        cin >> query;
        if(query == 1)
        {
            cin >> elem;
            st.push(elem);
        }
        else if(query == 2)
        {
            st.pop();
        }
        else if(query == 3)
        {
            cout << st.max_element() << "\n";
        }
    }
    return 0;
}
