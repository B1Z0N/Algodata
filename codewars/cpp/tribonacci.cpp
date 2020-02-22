#include <bits/stdc++.h>



typedef std::tuple<int, int, int> threenum;

void _tribonacci(std::vector<int>& sequence, threenum t, int n) {
	if (n == 0) return;
	auto [fst, snd, thrd] = t;
	auto next = fst + snd + thrd;
	sequence.push_back(next);
	_tribonacci(sequence, threenum{snd, thrd, next}, n - 1);
}	

std::vector<int> tribonacci(std::vector<int> signature, int n)
{
	if (std::accumulate(signature.begin(), signature.end(), 0) == 0) return {};

    std::vector<int> result {signature};
	_tribonacci(result, threenum{signature[0], signature[1], signature[2]}, n - 3); 
    return result;
}

int main() {
	int n;
	std::vector<int> signature;
	std::cout << "Enter signature: \n";
	for (int i = 0; i < 3; ++i) {
		std::cin >> n;
		signature.push_back(n);
	}
	std::cout << "Enter length of tribonacci sequence: \n";
	std::cin >> n;
	signature = tribonacci(signature, n);
	std::cout << "The result is: ";
	for (auto& x : signature) {
			std::cout << x << ' ';
	}
	std::cout << '\n';
}
