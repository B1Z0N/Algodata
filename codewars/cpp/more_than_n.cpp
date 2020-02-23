typedef std::vector<int> vi;
typedef std::map<int, int> mii;

using namespace std;

vi deleteNth(vi arr, int n)
{
  mii counter;
  vi res;
  copy_if(arr.begin(), arr.end(), back_inserter(res),
    [&](int el) {
      auto found = counter.find(el);
      if (found == counter.end()) counter[el] = 0;
      
      counter[el] += 1;
      return counter[el] <= n;
    });
    
   return res;
}
