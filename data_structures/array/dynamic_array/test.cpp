#include "basic_vector.hpp"
#include <iostream>

using namespace forvec;

using uint = unsigned int;

template <typename T>
ostream &operator<<(ostream &os, const Numvec<T> &vec);
template <typename __first, typename __second>
bool pack_equal(__first first, __second second);
template <typename __first, typename __second, typename... __args>
bool pack_equal(__first first, __second second, __args... args);

Numvec<int> test_move();
Numvec<int> test_data(int *arr, int len);
template <typename T>
bool array_equality(T * a1, T * a2, uint len1, uint len2);

int main()
{
    //testing constructors and assignments
    using ntype = Numvec<int>;
    using cntype = const ntype;
    cntype a1{};
    cntype a2 = {};
    cntype a3{a1};
    cntype a4 = a1;
    cntype a5(0);

    std::cout << pack_equal(a1, a2, a3, a4, a5);

    cntype b1{1, 2, 3};
    cntype b2 = {1, 2, 3};
    cntype b3 = b2;

    std::cout << pack_equal(b1, b2, b3);

    cntype c1{0, 0};
    cntype c2(2);

    std::cout << pack_equal(c1, c2);

    cntype d1{test_move()};
    cntype d2 = test_move();

    std::cout << pack_equal(d1, d2);

    // size and capacity tests
    using init_int = std::initializer_list<int>;
    cntype e1{1, 2, 3, 4};
    std::cout << (e1.size() == 4) << (e1.capacity() == 4 * e1.size());

    int array[] = {1, 2, 3};
    int len = sizeof(array) / sizeof(int);
    cntype arr = test_data(array, len);
    std::cout << array_equality(array, arr.data(), len, arr.size());

    std::cout << a1.is_empty() << !e1.is_empty();

    // modify functionality
    ntype f1 {1, 2};
    ntype f2 {1, 2, 3};
    ntype f3 {1, 2, 3, 4, 5, 6};
    ntype f4 {1, 2, 3, 1, 2, 3, 4, 5, 6};

    f1.push_back(3);

    std::cout << (f1 == f2);

    f1.push_back(4);
    f1.push_back(5);
    f1.push_back(6);

    std::cout << (f1 == f3);

    f1.pop_back();
    f1.pop_back();
    f1.pop_back();

    std::cout << (f1 == f2);

    f2.plus_back(f3);

    std::cout << (f2 == f4);
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const Numvec<T> &vec)
// output for debugging
{
    if (vec.is_empty())
        return os << "[ ]";

    os << "[" << vec[0];
    if (vec.size() >= 1)
    {
        for (int i = 1; i < vec.size(); i++)
        {
            os << ", " << vec[i];
        }
    }
    return os << "]";
}

template <typename __first, typename __second>
bool pack_equal(__first first, __second second)
{
    return first == second;
}

template <typename __first, typename __second, typename... __args>
bool pack_equal(__first first, __second second, __args... args)
{
    return first == second && pack_equal(second, args...);
}

Numvec<int> test_move()
{
    return {1, 2, 3};
}
Numvec<int> test_data(int *arr, int len)
{
    return {arr, static_cast<Numvec<int>::size_type>(len)};
}

template <typename T>
bool array_equality(T * a1, T * a2, uint len1, uint len2)
{
    if (len1 != len2) return false;

    for(int i = 0; i < len1; i++)
    {
        if(a1[i] != a2[i]) return false;
    }
    return true;
}
