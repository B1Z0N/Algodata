#include "container_printer.hpp"

#include <iostream>
#include <vector>

int main()
{
	// some usecases
	std::vector<int> _1 { 1, 2, 3 };
	std::vector<int> _2 { 5, 4, 0 };
	std::vector<int> _3 { 9, 1, 3 };

	std::vector<std::vector<int>> vec_of_vecs {_1, _2, _3};

	cmns::print_container(std::cout, _1);
	std::cout << '\n';
	cmns::print_container(std::cout, _2);
	std::cout << '\n';
	cmns::print_container(std::cout, _3);
	std::cout << '\n';

	cmns::print_container(std::cout, vec_of_vecs);
}