typedef std::string str;
typedef std::vector<str> vecs;

#define pb push_back

class Kata
{
public:
    vecs towerBuilder(int n)
    {
      vecs tower;
      for (int start = n - 1; start >= 0; --start) {
        str empty(start, ' ');
        tower.pb(empty + str((n - start) * 2 - 1, '*') + empty);
      }
      
      return tower;
    }
};
