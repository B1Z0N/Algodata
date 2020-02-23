typedef std::vector<int> vi;
typedef std::unordered_map<int, int> umii;

using namespace std;

vi deleteNth(vi arr, int n)
{
  umii counter;
  vi res;
  copy_if(arr.begin(), arr.end(), 
  back_inserter(res),
    [&](int el) { return ++counter[el] <= n; }
  );
    
   return res;
}

