class Solution {
public:
    int fib(int N) {
        std::map<int, int> cache{
            {0, 0}, {1, 1}, {2, 1}
        };
        return fib(N, cache);
    }
    int fib(int N, std::map<int, int>& cache) {
        auto search = cache.find(N);
        if (search != cache.end()) return search->second;
        else {
            int res = fib(N - 1, cache) + fib(N - 2, cache);
            cache[N] = res;
            return res;
        }
    }
};
