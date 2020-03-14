/*
 * Order statistics from CLRS book
 *
 * Time: O(n) (ammortized)
 * Space: O(1)
 *
 */

#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric> 

#define pb push_back

typedef std::vector<int> vi;
typedef vi::iterator vit;

int partition(int arr[], int l, int r) 
{ 
    int x = arr[r], i = l; 
    for (int j = l; j <= r - 1; j++) 
    { 
        if (arr[j] <= x) 
        { 
						std::swap(arr[i], arr[j]); 
            i++; 
        } 
    } 
    std::swap(arr[i], arr[r]); 
    return i; 
} 
  
int randomPartition(int arr[], int l, int r) 
{ 
    int n = r-l+1; 
    int pivot = rand() % n; 
		std::swap(arr[l + pivot], arr[r]); 
    return partition(arr, l, r); 
} 

// 4 1 34 79 245 287 78
// 3


int kthSmallest(int arr[], int l, int r, int k) 
{ 
    if (k > 0 && k <= r - l + 1) 
    { 
        int pos = randomPartition(arr, l, r); 
  
        if (pos-l == k-1) 
            return arr[pos]; 
        if (pos-l > k-1)  
            return kthSmallest(arr, l, pos-1, k); 
  
        return kthSmallest(arr, pos+1, r, k-pos+l-1); 
    } 
  
    return std::numeric_limits<int>::max(); 
} 

int order_statistic(vi& arr, int k) { return kthSmallest(arr.data(), 0,  arr.size() - 1, k); }

int main() {
	int n, k;
	vi arr;
	std::cin >> n;
	
	while (n--) {
		std::cin >> k;
		arr.pb(k);
	}
	
	std::cout << '\n';
	std::cin >> k;
	std::cout << "Answer: " << order_statistic(arr, k) << '\n';

	return 0;
}
