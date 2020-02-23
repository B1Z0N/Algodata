typedef std::vector<int> vi;
typedef std::map<int, int> mii;

using namespace std;

vi deleteNth(vi arr, int n)
{
  mii counter;
  vi res;
  copy_if(arr.begin(), arr.end(), 
  back_inserter(res),
    [&](int el) { return ++counter[el] <= n; }
  );
    
   return res;
}

